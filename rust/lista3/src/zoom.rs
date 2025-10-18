use std::cmp::max;

fn zoom_help(n: usize) -> Vec<Vec<char>> {
    let mut grid = vec![vec!['■'; n]; n];

    for (i , row) in grid.iter_mut().enumerate() {
        for (j, item) in row.iter_mut().enumerate(){
            if max(i32::abs(n as i32 / 2 - i as i32), i32::abs(n as i32 / 2 - j as i32)) % 2 == 1 {
                *item = '□';
            }
        }
    }

    grid
}

pub fn zoom(n: i32) -> String {
    zoom_help(n as usize).into_iter().enumerate() 
        .map(|(i, row)| {
            let mut s: String = row.iter().collect();
            if i + 1 != n as usize {
                s.push('\n');
            }

            s
        })
        .collect()
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn basic_test_1() {
      assert_eq!(zoom(1), "■");
    }

    #[test]
    fn basic_test_2() {
      assert_eq!(zoom(3), "\
□□□
□■□
□□□"
      );
    }

    #[test]
    fn basic_test_3() {
      assert_eq!(zoom(5), "\
■■■■■
■□□□■
■□■□■
■□□□■
■■■■■"
      );
    }

    #[test]
    fn basic_test_4() {
      assert_eq!(zoom(7), "\
□□□□□□□
□■■■■■□
□■□□□■□
□■□■□■□
□■□□□■□
□■■■■■□
□□□□□□□"
      );
    }

    #[test]
    fn basic_test_5() {
      assert_eq!(zoom(9), "\
■■■■■■■■■
■□□□□□□□■
■□■■■■■□■
■□■□□□■□■
■□■□■□■□■
■□■□□□■□■
■□■■■■■□■
■□□□□□□□■
■■■■■■■■■"
      );
    }
}
