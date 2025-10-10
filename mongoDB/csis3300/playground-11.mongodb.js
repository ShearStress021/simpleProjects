// MongoDB Playground
// Use Ctrl+Space inside a snippet or a string literal to trigger completions.

// The current database to use.
use("csis3300");

// Find a document in a collection.
// : In users collection find average age 
// of users by status for the users who joined in 2013

db.users.aggregate([
    {$match: {'join_date': /^2012/}},
    {$group: {_id: "$status", "avg_age": {$avg: "$age"}}},
    {$sort: {"avg_age": -1}}
])
