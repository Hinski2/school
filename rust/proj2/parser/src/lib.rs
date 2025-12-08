pub mod grammar;
pub mod rd_parser;
pub mod pc_parser;

#[cfg(test)]
mod tests {
    use lexer::token::Token;
    use crate::grammar::{BinOp, Block, Expr, ProcedureCall, Stmt};
    use crate::rd_parser::{parse_block};
    use crate::pc_parser::{parse_expr};
    use std::collections::LinkedList;

    #[test]
    fn parse_single_number() {
        let mut tokens = LinkedList::from([
            Token::INT(42),
            Token::EOL,
        ]);

        let expr = parse_expr(&mut tokens).unwrap();
        assert_eq!(expr, Expr::INT(42));
    }

    #[test]
    fn parse_addition() {
        let mut tokens = LinkedList::from([
            Token::INT(1),
            Token::ADD,
            Token::INT(2),
            Token::EOL,
        ]);

        let expr = parse_expr(&mut tokens).unwrap();

        assert_eq!(
            expr,
            Expr::BINARY {
                op: BinOp::ADD,
                e1: Box::new(Expr::INT(1)),
                e2: Box::new(Expr::INT(2)),
            }
        );
    }

    #[test]
    fn parse_add_mul_precedence() {
        let mut tokens = LinkedList::from([
            Token::INT(1),
            Token::ADD,
            Token::INT(2),
            Token::MULT,
            Token::INT(3),
            Token::EOL,
        ]);

        let expr = parse_expr(&mut tokens).unwrap();

        assert_eq!(
            expr,
            Expr::BINARY {
                op: BinOp::ADD,
                e1: Box::new(Expr::INT(1)),
                e2: Box::new(
                    Expr::BINARY {
                        op: BinOp::MULT,
                        e1: Box::new(Expr::INT(2)),
                        e2: Box::new(Expr::INT(3)),
                    }
                ),
            }
        );
    }



    #[test]
    fn parse_block_with_single_stmt() {
        let mut tokens = LinkedList::from([
            Token::LSQUAREDBRACKET,
            Token::PROCEDURECALL("id".to_string()),
            Token::RSQUAREDBRACKET,
        ]);

        let block = parse_block(&mut tokens, &mut 0).unwrap();
        let expected_stmts = LinkedList::from([
            Stmt::PROCEDURECALL( ProcedureCall { id: "id".to_string(), args: LinkedList::new() })
        ]);

        assert_eq!(
            block,
            Block {
                stmts: expected_stmts,
            }
        );
    }
}