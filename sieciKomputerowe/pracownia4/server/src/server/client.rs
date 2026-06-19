#[derive(Debug)]
pub struct Client {
	pub buffer: Vec<u8>,
	pub requests_served: usize,
	pub should_close: bool,
}

impl Client {
	pub fn new() -> Self {
		Self {
			buffer: Vec::new(),
			requests_served: 0,
			should_close: false,
		}
	}

	pub fn push_bytes(&mut self, bytes: &[u8]) {
		self.buffer.extend_from_slice(bytes);
	}

	pub fn mark_request_served(&mut self) {
		self.requests_served += 1;
	}

	pub fn try_take_request(&mut self) -> Option<String> {
		let end_str = b"\r\n\r\n";
		let end_pos = match self
			.buffer
			.windows(end_str.len())
			.position(|window| window == end_str) {
			Some(pos) => pos + end_str.len(),
			None => return None,
		};

		let request_bytes = self.buffer[..end_pos].to_vec();
		self.buffer = self.buffer[end_pos..].to_vec();

		Some(String::from_utf8_lossy(&request_bytes).into_owned())
	}
}