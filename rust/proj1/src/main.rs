use std::error::Error;

use proj1::view::image::Image;
use proj1::utils::env::Config;

fn main() -> Result<(), Box<dyn Error>> {
    let config = Config::new()?;
    let img = Image::new(config.x, config.y); 

    img.write_to_file(&config.img_path)?;
    println!("Your fractal is ready and saved in {} dir. You can open it with viu", &config.img_path);
    Ok(())
}
