// https://neo4j.com/docs/javascript-manual/current/ dokumentacja dla js

import 'dotenv/config'
import neo4j from 'neo4j-driver'

async function main() {
    const { Uri, Password, User } = process.env; // nie robimy skill issue i nie zapisujemy tego w kodzie na sztywno

    if(!Uri || !User || !Password) {
        console.error("błąd: brakuje .env lub jest źle zapisany");
        process.exit(1);
    }

    const driver = neo4j.driver( // logowanie do bazy
        Uri,
        neo4j.auth.basic(User, Password),
    )

    const db = driver.session();

    try {
        const res = await db.run("match (p:Person) return p")
        for(let record of res.records) {
            console.log(record.get('p').properties)
        }
        
    } catch (err) {
        console.error("błąd: {}", err)
    } finally {
        await db.close();
        await driver.close();
    }
}

main();