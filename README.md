PySW
=========

PySW is a simple Smith-Waterman [1] algorithm implementation wrapped by python and wrote in C++.

  - Find out the maximum score match string
  - available for setting different scores of "match", "mismatch" and gap
  - Return both of the matched string and their indexes in original strings


Version
-

0.1

Installation
--------------
1. First, make sure the "python-dev" has been installed, e.g. on Ubuntu, run
```sudo apt-get install python-dev 
```
2. run make


Usage
--------------
1. put the ```sw.so``` into the current folder and run ```python```
2. ```import sw```
3. use ```sw.setscore()``` to set the scores of "match", "mismatch" and gap (default 1, -1, 0)
4. use ```sw.setfoo()``` and ```sw.setbar()``` to set the two sequences (MUST be integer)
5. run ```sw.compare()``` and this will return a list ```[matched string, matched index in foo string, matched index in bar string]```

License
-

MIT

Reference
-------------
  [1]: *Smith, Temple F.; and Waterman, Michael S. (1981). "Identification of Common Molecular Subsequences". Journal of Molecular Biology 147*