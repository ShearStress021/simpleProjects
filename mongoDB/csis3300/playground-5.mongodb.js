// MongoDB Playground
// Use Ctrl+Space inside a snippet or a string literal to trigger completions.

// The current database to use.
use("csis3300");

// Find a document in a collection.
// Q: Group sales by province in the western provinces, 
// sort by sales amount descending
// BC, AB, SK, MB
db.sales.aggregate([
    {$match: {"address.province": {$in:["BC","AB","SK","MB"]}}},
    {$group: {_id: {"province": "$address.province"}, "Total_sales":{$sum: "$sales.product_total"}}},
    {$sort: {"Total_sales": -1}}
])
