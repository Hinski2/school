use std::io::{ErrorKind, Read, Write};
use std::net::{TcpListener, TcpStream};
use std::path::PathBuf;
use std::time::Duration;

use super::client::Client;
use super::request::{Request, RequestParseError};
use super::response::Response;

enum ReadStep {
	Data(usize),
	Continue,
	End,
}

pub struct ServerConfig {
	pub port: u16,
	pub path: PathBuf,
}

pub struct Server {
	config: ServerConfig,
}

impl Server {
	pub fn new(config: ServerConfig) -> Self {
		Self { config }
	}

	pub fn run(&self) {
		let listener = match self.bind_listener() {
			Ok(listener) => listener,
			Err(e) => {
				println!("Error: {}", e);
				return;
			}
		};

		for incoming in listener.incoming() {
			match incoming {
				Ok(stream) => {
					if let Err(e) = self.handle_client(stream) {
						println!("{}", e);
					}
				}
				Err(e) => println!("Error: {}", e),
			}
		}
	}

	pub fn bind_listener(&self) -> Result<TcpListener, String> {
		let bind_address = format!("0.0.0.0:{}", self.config.port);
		TcpListener::bind(&bind_address).map_err(|e| format!("Error: {}", e))
	}

	fn configure_client_stream(stream: &TcpStream) -> Result<(), String> {
		stream
			.set_read_timeout(Some(Duration::from_millis(500)))
			.map_err(|e| format!("Error setting timeout: {}", e))
	}

	fn read_step(
		stream: &mut TcpStream,
		temp_buf: &mut [u8; 4096],
		client: &Client,
	) -> Result<ReadStep, String> {
		match stream.read(temp_buf) {
			Ok(0) => Ok(ReadStep::End),
			Ok(n) => Ok(ReadStep::Data(n)),
			Err(e) if e.kind() == ErrorKind::WouldBlock || e.kind() == ErrorKind::TimedOut => {
				if client.buffer.is_empty() {
					Ok(ReadStep::End)
				} else {
					Ok(ReadStep::Continue)
				}
			}
			Err(e) => Err(format!("Error reading from stream: {}", e)),
		}
	}

	fn response_for_parse_error(parse_error: RequestParseError) -> Response {
		match parse_error {
			RequestParseError::UnsupportedMethod(method) => {
				Response::not_implemented(&format!("Method {} not supported", method))
			}
			_ => Response::bad_request("Invalid HTTP request"),
		}
	}

	fn response_for_request(raw_request: String, client: &mut Client) -> (Response, bool) {
		match Request::try_parse_request(&raw_request) {
			Ok(_request) => {
				let close = client.should_close;
				client.mark_request_served();
				(Response::ok_html("Hello, World!", close), !close)
			}
			Err(parse_error) => (Self::response_for_parse_error(parse_error), false),
		}
	}

	fn write_response(stream: &mut TcpStream, response: &Response) -> Result<(), String> {
		stream
			.write_all(&response.to_bytes())
			.map_err(|e| format!("Error writing response: {}", e))
	}

	fn process_pending_requests(client: &mut Client, stream: &mut TcpStream) -> Result<bool, String> {
		while let Some(raw_request) = client.try_take_request() {
			let (response, should_continue) = Self::response_for_request(raw_request, client);
			Self::write_response(stream, &response)?;

			if !should_continue {
				return Ok(false);
			}
		}

		Ok(true)
	}

	pub fn handle_client(&self, mut stream: TcpStream) -> Result<(), String> {
		Self::configure_client_stream(&stream)?;
		let mut client = Client::new();
		let mut temp_buf = [0u8; 4096];

		loop {
			match Self::read_step(&mut stream, &mut temp_buf, &client)? {
				ReadStep::Data(n) => {
					client.push_bytes(&temp_buf[..n]);
					if !Self::process_pending_requests(&mut client, &mut stream)? {
						break;
					}
				}
				ReadStep::Continue => continue,
				ReadStep::End => break,
			}
		}

		Ok(())
	}
}