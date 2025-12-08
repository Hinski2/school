use parser::grammar::{BinOp, Expr, Item, ProcedureCall, Program, Returnable, Stmt, UnOp};
use crate::env::{EnvEntry, Value, Lang, Function};

use super::env::Env;
use std::{collections::LinkedList, mem};

pub enum Flow {
    Next,
    Return(Value),
}

pub struct Interpreter {
    env: Env,
    global_env: Env,
    code: LinkedList<Stmt>,
}

impl Interpreter {
    pub fn new(program: Program) -> Interpreter {
        let env = Env::new();
        let global_env = Env::new();

        // add stdlib
        // add turtlelib

        Interpreter { env, global_env, code: program.body }
    }

    pub fn interpret_program(&mut self) -> Result<Value, Box<dyn std::error::Error>> {
        while let Some(stmt) = self.code.pop_front() {
            let result = self.interpret_stmt(stmt)?;

            match result {
                Flow::Next => continue,
                Flow::Return(v) => return Ok(v),
            }
        }

        Ok(Value::VOID)
    }

    fn evaluate_expr(&self, expr: Expr) -> Result<Value, Box<dyn std::error::Error>> {
        match expr {
            Expr::INT(i) => Ok(Value::INT(i)),
            Expr::FLOAT(f) => Ok(Value::FLOAT(f)),
            Expr::VARREF(name) => {
                let env_entry = self.env.lookup(&name)
                    .ok_or_else(|| "interpreter error: varref with that name doesnt exit")?;

                match env_entry {
                    EnvEntry::FUNCTION(_) => Err(format!("interpreter error: innapropriate expr").into()),
                    EnvEntry::VALUE(v) => Ok(v),
                }
            },
            Expr::REPCOUNT => {
                Ok(Value::INT(self.env.get_repcount()?))
            },
            Expr::BINARY { e1, op, e2 } => {

                fn f<I, F>(v1: Value, v2: Value, int_op: I, float_op: F)
                    -> Result<Value, Box<dyn std::error::Error>> 
                where 
                    I: Fn(i64, i64) -> i64,
                    F: Fn(f64, f64) -> f64
                {
                        match (v1.clone(), v2.clone()) {
                            (Value::INT(a), Value::INT(b)) => Ok(Value::INT(int_op(a, b))),
                            (Value::FLOAT(a), Value::FLOAT(b)) => Ok(Value::FLOAT(float_op(a, b))),
                            (Value::INT(a), Value::FLOAT(b)) => Ok(Value::FLOAT(float_op(a as f64, b))),
                            (Value::FLOAT(a), Value::INT(b)) => Ok(Value::FLOAT(float_op(a, b as f64))),
                            _ => Err(format!("interpreter error: you try to merge join types in expr {:#?}, {:#?}", v1, v2).into()),
                        }
                }

                let (int_op, float_op): (fn(i64, i64)->i64, fn(f64, f64)->f64) = match op {
                    BinOp::ADD => (|a, b| a + b, |a, b| a + b),
                    BinOp::SUB => (|a, b| a - b, |a, b| a - b),
                    BinOp::MULT => (|a, b| a * b, |a, b| a * b),
                    BinOp::DIV => (|a, b| a / b, |a, b| a / b),
                    BinOp::MOD => (|a, b| a % b, |a, b| a % b),

                    BinOp::EQP  => (|a, b| (a == b) as i64, |a, b| (a == b) as i64 as f64),
                    BinOp::NEQP => (|a, b| (a != b) as i64, |a, b| (a != b) as i64 as f64),
                    BinOp::GEQP => (|a, b| (a >= b) as i64, |a, b| (a >= b) as i64 as f64),
                    BinOp::LEQP => (|a, b| (a <= b) as i64, |a, b| (a <= b) as i64 as f64),
                    BinOp::GTP  => (|a, b| (a > b) as i64,  |a, b| (a > b) as i64 as f64),
                    BinOp::LTP  => (|a, b| (a < b) as i64,  |a, b| (a < b) as i64 as f64),

                    BinOp::AND => (|a, b| (a != 0 && b != 0) as i64, |a, b| (a != 0. && b != 0.) as i64 as f64),
                    BinOp::OR  => (|a, b| (a != 0 || b != 0) as i64, |a, b| (a != 0. || b != 0.) as i64 as f64),
                };

                let v1 = self.evaluate_expr(*e1)?;
                let v2 = self.evaluate_expr(*e2)?;

                f(v1, v2, int_op, float_op)
            }
            Expr::UNARY { op, e1 } => {

                fn f<I, F>(v1: Value, int_op: I, float_op: F)
                    -> Result<Value, Box<dyn std::error::Error>> 
                where 
                    I: Fn(i64) -> i64,
                    F: Fn(f64) -> f64
                {
                    match v1.clone() {
                        Value::INT(i) => Ok(Value::INT(int_op(i))),
                        Value::FLOAT(f) => Ok(Value::FLOAT(float_op(f))),
                        _ => Err(format!("interpreter error: you try to merge join types in expr {:#?}", v1).into()),
                    }
                }

                let (int_op, float_op): (fn(i64)->i64, fn(f64)-> f64) = match op {
                    UnOp::NOT => (|a| if a == 0 {1} else {0}, |a| if a == 0. {1.} else {0.})
                };

                let v1 = self.evaluate_expr(*e1)?;
                f(v1, int_op, float_op)
            },
        }
    }

