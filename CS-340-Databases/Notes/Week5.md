# Advanced SQL

## Select from multiple tables
- The easy way
```SQL
  Select * from Student, Grade, Course ;
  Where Student.ID = Grade.ID;
  AND Course.Code = Grade.Code;
```
- The different types of join
  - A Cross join B
    - Returns all pairs of rows from A and B
  - A Natural Join B
    - Returns pairs of rows with common values for identical named columns without duplicating columns
    - Good for just tacking on an extra row and not having duplicate columns
    - Kinda the same as `A.id = B.id`
  - A inner join B
    - returns pairs of rows satisfying a condition

### Aliases
- Selecting an attribute and renaming it with `AS`

### Subqueries 
- Select statements can be nested inside eachother
  - Subquery is executed first, and past back to the first select
### Aggregate functions
- Count
  - Count # of rows
- Sum
  - Sum of entries in a column
- AVG
  - Avg entry in a column
- Min/Max
  - Min and max entries of a column

## Where vs. Having
- Where refers to the rows of tables
  - Can't use aggregate functions
- Having refers to groups of rows
