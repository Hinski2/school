use std::collections::HashSet;

pub fn longest(a1: &str, a2: &str) -> String {
    let mut s: String = a1.to_string();
    s.push_str(a2);

    let h: HashSet<char> = s
        .chars()
        .collect();

    let mut v1: Vec<char> = h.into_iter().collect();
    v1.sort();
    v1.into_iter().collect()
}

#[cfg(test)]
    mod tests {
    use super::*;
   
    fn testing(s1: &str, s2: &str, exp: &str) -> () {
        println!("s1:{:?} s2:{:?}", s1, s2);
        println!("{:?} {:?}", longest(s1, s2), exp);
        println!("{}", longest(s1, s2) == exp);
        assert_eq!(&longest(s1, s2), exp)
    }

    #[test]
    fn t1() {
        testing("aretheyhere", "yestheyarehere", "aehrsty");
        
    }

    #[test]
    fn t2() {
        testing("loopingisfunbutdangerous", "lessdangerousthancoding", "abcdefghilnoprstu");
        
    }

    #[test]
    fn t3() {
        testing("ab", "abc", "abc");
        
    }

    #[test]
    fn t4() {
        testing("a", "b", "ab");
    }

    #[test]
    fn t5() {
        testing("ab", "b", "ab");
        
    }
}