    fn add_block(&mut self, mut stmts: LinkedList<Stmt>) {
        stmts.append(&mut self.code);
        self.code = stmts;
    }

    fn interpret_block(&mut self) -> Result<Flow, Box<dyn std::error::Error>> {
        while let Some(stmt) = self.code.pop_front() {
            match stmt {
                Stmt::STOP => return Ok(Flow::Return(Value::VOID)),
                Stmt::OUTPUT(r) => {
                    return Ok(self.interpret_returnable(r)?);
                },
                _ => {
                    match self.interpret_stmt(stmt)? {
                        Flow::Next => (), 
                        Flow::Return(v) => return Ok(Flow::Return(v)),
                    }
                },
            }
        }

        Ok(Flow::Next)
    }



    fn convert_item_env_entry(&self, item: Item) -> Result<EnvEntry, Box<dyn std::error::Error>> {
        match item {
            Item::EXPR(e) => Ok(EnvEntry::VALUE(self.evaluate_expr(e)?)),
            Item::COLOR(c) => Ok(EnvEntry::VALUE(Value::COLOR(c))),
            Item::LIST(l) => {      // note for fure me: We decided that we don't support having functions inside list
                let vals: LinkedList<Value> = l.items.into_iter()
                    .map(|item| self.convert_item_val(item))
                    .collect::<Result<LinkedList<Value>, _>>()?;

                Ok(EnvEntry::VALUE(Value::LIST(vals)))
            },
            Item::VARNAME(name) => {
                match self.env.lookup(&name) {
                    Some(ee) => Ok(ee),
                    None => Ok(EnvEntry::VALUE(Value::STRING(name))),
                }
            },
        }
    }

    fn convert_item_val(&self, item: Item) -> Result<Value, Box<dyn std::error::Error>> {
        match item {
            Item::EXPR(e) => Ok(self.evaluate_expr(e)?),
            Item::COLOR(c) => Ok(Value::COLOR(c)),
            Item::LIST(l) => {
                let vals: LinkedList<Value> = l.items.into_iter()
                    .map(|item| self.convert_item_val(item))
                    .collect::<Result<LinkedList<Value>, _>>()?;

                Ok(Value::LIST(vals))
            },
            Item::VARNAME(name) => {
                match self.env.lookup(&name) {
                    Some(EnvEntry::FUNCTION(f)) => Err(format!("interpreter error: you can't pass function {:#?} to the rust inplemented function", f).into()),
                    Some(EnvEntry::VALUE(v)) => Ok(v),
                    None => Ok(Value::STRING(name)),
                }
            },
        }
    }

    fn interpret_logo_args(&mut self, items: LinkedList<Item>) -> Result<LinkedList<EnvEntry>, Box<dyn std::error::Error>> {
        // convert items -> EnvEntry
        let vals: LinkedList<EnvEntry> = items.into_iter()
            .map(|item| self.convert_item_env_entry(item))
            .collect::<Result<LinkedList<EnvEntry>, _>>()?;

        Ok(vals)
    }

    fn interpret_rust_args(&mut self, items: LinkedList<Item>) -> Result<Vec<Value>, Box<dyn std::error::Error>> {
        // convert items -> Value
        let vals: Vec<Value> = items.into_iter()
            .map(|item| self.convert_item_val(item))
            .collect::<Result<Vec<Value>, _>>()?;

        Ok(vals)
    }

    fn interpret_returnable(&mut self, r: Returnable) -> Result<Flow, Box<dyn std::error::Error>> {
        Ok(match r {
            Returnable::ITEM(Item::EXPR(e)) => Flow::Return(self.evaluate_expr(e)?),
            Returnable::ITEM(Item::VARNAME(name)) => {
                match self.env.lookup(&name) {
                    Some(EnvEntry::FUNCTION(f)) => return Err(format!("interpreter error: returning funciton ptr {:#?} is not supported (yet)", f).into()),
                    _ => Flow::Return(Value::STRING(name.clone())),
                }
            },
            Returnable::ITEM(Item::COLOR(c)) => Flow::Return(Value::COLOR(c)),
            Returnable::ITEM(il) => Flow::Return(self.convert_item_val(il)?),
            Returnable::PROCEDURECALL(pc) => self.interpret_procedure_call(pc)?,
        })
    }

