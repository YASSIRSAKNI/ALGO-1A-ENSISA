#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
/* ================= EXERCISE 1 : FIBONACCI ================= */
 
/* Naive recursion : O(2^n) */
long long fib_naive(int n)
{
    if (n <= 1)
        return n;
    return fib_naive(n - 1) + fib_naive(n - 2);
}
 
/* Dynamic programming : O(n) time, O(n) memory */
long long fib_dp(int n)
{
    if (n <= 1)
        return n;
 
    long long *f = malloc((n + 1) * sizeof(long long));
    f[0] = 0;
    f[1] = 1;
    for (int i = 2; i <= n; i++)
        f[i] = f[i - 1] + f[i - 2];    /* reuse the results already computed */
 
    long long result = f[n];
    free(f);
    return result;
}
 
/* ================= EXERCISE 2 : PRIME NUMBERS ================= */
 
/* Naive : test each number with divisors up to sqrt(k) -> O(n * sqrt(n)) */
int is_prime(int k)
{
    if (k < 2)
        return 0;
    for (int d = 2; d * d <= k; d++)
        if (k % d == 0)
            return 0;
    return 1;
}
 
int count_primes_naive(int n)          /* primes strictly less than n */
{
    int count = 0;
    for (int k = 2; k < n; k++)
        if (is_prime(k))
            count++;
    return count;
}
 
/* Efficient : Sieve of Eratosthenes -> O(n log(log n)) */
int count_primes_sieve(int n)          /* primes strictly less than n */
{
    if (n < 3)
        return 0;
 
    char *prime = malloc(n);           /* prime[k] = 1 if k is prime */
    for (int k = 0; k < n; k++)
        prime[k] = 1;
    prime[0] = prime[1] = 0;
 
    for (int p = 2; (long long)p * p < n; p++)
        if (prime[p])
            for (long long m = (long long)p * p; m < n; m += p)
                prime[m] = 0;          /* multiples of a prime are not prime */
 
    int count = 0;
    for (int k = 2; k < n; k++)
        count += prime[k];
 
    free(prime);
    return count;
}
 
/* ================= MAIN : RUNTIME COMPARISON ================= */
 
int main(void)
{
    clock_t start;
    double t;
 
    /* ---- Fibonacci ---- */
    int n = 40;
 
    start = clock();
    long long a = fib_naive(n);
    t = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("Fibonacci naive (n=%d) : %lld in %f s\n", n, a, t);
 
    start = clock();
    long long b = fib_dp(n);
    t = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("Fibonacci DP    (n=%d) : %lld in %f s\n\n", n, b, t);
 
    /* ---- Primes ---- */
    int m = 5000000;
 
    start = clock();
    int c1 = count_primes_naive(m);
    t = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("Primes naive (n=%d) : %d in %f s\n", m, c1, t);
 
    start = clock();
    int c2 = count_primes_sieve(m);
    t = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("Primes sieve (n=%d) : %d in %f s\n", m, c2, t);
 
    return 0;
}
 