// MongoDB Playground
// Use Ctrl+Space inside a snippet or a string literal to trigger completions.

// The current database to use.
use("csis3300");

// Find a document in a collection.
// Q. cust_sup collection find the avg days 
// by department for tickets in year 2014

db.cust_sup.aggregate([
    {$match: {"date":/^2015/}},
    {$group: {_id: {"dept": "$department"}, "avg_day": {$avg: "$estimation.days"}}}
])