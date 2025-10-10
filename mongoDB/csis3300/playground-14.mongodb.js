// MongoDB Playground
// Use Ctrl+Space inside a snippet or a string literal to trigger completions.

// The current database to use.
use("csis3300");

// Find a document in a collection.
// Q. In cust_sup, Find avg estimation days
//  by department by estimation effort when the cost was > 500
// Hint: You can do two group by, in the _id separated by comma 

db.cust_sup.aggregate([
    {$match: {"estimation.cost": {$gt: 500}}},
    {$group :{_id: {"dept": "$department", "enst": "$estimation.effort"}, "avg_days": {$avg: "$estimation.days"}}},
    
])