# Program Two

_Due June 5 at 11:59 PM_

In this assignment you will implement an  [AVL tree][avl]  that stores integers.
Your program will be tested on "command files" that describe the operations your
tree should perform.  You will need  to write a parser for these files as well -
their syntax is described below.


## Program Specification

Define  your  AVL  tree  class  (or classes)  in  `Tree.h`.  Implement  them  in
`Tree.cpp`. All parsing and most output should be done in your `main()` function
(and/or helper functions) in `avl.cpp`.

Your code  will be compiled with the makefile provided - it must compile without
any warnings on  Gradescope and CSIL.  Once compiled,  your program  will be run
with a single command-line argument:

```sh
./avl path/to/command/file.avl
```

Each line in the command file describes an operation  or set of operations  that
your tree must perform. The possible commands are described below.  Your program
will not  be tested on invalid command files,  but you may find it useful to add
error handling to help you debug.


## Command File Specification

### Comments and Blanks

Any line starting with  a hash sign  (`#`)  is a comment  and should be ignored.
Likewise, empty lines should be ignored.

```
# Ignore this line and the next one.

```


### Inserts

Any line starting with the word `insert` contains a whitespace-separated list of
numbers  that you should insert into your tree.  Insert them in the order given.
If your tree already  contains one of the numbers, do not add it again (that is,
your tree should act like a set).

```
# After this, your tree should contain {7, 12, 42, 108}
insert 12 7 108 42 12
```

After performing the insert,  print statistics  on what you did;  the numbers in
parentheses are amortized costs.  A newly inserted node should not be counted as
visited  during its own insert.  Single rotations  should count as one rotation,
and double rotations should count as two.

```
Added 4 of 5 nodes.
Visited 5 (1) nodes and performed 0 (0) rotations.

```


### Lookups

Any line starting with the word `lookup` contains a whitespace-separated list of
numbers that should be looked up in your tree.

```
# Look these up in the tree constructed above:
lookup 7 14 -82 12 7
```

Report the nodes you found in the order they were listed, and statistics.  There
should never be any rotations during a lookup, but reporting them lets you reuse
your print function from insert.

```
Found 3 of 5 nodes: [7, 12, 7]
Visited 10 (2) nodes and performed 0 (0) rotations.

```


### Prints

Any line starting with the word `print` will have you print something.  What you
need to print is determined by the next word.

If the next word is `tree`, print your entire tree.  Use two spaces to indent at
each level.  Leaf nodes have a special form for compactness; internal nodes also
include their height.  An empty tree should simply print as `Null`.

```
Node(12, h=2):
  Leaf(7)
  Node(108, h=1):
    Leaf(42)
    Null

```

If the next word  is  `left-left`, `left-right`, `right-left`, or `right-right`,
print a list of the inserts that would cause the given rotation.

```
The following inserts would cause a left-left rotation:
13 to 41

```

If no inserts would cause that rotation, say so:

```
No inserts would cause a right-left rotation.

```

If multiple ranges  would cause the  given rotation,  list them in sorted order,
separated by commas.  If a range only contains a single value, represent it as a
single number.  If any large (or small)  insert would cause a rotation,  use the
maximum (or minimum) value of a 32-bit signed integer as an endpoint.

```
The following inserts would cause a right-right rotation:
-44 to 17, 37, 102 to 558, 1007, 1009 to 2147483647

```


## Submission

Submit your program on Gradescope.  Not all of the automatic test output will be
visible to you;  passing the simple test cases provided does not ensure that you
will get full credit!

You will also need to meet with a TA to review your code and explain your design
decisions. These meetings should only take about ten minutes per person; sign-up
sheets will be made available closer to the submission deadline.


## Miscellaneous

- This is an individual assignment.  No group work!
- You are _highly_ encouraged to add your own tests for more complicated trees.
- Look at [`std::getline()`][get]  and [`std::istringstream`][str]  for ideas on
  parsing files and individual commands.
- Make sure you test your code on any edge cases you think of.
- Note that every command prints a  blank line after its output.  Make sure your
  test cases include this (it's easy to forget the last one).


[avl]: https://en.wikipedia.org/wiki/AVL_tree
[get]: https://en.cppreference.com/w/cpp/string/basic_string/getline
[str]: https://en.cppreference.com/w/cpp/io/basic_istringstream