    fn interpret_procedure_call(&mut self, pc: ProcedureCall) -> Result<Flow, Box<dyn std::error::Error>> {
        let ProcedureCall{id, args} = pc;

        let entry = self.env.lookup(&id)
            .ok_or_else(|| -> Box<dyn std::error::Error> { 
                format!("interpreter error: function with name {} doesnt exist", id).into() 
            })?;

        match entry {
            EnvEntry::VALUE(_) => Err(format!("interpreter error: expected function call, received value").into()),
            EnvEntry::FUNCTION(Function { lang: Lang::LOGO(content), arg_no, arg_names }) => {
                if args.len() != arg_no {
                    return Err(format!("interpreter error: expected {} args, received {}", arg_no, args.len()).into());
                }

                // interpret args in old env
                let env_entries = self.interpret_logo_args(args)?;

                // remember old env and replace it
                let old_env= mem::replace(&mut self.env, Env::from(&self.global_env));
                let old_code = mem::replace(&mut self.code, content);
                
                // add arguments to the new env
                self.env.add_function_args(&env_entries, &arg_names)?;

                let result_val = match self.interpret_block()? {
                    Flow::Next => Flow::Return(Value::VOID),
                    Flow::Return(v) => Flow::Return(v),
                };

                // restore old env
                (self.env, self.code) = (old_env, old_code);
                Ok(result_val)
            },
            EnvEntry::FUNCTION(Function { lang: Lang::RUST(fun), arg_no, arg_names: _ }) => {
                if args.len() != arg_no {
                    return Err(format!("interpreter error: expected {} args, received {}", arg_no, args.len()).into());
                }

                let values = self.interpret_rust_args(args)?;
                let result_value = fun(&mut self.env, &values)?;
                Ok(Flow::Return(result_value))
            },
        }
    }

    fn interpret_stmt(&mut self, stmt: Stmt) -> Result<Flow, Box<dyn std::error::Error>> {
        match stmt {
            Stmt::OUTPUT(r) => {
                Ok( self.interpret_returnable(r)? )
            }, 
            Stmt::STOP => {
                Ok(Flow::Return(Value::VOID))
            },
            Stmt::PROCEDUREDEF { id, args, content } => {
                self.env.add(id, EnvEntry::FUNCTION( Function {
                    lang: Lang::LOGO(content),
                    arg_no: args.len(),
                    arg_names: args, 
                }))?; 

                Ok(Flow::Next)
            },
            Stmt::PROCEDURECALL(pc) => {
                Ok(self.interpret_procedure_call(pc)?)
            }, 
            Stmt::IFSTMT { cond, body } => {
                let val: Value = self.evaluate_expr(cond)?;
                match val {
                    Value::INT(x) if x != 0 => {
                        self.add_block(body.stmts);
                        Ok(Flow::Next)
                    },
                    Value::FLOAT(x) if x != 0. => {
                        self.add_block(body.stmts);
                        Ok(Flow::Next)
                    }
                    Value::INT(_) | Value::FLOAT(_) => Ok(Flow::Next),
                    _ => {
                        Err(format!("interpreter error: expected INT or FLOAT, received {:#?}", val).into())
                    }
                }
            },
            Stmt::IFELSE { cond, body1, body2 } => {
                let val: Value = self.evaluate_expr(cond)?;
                match val {
                    Value::INT(x) if x != 0 => {
                        self.add_block(body1.stmts);
                        Ok(Flow::Next)
                    },
                    Value::FLOAT(x) if x != 0. => {
                        self.add_block(body1.stmts);
                        Ok(Flow::Next)
                    }
                    Value::INT(_) | Value::FLOAT(_) => {
                        self.add_block(body2.stmts);
                        Ok(Flow::Next)
                    }
                    _ => {
                        Err(format!("interpreter error: expected INT or FLOAT, received {:#?}", val).into())
                    }
                }
            },
            Stmt::REPEATSTMT { repeat_no, body } => {
                let val = self.evaluate_expr(repeat_no)?;
                let range = match val {
                    Value::INT(i) => i,
                    _ => return Err(format!("interpreter error, repeat_no shout be INT, received {:#?}", val).into()),
                };

                let old_code = mem::replace(&mut self.code, body.stmts.clone());
                for repcount in 0..range {
                    self.env.set_repcount(Some(repcount));
                    self.code = body.stmts.clone();

                    match self.interpret_block()? {
                        Flow::Next => continue,
                        Flow::Return(v) => {
                            self.env.set_repcount(None);
                            self.code = old_code;

                            return Ok(Flow::Return(v));
                        }
                    }
                }

                self.env.set_repcount(None);
                self.code = old_code;

                Ok(Flow::Next)
            },
            Stmt::MAKE { name, val } => {
                let entry = match self.interpret_returnable(val)? {
                    Flow::Next => return Err(format!("interpreter error: you try to assign not value to variable with name {}", name).into()),
                    Flow::Return(v) => v,
                };

                self.env.add(name, EnvEntry::VALUE(entry))?; 
                Ok( Flow::Next )
            }
        }
    }
}
