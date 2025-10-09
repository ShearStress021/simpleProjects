// MongoDB Playground
// Use Ctrl+Space inside a snippet or a string literal to trigger completions.

// The current database to use.
use("csis3300");

// Find a document in a collection.
// Q: from users collection, find avg age 
// of users who joined in year 2012

db.users.aggregate([
    {$match: {"join_date": /^2012/}},
    {$group: {_id: null, "avg_age": {$avg: "$age"}}}
])
