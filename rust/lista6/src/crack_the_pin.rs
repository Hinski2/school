use std::ptr::from_ref;

pub fn crack(hash: &str) -> String {
    for i in 0..=99999 {
        let s = format!("{:05}",i);
        let md5 = MD5::new(&s);

        if hash == md5.as_string() {
            return s;
        }
    }

    "42".to_string()
}

const S: [u32; 64] = [ 
    7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 
];

const K: [u32; 64] = [
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
];

struct MD5 {
    state: [u32; 4],
    bytes: [u8; 64],
}

impl MD5 {
    pub fn new(s: &str) -> MD5 {
        if s.len() > 55 {
            panic!("long msgs are not suppoerted")
        }

        let state = [0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476];
        let mut bytes = [0u8; 64];

        let s_bytes = s.as_bytes();
        let len = s_bytes.len();

        bytes[..len].copy_from_slice(s_bytes);
        bytes[len] = 0x80;
        bytes[56..64].copy_from_slice(&(len as u64 * 8).to_le_bytes());

        // compute hsh
        let mut md5 = MD5 {bytes, state};
        md5.compile();
        md5
    }

    fn compile(&mut self) {
        let original_state = self.state;

        for i in 0..64 {
            let (idx, fun) = match i {
                0..16 => (
                    i,
                    (|b: u32, c: u32, d: u32| (b & c) | (!b & d)) as fn(u32, u32, u32) -> u32
                ),
                16..32 => (
                    (5 * i + 1) % 16,
                    (|b: u32, c: u32, d: u32| (b & d) | (c & !d)) as fn(u32, u32, u32) -> u32
                ),
                32..48 => (
                    (3 * i + 5) % 16,
                    (|b: u32, c: u32, d: u32| b ^ c ^ d) as fn(u32, u32, u32) -> u32
                ),
                48..64 => (
                    (7 * i) % 16,
                    (|b: u32, c: u32, d: u32| c ^ (b | !d)) as fn(u32, u32, u32) -> u32
                ),
                _ => unreachable!(),
            };

            self.transform(i, idx, fun);
        }

        for i in 0..4 {
            self.state[i] = self.state[i].wrapping_add(original_state[i]);
        }
    }

    fn transform(&mut self, i: usize, idx: usize, fun: fn(u32, u32, u32) -> u32) {
        let [a, b, c, d] = self.state;
        let message_chunk = u32::from_le_bytes([
            self.bytes[idx * 4],
            self.bytes[idx * 4 + 1],
            self.bytes[idx * 4 + 2],
            self.bytes[idx * 4 + 3],
        ]);

        let combined = fun(b, c, d);
        let tmp = a 
            .wrapping_add(combined)
            .wrapping_add(message_chunk)
            .wrapping_add(K[i])
            .rotate_left(S[i]);

        self.state = [d, b.wrapping_add(tmp), b, c];
    }

    pub fn as_string(&self) -> String {
        let mut hsh = String::new();
        for state in self.state.iter() {
            let bytes = state.to_le_bytes();
            for b in bytes {
                hsh += &format!("{:02x}", b);
            }
        }

        hsh
    }
}


#[cfg(test)]
mod sample_tests {
    use super::crack;

    #[test]
    fn easy_pin() {
        assert_eq!(crack("827ccb0eea8a706c4c34a16891f84e7b"), "12345");
    }
    #[test]
    fn harder_pin() {
        assert_eq!(crack("86aa400b65433b608a9db30070ec60cd"), "00078");
    }
    #[test]
    fn test0() {
        assert_eq!(crack("dcddb75469b4b4875094e14561e573d8"), "00000");
    }
    #[test]
    fn test1() {
        assert_eq!(crack("d3eb9a9233e52948740d7eb8c3062d14"), "99999");
    }
    #[test]
    fn test2() {
        assert_eq!(crack("fa0fe7a225b3d30d0aa7d1958de81f6a"), "00042");
    }
}
