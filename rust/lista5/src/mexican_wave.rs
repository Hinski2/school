fn wave(s: &str) -> Vec<String> {
    let chars: Vec<char> = s.chars().collect();

    (0..chars.len())
        .filter(|&i| chars[i] != ' ')
        .map(|i| {
            chars.iter().enumerate()
                .map(|(idx, &char)| {
                    if idx == i {
                        char.to_ascii_uppercase()
                    } else {
                        char
                    }
                })
            .collect()
        })
    .collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t0() {
        let expect = ["Hello", "hEllo", "heLlo", "helLo", "hellO"];
        assert_eq!(wave("hello"), expect);
    }

    #[test]
    fn t1() {
        let expect = ["Codewars", "cOdewars", "coDewars", "codEwars", "codeWars", "codewArs", "codewaRs", "codewarS"];
        assert_eq!(wave("codewars"), expect);
    }

    #[test]
    fn t2() {
        let expect: [&str; 0] = [];
        assert_eq!(wave(""), expect);
    }

    #[test]
    fn t3() {
        let expect = ["Two words", "tWo words", "twO words", "two Words", "two wOrds", "two woRds", "two worDs", "two wordS"];
        assert_eq!(wave("two words"), expect);
    }

    #[test]
    fn t4() {
        let expect = [" Gap ", " gAp ", " gaP "];
        assert_eq!(wave(" gap "), expect);
    }
}

