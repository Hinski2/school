import 'dotenv/config'
import neo4j from 'neo4j-driver'

import {read, create_node, create_relation, update, delete_node, delete_relation} from './crud.js'
import {handle_input} from './handle_input.js'

async function init() {
    const { Uri, Password, User } = process.env; // nie robimy skill issue i nie zapisujemy tego w kodzie na sztywno

    if(!Uri || !User || !Password) {
        console.error("błąd: brakuje .env lub jest źle zapisany");
        process.exit(1);
    }

    const driver = neo4j.driver( // logowanie do bazy
        Uri,
        neo4j.auth.basic(User, Password),
    )

    return driver
}

async function main() {
    const driver = await init(); // inicjujemy baze danych

    while (true) {
        const input = await handle_input(); // wczytujemy input od usera

        /*
            input ma pola { // w zależności od operacji
                status,
                node1,
                node2
                relation, 
                property_key
                property_val
                error // jeśli wystąpi => status = error
            }

        */

        const output = await { 
                "exit": () => process.exit(0),
                "error": () => {
                    console.error(input.error);
                    process.exit(1)                
                },
                "read": async () => await read(input, driver),
                "create_node": async () => await create_node(input, driver),
                "create_relation": async () => await create_relation(input, driver),
                "update": async () => await update(input, driver),
                "delete_node": async () => await delete_node(input, driver),
                "delete_relation": async () => await delete_relation(input, driver),
        }[input.status](); // wywolujemy odpowiednią funkcje

        console.log(output); 
    }
}

main();