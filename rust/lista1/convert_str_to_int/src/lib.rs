fn string_to_number(s: &str) -> i32 {
    s.parse().unwrap()
}

#[cfg(test)]
mod tests {
    use super::string_to_number;

    #[test]
    fn returns_expected() {
      assert_eq!(string_to_number("1234"), 1234);
    }

    #[test]
    fn returns_expected2() {
        assert_eq!(string_to_number("605"), 605);
    }

    #[test]
    fn returns_expected3() {
        assert_eq!(string_to_number("1405"), 1405);
    }

    #[test]
    fn returns_expected4() {
        assert_eq!(string_to_number("-7"), -7);
    }

    #[test]
    fn returns_expected5() {
        assert_eq!(string_to_number("-7777"), -7777);
    }

}
