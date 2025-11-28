db.books.aggregate([
  {
    $group: {
      _id: "$author",
      totalBooks: { $sum: 1 }
    }
  }
]);
``` js 
db.books.aggregate([
    {
        $group: {
            _id: "$author", 
            booksSum: {$sum: 1}
        }
    }
])
```