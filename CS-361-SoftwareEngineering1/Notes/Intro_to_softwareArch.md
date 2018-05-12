# Software architecture of Designing
- module interconnection
- templates
- frameworks
- Data access

# High level languages
- Help abstract the details of bits/registers etc etc
 Machine code -> Symbolic assemblers -> Macro processors -> symbolic representation of a machine instruction
- Moving out of machine code to fortran allowed more sophisticated program to be built

### Abstract data types
  - similar thinking to classes
  - helped hide the complexity of the software

# Common architecture styles
- Components  
  - collection of components(i.e functions)
- Connectors
  - Interactions b/w components
- constraints
  - how connectors and components are combined

### Pipe and Filter (components & connectors)
  - A unit takes in streams of data from input and produces streams of data in output
    - output begins as input comes in
  - flow from one end to another in
  - Independent entities, don't know whats before or after
  - Processing all data at one does not make it pipe and filter
  - Support concurrency
  - Often lead to batch processing
  - Sometimes need to parse and un-parse data

### OOP are similar to pipe and filter
  - In each module is encapsulated
  - But the biggest disadvantage is that they must know who are they talking to to communicate across classes.
  - When one module is changed, it has to be changed throughout all explicit invocations
  
### Event based implicit invocation
  - When an event is triggered other procedures listen to it and do an action based off the triggered event
    - Think of when using a debugger how it the program stops when it hits a breakpoint
  - Primarily used in IDE's
  - EXTREMELY easy to add and negate a feature, just simply add the feature as a listener to the event.
    - Opposed to explicit where you have to change any invocation
    
### layered systems
  - Hierarchal organized, supplies to layer above, and is client to layer below
  - Think of networking protocols
  - similar to filters but speak to both upper and lower 'filters'

### Repositories
- Use of common memory called 'blackboard memory'
- invocation of computation is dependent on blackboard state

## State transmission systems   
  - have a set of states that they can be in and a set of transitions each one can make
  
# Heterogenous structures
  - When you have a very isolationable system you can mix them, such as pipe and filters, within pipe and filters.
  - Or a Hierarchy that holds pipe and filters or whatever it wants really .

# KWIC implementations

  - ## Shared data systems
    - near impossible to make changes
    - Used by a master control module that invokes needed subroutines
    
  - ## Abstract Data Type(Class-esque)
    - Master control still invokes everything
    - But each module needs permissions to talk to another module
    - And changing one, means changing permissions of all modules
    
  - ## Implicit invocation
    - There is a master controller
    - After a line of input has been read it signals that it is ready for the next step by another module and so forth
    - Any changes just need to follow correct formats between implicit calls
    - Uses a ton of space as more inputs are received and concurrent modules are running.
# Tectronix
  - Had problems with Reusability when it came to making new models of oscilloscopes and typically had to start from scratch
  - A modified pipe and filter approach helped wrangle all seperate modules together and help bring modifiability to a systems

# Provox
  - A system by Fisher that controls chemical production process is a great example of Heterogenous architecture in which the top uses a hierarchy and the bottom levels use an object oriented approach 
