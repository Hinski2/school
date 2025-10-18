type Clues = Vec<Vec<u8>>;

pub fn encode(sol: &[&[u8]]) -> (Clues, Clues) {
    let mut rows: Clues = Vec::new();
    let mut cols: Clues = Vec::new();
    
    for i in 0..sol.len() {
        let mut counter = 0;
        rows.push(Vec::new());

        for j in 0..sol[0].len() {
            match sol[i][j] {
                0 if counter > 0 => {
                    rows[i].push(counter);
                    counter = 0;
                },
                1 => counter += 1,
                _ => {},
            }             
        }

        if counter > 0 {
            rows[i].push(counter);
        }
    }


    for j in 0..sol[0].len() {
        let mut counter = 0;
        cols.push(Vec::new());

        for i in 0..sol.len() {
            match sol[i][j] {
                0 if counter > 0 => {
                    cols[j].push(counter);
                    counter = 0;
                },
                1 => counter += 1,
                _ => {},
            }             
        }

        if counter > 0 {
            cols[j].push(counter);
        }
    }

    (cols, rows)
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn _0_should_encode_my_nonogram() {
        let my_nonogram: &[&[u8]] = &[
            &[0, 0, 0, 1, 0, 0, 0, 1, 1, 0],
            &[0, 0, 1, 1, 1, 0, 1, 1, 1, 1],
            &[0, 0, 1, 1, 1, 1, 1, 1, 1, 1],
            &[0, 0, 0, 1, 1, 1, 1, 1, 1, 0],
            &[0, 0, 0, 0, 0, 1, 1, 0, 0, 0],
            &[0, 1, 0, 0, 0, 0, 1, 1, 0, 0],
            &[1, 0, 1, 0, 0, 0, 1, 1, 0, 0],
            &[1, 1, 1, 0, 0, 1, 1, 0, 0, 0],
            &[1, 1, 1, 0, 0, 1, 1, 1, 0, 1],
            &[1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        ];

        let clues_for_my_nonogram: (Clues, Clues) = (
            vec![
                vec![4],
                vec![1, 3],
                vec![2, 4],
                vec![4, 1],
                vec![3, 1],
                vec![3, 3],
                vec![9],
                vec![4, 2, 2],
                vec![4, 1],
                vec![2, 2],
            ],
            vec![
                vec![1, 2],
                vec![3, 4],
                vec![8],
                vec![6],
                vec![2],
                vec![1, 2],
                vec![1, 1, 2],
                vec![3, 2],
                vec![3, 3, 1],
                vec![10],
            ],
        );

        assert_eq!(
            encode(my_nonogram),
            clues_for_my_nonogram,
            "your solution (left) did not match the expected clues (right)"
        );
    }

    #[test]
    fn _1_should_encode_another_small_nonogram() {
        let small_nonogram: &[&[u8]] = &[
            &[0, 1, 0, 1, 0],
            &[1, 1, 1, 1, 1],
            &[1, 1, 1, 1, 1],
            &[0, 1, 1, 1, 0],
            &[0, 0, 1, 0, 0],
        ];

        let clues_for_small_nonogram: (Clues, Clues) = (
            vec![vec![2], vec![4], vec![4], vec![4], vec![2]],
            vec![vec![1, 1], vec![5], vec![5], vec![3], vec![1]],
        );

        assert_eq!(
            encode(small_nonogram),
            clues_for_small_nonogram,
            "your solution (left) did not match the expected clues (right)"
        );
    }

    #[test]
    fn _2_should_handle_empty_rows() {
        let nono1: &[&[u8]] = &[
            &[0, 0, 0, 0, 0],
            &[1, 1, 1, 1, 1],
            &[1, 1, 1, 1, 1],
            &[0, 1, 1, 1, 0],
            &[0, 0, 1, 0, 0],
        ];

        let clues_for_nono1: (Clues, Clues) = (
            vec![vec![2], vec![3], vec![4], vec![3], vec![2]],
            vec![vec![], vec![5], vec![5], vec![3], vec![1]],
        );

        assert_eq!(
            encode(nono1),
            clues_for_nono1,
            "your solution (left) did not match the expected clues (right)"
        );
    }

    #[test]
    fn _3_should_handle_empty_rows_and_columns() {
        let nono2: &[&[u8]] = &[
            &[0, 1, 0, 1, 0],
            &[1, 1, 0, 1, 1],
            &[1, 1, 0, 1, 1],
            &[0, 1, 0, 1, 0],
            &[0, 0, 0, 0, 0],
        ];

        let clues_for_nono2: (Clues, Clues) = (
            vec![vec![2], vec![4], vec![], vec![4], vec![2]],
            vec![vec![1, 1], vec![2, 2], vec![2, 2], vec![1, 1], vec![]],
        );

        assert_eq!(
            encode(nono2),
            clues_for_nono2,
            "your solution (left) did not match the expected clues (right)"
        );
    }

    #[test]
    fn test4() {
        let nano: &[&[u8]] = &[
            &[1]
        ];
    
        let clues: (Clues, Clues) = (
            vec![vec![1]],
            vec![vec![1]],
        );

        assert_eq!(
            encode(nano),
            clues, 
            "your solution (left) did not match the expected clues (right)"
        )
    }
}
