// MongoDB Playground
// Use Ctrl+Space inside a snippet or a string literal to trigger completions.

// The current database to use.
use("csis3300");

// Find a document in a collection.
db.sales.find({
    "category": "vip",
    "sales.product_total": {$gte: 500}
})