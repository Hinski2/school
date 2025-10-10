pub fn is_vowel(chr: &char) -> bool {
    match chr {
        'a' | 'e' | 'i' | 'o' | 'u' => true,
        _ => false
    }
}

pub fn get_count(string: &str) -> usize {
    string
        .chars()
        .filter(|c| is_vowel(c))
        .count()
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(get_count("abracadabra"), 5);
    }

    #[test]
    fn t2() {
        assert_eq!(get_count("y"), 0);
    }

    #[test]
    fn t3() {
        assert_eq!(get_count("ya"), 1);
    }

    #[test]
    fn t4() {
        assert_eq!(get_count("aeiou"), 5);
    }

    #[test]
    fn t5() {
        assert_eq!(get_count("bbb"), 0);
    }
}

