# What are design patterns?
- Description of what experienced designers know
- Reminders for choosing classes/methods
- Weigh design tradeoffs
- Higher order abstractions

## Level of implementation of a pattern
- Invisible
  - Part of a language you don't even notice
- Informal
  - Design pattern in prose, build from scratch for use
- Formal
  - Pattern within the language
    - Usually macros
    - Macros provide syntactic abstractions

### Observer with method combination
  - Notify after every change

### Pattern: Facade
  - Provide a simple interface to a subsystem
### Invisible patterns
  - Smart pointers
  - Reference counting
  - Closure
  - Wrappers
### Pattern: Protocol method
- implement set of related operations
### Pattern: Iterator
- Work over each element in collection

### Pattern: Coroutine
  - Separate out distinct kinds of processing, stave state form one iteration to next
### Pattern: New control abstraction
  - Replace loops with named function or macro
### Pattern: Memoization
  - Cache result after computing it transparently

### Pattern: Run time loading
  - Allow program to be updated while it is running by loading new classes/methods
### Pattern: Relation
  -  Represent that x -> y by R


# 3 laws of robotics
1. Dont harm humans, through action or inaction
2. Obey humans except when in coflict with (1)
3. Protect self, except when conflict with (1,2)
