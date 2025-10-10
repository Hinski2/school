pub fn summy(strng: &str) -> i32 {
    strng 
        .split(" ")
        .map(|s| s.parse::<i32>().unwrap())
        .sum()
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn sample_tests() {
        assert_eq!(summy("1 2 3"), 6);
    }

    #[test]
    fn t2() {
        assert_eq!(summy("1 2 3 4"), 10);
    }

    #[test]
    fn t3() {
        assert_eq!(summy("1 2 3 4 5"), 15);
    }

    #[test]
    fn t4() {
        assert_eq!(summy("10 10"), 20);
    }

    #[test]
    fn t5() {
        assert_eq!(summy("0 0"), 0);
    }
}
