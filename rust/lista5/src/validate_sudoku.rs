pub struct Sudoku{
    pub data: Vec<Vec<u32>>,
}


impl Sudoku{
    pub fn is_valid(&self) -> bool {
        let n = self.data.len();
        let n_sqrt= (n as f64).sqrt() as usize;

        if !self.data.iter()
            .all(|line| line.len() == n) {
                return false
        }
   
        // rows
        if !self.data.iter()
            .all(|line| {
                Sudoku::is_valid_list(&line, n)
            }) {
            return false;
        }
       
        // cols
        for j in 0..n {
            let mut vals = Vec::new();
            for i in 0..n {
                vals.push(self.data[i][j]);
            }

            if !Sudoku::is_valid_list(&vals, n) {
                return false
            }
        }

        // blocks
        for block_i in 0..n_sqrt {
            for block_j in 0..n_sqrt {

                let mut vals = Vec::new();
                for i in 0..n_sqrt {
                    for j in 0..n_sqrt {
                        vals.push(self.data[n_sqrt * block_i + i][n_sqrt * block_j + j]);
                    }
                }

                if !Sudoku::is_valid_list(&vals, n) {
                    return false
                }
            }
        }
        
        true
    }

    pub fn is_valid_list(vals: &Vec<u32>, n: usize) -> bool {
        let mut occ = vec![false; n + 1];
        occ[0] = true;
        
        for val in vals {
            if *val > n as u32 || *val <= 0 {return false}
            occ[*val as usize] = true;
        }

        occ.iter()
            .all(|v| *v)
    }
}


#[cfg(test)]
mod tests {
    use super::Sudoku;

    #[test]
    fn t0() {
        let good_sudoku_1 = Sudoku {
            data: vec![
                vec![7,8,4, 1,5,9, 3,2,6],
                vec![5,3,9, 6,7,2, 8,4,1],
                vec![6,1,2, 4,3,8, 7,5,9],
                vec![9,2,8, 7,1,5, 4,6,3],
                vec![3,5,7, 8,4,6, 1,9,2],
                vec![4,6,1, 9,2,3, 5,8,7],
                vec![8,7,6, 3,9,4, 2,1,5],
                vec![2,4,3, 5,6,1, 9,7,8],
                vec![1,9,5, 2,8,7, 6,3,4],
            ],
        };
        assert!(good_sudoku_1.is_valid());
    }

    #[test]
    fn t1() {
        let good_sudoku_2 = Sudoku {
            data: vec![
                vec![1, 4, 2, 3],
                vec![3, 2, 4, 1],
                vec![4, 1, 3, 2],
                vec![2, 3, 1, 4],
            ],
        };
        assert!(good_sudoku_2.is_valid());
    }

    #[test]
    fn t2() {
        let bad_sudoku_1 = Sudoku {
            data: vec![
                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],
                vec![1,2,3, 4,5,6, 7,8,9],
            ],
        };
        assert!(!bad_sudoku_1.is_valid());
    }

    #[test]
    fn t3() {
        let bad_sudoku_2 = Sudoku {
            data: vec![
                vec![1,2,3,4,5],
                vec![1,2,3,4],
                vec![1,2,3,4],
                vec![1],
            ],
        };
        assert!(!bad_sudoku_2.is_valid());
    }

    #[test]
    fn t4() {
        let bad_sudoku_3 = Sudoku {
            data: vec![
                vec![0,8,4, 1,5,9, 3,2,6],
                vec![5,3,9, 6,7,2, 8,4,1],
                vec![6,1,2, 4,3,8, 7,5,9],
                vec![9,2,8, 7,1,5, 4,6,3],
                vec![3,5,7, 8,4,6, 1,9,2],
                vec![4,6,1, 9,2,3, 5,8,7],
                vec![8,7,6, 3,9,4, 2,1,5],
                vec![2,4,3, 5,6,1, 9,7,8],
                vec![1,9,5, 2,8,7, 6,3,10],
            ],
        };
        assert!(!bad_sudoku_3.is_valid());
    }
}
