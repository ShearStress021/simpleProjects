// MongoDB Playground
// Use Ctrl+Space inside a snippet or a string literal to trigger completions.

// The current database to use.
use("csis3300");

// Find a document in a collection.
// Q2: [SQL] Select province, count(province) as count
// 	from users
//   group by province
//   order by count desc

db.users.aggregate([
    {$match: {"address.province": {$exists: true}}},
    {$group: {_id: {"province": "$address.province"}, "ProvCount": {$sum: 1}}},
    {$sort: {"ProvCount": -1}}
])