# Motivation

I was learning the extended Euclidean algorithm in basic number theory and wondered how I should solve it for $n$ variables without using the fact that $gcd(cof1,cof2,…,cofn)=gcd(cof1,gcd(cof2,cof3,…,cofn))$ since this implementation can cause an overflow for specific test cases.

# Concept

I tried to grasp the idea of extended Euclidean for $2$ variables. It used the fact that $gcd(a+b,b)=gcd(a,b)=gcd((a+b)\mod b,b)$ such that $a>0$ and $b>0$. This fact can be applied to $n$ variables by taking $\mod cof_n$ to all the $n−1$ coefficients (from $1$ to $n−1$) and moving the last element to the beginning (i.e. doing a right cyclic shift) since $cof_n$ is now greater than all other coefficients and taking another modulo will not change the whole $gcd$.

The extended Euclidean for $2$ variables also used the fact that $gcd(a,0)=a$ and that to solve the equation $a\cdot x+b\cdot y=GCD$, $x$ must equal $1$ since $b$ equals $0$. Moreover, $x$ and $y$ values from the previous call to the recursive function can be deduced from the current call using $y_{prev}=x_{cur}−a_{prev}/b_{prev}\cdot y_{cur}$; such that $prev$ and $cur$ correspond to $previous$ and $current$, respectively. This also can be generalized to $n$ variables as we always take $\mod cof_n$, so the equation will be $var_{n,prev}=var_{1,cur}−\sum_{i=1}^{n−1} cof_{i,prev}/cof_{n,prev}\cdot var_{i+1,cur}$; such that $cof_i$ stands for $coefficient_i$ and $var_i$ stands for $variable_i$.

The last thing to consider is the case where one of the coefficients became $0$. The idea is to just discard those coefficients and their corresponding variables, since their values will not change anymore. When the number of non-zero coefficients reduces to $1$, this one coefficient is for sure the gcd of all coefficients and its corresponding variable has the value of $1$. All of this can be proved by induction from the facts in the [first paragraph](#concept).

# Implementation

For easy manipulations, a recursive approach is used, but for efficieny, doubly-linked lists (`std::list`) are used for coefficients and variables. In the implementation, the equation in the second paragraph of the [Concept](#concept) section is a little different. Since a right cyclic shift is required after taking the modulous of $cof_n$ and before each call, the $var$ deque is cyclically right-shifted too. As for the complexity, I tested this algorithm against the Fibonacci series (worst-case scenario) and found that it takes an approximated memory and time complexity of $O(cof_{size}\cdot log_2(cof_{min}))$. You can look up my implementation [here](https://github.com/AhmedYasser5/Extended_Euclidean_for_n_variables/blob/main/include/extended_euclidean.hpp).
