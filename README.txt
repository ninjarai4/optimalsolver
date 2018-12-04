Aaron Altmejd aa62462
Brandon Sides bks874

Accomplishments so far:
    - Conceptualizing algorithm at high level, experimenting with existing implementation to make parallelizable

Basic concept:
    We are trying to use Mike Reid's 1997 implementation of Korf's Algorithm as the basis for a GPU accelerated
    optimal Rubik's cube solver.  The algorithm essentially involved doing an iterative-deepening A* search over
    the Rubik's Cube Group.  Because this space is enormous, we keep a table of distances from certain configurations
    of the cube to some semi-solved position; this is used as a minimum distance to the solved position, which is used
    to prioritize search paths and prune those that we know to be non-optimal.  The table makes use of the symmetric
    properties of the cube and the fact that not all sub-cube positions are relevant when calculating distances from
    the semi-solved state; this makes the table much smaller than it would need to be if we were storing all states
    explicitly.  Mike Reid's implementation makes use of many of the group-theoretic properties of the cube in order
    to come up with a useful heuristic.  This cheaply but effectively speeds up our search.  An important step will be
    finding a balance between the size of our table, which will be limited by the amount of memory available to us on
    the GPU, and speed, which will generally increase the larger we are able to make our table.  The particularities
    of the heuristic we end up using may become significant.

    We expect to perform the search to a certain depth on the CPU.  Because this is essentially a tree search, each
    step down the tree creates a number of independent sub-problems.  Once we reach a threshold of sub-problems, we
    will begin solving these on the GPU, distributing the sub-problems among the cores.

Remaining tasks:
    At present we are tweaking Mike Reid's published implementation of the algorithm in order to find out which parts of
    it are parallelizable using OpenMP, without reimplementing the boilerplate functionality from scratch.  When we have finished this,
    we will need to do our own implementation making use of the GPU.  We will do this using either OpenMP 4.5, which supports
    GPU acceleration, or OpenACC.  We will at that point have to address any problems that arise from moving our functionality
    onto the GPU, including possible memory issues caused by a very large pruning table.

Compiling and running:

    make && bin/optimal