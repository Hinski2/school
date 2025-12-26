use std::env::args;
use std::error::Error;
use super::linspace::Linspace;

pub struct Config {
    pub img_path: String, 
    pub x: Linspace, 
    pub y: Linspace,
    pub max_itr: usize,
    pub r: usize, 
    pub passes: usize,
}

impl Config {
    pub fn new() -> Result<Self, Box<dyn Error>> {
        let env: Vec<String> = args().collect();

        let path;
        let (mut x_start, mut x_end, mut y_start, mut y_end) = (-1.5, 0.8, -1.2, 1.2);
        let (mut x_pts, mut y_pts) = (1920, 1080);
        let mut max_itr = 50;
        let (mut r, mut passes) = (1, 1);

        if env.len() == 2 {
            path = env[1].clone();
        } else if env.len() == 11 {
            path = env[1].clone();

            x_start = env[2].parse::<f64>().expect("2'th argument x_start: f64");
            x_end = env[3].parse::<f64>().expect("3'th argument x_end: f64");
            x_pts = env[4].parse::<usize>().expect("4'th argument x_pts: usize");

            y_start = env[5].parse::<f64>().expect("5'th argument y_start: f64");
            y_end = env[6].parse::<f64>().expect("6'th argument y_end: f64");
            y_pts = env[7].parse::<usize>().expect("7'th argument y_pts: usize");

            max_itr = env[8].parse::<usize>().expect("8'th argument max_itr: usize");

            r = env[9].parse::<usize>().expect("9'th arument r: usize");
            passes = env[10].parse::<usize>().expect("10'th argumet passes: usize");

        } else {
            return Err("innapropriate ammount of arguments, you have two options: 1. [img_path], 2. [img_path] [x_start] [x_end] [x_pts] [y_start] [y_end] [y_pts] [max_itr] [r] [passes]".into());
        }

        let x = Linspace::new(x_start, x_end, x_pts)?;
        let y = Linspace::new(y_start, y_end, y_pts)?;

        Ok(Config {
            img_path: path,
            x: x, 
            y: y,
            max_itr: max_itr,
            r: r,
            passes: passes,
        })
    }    
}
