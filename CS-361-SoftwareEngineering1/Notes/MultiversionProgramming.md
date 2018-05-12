# Multiversion programming  
  - Having more than one team build a project with the same exact spec given to each
    - Theoretically each team will create different bugs and when they come back together there will be better fault tolerance and reliability between the two
    - The probability that two teams come up with the same bug is low
  - Input is assumed correct if correct output on both systems
  - Used in some flight avionics, some railway switching in Sweden
  - Software costs due to N version programming is offset by minimizing testing costs

# Throughout the paper they found that the independence of errors on N = 27 DOES NOT HOLD
  - However the test merely states that the theory is not as reliable as once previously thought
  - It was found that 1/2 of all faults were shared between 2  random programs
## It should go to note a lot of the paper was them discussing how they set up the experiment and attempted to get rid of any variables 
