pub fn gimme_the_letters(sp: &str) -> String {
    let chars: Vec<char> = sp.chars().collect();
    ((chars[0])..=(chars[2]))
        .collect()
}


#[cfg(test)]
mod tests {
    use super::gimme_the_letters;
        
    fn dotest(sp: &str, expected: &str) {
        let actual = gimme_the_letters(sp);
        assert!(actual == expected, 
            "With sp = \"{sp}\"\nExpected \"{expected}\" but got \"{actual}\"")
    }

    #[test]
    fn t1() {
        dotest("a-z", "abcdefghijklmnopqrstuvwxyz");
        dotest("h-o", "hijklmno");
        dotest("Q-Z", "QRSTUVWXYZ");
        dotest("J-J", "J");
        dotest("a-b", "ab");
        dotest("A-A", "A");
        dotest("g-i", "ghi");
        dotest("H-I", "HI");
    }

    #[test]
    fn t2() {
        dotest("F-O", "FGHIJKLMNO");
    }

    #[test]
    fn t3() {
        dotest("a-q", "abcdefghijklmnopq");
    }

    #[test]
    fn t4() {
        dotest("e-k", "efghijk");
    }

    #[test]
    fn t5() {
        dotest("y-z", "yz");
    }
}

