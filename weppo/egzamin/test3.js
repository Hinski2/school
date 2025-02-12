var Foo = (() => {
    function Qux(){
        console.log("wywołanie Qux")
    }

    function Foo(){ // konstruktor Foo
    }
    
    Foo.prototype.Bar = function() {
        Qux();
    }

    return Foo // zwracam konstruktor Foo
})();

const foo = new Foo();
// foo.Bar()
// foo.Qux()

const readline = require('readline')

async function getInput(){
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout,
    });

    return new Promise((resolve, reject) => {
        rl.question('input your name: ', (userInput) => {
            rl.close();
            resolve(userInput);
        });
    });
}

(async function main(){
    try{
        const user_input = await getInput();
        console.log(`witaj ${user_input}`);
    } catch (e) {
        console.log(e)
    };

})()

fs = require('fs')

async function readFile(path){
    try{
        const file = fs.promises.readFile(path, 'utf8');
        console.log(file)
    } catch (e){
        console.log(e)
    }
}


