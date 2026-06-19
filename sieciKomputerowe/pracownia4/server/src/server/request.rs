#[derive(Debug, Clone)]
pub struct Request {
	pub method: String,
	pub target: String,
	pub version: String,
	pub host: String,
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum RequestParseError {
	EmptyRequest,
	InvalidRequestLine,
	MissingHostHeader,
	EmptyHostHeader,
	UnsupportedMethod(String),
}

impl Request {
	pub fn new(method: String, target: String, version: String, host: String) -> Self {
		Self {
			method,
			target,
			version,
			host,
		}
	}

	pub fn is_get(&self) -> bool {
		self.method == "GET"
	}

	pub fn host_without_port(&self) -> &str {
		self.host.split(':').next().unwrap_or("")
	}

	pub fn try_parse_request(raw: &str) -> Result<Self, RequestParseError> {
		if raw.trim().is_empty() {
			return Err(RequestParseError::EmptyRequest);
		}

		let mut lines = raw.split("\r\n");
		let request_line = lines.next().ok_or(RequestParseError::InvalidRequestLine)?;

		let mut parts = request_line.split_whitespace();
		let method = parts
			.next()
			.ok_or(RequestParseError::InvalidRequestLine)?
			.to_string();
		let target = parts
			.next()
			.ok_or(RequestParseError::InvalidRequestLine)?
			.to_string();
		let version = parts
			.next()
			.ok_or(RequestParseError::InvalidRequestLine)?
			.to_string();

		if parts.next().is_some() {
			return Err(RequestParseError::InvalidRequestLine);
		}

		if method != "GET" {
			return Err(RequestParseError::UnsupportedMethod(method));
		}

		let mut host: Option<String> = None;
		for line in lines {
			if line.is_empty() {
				break;
			}

			if let Some((name, value)) = line.split_once(':') {
				if name.trim() == "Host" {
					let host_value = value.trim();
					if host_value.is_empty() {
						return Err(RequestParseError::EmptyHostHeader);
					}
					host = Some(host_value.to_string());
					break;
				}
			}
		}

		let host = host.ok_or(RequestParseError::MissingHostHeader)?;

		Ok(Self {
			method,
			target,
			version,
			host,
		})
	}
}