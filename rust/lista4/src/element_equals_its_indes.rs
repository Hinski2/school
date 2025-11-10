fn index_equals_value(arr: &[i32]) -> i32 {
    arr.iter() 
        .enumerate()
        .position(|(a, &b)| a as i32 == b)
        .map(|i| i as i32)
        .unwrap_or(-1)
}

#[cfg(test)]
mod fixed_tests {
    use super::*;

    #[test]
    fn test_small() {
        let arr = vec![-3, 0, 1, 3, 10];
        let expected = 3;
        assert_eq!(index_equals_value(&arr), expected);
    }

    #[test]
    fn test_multiple() {
        let arr = vec![-5, 1, 2, 3, 4, 5, 7, 10, 15];
        let expected = 1;
        assert_eq!(index_equals_value(&arr), expected);
    }


    #[test]
    fn test() {
        let arr = vec![];
        let expected = -1;
        assert_eq!(index_equals_value(&arr), expected);
    }
}

#[cfg(test)]
mod edge_cases {
    use super::*;

    #[test]
    fn test_no_match() {
        let arr = vec![9, 10, 11, 12, 13, 14];
        let expected = -1;
        assert_eq!(index_equals_value(&arr), expected);
    }

    #[test]
    fn test_one_element() {
        let arr = vec![0];
        let expected = 0;
        assert_eq!(index_equals_value(&arr), expected);
    }
}
