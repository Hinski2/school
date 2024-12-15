const fs = require('fs')

async function readfile(path){
    try{
        const file = await fs.promises.readFile(path, 'utf8');
        console.log(file);
    }
    catch(error){
        console.log('ERROR:', error);
    }
}

readfile('./file_to_read.txt');