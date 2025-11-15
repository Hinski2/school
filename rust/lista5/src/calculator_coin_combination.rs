pub fn coin_combo(mut cents: u64) -> [u64; 4] {
    let mut coins = [0; 4];
    let value = [1, 5, 10, 25];

    for i in (0..=3).rev() {
        let x = cents / value[i];
        coins[i] = x;
        cents -= x * value[i];
    }

    coins
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t0() {
        assert_eq!(coin_combo(1), [1, 0, 0, 0], "takes 1 and returns, 1 penny");
    }

    #[test]
    fn t1() {
        assert_eq!(coin_combo(2), [2, 0, 0, 0], "takes 2 and returns, 2 penny.");
    }

    #[test]
    fn t2() {
        assert_eq!(coin_combo(5), [0, 1, 0, 0], "takes 5 and returns, 1 nickel.");
    }

    #[test]
    fn t3() {
        assert_eq!(
            coin_combo(6),
            [1, 1, 0, 0],
            "takes 6 and returns, 1 penny, 1 nickel."
        );
    }

    #[test]
    fn t4() {
        assert_eq!(
            coin_combo(10),
            [0, 0, 1, 0],
            "takes 10 and returns, 1 dime."
        );
    }
}

