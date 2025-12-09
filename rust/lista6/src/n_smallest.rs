fn first_n_smallest (arr: &[i32], n: usize) -> Vec<i32> {
    let mut vals: Vec<(usize, i32)> = arr.iter().cloned().enumerate()
        .collect();

    vals.sort_by(|a, b| {
        a.1.cmp(&b.1)
    });

    let mut n_fist: Vec<(usize, i32)> = vals.into_iter()
        .take(n)
        .collect();

    n_fist.sort();
    n_fist.into_iter()
        .map(|(_, val)| val)
        .collect()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_basic() {
        assert_eq!(first_n_smallest(&[1,2,3,4,5],3), [1,2,3]);
        assert_eq!(first_n_smallest(&[5,4,3,2,1],3), [3,2,1]);
        assert_eq!(first_n_smallest(&[1,2,3,1,2],3), [1,2,1]);
        assert_eq!(first_n_smallest(&[1,2,3,-4,0],3), [1,-4,0]);
        assert_eq!(first_n_smallest(&[1,2,3,4,5],0), []);
    }

    #[test]
    fn test0() {
        assert_eq!(first_n_smallest(&[2,1,2,3,4,2],4), [2,1,2,2]);
    }
    #[test]
    fn test1() {
        assert_eq!(first_n_smallest(&[2,1,2,3,4,2],3), [2,1,2]);
    }
    #[test]
    fn test2() {
        assert_eq!(first_n_smallest(&[2,1,2,3,4,2],2), [2,1]);
    }
    #[test]
    fn test3() {
        assert_eq!(first_n_smallest(&[1,2,3,4,2],4), [1,2,3,2]);
    }
    #[test]
    fn test4() {
        assert_eq!(first_n_smallest(&[1,2,3,4,5],5), [1,2,3,4,5]);
    }
}
