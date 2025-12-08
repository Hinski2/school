use std::{collections::{HashMap, LinkedList}, io::LineWriter};
use parser::grammar::{Stmt};
use turtlelib::color::Color;

#[derive(Clone, Debug)]
pub enum Value {
    VOID, 
    INT(i64),
    FLOAT(f64),
    COLOR(Color), 
    LIST(LinkedList<Value>),
}

#[derive(Clone)]
pub enum Lang {
    RUST(fn(&mut Env, &[Value]) -> Result<Value, Box<dyn std::error::Error>>), 
    LOGO(LinkedList<Stmt>),
}

#[derive(Clone)]
pub struct Function {
    pub lang: Lang,
    pub arg_no: usize,
    pub arg_names: LinkedList<String>,
}

#[derive(Clone)]
pub enum EnvEntry {
    FUNCTION(Function),
    VALUE(Value),
}

pub struct Env {
    map: HashMap<String, EnvEntry>,
    repcount: Option<i64>,
}

impl Env {
    pub fn new() -> Env {
        Env { map: HashMap::new(), repcount: None }
    }

    pub fn from(env: &Env) -> Env {
        Env { map: env.map.clone(), repcount: env.repcount }
    }

    pub fn add(&mut self, name: String, entry: EnvEntry) -> Result<(), Box<dyn std::error::Error>> {
        if self.map.contains_key(&name) {
            return Err(format!("interpreter error: variable with name {} already exists", name).into());
        }

        self.map.insert(name, entry);
        Ok(())
    }

    pub fn lookup(&self, name: &str) -> Option<EnvEntry> {
        match self.map.get(name) {
            Some(val) => Some(val.clone()),
            None => None,
        }
    }

    pub fn get_repcount(&self) -> Result<i64, Box<dyn std::error::Error>> {
        match self.repcount {
            Some(v) => Ok(v), 
            None => Err(format!("interpreter error: you cant use repcont outside loop").into())
        }
    }

    pub fn add_function_args(&mut self, entries: &LinkedList<EnvEntry>, names: &LinkedList<String>) -> Result<(), Box<dyn std::error::Error>> {
        for (entry, name) in entries.iter().zip(names.iter()) {
            self.add(name.to_string(), entry.clone())?;
        }

        Ok(())
    }

    pub fn set_repcount(&mut self, repcount: Option<i64>) {
        self.repcount = repcount;
    }
}
