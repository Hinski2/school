const readline = require('readline');

async function getInput(){
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout,
    });

    return new Promise((resolve, reject) => {
        rl.question('input your guess: ', (user_input) => {
            rl.close();
            try{
                if(isNaN(parseFloat(user_input)))
                    throw 'not valid number'

                let user_number = Number(user_input)
                resolve(user_number);
            }
            catch(error){
                console.log(error)
                return resolve((async() => await getInput())())
            }
        });
    });
}

(async function main(){
    let continue_game = true;
    let random_number = Math.floor(Math.random() * 101);

    while(continue_game){
        try{
            const user_number = await getInput();
            if(user_number == random_number){
                console.log('your number is correct')
                continue_game = false;
            }
            else if(user_number < random_number)
                console.log('your number is too small')
            else 
                console.log('your number is too big')
        }
        catch(error){
            console.log(error)
        }
    }
})()
