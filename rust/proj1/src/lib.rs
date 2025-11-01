pub mod utils;
pub mod view;

#[cfg(test)]
mod tests {
    use crate::utils::{env::Config, linspace::Linspace};
    use super::*;

    fn test_config(config: Config) {
        let mut img = view::image::Image::new(config.x, config.y, config.max_itr); 
        if config.r > 1 {
            img.smooth(config.r, config.passes);
        }

        img.write_to_file(&config.img_path).unwrap();
    }

    #[test]
    fn test1() {
        // create config
        let x = Linspace::new(-2.0, 2.0, 2000).unwrap();
        let y = Linspace::new(-1.5, 1.5, 2000).unwrap();
        let img_path: String = "img/test/test1.bmp".to_string();
        let max_itr = 100;
        let r = 1; 
        let passes = 1;

        let config = utils::env::Config {x, y, img_path, max_itr, r, passes};
        test_config(config);
    }

    #[test]
    fn test2() {
        // create config
        let x = Linspace::new(-2.0, 2.0, 2000).unwrap();
        let y = Linspace::new(-1.5, 1.5, 2000).unwrap();
        let img_path: String = "img/test/test2.bmp".to_string();
        let max_itr = 250;
        let r = 1;
        let passes = 1;

        let config = utils::env::Config {x, y, img_path, max_itr, r, passes};
        test_config(config);
    }

    #[test]
    fn test3() {
        // create config
        let x = Linspace::new(-2.0, 2.0, 2000).unwrap();
        let y = Linspace::new(-1.5, 1.5, 2000).unwrap();
        let img_path: String = "img/test/test3.bmp".to_string();
        let max_itr = 1000;
        let r = 1;
        let passes = 1;

        let config = utils::env::Config {x, y, img_path, max_itr, r, passes};
        test_config(config);
    }

    #[test]
    fn test4() {
        // create config
        let x = Linspace::new(-2.0, 2.0, 1920).unwrap();
        let y = Linspace::new(-1.5, 1.5, 1080).unwrap();
        let img_path: String = "img/test/test4.bmp".to_string();
        let max_itr = 250;
        let r = 1;
        let passes = 1;

        let config = utils::env::Config {x, y, img_path, max_itr, r, passes};
        test_config(config);
    }

    #[test]
    fn test5() {
        // create config
        let x = Linspace::new(-1.0, 2.0, 1920).unwrap();
        let y = Linspace::new(-0.5, 0.5, 1080).unwrap();
        let img_path: String = "img/test/test5.bmp".to_string();
        let max_itr = 250;
        let r = 1;
        let passes = 1;

        let config = utils::env::Config {x, y, img_path, max_itr, r, passes};
        test_config(config);
    }

    #[test]
    fn test6() {
        // create config
        let x = Linspace::new(-2.0, 2.0, 4000).unwrap();
        let y = Linspace::new(-1.5, 1.5, 4000).unwrap();
        let img_path: String = "img/test/test6.bmp".to_string();
        let max_itr = 100;
        let r = 1;
        let passes = 1;

        let config = utils::env::Config {x, y, img_path, max_itr, r, passes};
        test_config(config);
    }

    #[test]
    fn test7() {
        // create config
        let x = Linspace::new(-2.0, 2.0, 2000).unwrap();
        let y = Linspace::new(-1.5, 1.5, 2000).unwrap();
        let img_path: String = "img/test/test7.bmp".to_string();
        let max_itr = 100;
        let r = 2; 
        let passes = 1;

        let config = utils::env::Config {x, y, img_path, max_itr, r, passes};
        test_config(config);
    }

    #[test]
    fn test8() {
        // create config
        let x = Linspace::new(-2.0, 2.0, 2000).unwrap();
        let y = Linspace::new(-1.5, 1.5, 2000).unwrap();
        let img_path: String = "img/test/test8.bmp".to_string();
        let max_itr = 100;
        let r = 2; 
        let passes = 2;

        let config = utils::env::Config {x, y, img_path, max_itr, r, passes};
        test_config(config);
    }

    #[test]
    fn test9() {
        // create config
        let x = Linspace::new(-2.0, 2.0, 2000).unwrap();
        let y = Linspace::new(-1.5, 1.5, 2000).unwrap();
        let img_path: String = "img/test/test9.bmp".to_string();
        let max_itr = 100;
        let r = 3; 
        let passes = 1;

        let config = utils::env::Config {x, y, img_path, max_itr, r, passes};
        test_config(config);
    }

}
