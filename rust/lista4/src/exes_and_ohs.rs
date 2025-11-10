fn xo(s: &str) -> bool {
    s.to_lowercase()
        .chars()
        .filter(|&c| c == 'x')
        .count() 

    == s.to_lowercase()
        .chars()
        .filter(|&c| c == 'o')
        .count()
}


#[cfg(test)]
mod tests {
    use super::xo;
    
    fn do_test(s: &str, expected: bool) {
        let actual = xo(s);
        assert!(expected == actual, "Test failed.\n\nInput:    {s:?}\nExpected: {expected}\nActual:   {actual}\n")
    }
    
    #[test]
    fn a() {
        do_test("xo", true);
    }

    #[test]
    fn b() {
        do_test("Xo", true);
    }


    #[test]
    fn c() {
        do_test("xxOo", true);
    }

    #[test]
    fn d() {
        do_test("xxxm", false);
    }


    #[test]
    fn e() {
        do_test("ooom", false);
    }
}
