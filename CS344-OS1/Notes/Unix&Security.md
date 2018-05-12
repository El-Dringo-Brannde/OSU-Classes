## Dual modes in unix
  - Monitor modes
  - User modes
  - Special hardware had been added
  - All I/O instructions are privleged instructions, and have to be in Monitor mode

## Memory Protection
  - all physical memory has a base register where memory starts and a limit register for each specific program
  - Monitor mode has unrestricted access to Monitor and user memory

## Cpu protection
  - a timer is constantly ticking down to give the OS a chance to retain control

## The root Account
  - Root allows you to do ANYTHING, don't login to root, just do SUDO
## SUID SGID
  - Each executable has 2 security bits with it SUID and SGID
    - It allows you to run the program as whatever user

### Why does SUID matter?
- If you say did PING, and insert your own code, you could do literally you want
- But you can't, so you have to do `chown` and `chgrp`

## The best security is isolation from the network and physical
  - All bets are off they have physical access.

## Password Security
  - Longer is better than complicated
    - simple combinatorics

### Neat little script to wipe Windows Password
http://pogostick.net/~pnh/ntpasswd/
