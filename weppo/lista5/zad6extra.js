const fs = require('fs')

function getnerate_log(){
    function generate_time(){
        let hour = Math.floor(Math.random() * 24).toString();
        let min = Math.floor(Math.random() * 60).toString();
        let sec = Math.floor(Math.random() * 60).toString();
        return [hour, min, sec].join(':');
    }
    
    function generate_ip(){
        return `192.168.0.${Math.floor(Math.random() * 999)}`;
    }

    function generate_resource(){
        const arr = ['/index.html', '/TheApplication/WebResource.axd', '/api', '/contact']
        return arr[Math.floor(Math.random() * arr.length)];
    }

    function generate_status(){
        return Math.floor(Math.random() * 900);
    }

    time_str = generate_time();
    ip = generate_ip();
    method = 'GET'
    resorce = generate_resource();
    conection_status = generate_status()

    return [time_str, ip, method, resorce, conection_status].join(' ');
}

(function main(){
    const content = []
    for(let i = 0; i < 1000000; i++)
        content.push(getnerate_log())

    log_file = content.join('\n');

    fs.writeFile('./logs.txt', log_file, err => {
        if (err) {
            console.error(err);
        } else {
            console.log('ok');
        }
    });
   
})()


