use std::{error::Error, fs::File, io::Write};
use super::pixel::Pixel;
use crate::utils::linspace::Linspace;

pub struct Image {
    data: Vec<Vec<Pixel>>,
    x: Linspace,
    y: Linspace,
}

impl Image {
    pub fn new(x: Linspace, y: Linspace) -> Self {

        let data: Vec<Vec<Pixel>> = (0..y.get_pts())
            .map(|i| {
                (0..x.get_pts())
                .map(|j| Pixel::new(x.pos(j), y.pos(i))) 
                .collect()
            })
            .collect();

        Image {
            x: x, 
            y: y,
            data: data,
        }
    } 

    pub fn set_pixel(&mut self, i: usize, j: usize, pixel: Pixel) -> Result<(), Box<dyn Error>> {
        if i > self.x.get_pts() || j > self.y.get_pts() {
            return Err("x or y val are too big".into());
        }

        self.data[i][j] = pixel;

        Ok(())
    }

    pub fn write_to_file(&self, path: &str) -> Result<(), Box<dyn Error>> {
        let mut file = File::create(path)?;
        writeln!(file, "P6")?;
        writeln!(file, "{} {}", self.x.get_pts(), self.y.get_pts())?;
        writeln!(file, "255")?;

        for v_pixel in &self.data {
            for pixel in v_pixel {
                // write!(file, "{pixel} ")?
                let color = pixel.get_color();
                file.write_all(&[color.r, color.g, color.b])?;
            }
        }
    
        file.flush()?;
        Ok(())
    }
}
