use std::{error::Error, fs::File, io::Write};
use super::pixel::Pixel;
use crate::{utils::linspace::Linspace, view::color::Color};

pub struct Image {
    data: Vec<Vec<Pixel>>,
    x: Linspace,
    y: Linspace,
}

impl Image {
    pub fn new(x: Linspace, y: Linspace, max_itr: usize) -> Self {

        let data: Vec<Vec<Pixel>> = (0..y.get_pts())
            .map(|i| {
                (0..x.get_pts())
                .map(|j| Pixel::new(x.pos(j), y.pos(i), max_itr)) 
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

    pub fn smooth(&mut self, r: usize, passes: usize) {
        for _ in 0..passes {
            let new_data: Vec<Vec<Pixel>> = (0..self.y.get_pts())
                .map(|i| {
                    (0..self.x.get_pts())
                    .map(|j| self.get_avg_pixel(i as isize, j as isize, r as isize))
                    .collect()
                }) 
                .collect();

            self.data = new_data;
        }
    }

    fn get_avg_pixel(&self, i: isize, j: isize, r: isize) -> Pixel {
        let colors: Vec<Color> = (i - r..=i + r) 
            .filter(|&x| x >= 0 && x < self.x.get_pts() as isize)
            .flat_map(|x| {
                (j - r..=j + r) 
                    .filter(move |&y| y >= 0 && y < self.y.get_pts() as isize)
                    .map(move |y| self.data[x as usize][y as usize].get_color())
            })
            .collect();
            
        let color_sum: (isize, isize, isize) = colors.iter()
            .fold((0, 0, 0), |acc, Color{r, g, b}| (acc.0 + *r as isize, acc.1 + *g as isize, acc.2 + *b as isize));

        let color = Color { 
            r: (color_sum.0 / colors.len() as isize) as u8,
            g: (color_sum.1 / colors.len() as isize) as u8,
            b: (color_sum.2 / colors.len() as isize) as u8,
        };
        
        Pixel::from(self.x.pos(i as usize), self.y.pos(j as usize), color)
    }
}
