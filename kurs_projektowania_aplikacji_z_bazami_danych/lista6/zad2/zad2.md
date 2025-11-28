### books 

``` js
{
    _id: Number 
    isbn: String
    title: String,
    author: String, 
    year: Number,
    price: Number, 
    lastMontBorrowed: Boolean
    copies: [
        {
            signature: String
        }
    ]
}
```

### readers 

``` js 
{
    _id: Number,
    pesel: String, 
    surname: String, 
    city: String, 
    birthDate: Date,
    lastBorrowing: Date
}
```

### borrowinds 
``` js
{ 
    readerId: Number, 
    bookId: Number,
    signature: String, 
    borrowData: Date, 
    returnDate: Date | null
}
```

--- 
``` js
db.books.insertMany([
    {
        _id: 1, 
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
    },
    {
        _id: 2, 
        isbn: "34938493894839", 
        title: "lalka",
        author: "bolesław prus",
        year: 1899, 
        price: 42.42,
        lastMonthBorrowed: true,
        copies: [
            {signature: "844983984938"},
            {signature: "844983984939"}
        ]
    },
    {
        _id: 3, 
        isbn: "44938493894839", 
        title: "folwark zwierzęcy",
        author: "george orwel",
        year: 1984, 
        price: 42.42,
        lastMonthBorrowed: false,
        copies: [
            {signature: "944983984938"},
            {signature: "944983984939"}
        ]
    }
])

```

``` js
db.readers.insertMany([
    {
        _id: 1,
        pesel: "439839843",
        surname: "kowalski",
        city: "wrocław",
        birthDate: ISODate("1990-01-01"),
        lastBorrowing: ISODate("2025-11-20")
    },
    {
        _id: 2,
        pesel: "449839843",
        surname: "iliński",
        city: "wrocław",
        birthDate: ISODate("2004-12-20"),
        lastBorrowing: ISODate("2025-11-20")
    },
])
```

``` js 
db.borrowings.insertMany([
    {
        readerId: 1,
        bookId: 1,
        signature: "844983984938",
        borrowDate: ISODate("2025-11-20"),
        returnDate: null
    },
    {
        readerId: 2,
        bookId: 2,
        signature: "844983984939",
        borrowDate: ISODate("2025-11-20"),
        returnDate: null
    },
    {
        readerId: 2,
        bookId: 3,
        signature: "944983984939",
        borrowDate: ISODate("2025-11-20"),
        returnDate: null
    },
    {
        readerId: 3,
        bookId: 3,
        signature: "944983984938",
        borrowDate: ISODate("2025-11-20"),
        returnDate: null
    }
])
```