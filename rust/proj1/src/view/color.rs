use std::fmt;
use std::cmp::{min, max};

#[derive(Debug, Clone)]
pub struct Color {
    pub r: u8, 
    pub g: u8, 
    pub b: u8,
}


const COLOR_1: Color = Color {r: 102, g: 0, b: 204};
const COLOR_2: Color = Color {r: 102, g: 255, b: 255};

impl Color {
    pub fn calculate_color(escape_time: usize, max_itr: usize) -> Color {

        let (min_r, max_r) = ( min(COLOR_1.r, COLOR_2.r) as f64, max(COLOR_1.r, COLOR_2.r) as f64);
        let (min_g, max_g) = ( min(COLOR_1.g, COLOR_2.g) as f64, max(COLOR_1.g, COLOR_2.g) as f64);
        let (min_b, max_b) = ( min(COLOR_1.b, COLOR_2.b) as f64, max(COLOR_1.b, COLOR_2.b) as f64);

        let r = (min_r + (max_r - min_r) / max_itr as f64 * escape_time as f64) as u8;
        let g = (min_g + (max_g - min_g) / max_itr as f64 * escape_time as f64) as u8;
        let b = (min_b + (max_b - min_b) / max_itr as f64 * escape_time as f64) as u8;

        Color {r, g, b}
    }
}

impl fmt::Display for Color {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{} {} {}", self.r, self.g, self.b)
    }
}
