// MongoDB Playground
// Use Ctrl+Space inside a snippet or a string literal to trigger completions.

// The current database to use.
use("csis3300");

// Find a document in a collection.
//  In users collection find number of users by 
// status for the users who joined in 2013.

db.users.aggregate([
    {$match: {"join_date": /^2013/}},
    {$group: {_id: "$status", "count": {$sum: 1}}},
    
])
