# kSAT-Resample
A project that contains
1. a parametrized random kSAT generator
2. resampling algorithms

## kSAT generator
We want to generate some "random" k-SAT instances such that the degree of each clause (in the dependency graph) is at most d. It suffices to require that each variable appears in at most d/k+1 clauses. So if you want a dependency graph of n nodes with degree at most d, then you can randomly distribute (d/k+1) copies of kn/(d/k+1) different random variables.

The basic idea is that, for each variable, you choose a random set of (d/k+1) clauses and add the variable to that clause, with a random coin indicating whether it's negated or not. A clause is removed if it has k variables assigned. If a clause has been assigned a same variable twice, then they must be of the same value (to ensure that the clause is satisfiable by itself).

One disadvantage of this idea is that, as n grows large, you don't get much variety in the instance you get. Because the number of clauses is so large, it is with high probability that the dependency graph will have a very high girth (ignoring the cycles formed by a same variable).

One ad hoc fix is to introduce a bias parameter q as a dynamic parameter. So during the process of assigning variables, for each variable, with probability q that it will be assigned to a clause that already has some variable assigned. The paramter q should dependent on the current number of living clauses (consider a clause is unborn if no variable is assigned to it, living if some varible but not all is assigned, dead if all variables have been assigned). For now let's say q is an exponential function of the number of living cluases, q(x) = 1 - exp(-x/r), where r is a parameter, which says, approximately how large your set of living clauses is so that you have some decent probability to be assigned to living clause

The resulting kSAT should be stored in a file, in the following format.

- (number of nodes) (number of variables) (k) (designed degree)
- (variable 1, negate?) (variable 2, negate?) ... (variable k, - negate?)  % the first clause
- (variable 1, negate?) (variable 2, negate?) ... (variable k, negate?)  % the second clause
...

The input of the generator should be (n,k,d,r). Note that lovas local lemms garentees that it is solvable as long as (e 2^{-k} d) < 1.
