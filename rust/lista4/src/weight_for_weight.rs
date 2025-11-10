fn order_weight(s: &str) -> String {
    let mut xs: Vec<&str> = s.split(' ').collect();
    xs.sort_by(|a, b| {
        let a_numb = a.chars().fold(0, |acc, x| acc + x.to_digit(10).unwrap());         
        let b_numb = b.chars().fold(0, |acc, x| acc + x.to_digit(10).unwrap());         
        
        if a_numb != b_numb {
            a_numb.cmp(&b_numb)
        } else {
            a.cmp(b)
        }
    });

    xs.join(" ")
}


#[cfg(test)]
mod fixed_tests {
    use super::*;

    #[test]
    fn t1() {
        assert_eq!(order_weight("1 2 3"), "1 2 3")
    }

    #[test]
    fn t2() {
        assert_eq!(order_weight("22 11"), "11 22")
    }

    #[test]
    fn t3() {
        assert_eq!(order_weight("99 100"), "100 99")
    }


    #[test]
    fn t4() {
        assert_eq!(order_weight("99 100 1"), "1 100 99")
    }

    #[test]
    fn t5() {
        assert_eq!(order_weight("200 20 2"), "2 20 200")
    }
}

