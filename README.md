# ImrpovingDegreeEvalution
1. CorrelationCubeAttacks/Decomposition: It is used to search cubes which are useful in correlation cube attacks.
2. CorrelationCubeAttacks/DecompositionFreeIV: It is used to figure out the free IV bits for a useful cube in correlation cube attacks.
3. Kreyvium-DegEst-Greedy: It is the improved tuned GreedyBitSet algorithm for Kreyvium. In this program, we do not compute the ANFs of the first N_0 rounds of the internal state bits of Kreyvium.
4. Kreyvium-DegEst-Greedy-withANF: This is the improved version of  Kreyvium-DegEst-Greedy. In this program, we compute the ANFs of the first N_0 rounds of the internal state bits of Kreyvium.
5. Kreyvium-DegEst-WithDivisionProperty: This is the program which utilizes division property to do degree evaluation for the round-reduced Kreyvium. It is writen in C# and the solver used is Gurobi 8.1.
