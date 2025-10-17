// MongoDB Playground
// Use Ctrl+Space inside a snippet or a string literal to trigger completions.

// The current database to use.
use("csis3300");

// Find a document in a collection.
// Find all users from the 
// city "Shinyanga" or "Oyem" who 
// purchased products 
// from the "Grocery" category:
db.sales.find({
    "address.city": {$in: ["Shinyanga","Oyem"]},
    "sales.product_category": "Grocery"
});
