use lexer::lexer::tokenize_file;
use parser::rd_parser::parse_program;
use interpreter::interpreter::Interpreter;
use std::env::args;

fn parse_args() -> Result<String, Box<dyn std::error::Error>> {
    let env: Vec<String> = args().collect();
    if env.len() < 2 {
        Err("parser error: you didnt passed file to interpret".into())
    } else {
        Ok(env[1].clone())
    }
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let file = parse_args()?;

    print!("\nTOKENS:\n");
    let mut tokens = tokenize_file(file)?;
    dbg!(&tokens);


    print!("\nPROGRAM:\n");
    let program = parse_program(&mut tokens)?;
    dbg!(&program);

    print!("\nOUTPUT:\n");
    let mut interpreter = Interpreter::new(program);
    let ans = interpreter.interpret_program()?;
    println!("{:#?}", ans);

    Ok(())
}
