
fn largest_difference(data: &[i32]) -> usize {
    let mut stack: Vec<(usize, i32)> = Vec::new();

    data.iter().enumerate()
        .map(|(idx, &val)| {
            let pos = bs(&stack, val);

            if stack.is_empty() || val < stack.last().unwrap().1 {
                stack.push((idx, val));
            }
            
            if let Some(p) = pos {
                return idx - p;
            } else {
                return 0
            }
        })
    .max()
    .unwrap_or(0)
}

fn bs(vals: &Vec<(usize, i32)>, val: i32) -> Option<usize> {
    if vals.is_empty() {
        return None;
    }
    
    let (mut l, mut r) = (0, vals.len() - 1);

    while l < r {
        let mid = (l + r) / 2;
        if vals[mid].1 <= val {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    if vals[l].1 <= val {
        return Some(vals[l].0);
    } else {
        return None;
    }
}

#[cfg(test)]
mod tests {
    use super::largest_difference;

    const ERR_MSG: &str = "\nYour result (left) did not match the expected output (right)";
    
    fn dotest(data: &[i32], expected: usize) {
        assert_eq!(largest_difference(data), expected, "{ERR_MSG} with data = {data:?}")
    }

    #[test]
    fn t0() {
        dotest(&[9, 4, 1, 10, 3, 4, 0, -1, -2], 4);
    }

    #[test]
    fn t1() {
        dotest(&[3, 2, 1], 0);
    }

    #[test]
    fn t2() {
        dotest(&[1, 2, 3], 2);
    }

    #[test]
    fn t3() {
        dotest(&[78, 88, 64, 94, 17, 91, 57, 69, 38, 62, 13, 17, 35, 15, 20], 10);
    }

    #[test]
    fn t4() {
        dotest(&[4, 3, 3, 1, 5, 2], 4);
    }
}
