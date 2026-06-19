use std::env;
use std::path::PathBuf;
use std::process::ExitCode;
use server::server::server::{Server, ServerConfig};

fn parse_args() -> Result<ServerConfig, String> {
	let args: Vec<String> = env::args().collect();
	if args.len() != 3 {
		return Err(format!("Error: you need to pass <port> <path>"));
	}

	let port = args[1]
		.parse::<u16>()
		.map_err(|_| format!("Error: invalid port {}", args[1]))?;

	let path = PathBuf::from(&args[2]);
	if !path.exists() {
		return Err(format!("Error: path does not exist"));
	}
	if !path.is_dir() {
		return Err(format!("Error: path is not a directory"));
	}

	Ok(ServerConfig { port, path })
}

fn main() -> ExitCode {
	let config = match parse_args() {
		Ok(c) => c,
		Err(e) => {
			println!("{}", e);
			return ExitCode::FAILURE;
		}
	};

	let server = Server::new(config);
    server.run();

	ExitCode::SUCCESS
}