# Designing a computer system is harder than an Algorithm
  - Many more interfaces, and subject to change, the measuring of success is clear

# Functionality
  - Depends on interface to separate implementation from the users
  - ## An interface must have
    - Simple layout
    - Complete
    - Admit a simple implementation
    - KISS(Keep it Simple Stupid)
    - Do one thing at a time and do it well
  - Don't focus on the features of a select few if it will penalize the rest of the users
  - Just get it right, do abstraction and simplicity later.
  - Most programs just do simple things
    - read data, test equality, add one
    - If you were to get those right, you could do everything else bad and still have a rather fast system
  - Divide and Conquer
  - Use a good idea again and again
  - Handle Best and worse cases seperatley
    - The Best case must be fast
    - The worst case just needs to make progress
# Keep basic and crucial interfaces stable

# Speed
  - Split resources when possible
  - Use Cache when you can as it is MUCH faster
  - But when in doubt, use brute force
  - Compute in the background when possible
  - Shed load to control demand

# Fault Tolerance
  - The unavoidable price of realiability is simplicity
  - Log updates to record the truth
  - Make actions atomic or restartable
    - atomic action: action that completes or has no affect
