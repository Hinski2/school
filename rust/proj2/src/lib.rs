#[cfg(test)]
mod tests {
    use lexer::lexer::tokenize_code;
    use parser::rd_parser::parse_program;

    #[test]
    fn test1() {
        let code = "
            TO star
                REPEAT 5 [ fd 100 rt 144 ]
            END

            clearscreen
            star
        ".to_string();

        let mut tokens = tokenize_code(code).unwrap();
        let _program = parse_program(&mut tokens).unwrap();
    }


    #[test]
    fn test2() {
        let code = "
        TO square :length
            REPEAT 4 [ fd :length rt 90 ]
        END

        TO randomcolor
            setcolor pick [ RED ORANGE YELLOW GREEN BLUE PURPLE ]
        END

        clearscreen
        REPEAT 36 [ randomcolor square random 200 rt 10 ]
        ".to_string();

        let mut tokens = tokenize_code(code).unwrap();
        let _program = parse_program(&mut tokens).unwrap();
    }


    #[test]
    fn test3() {
        let code = "
        clearscreen window hideturtle

        REPEAT 144 [
            setlabelheight REPCOUNT
            penup
            fd REPCOUNT * REPCOUNT / 30
            label \"Logo
            bk REPCOUNT * REPCOUNT / 30
            pendown
            rt 10
            wait 5
        ]

        showturtle
        ".to_string();

        let mut tokens = tokenize_code(code).unwrap();
        let _program = parse_program(&mut tokens).unwrap();
    }

    #[test]
    fn test4() {
        let code = "
        TO tree :size
            IF :size < 5 [forward :size back :size stop]
            forward :size/3
            left 30 tree :size*2/3 right 30
            forward :size/6
            right 25 tree :size/2 left 25
            forward :size/3
            right 25 tree :size/2 left 25
            forward :size/6
            back :size
        END

        clearscreen
        tree 150
        ".to_string();

        let mut tokens = tokenize_code(code).unwrap();
        let _program = parse_program(&mut tokens).unwrap();
    }

    #[test]
    fn test5() {
        let code = "
            TO fern :size :sign
                if :size < 1 [ stop ]
                fd :size
                rt 70 * :sign fern :size * 0.5 :sign * -1 lt 70 * :sign
                fd :size
                lt 70 * :sign fern :size * 0.5 :sign rt 70 * :sign
                rt 7 * :sign fern :size - 1 :sign lt 7 * :sign
                bk :size * 2
            END

            window clearscreen pu bk 150 pd
            fern 25 1
        ".to_string();

        let mut tokens = tokenize_code(code).unwrap();
        let _program = parse_program(&mut tokens).unwrap();
    }

    #[test]
    fn test6() {
        let code = "
            clearscreen
            setturtle 2 penup right 90 forward 100 left 90 pendown

            REPEAT 100 [
                setturtle 1 forward random 4
                setturtle 2 forward random 4
                wait 2
            ]
        ".to_string();

        let mut tokens = tokenize_code(code).unwrap();
        let _program = parse_program(&mut tokens).unwrap();
    }
}