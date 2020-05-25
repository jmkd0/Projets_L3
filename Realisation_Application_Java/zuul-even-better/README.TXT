Project: zuul-even-better
Authors: Michael Kolling and David J. Barnes
Last updated: 16 December 2002

This project is part of supplementary material for the book

   Objects First with Java - A Practical Introduction using BlueJ
   David J. Barnes and Michael Kolling
   Pearson Education, 2002
   
This project is a solution to Exercise 7.39, page 198 of the book.
It is a redesigned version of the original game structure, that 
implements much better (more object-orienated) command dispatch.

Each user command is now represented by a separate class, and the
Game class does not implement the user commands anymore. Instead,
it just invokes an 'execute' method on a command object.

A Player class was also introduced.