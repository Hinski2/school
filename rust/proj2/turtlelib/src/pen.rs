use super::color::Color;

pub struct Pen {
    up: bool, 
    color: Color,
    size: usize,
}

// utils
impl Pen {
    pub fn new() -> Pen {
        Pen {
            up: false, 
            color: Color::BLACK,
            size: 20,
        }
    }
}

// pen control
impl Pen {
    pub fn pen_down(&mut self) {
        self.up = false;
    }

    pub fn pen_up(&mut self) {
        self.up = true;
    }

    pub fn set_pen_color(&mut self, color: Color) {
        self.color = color;
    }

    pub fn set_pen_size(&mut self, size: usize) {
        self.size = size;
    }
}

// pen queries
impl Pen {
    pub fn pen_down_p(&self) -> bool {
        return !self.up;
    }

    pub fn pen_color(&self) -> Color {
        return self.color;
    }

    pub fn pen_size(&self) -> usize {
        return self.size;
    }
}