
pub fn open_or_senior(data: Vec<(i32, i32)>) -> Vec<String> {
    data.iter()
        .map(|item| {
            match item {
                (years, handicap) if *years >= 55 && *handicap > 7 => "Senior".to_string(),
                _ => "Open".to_string(),
            }
        })
        .collect()
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test1() {
        assert_eq!(open_or_senior(vec![(45, 12), (55,21), (19, -2), (104, 20)]), vec!["Open", "Senior", "Open", "Senior"]);
    }

    #[test]
    fn test2() {
        assert_eq!(open_or_senior(vec![(3, 12), (55,1), (91, -2), (54, 23)]), vec!["Open", "Open", "Open", "Open"]);
    }

    #[test]
    fn test3() {
        assert_eq!(open_or_senior(vec![(3, 12)]), vec!["Open"]);
    }

    #[test]
    fn test4() {
        assert_eq!(open_or_senior(vec![(55, 7)]), vec!["Open"]);
    }

    #[test]
    fn test5() {
        assert_eq!(open_or_senior(vec![(55, 8)]), vec!["Senior"]);
    }
}


