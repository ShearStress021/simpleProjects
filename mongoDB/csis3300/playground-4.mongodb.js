// MongoDB Playground
// Use Ctrl+Space inside a snippet or a string literal to trigger completions.

// The current database to use.
use("csis3300");

// Find a document in a collection.
// Q2b: [SQL] Select province, city, count(province) as count
// 	from users
// 	group by province, city
//   order by province, city

db.users.aggregate(
    
    {$match: {"address.province": {$exists: true}}},
    {$match: {"address.city": {$exists: true}}},
    {$group: {_id: {"province": "$address.province", "city": "$address.city"}}},
    {$sort: {"_id.province": 1, "_id.city": 1}} 
)