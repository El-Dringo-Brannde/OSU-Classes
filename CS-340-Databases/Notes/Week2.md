# Database Schema

Database Schema
  Description of Database
Schema Diagram
  Illustrative display of Database Schema

Database schema almost never changes, Database state changes constantly

Internal Schema - Physical storage structures and indexes

Conceptual Schema - Describes structure of DB and constraints on data

External Schema - Describe user views
```{mermaid}
graph TD;
a --> b;
```
Logical Data independence - Ability to change conceptual schema and not worry
about external schema

Physical Data Independence - Able to change Internal schema, without changing
Conceptual
# DBMS
DBMS Programming Language interface
  - Interface a DBS language into another language
  - Embedded: Extensions to C/C++,Java
  - Proc call: Use of DBS in API's for a programming language
  - Scripting Languages: PHP & Python


Centralized DBMS
  DBMS software, Hardware, programs, UI
    User just connects via ssh from remote terminal

# architecture
Two tier architecture just connects a client to a server via a network

Three tier architecture increases security so that the client can't directly access the
server


# Data Models
- concepts to describe the structure of a database, operations to manipulate the structures, and the constraints that they should obey
### Network Model
- First implementation of DBMS
- Can handle most models using record/Relationship types
- But the database has array of pointers that go through records

### Hierarchal model
- Made by IBM
- Simple to construct and operate
- DB is visualized as linear records

### OO Data models
- Mixed well with OO programming languages

### Relational model
- Main concept:
  - A relation is just a table with rows and columns
  - Every relation has a schema which describes the columns
#### How is relational data represented?
Three levels of abstraction

```{mermaid}
graph TD;
External_Schema --> Conceptual_Schema;
Conceptual_Schema --> Physical_Schema;
```

# Database design
## conceptual design  
- ER models are used here
  - tells the constraints and attributes of a database

- ER model basics
  - Entity: object disinguishable from other objects
    - Each Entity has a key
    - Each attribute has a domain
  - Attribute: Property of an object 
  - Relationship: Association among two or more entities
### DDL (Data definition language )
- Defines Data structures of Database Schema
  - Such as MySQL (Although High level )
