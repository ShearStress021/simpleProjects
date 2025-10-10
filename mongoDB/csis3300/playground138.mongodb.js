// MongoDB Playground
// Use Ctrl+Space inside a snippet or a string literal to trigger completions.

// The current database to use.
use("csis3300");

// Find a document in a collection.
// Q: Find the avg losses by games code for
//  users with active status and
//  who logged in in the years 2014 or 2016
// Hint: you have to use $unwind
//  before you can do group.
db.games.aggregate([
    {$unwind: "$games"},
    {$match: {"status": {$eq: "active"}}},
    {$match: {"last_login_date": {$in:[/^2014/, /^2016/]}}},
    {$group: {_id: "$games.code", "avg_losses": {$avg: "$games.losses"}}}
    {$sort: {"games.code": -1}}
])