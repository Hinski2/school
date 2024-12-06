const https = require('https');

function get_site_content(url){
    return new Promise((resolve, reject) => {
        https.get(url, (resp) => {
            let data = '';

            resp.on('data', (chunk) => { // zdarzenie data
                data += chunk;
            })

            resp.on('end', () => {
                resolve(data)
            })

            resp.on('error', (error) => {
                reject(error)
            })
        });
    });
}

(async function main(){
    try{
        const file_content = await get_site_content('https://nodejs.org/api/https.html#httpsgeturl-options-callback')
        console.log(file_content)
    }
    catch(err){
        console.log(err)
    }
})()

