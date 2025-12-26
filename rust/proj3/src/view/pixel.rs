use std::fmt;
use crate::utils::linspace::Linspace;
use crate::utils::complex::Complex;
use super::color::Color;
use wasm_bindgen::prelude::*;

#[wasm_bindgen]
#[derive(Debug, Clone)]
pub struct Pixel {
    pos: Complex,
    color: Color,
}

impl Pixel {
    pub fn new(x_pos: f64, y_pos: f64, max_itr: usize) -> Pixel {
        let pos = Complex {re: x_pos, im: y_pos};
        let escape_time = pos.escape_itr(max_itr);
        let color = Color::calculate_color(escape_time, max_itr);        

        Pixel {pos, color}
    }

    pub fn from(x_pos: f64, y_pos: f64, color: Color) -> Pixel {
        let pos = Complex {re: x_pos, im: y_pos};
        Pixel {pos, color}
    }

    pub fn set_rgb(&mut self, r: u8, g: u8, b: u8) {
        self.color = Color {r, g, b}
    }

    pub fn get_rgb(&self) -> [u8; 4] {
        [self.color.r, self.color.g, self.color.b, 255]
    }

    pub fn get_color(&self) -> Color {
        self.color.clone()
    }

    pub fn get_x_pos(&self) -> f64 {
        self.pos.re
    }

    pub fn get_y_pos(&self) -> f64 {
        self.pos.im
    }

    pub fn get_pos(&self) -> Complex {
        self.pos.clone()
    }
    
    pub fn set_pos(&mut self, x: &Linspace, y: &Linspace, i: usize, j: usize) {
        self.pos.re = x.get_start() + (x.get_end() - x.get_start()) / x.get_pts() as f64 * i as f64;
        self.pos.im = y.get_start() + (y.get_end() - x.get_start()) / y.get_pts() as f64 * j as f64;
    }
}

impl fmt::Display for Pixel {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
       write!(f, "{}", self.color) 
    }
}

