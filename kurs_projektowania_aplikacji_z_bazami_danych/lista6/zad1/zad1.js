/* 
    run the server: systemctl start mongodb
    test: systemctl status mongodb
    shell: mongosh
    available databases query: show dbs
*/ 

import { MongoClient } from "mongodb";

async function run_db() {
    let client = new MongoClient("mongodb://localhost:27017")

    try {
        await client.connect();

        let db = client.db("library");
        let books = db.collection("books");
        let all_books = await books.find().toArray();
        console.log(all_books.map(b => b.author));

    } catch (err) {
        console.error("error: ", err);
    } finally {
        await client.close();
    }
}

run_db()