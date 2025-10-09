// MongoDB Playground
// Use Ctrl+Space inside a snippet or a string literal to trigger completions.

// The current database to use.
use("csis3300");

// Find a document in a collection.
// Q.   Avg number of wins by games.code


db.games.aggregate([
    {$unwind: "$games"},
    {$group: {_id: {"code": "$games.code"}, "avg_wins":{$avg: "$games.wins"}}}
])
