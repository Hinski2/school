use super::pen::Pen;

#[derive(Clone, Copy)]
pub struct Pos {
    pub x: i64,
    pub y: i64,
}

pub enum TurtleMode {
    WRAP, 
    WINDOW,
    FENCE,
}

pub struct Turtle {
    pos: Pos,
    heading: f64, // in deg
    visable: bool,
    turtle_mode: TurtleMode,
    pen: Pen,
}

// turtle utils 
impl Turtle {
    pub fn new() -> Turtle {
        Turtle {
            pos: Pos {x: 0, y: 0},
            heading: 0.0,
            visable: true,
            turtle_mode: TurtleMode::WINDOW,
            pen: Pen::new(),
        }
    }

    fn heading_in_randians(&self) -> f64 {
        return self.heading * std::f64::consts::PI / 180.0;
    }
}

// turtle motion
impl Turtle {

    pub fn forward(&mut self, dist: i64) {
        self.pos.x += (self.heading_in_randians().cos() * dist as f64) as i64;
        self.pos.y += (self.heading_in_randians().sin() * dist as f64) as i64;
    }

    pub fn back(&mut self, dist: usize) {
        self.pos.x += (self.heading_in_randians().cos() * dist as f64) as i64;
        self.pos.y += (self.heading_in_randians().sin() * dist as f64) as i64;
    }

    pub fn right(&mut self, deg: f64) {
        self.heading = (self.heading - deg).rem_euclid(360.);
    }

    pub fn left(&mut self, deg: f64) {
        self.heading = (self.heading + deg).rem_euclid(360.);
    }

    pub fn set_pos(&mut self, pos: Pos) {
        self.pos = pos; 
    }

    pub fn set_xy(&mut self, x: i64, y: i64) {
        self.pos.x = x;
        self.pos.y = y;
    }

    pub fn set_x(&mut self, x: i64) {
        self.pos.x = x;
    }

    pub fn set_y(&mut self, y: i64) {
        self.pos.y = y;
    }

    pub fn set_heading(&mut self, deg: f64) {
        self.heading = deg.rem_euclid(360.);
    }

    pub fn home(&mut self) {
        self.set_pos(Pos {x: 0, y: 0});
        self.set_heading(0.);
    }
}

// turtle motion queries 
impl Turtle {
    pub fn pos(&self) -> Pos {
        return self.pos;
    }

    pub fn xcor(&self) -> i64 {
        return self.pos.x;
    }

    pub fn ycor(&self) -> i64 {
        return self.pos.y;
    }

    pub fn heading(&self) -> f64 {
        return self.heading;
    }
}

// turtle control
impl Turtle {
    pub fn show_turtle(&mut self) {
        self.visable = true;
    }

    pub fn hide_turtle(&mut self) {
        self.visable = false;
    }

    pub fn wrap(&mut self) {
        self.turtle_mode = TurtleMode::WRAP;
    }

    pub fn window(&mut self) {
        self.turtle_mode = TurtleMode::WINDOW;
    }

    pub fn fence(&mut self) {
        self.turtle_mode = TurtleMode::FENCE;
    }

    pub fn label(&self, text: String) {
        todo!();
    }

    pub fn set_label_height(&self, height: usize) {
        todo!();
    }
}