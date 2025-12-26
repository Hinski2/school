use std::ops;
use wasm_bindgen::prelude::*;

#[wasm_bindgen]
#[derive(Debug, Clone, Copy)]
pub struct Complex {
    pub re: f64, 
    pub im: f64,
}

impl Complex {
    pub fn new(re: f64, im: f64) -> Self {
        Complex {re, im}
    }    

    pub fn norm_sqr(&self) -> f64 {
        self.re * self.re + self.im * self.im
    }

    pub fn norm(&self) -> f64 {
        (self.re * self.re + self.im * self.im).sqrt()
    }

    pub fn escape_itr(&self, max_iter: usize) -> usize {
        let mut z = Complex::default();

        for i in 0..max_iter {
            z = z * z + *self;
            if z.norm_sqr() > 4.0 {
                return i
            }
        }

        max_iter
    }
}

impl ops::Add<Complex> for Complex {
    type Output = Complex;

    fn add(self, rhs: Complex) -> Self::Output {
        Complex::new(self.re + rhs.re, self.im + rhs.im)
    } 
}

impl ops::Sub<Complex> for Complex {
    type Output = Complex;

    fn sub(self, rhs: Complex) -> Self::Output {
        Complex::new(self.re - rhs.re, self.im - rhs.im)
    } 
}

impl ops::Mul<Complex> for Complex {
    type Output = Complex;

    fn mul(self, rhs: Complex) -> Self::Output {
        Complex {
            re: self.re * rhs.re - self.im * rhs.im, 
            im: self.re * rhs.im + self.im * rhs.re,
        }
    }
}

impl Default for Complex {
    fn default() -> Self {
        return Complex { re: 0.0, im: 0.0 }
    } 
}
