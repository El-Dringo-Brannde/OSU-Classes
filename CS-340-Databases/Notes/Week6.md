# Views
- Virtual table of a select statement
- Grabs employees who make more than the manager
```SQL
SELECT E.FNAME, E.LNAME FROM EMPLOYEE E, MANAGER M WHERE E.DNO=M.DNUMBER AND E.SALARY > M.SALARY;
```

## Triggers
``` SQL
CREATE TRIGGER trigger-name
trigger-time trigger-event
ON table-name
FOR EACH ROW
trigger-action;
```
- Trigger-time <- Before/After
- Trigger-event <- Insert/Delete/Update
- Triggers are used to enforce constraints of a table
  - business rules


### Creating triggers to update salary when new employee is hired
```SQL
Delimiter |
create trigger update_salary
  after insert on employee
  for each row
  begin
    if new.dno is not NULL then
    update deptsal
      set totalsal = totalsal + new.salary
      where dnumber = new.dno
    end if;
  end |
```
-  The `new` keyword refers to guy being inserted

## Trigger to update tables before a Delete
```SQL
Delimiter |
create trigger update_salary2
  before delete on employee
  for each row
  begin
    if old.dno is not NULL then
    update deptsal
      set totalsal = totalsal - new.salary
      where dnumber = old.dno
    end if;
  end |
```
### Delimiter
- Delimeters change the terminating character of a SQL statement form ; to something else


## Procedures in MySQL
```SQL
Create Procedure <proc-name> (param_spec1,
  param_spec2, …, param_specn )
  begin
    -- execution
code end;
```
- Create a Procedure to update the salary in a table with a given input
```SQL
Delimiter //
create Procedure addSalary (IN param1 int)
  begin
    update deptsal
      set totalsal = (select sum(salary) from employee where d.no = param1);
      where dnumber = param1;
  end; //


call addSalary(1);
```

## Functions are better than cursors
- Function Syntax
```SQL
function <function-name> (param_spec1, …, param_speck)
returns <return_type>
[not] deterministic             allow optimization if same output for the same input (use RAND not deterministic )
  Begin                       
    -- execution code end;
```
- An example SQL function to give raises
```SQL
Delimiter |
create function giveRaise(Oldval double, amount double)
  returns double
  deterministic
  begin
    declare Newval double;
    set Newval = Oldval * (1 + amount)
    return Newval
  end |

set @result = call giveRaise(salary,0.1)
Select @result
```
### __A function in mySQL can have if statements and for loops__

### Variables in MySQL
- declare var1 INT
  - set var1 = 100;
