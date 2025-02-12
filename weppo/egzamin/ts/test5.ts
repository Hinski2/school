function filter<T>(arr: T[], f: (n: T) => boolean): T[] {
    let ans: T[] = [];
    for(let u of arr)
        if(f(u)) ans.push(u);

    return ans;
}

function map<T, K>(arr: T[], f: (n: T) => K): K[] {
    let ans = new Array<K>();
    for(let i in arr)
        ans[i] = f(arr[i]);

    return ans;
}

function for_each<T>(a: T[], f:(t: T) => void): void {
    for(let u of a)
        f(u)
}

let x = filter([1, 3, 4, 5, 2], (n: number): boolean => (n % 2 == 0));
let y = map([1, 3, 4, 5, 2], (n: number): boolean => n % 2 == 0);
// console.log(y)

