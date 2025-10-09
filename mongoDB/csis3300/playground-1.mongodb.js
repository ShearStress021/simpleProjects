// MongoDB Playground
// Use Ctrl+Space inside a snippet or a string literal to trigger completions.

// The current database to use.
use("csis3300");

// Find a document in a collection.
// group by status and find the average

db.users.aggregate([
    {$match: {"status": {$exists : true}}},
    {$group: {_id: '$status', 'average': {$avg: "$age"}}},
    {$sort: {"status": -1}}
])