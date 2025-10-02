use std::fmt::format;

fn printer_error(s: &str) -> String {
    format!("{}/{}", s.chars().filter(|&c| c > 'm').count(), s.len())
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn should_pass_all_the_tests_provided() {
        assert_eq!(&printer_error("aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "3/56");
    }

    #[test]
    fn should_pass_all_the_tests_provided2() {
        assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "6/60");
    }

    #[test]
    fn should_pass_all_the_tests_provided3() {
        assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyzuuuuu"), "11/65");
    }
    #[test]
    fn should_pass_all_the_tests_provided4() {
        assert_eq!(&printer_error("aa"), "0/2");
    }
    #[test]
    fn should_pass_all_the_tests_provided5() {
        assert_eq!(&printer_error("nn"), "2/2");
    }
}