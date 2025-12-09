fn part_list(arr: Vec<&str>) -> String {
    (1..arr.len())
        .map(|i| format!("({}, {})", arr[..i].join(" "), arr[i..].join(" ")))
        .collect()
}

#[cfg(test)]
    mod tests {
    use super::*;

    fn dotest(arr: Vec<&str>, exp: &str) -> () {
        println!("arr: {:?}", arr);
        let ans = part_list(arr);
        println!("actual:\n{}", ans);
        println!("expect:\n{}", exp);
        println!("{}", ans == exp);
        assert_eq!(ans, exp);
        println!("{}", "-");
    }

    #[test]
    fn basis_tests() {
        dotest(vec!["I", "wish", "I", "hadn't", "come"],
                "(I, wish I hadn't come)(I wish, I hadn't come)(I wish I, hadn't come)(I wish I hadn't, come)");
    }

    #[test]
    fn test0() {
        dotest(vec!["cdIw", "tzIy", "xDu", "rThG"], 
            "(cdIw, tzIy xDu rThG)(cdIw tzIy, xDu rThG)(cdIw tzIy xDu, rThG)");
    }

    #[test]
    fn test1() {
        dotest(vec!["a", "a"], 
            "(a, a)");
    }

    #[test]
    fn test2() {
        dotest(vec!["a", "a", "a"], 
            "(a, a a)(a a, a)");
    }

    #[test]
    fn test3() {
        dotest(vec!["a", "a", "b"], 
            "(a, a b)(a a, b)");
    }
}
