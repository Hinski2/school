use std::error::Error;

pub struct Linspace {
    start: f64,
    end: f64, 
    pts: usize,
}

impl Linspace {
    pub fn new(start: f64, end: f64, pts: usize) -> Result<Linspace, Box<dyn Error>> {
        if start > end {
            return Err(format!("Invalid range: start = {}, end = {} (expected start < end)", start, end).into());
        }
        
        Ok(Linspace { start: start, end: end, pts: pts })
    }

    pub fn pos(&self, i: usize) -> f64 {
        return self.start + (self.end - self.start) / (self.pts - 1) as f64 * i as f64
    }

    pub fn get_start(&self) -> f64 {
        self.start  
    }

    pub fn get_end(&self) -> f64 {
        self.end
    }

    pub fn get_pts(&self) -> usize {
        self.pts
    }
}
