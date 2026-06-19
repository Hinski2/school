#[derive(Debug, Clone)]
pub struct Response {
	pub status_line: String,
	pub headers: Vec<(String, String)>,
	pub body: Vec<u8>,
}

impl Response {
	pub fn empty(status_line: &str) -> Self {
		Self {
			status_line: status_line.to_string(),
			headers: vec![],
			body: vec![],
		}
	}

	pub fn ok_html(body: &str, close_connection: bool) -> Self {
		Self::new("200 OK", body, close_connection)
	}

	pub fn bad_request(body: &str) -> Self {
		Self::new("400 Bad Request", body, true)
	}

	pub fn not_implemented(body: &str) -> Self {
		Self::new("501 Not Implemented", body, true)
	}

	pub fn add_header(&mut self, name: &str, value: &str) {
		self.headers.push((name.to_string(), value.to_string()));
	}

	pub fn to_bytes(&self) -> Vec<u8> {
		let mut output = Vec::new();
		output.extend_from_slice(format!("HTTP/1.1 {}\r\n", self.status_line).as_bytes());

		for (name, value) in &self.headers {
			output.extend_from_slice(format!("{}: {}\r\n", name, value).as_bytes());
		}

		output.extend_from_slice(b"\r\n");
		output.extend_from_slice(&self.body);
		output
	}

	pub fn new(status_line: &str, body: &str, close_connection: bool) -> Self {
		let mut response = Self::empty(status_line);
		let body_bytes = body.as_bytes().to_vec();

		response.add_header("Content-Type", "text/html; charset=utf-8");
		response.add_header("Connection", if close_connection { "close" } else { "keep-alive" });
		response.add_header("Content-Length", &body_bytes.len().to_string());
		response.body = body_bytes;

		response
	}
}