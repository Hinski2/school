pub struct Cipher {
    map1: Vec<char>,
    map2: Vec<char>,
}

impl Cipher {
  pub fn new(map1: &str, map2: &str) -> Cipher {
      Cipher {map1: map1.chars().collect(), map2: map2.chars().collect()}
  }
  
  pub fn encode(&self, string: &str) -> String {
      string.chars()
          .map(|c| {
              if let Some(i) = self.map1.iter().position(|pos| *pos == c) {
                  self.map2[i]
              } else {
                  c
              }
          })
          .collect()
  }
  
  pub fn decode(&self, string: &str) -> String {
      string.chars()
          .map(|c| {
              if let Some(i) = self.map2.iter().position(|pos| *pos == c) {
                  self.map1[i]
              } else {
                  c
              }
          })
          .collect()
  }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test1() {
          let map1 = "abcdefghijklmnopqrstuvwxyz";
          let map2 = "etaoinshrdlucmfwypvbgkjqxz";

          let cipher = Cipher::new(map1, map2);
          
          assert_eq!(cipher.decode("erlang"), "aikcfu");
    }


    #[test]
    fn test2() {
          let map1 = "abcdefghijklmnopqrstuvwxyz";
          let map2 = "etaoinshrdlucmfwypvbgkjqxz";

          let cipher = Cipher::new(map1, map2);
          assert_eq!(cipher.encode("xyz"), "qxz");
    }

    #[test]
    fn test3() {
          let map1 = "abcdefghijklmnopqrstuvwxyz";
          let map2 = "etaoinshrdlucmfwypvbgkjqxz";

          let cipher = Cipher::new(map1, map2);
          assert_eq!(cipher.decode("eirfg"), "aeiou");
    }

    #[test]
    fn test4() {
          let map1 = "abcdefghijklmnopqrstuvwxyz";
          let map2 = "etaoinshrdlucmfwypvbgkjqxz";

          let cipher = Cipher::new(map1, map2);
          assert_eq!(cipher.encode("abc"), "eta");
    }
 
    #[test]
    fn test5() {
          let map1 = "abcdefghijklmnopqrstuvwxyz";
          let map2 = "etaoinshrdlucmfwypvbgkjqxz";

          let cipher = Cipher::new(map1, map2);
          assert_eq!(cipher.encode(";"), ";");
    }
}
