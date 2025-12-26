use wasm_bindgen::prelude::*;
use crate::{utils::linspace::Linspace, view::pixel::Pixel};
use std::ptr::addr_of;

const WIDTH: usize = 1024;
const HEIGHT: usize = 1024;
const BUFFER_SIZE: usize = WIDTH * HEIGHT * 4;

static mut BUFFER: [u8; BUFFER_SIZE] = [0; BUFFER_SIZE];

#[wasm_bindgen]
pub struct Renderer;

#[wasm_bindgen]
impl Renderer {
    pub fn init() {
        for i in 0..WIDTH*HEIGHT {
            unsafe {
                BUFFER[3 + i * 4] = 255;
            }
        }
    }

    pub fn update(x: Linspace, y: Linspace, max_itr: usize) {
        for i in 0..WIDTH {
            for j in 0..HEIGHT {
                let rgb = Pixel::new(x.pos(j), y.pos(i), max_itr).get_rgb();
                let idx = (i * WIDTH + j) * 4;
                unsafe {
                    BUFFER[idx] = rgb[0];
                    BUFFER[idx + 1] = rgb[1];
                    BUFFER[idx + 2] = rgb[2];
                }
            }
        }
    }

    pub fn get_buffer_ptr() -> *const u8 {
        addr_of!(BUFFER) as *const u8
    }
}

