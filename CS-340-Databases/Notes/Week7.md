
# Relational Algebra
#### Selection
- ø: Selects a subset of rows from relation

#### Projection  
- π: Deletes unwanted columns from relation
- Also removes duplicates

#### Natural-Join
- x: Allows us to combine two relations
  - Kinda like a.ID = b.ID

#### Set-Difference
- '-': Tuples in relation 1 but not relation 2

#### Union
- U: Tuples in relation 1 and in relation 2

# Projection Example
- π sname,rating(S2)
  - Would choose all the names and ratings from table S2

# Selection Example
- ø rating > 8 (S2)
  - returns everything from everyone who has a rating over 8

- π sname,rating(ø rating > 8 (S2))

# Find names of sailors who reserve boat #103
- π sname((ø bid = 103 (Reserves)) x Sailors )

## Find names of sailors who reserved a red boat
- π sname((ø color = 'red' BOATS) x Reserves x Sailors)

## Find sailors who've reserved a red and a green boat
- P(Tempred, π sid((ø color = 'red' (BOATS)) X Reserves ))
- P(Tempgreen, π sid ((ø color = 'green' (BOATS)) X Reserves))
- π sname ((Tempred AND Tempgreen) X Sailors)

## Find the names of sailors who've reserved all boats
- P(Tempsids, (π sid,bid(RESERVES) /(π bid (BOATS))
- π sname(Tempsids X Sailors)

## Using SQL for same statement
```SQL
Select S.sname
From Sailors S
Where not exists (Select B.bid
                  From Boats B
                  Where not exists (Select R.bid
                                    From Reserves R
                                    Where R.bid=B.bid AND R.sid = S.sid))
```
