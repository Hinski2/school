const readline = require('readline');

async function getInput(){
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout,
    });

    return new Promise((resolve, reject) => {
        rl.question('input your name: ', (user_input) => {
            rl.close();
            resolve(user_input);
        });
    });
}

(async function main(){
    try{
        const user_input = await getInput();
        console.log(`Witaj ${user_input}`)
    }
    catch(error){
        console.log(error)
    }
})()
