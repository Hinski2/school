const fs = require('fs')
const rl = require('readline')

function parse_file(path){
    let data = new Map();
    return new Promise((resolve, reject) => {
        const fileStream = fs.createReadStream(path);
        const readline = rl.createInterface({
            input: fileStream 
        });

        readline.on('line', (line) => {
            let ip = line.split(' ')[1];
            if(data.has(ip))
                data.set(ip, data.get(ip) + 1);
            else 
                data.set(ip, 1);
        });

        readline.on('close', () => {
            resolve(data);   
        });

        readline.on('error', (err) => {
            reject(err);
        });
        
        fileStream.on('error', (err) => {
            reject(err);
        });
    });
}

(async function main(){
    try{
        data = await parse_file('./logs.txt');
    }
    catch(err){
        console.log(err)
    }

    arr = []
    for(let u of data)
        arr.push(u)

    arr.sort((a, b) => b[1] - a[1]) //descenting order
    arr.splice(3); // or let top3 = arr.slice(0, 3)
    arr.forEach((u) => console.log(u))
})();