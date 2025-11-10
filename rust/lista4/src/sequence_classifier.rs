#[derive(Debug, PartialEq, Clone, Copy)]
pub enum Order {
    Unordered,
    Increasing,
    NotDecreasing,
    Decreasing,
    NotIncreasing,
    Constant,
}

fn sequence_classifier(arr: &[i32]) -> Order {
    match arr {
        _ if arr.iter().zip(&arr[1..]).all(|(a, b)| a == b) => Order::Constant,
        _ if arr.iter().zip(&arr[1..]).all(|(a, b)| a < b) => Order::Increasing,
        _ if arr.iter().zip(&arr[1..]).all(|(a, b)| a <= b) => Order::NotDecreasing,
        _ if arr.iter().zip(&arr[1..]).all(|(a, b)| a > b) => Order::Decreasing,
        _ if arr.iter().zip(&arr[1..]).all(|(a, b)| a >= b) => Order::NotIncreasing,
        _ => Order::Unordered,
    }
}

#[cfg(test)]
mod tests {
    use super::sequence_classifier;
    use super::Order::*;
    
    #[test]
    fn t1() {
        let (seq, ord) = (&[3,5,8,1,14,3], Unordered);
        assert_eq!(sequence_classifier(seq), ord);
    }

    #[test]
    fn t2() {
        let (seq, ord) = (&[3,5,8,9,14,23], Increasing);
        assert_eq!(sequence_classifier(seq), ord);
    }


    #[test]
    fn t3() {
        let (seq, ord) = (&[3,5,8,8,14,14], NotDecreasing);
        assert_eq!(sequence_classifier(seq), ord);
    }


    #[test]
    fn t4() {
        let (seq, ord) = (&[14,9,8,5,3,1], Decreasing);
        assert_eq!(sequence_classifier(seq), ord);
    }


    #[test]
    fn t5() {
        let (seq, ord) = (&[14,14,8,8,5,3], NotIncreasing);
        assert_eq!(sequence_classifier(seq), ord);
    }
}
