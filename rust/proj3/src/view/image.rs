use super::pixel::Pixel;
use crate::{utils::linspace::Linspace};
use wasm_bindgen::prelude::*;

#[wasm_bindgen]
pub struct Image {
    data: Vec<Pixel>,
    x: Linspace,
    y: Linspace,
}

#[wasm_bindgen]
impl Image {
    #[wasm_bindgen(constructor)]
    pub fn new() -> Self {
        Image {
            x: Linspace::new(0., 0., 0).unwrap(),
            y: Linspace::new(0., 0., 0).unwrap(),
            data: Vec::new(),
        }
    } 

    pub fn update(&mut self, x: Linspace, y: Linspace, max_itr: usize)  {
        self.data = (0..y.get_pts())
            .flat_map(|i| {
                (0..x.get_pts())
                .map(|j| Pixel::new(x.pos(j), y.pos(i), max_itr)) 
                .collect::<Vec<Pixel>>()
            })
            .collect();

        self.x = x;
        self.y = y;
    }

    pub fn pixels(&self) -> Vec<u8> {
        self.data.iter()
            .flat_map(|p| p.get_rgb())
            .collect()
    }

    pub fn set_pixel(&mut self, i: usize, j: usize, pixel: Pixel) -> Result<(), String> {
        if i > self.x.get_pts() || j > self.y.get_pts() {
            return Err("x or y val are too big".to_string());
        }

        self.data[i * self.x.get_pts() + j] = pixel;

        Ok(())
    }
}
