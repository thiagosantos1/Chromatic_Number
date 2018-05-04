# Chromatic Number - Coloring Search - NP-Complete

The aim of this project is to determine the chromatic number of a graph, which is known as a NP-Complete problem. 

1) Ideas used to improve performancing.
  * Hill Climbing (Rand Search)
    * Try to guess first the chromatic number.
    * This speeds up the process.
    * First, we get a greedy coloring. Then, we try to recolor the graph with 1 less color
      * repeat this process until we can't improve anything anymore.
  * Exhaust Search
    * After we got a good chromatic number guess, we shall try a exhaust search, with 1 less color.
      * repeat this process until we can't improve anything anymore.
  * Multithreading 
    * Whenever possible, we aim to use multithreading, to speed up the algorithms.
