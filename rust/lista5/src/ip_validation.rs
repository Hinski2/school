pub fn is_valid_ip(ip: &str) -> bool {

    ip.split('.').collect::<Vec<&str>>().len() == 4 && ip.split('.')
        .all(|s| {
            if s.len() > 1 && s.chars().next().unwrap() == '0' {
                return false
            } 
            s.parse::<u8>().is_ok()
        })
}

#[cfg(test)]
mod tests {
    use super::is_valid_ip;

    #[test]
    fn t0_valid() {
        assert!(is_valid_ip("12.255.56.1"));
    }

    #[test]
    fn t1_invalid_letters() {
        assert!(!is_valid_ip("abc.def.ghi.jkl"));
    }

    #[test]
    fn t2_invalid_range() {
        assert!(!is_valid_ip("256.1.2.3"));
    }

    #[test]
    fn t3_invalid_parts_count() {
        assert!(!is_valid_ip("1.2.3.4.5"));
    }

    #[test]
    fn t4_invalid_leading_zero() {
        assert!(!is_valid_ip("01.02.03.04"));
    }
}

