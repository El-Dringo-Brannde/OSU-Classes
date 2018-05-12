# Physical data independence
  The way data is actually stored on a disk,
  independent of how the program thinks about the structure of the data

# MySQL – (MariaDB) Database
- Web access http://mysql.cs.orst.edu
- use cs340<your ONID user name>
- Default pw is the last 4 digits of their OSU ID number


### languages used to build web pages
PHP - Server-side Scripting, gets rendered first
HTML/CSS/JS - All client side



```{mermaid}
graph TD;
Users/Programmers --> DBSQueries/Programs;
DBSQueries/Programs --> DBMS(Process queries);
DBMS(Process queries) --> DBMS(Access Query data);
DBMS(Access Query data) --> actual-DB-data;
```
A DBMS should be able to handle multiple users at once and allow them to
Retrieve, alter, or access the data in the database.


## User types of a DB
#### Actors on the scene
 - Database administrators, Database designers (Maintenance, design, control etc)
#### Actors behind the scene
- System designers, Tool developers, Maintenance


#### End users
 - Casual: access DB occasionally
 - naive: power users (mobile people)
 - Sophisticated: Know limits of DB and rely on packages that use DB
 - Stand alone: Use DB internally that doesn't really connect from outside network, Tax programs, media files
