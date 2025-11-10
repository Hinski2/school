#[derive(Debug)]
enum Move {
    Left(i32),
    Right(i32),
    Forward(i32),
}

impl Move {
    fn get_move(code: &[char]) -> Move {
        let digits: String = code.iter()
            .skip(1)
            .take_while(|c| c.is_ascii_digit())
            .cloned()
            .collect();

        let distance = digits.parse::<i32>().unwrap_or(1);
        
        match code[0] {
            'L' => Move::Left(distance),
            'R' => Move::Right(distance),
            _ => Move::Forward(distance),
        }
    }

    fn convert_to_moves(code: &str) -> Vec<Move> {
        let chars: Vec<char> = code.chars().collect();
        let mut moves = Vec::new();

        for i in 0..chars.len(){
            match chars[i] {
                'L' | 'R' | 'F' => moves.push(Move::get_move(&chars[i..])),
                _ => (),
            } 
        }

        // dbg!(&moves);
        moves
    }
}
    
// right, down, left, up
fn get_size(moves: &Vec<Move>) -> (usize, usize, usize, usize) {
    let mut dir: i32 = 0;
    let mut pos: (i32, i32) = (0, 0);
    let (mut up, mut left, mut right, mut down) = (0, 0, 0, 0);

    for m in moves {
        match m {
            Move::Left(x) => dir = (dir + *x) % 4,
            Move::Right(x) => dir = ((dir - *x) % 4 + 4) % 4,
            Move::Forward(x) => {
                match dir {
                    0 => {pos.1 += x; right = right.max(pos.1)},
                    1 => {pos.0 += x; down = down.max(pos.0)},
                    2 => {pos.1 -= x; left = left.max(-pos.1)},
                    _ => {pos.0 -= x; up = up.max(-pos.0)},
                };
            },
        }
    }

    (up as usize, left as usize, right as usize, down as usize)
}

pub fn execute(code: &str) -> String {
    let moves = Move::convert_to_moves(code);
    let (up, left, right, down) = get_size(&moves);
    
    let mut board = vec![vec![' '; left + right + 1]; up + down + 1];
    let mut pos: (i32, i32) = (up as i32, left as i32);
    let mut dir: i32 = 0;
    board[pos.0 as usize][pos.1 as usize] = '*';

    for m in moves {
        match m {
            Move::Left(x) => dir = (dir + x) % 4,
            Move::Right(x) => dir = ((dir - x) % 4 + 4) % 4,
            Move::Forward(x) => {

                let vector: (i32, i32) = match dir {
                    0 => (0, 1),
                    1 => (1, 0),
                    2 => (0, -1),
                    _ => (-1, 0),
                };

                for _ in 0..x {
                    pos.0 += vector.0;
                    pos.1 += vector.1;

                    board[pos.0 as usize][pos.1 as usize] = '*';
                }
            },
        }
    } 

    board.iter()
        .rev()
        .map(|row| row.iter().collect::<String>())
        .collect::<Vec<String>>()
        .join("\r\n")
}

#[cfg(test)]
macro_rules! expect_equal {
  ($actual:expr, $expected:expr $(,)*) => {{
    let actual = $actual;
    let expected = $expected;
    assert_eq!(actual, expected, "\ngot:\n{}\n\nexpected:\n{}\n", actual, expected);
  }};
}

#[cfg(test)]
    mod tests {
    use super::execute;

    #[test]
    fn test1() {
        expect_equal!(
            execute("FFFFFLFFFFFLFFFFFLFFFFFL"),
            "******\r\n*    *\r\n*    *\r\n*    *\r\n*    *\r\n******",
        );
    }

    #[test]
    fn test2() {
        // println!("{}", execute(""));
        expect_equal!(
            execute("LFFFFFRFFFRFFFRFFFFFFF"),
            "    ****\r\n    *  *\r\n    *  *\r\n********\r\n    *   \r\n    *   ",
        );
    }

    #[test]
    fn test3() {
        expect_equal!(
            execute("LF5RF3RF3RF7"),
            "    ****\r\n    *  *\r\n    *  *\r\n********\r\n    *   \r\n    *   ",
        );
    }

    #[test]
    fn test4() {
        expect_equal!(execute(""), "*");
    }


    #[test]
    fn test5() {
        expect_equal!(execute("FFFFF"), "******");
    }
}
