CCL
===

C Code implementation of ARemSP and it's parallel version


ARemSP.c -- most optimized sequential algorithm

PARemSP.c -- Parallel version of ARemSP in which count is shared among all the threads.

PARemSP_count.c -- Parallel version of ARemSP in which count is local to each thread.

PARemSP_cache.c -- Parallel version of ARemSP in which padding is done.

Suzuki.c -- One Pass Suzuki CCL Algorithm for which OpenMP implementation exists.
