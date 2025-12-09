fn interpreter(code: &str, iterations: usize, width: usize, height: usize) -> String {
    let mut interpreter = Interpreter::new(code, iterations, width, height);
    interpreter.interpret()
}

struct Interpreter {
    grid: Vec<Vec<u8>>,
    grid_pos: (usize, usize),
    code: Vec<char>,
    code_pos: usize,
    open_brackets: Vec<usize>,
    itr_left: usize,

    x: usize, 
    y: usize,
}

impl Interpreter {
    pub fn new(code: &str, iterations: usize, width: usize, height: usize) -> Interpreter {
        let x = height;
        let y = width;
        let grid = vec![vec![0u8; width]; height];
        let grid_pos = (0, 0);
        let code = code.chars().collect();
        let code_pos = 0;
        let open_brackets = Vec::new();
        let itr_left = iterations;

        Interpreter { grid, grid_pos, code, code_pos, open_brackets, itr_left, x, y }
    }

    pub fn interpret(&mut self) -> String {
        while self.code_pos < self.code.len() && self.itr_left != 0 {
            match self.code[self.code_pos] {
                '*' => self.grid[self.grid_pos.0][self.grid_pos.1] ^= 1,
                's' => self.go_s(),
                'w' => self.go_w(),
                'e' => self.go_e(),
                'n' => self.go_n(),
                '[' => self.start_loop(),
                ']' => self.end_loop(),
                _ => self.itr_left += 1,
            }
            
            self.itr_left -= 1;
            self.code_pos += 1;
        } 
    
        self.grid.iter()
            .map(|vec|  {
                vec.iter() 
                    .map(|e| e.to_string())
                    .collect::<String>()
            })
            .collect::<Vec<String>>()
            .join("\r\n")
    }

    fn start_loop(&mut self) {
        if self.grid[self.grid_pos.0][self.grid_pos.1] == 0 {
            let mut to_skipp = 0;
            
            loop { // like do while loop
                if self.code_pos >= self.code.len() {
                    break;
                }

                match self.code[self.code_pos] {
                    ']' => to_skipp -= 1,
                    '[' => to_skipp += 1, 
                    _ => (),
                }

                self.code_pos += 1;

                if to_skipp == 0 {
                    break;
                }
            }

            self.code_pos -= 1; // because we skipped ] and in main loop we also make code_pos + 1
        } else {
            self.open_brackets.push(self.code_pos);
        }
    }

    fn end_loop(&mut self) {
        if self.grid[self.grid_pos.0][self.grid_pos.1] == 1 {

            match self.open_brackets.last() {
                Some(pos) => self.code_pos = *pos,
                None => (),
            }
        } else {
            self.open_brackets.pop();
        }
    }

    fn go_s(&mut self) {
        if self.grid_pos.0 == self.x - 1 {
            self.grid_pos.0 = 0;
        } else {
            self.grid_pos.0 += 1;
        }
    }

    fn go_n(&mut self) {
        if self.grid_pos.0 == 0 {
            self.grid_pos.0 = self.x - 1;
        } else {
            self.grid_pos.0 -= 1;
        }
    }

    fn go_w(&mut self) {
        if self.grid_pos.1 == 0 {
            self.grid_pos.1 = self.y - 1;
        } else {
            self.grid_pos.1 -= 1;
        }
    }

    fn go_e(&mut self) {
        if self.grid_pos.1 == self.y - 1 {
            self.grid_pos.1 = 0;
        } else {
            self.grid_pos.1 += 1;
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t0() {
        assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 100, 6, 9)), display_expected("111100\r\n100010\r\n100001\r\n100010\r\n111100\r\n100000\r\n100000\r\n100000\r\n100000"), "Your interpreter should terminate normally and return a representation of the final state of the 2D datagrid when all commands have been considered from left to right even if the number of iterations specified have not been fully performed");
    }
    #[test]
    fn t1() {
        assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 42, 6, 9)), display_expected("111100\r\n100010\r\n100001\r\n100010\r\n111100\r\n100000\r\n100000\r\n100000\r\n100000"), "Your interpreter should traverse the 2D datagrid correctly for all of the \"n\", \"e\", \"s\" and \"w\" commands");
    }
    #[test]
    fn t2() {
        assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 19, 6, 9)), display_expected("111100\r\n000010\r\n000001\r\n000010\r\n000100\r\n000000\r\n000000\r\n000000\r\n000000"), "Your interpreter should traverse the 2D datagrid correctly");
    }
    #[test]
    fn t3() {
        assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 7, 6, 9)), display_expected("111100\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000"), "Your interpreter should adhere to the number of iterations specified");
    }
    #[test]
    fn t4() {
        assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 0, 6, 9)), display_expected("000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000"), "Your interpreter should initialize all cells in the datagrid to 0");
    }

    /// Prints representation of datagrid - 0's are black and 1's are white.
    /// Note: it only works properly if your interpreter returns a representation
    /// of the datagrid in the correct format.
    fn pretty_print(datagrid: &str) -> &str {
        let rows = datagrid.split("\r\n");
        let mut output = String::new();
        output += "<pre>";
        for row in rows {
            for cell in row.chars() {
                output += "<span style=\"color:"; 
                output += if cell == '0' { "black" } else { "white" };
                output += ";background-color:"; 
                output += if cell == '0' { "black" } else { "white" };
                output += "\">xx</span>";
            }
            output += "<br />";
        }
        output += "</pre>";
        println!("{}", output);
        datagrid
    }

    /// Displays the grid the interpreter returns
    fn display_actual(actual: &str) -> &str {
        println!("You returned:");
        pretty_print(actual)
    }

    /// Displays the expected final state of datagrid
    fn display_expected(expected: &str) -> &str {
        println!("Expected final state of data grid:");
        pretty_print(expected)
    }   
}
