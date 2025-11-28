``` js
db.runCommand({
    collMod: "books",
    validator: {
        $jsonSchema: {
            bsonType: "object",
            required: ["_id", "isbn", "title", "author", "year", "price", "lastMonthBorrowed", "copies"],
            properties: {
                _id: {},
                isbn: {bsonType: "string"},
                title: {bsonType: "string"},
                author: {bsonType: "string"},
                year: {bsonType: "int"},
                price: {bsonType: "double"},
                lastMonthBorrowed: {bsonType: "bool"},
                copies: {

                    bsonType: "array",
                    minItems: 1, 
                    items: {
                        bsonType: "object",
                        required: ["signature"],
                        properties: {
                            signature: {bsonType: "string"}
                        }
                    }

                }
            }
        }
    },
    validationLevel: "strict",
    validationAction: "error"
})
```

``` js
db.runCommand({
    collMod: "readers", 
    validator: {
        $jsonSchema: {
            bsonType: "object",
            required: ["pesel", "surname", "city", "birthDate", "lastBorrowing"],
            properties: {
                _id: {}, 
                pesel: {
                    bsonType: "string", 
                    pattern: "^[0-9]{11}$"
                },
                surname: {bsonType: "string"},
                city: {bsonType: "string"},
                birthDate: {bsonType: "date"},
                lastBorrowing: {bsonType: "date"}
            }
        }
    },
    validationLevel: "strict",
    validationAction: "error"
})
```

``` js 
db.runCommand({
    collMod: "borrowings", 
    validator: {
        $jsonSchema: {
            bsonType: "object",
            required: ["readerId", "bookId", "signature", "borrowDate"],
            properties: {
                _id: {}, 
                readerId: {bsonType: "int"},
                bookId: {bsonType: "int"},
                signature: {bsonType: "string"},
                borrowDate: {bsonType: "date"},
                returnDate: {bsonType: ["date", "null"]}
            }
        }
    },
    validationLevel: "strict",
    validationAction: "error"
})
```

--- 

``` js 
db.books.insertOne({
    _id: 42, 
    isbn: "34938493894839", 
    title: "Nowy wspaniały świat",
    author: "aldous haxley",
    year: 1999, 
    price: 42.42,
    lastMonthBorrowed: true,
    copies: [
        {signature: "843983984938"},
        {signature: "843983984939"}
    ]
})
```

``` js
db.readers.insertOne({
    _id: 42,
    pesel: "43983984399",
    surname: "kowalski",
    city: "wrocław",
    birthDate: ISODate("1990-01-01"),
    lastBorrowing: ISODate("2025-11-20")
})
```

``` js
db.borrowings.insertOne({
    readerId: 1,
    bookId: 1,
    signature: "844983984938",
    borrowDate: ISODate("2025-11-20"),
    returnDate: null
})
```

--- 

``` js 
db.readers
    .find()
    .forEach(doc => {
        try {
            db.readers.updateOne(
                {_id: doc._id},
                {$set: {
                    pesel: doc.pesel,
                    surname: doc.surname,
                    city: doc.city,
                    birthDate: doc.birthDate,
                    lastBorrowing: doc.lastBorrowing
                }}
            );
            print("ok")
        } catch {
            print("err")
        }
    })
```