``` js
db.books
    .find()
    .sort({title: 1}) // 1 -> rosnąco, -1 -> malejąco 
    .skip(2)
    .limit(2)
```

--- 

``` js 
db.books.find({
    "copies.signature": /^84/
})
```