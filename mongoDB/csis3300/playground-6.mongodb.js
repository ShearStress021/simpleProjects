// MongoDB Playground
// Use Ctrl+Space inside a snippet or a string literal to trigger completions.

// The current database to use.
use("csis3300");

// Find a document in a collection.
// Q: Overall average of product_qty 
// for the entire collection

db.sales.aggregate([
    {$group: {_id: null, "avg_qty": {$avg: "$sales.product_qty"}}}
])
