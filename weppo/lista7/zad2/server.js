const fs = require('fs');
const https = require('https');

(async function() {
    const pfx = await fs.promises.readFile('./certificate.pfx')     // load our certificate
    const server = https.createServer(
        {
            pfx: pfx,
            passphrase: "test"
        },
        (req, res) => {
            res.setHeader('Content-type', 'text/html; charset=utf-8');
            res.end(`hi ${new Date()}`);
        }
    );

    server.listen(3000);
    console.log('started')


})();
