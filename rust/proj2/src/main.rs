use lexer::lexer::tokenize_file;
use parser::rd_parser::parse_program;
use interpreter::interpreter::Interpreter;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    print!("\nTOKENS:\n");
    let mut tokens = tokenize_file("test/test4.in".to_string())?;
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
