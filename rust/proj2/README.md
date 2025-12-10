## Logo Language Recreation

--- 

### How to run the program 

    cargo run file.in

### Example 

    cargo run test/test5.in

```
TO foo :f :x :y 
    OUTPUT f :x :y 
END 

TO add :a :b 
    OUTPUT :a + :b
END 

OUTPUT foo "add 1 1
```

output: INT(2)

#### Another example 
```
TO foo
    REPEAT 5 [
        IF REPCOUNT = 2 [
            OUTPUT REPCOUNT
        ]
    ]
END

OUTPUT foo
```

output INT(2)

---

#### Data types in my logo:
``` rust
pub enum Value {
    VOID, 
    INT(i64),
    FLOAT(f64),
    STRING(String),
    COLOR(Color), 
    LIST(LinkedList<Value>),
}
```


--- 

#### grammar 
``` ocaml
    <expr> ::= 
        | numb
        | <varref>
        | <repcount>
        | <expr> <op> <expr>

    <item> := 
        | <expr> 
        | <varname>
        | <color>
        | <list>

    <returnable> :=
        | <item> 
        | <procedure-call>
    
    <list> ::= [ <item>* ]

    <procedure-def> ::= to <PROCEDURECALL>  <varref>* <stmt>* end
    <procedure-call> ::= <PROCEDURECALL> <item>*

    <stmt> ::= 
        | <procedure-def>
        | <procedure-call> 
        | if <expr> <block>
        | ifelse <expr> <block> <block>
        | repeat <expr> <block>
        | output <returnable>
        | stop
        | make <varname> <returnable>

    <block> := [ <stmt>* ]
    
    <program> ::= <stmt>*
```

--- 

#### Vision for the future
* TurtleLib and StdLib need to be implemented
* Allow returning functions from functions and assigning functions to variables
* Implement anonymous functions