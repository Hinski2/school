use std::fmt;
use wasm_bindgen::prelude::*;

#[wasm_bindgen]
#[derive(Debug, Clone)]
pub struct Color {
    pub r: u8, 
    pub g: u8, 
    pub b: u8,
}

const COLOR_1: Color = Color {r: 102, g: 0, b: 204};
const COLOR_2: Color = Color {r: 102, g: 255, b: 255};
const COLOR_3: Color = Color {r: 255, g: 102, b: 255};
const COLOR_4: Color = Color {r: 102, g: 0, b: 102};
const COLOR_5: Color = Color {r: 51, g: 51, b: 153};
const COLOR_6: Color = Color {r: 0, g: 0, b: 102};

#[wasm_bindgen]
impl Color {
    pub fn calculate_color(escape_time: usize, max_itr: usize) -> Color {
        let t = escape_time as f64 / max_itr as f64;
        
        if t < 0.33 {
            Color::lerp(COLOR_1, COLOR_2, t)
        } else if t < 0.66 {
            Color::lerp(COLOR_3, COLOR_4, t)
        } else {
            Color::lerp(COLOR_5, COLOR_6, t)
        }
    }

    fn lerp(a: Color, b: Color, t: f64) -> Color {
        let r = a.r as f64 + t * (b.r as f64 - a.r as f64);
        let g = a.g as f64 + t * (b.g as f64 - a.g as f64);
        let b = a.b as f64 + t * (b.b as f64 - a.b as f64);

        Color {r: r as u8, g: g as u8, b: b as u8}
    }
}

impl fmt::Display for Color {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{} {} {}", self.r, self.g, self.b)
    }
}
