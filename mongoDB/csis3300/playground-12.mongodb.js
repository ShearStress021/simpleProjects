// MongoDB Playground
// Use Ctrl+Space inside a snippet or a string literal to trigger completions.

// The current database to use.
use("csis3300");

// Find a document in a collection.
// In students collection find the average 
// grade (grade) by enrollment_sem . 
db.students.aggregate([
    {$unwind: "$terms"},
    {$unwind: "$terms.courses"},
    {$match: {"enrollment_sem": {$exists: true}}},
    {$group: {_id: {"enroll_sem": "$enrollment_sem"}, 
    "avg_grade": {$avg: "$terms.courses.grade"}}}

])