use lexer::lexer::tokenize_file;
use parser::rd_parser::parse_program;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let mut tokens = tokenize_file("test/test3.in".to_string())?;
    dbg!(&tokens);

    let program = parse_program(&mut tokens)?;
    dbg!(&program);

    Ok(())
}
