# Relational Model

-  Started in 1970

### Informal Definition
- A relation is really just a table of values
- Each row has a value of a data item that uniquely identifies that row in the table
  - AKA the key

### Key Constraint
- No key can share values
### Entity Integrity constraint
- Primary keys can not have a NULL value in any PK tuple
### Referential Integrity constraint
- The value of the PK in a foreign table is referenced from another table as the FK

## What to do if a Referential Integrity deletes
- Restrict
  - Don't delete the parent if there are foreign keys hooked onto the primary key
- Cascade
  - Auto Delete dependent side rows that rely on the parent
- Set to NULL
  - Set FK to NULL if parent is Deleted

# Data Normalization
 - A tool that tries to avoid unnecessary duplication of data
 - 1st NF
   - Remove Partial Dependencies
 - 2nd NF
   - Remove Transitive Dependencies
 - 3rd NF
   - Remove remaining anomalies from multiple candidate keys
### First NF
 - Take out
    - Composite attributes
    - Multivalued attributes
    - nested relations
### Second NF
  - Take out
    - Every non key attribute is functional on the entire primary key
  - So you break up rows/schema based on multiple PK's in each 1st NF row
### Third NF
  - Remove transitive dependencies
    - each non essential attributes points to new schema as a FK with a PK in the new row
## Informal Definitions
- 1st NF
  - All attributes depend on the key
- 2nd NF
  - All attributes depend on the __whole__ key
- 3rd NF
  - All attributes depend on __nothing but the key__ 
