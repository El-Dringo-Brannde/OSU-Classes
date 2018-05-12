# Select Statement
- Clauses of the Select Statement
- Select
  - List the columns to be returned
- From
  - What table to choose from
- Where
  - Indicate conditions which row will be chosen
- Group by
  - indicate categorized results
  - Like a where clause, but it operates on groups, not individual rows.
- Having
  - Indicate the condition under which a group will be included
- Order by
  - Sorts the result by criteria

## SQL example
- Find the names of sailors who have reserved both a red and green boat
```SQL
SELECT S.sname;
From Sailors S, Reserves R1, Reserves R2, Boats B1, Boats B2;
Where S.sid = R1.sid AND R1.bid = B1.bid AND B1.color = 'red'AND S.sid = R2.sid AND R2.bid = B2.bid AND B2.color = 'green';
```
