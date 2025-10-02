fn sum_two_smallest_numbers(numbers: &[u32]) -> u32 {
    let mut n = numbers.to_vec();
    n.sort();
    n
        .iter()
        .enumerate()
        .filter(|(i, _)| *i < 2)
        .map(|(_, &x)| x)
        .sum()
}

#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn sample_tests() {
        assert_eq!(sum_two_smallest_numbers(&[5, 8, 12, 19, 22]),  13, "Incorrect result for [5, 8, 12, 19, 22]");
    }

    #[test]
    fn sample_tests2() {
        assert_eq!(sum_two_smallest_numbers(&[15, 28, 4, 2, 43]), 6, "Incorrect result for [15, 28, 4, 2, 43]");
    }

    #[test]
    fn sample_tests3() {
        assert_eq!(sum_two_smallest_numbers(&[23, 71, 33, 82, 1]), 24, "Incorrect result for [23, 71, 33, 82, 1]");
    }

    #[test]
    fn sample_tests4() {
        assert_eq!(sum_two_smallest_numbers(&[52, 76, 14, 12, 4]), 16, "Incorrect result for [52, 76, 14, 12, 4]");
    }

    #[test]
    fn sample_tests5() {
        assert_eq!(sum_two_smallest_numbers(&[1, 1, 5, 5]),  2, "Incorrect result for [1, 1, 5, 5]");
    }
}
