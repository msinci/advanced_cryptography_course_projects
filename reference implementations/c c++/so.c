#include <vector>
#include <queue>

#include <gmpxx.h>

// Interface to the GMP random number functions.
gmp_randclass rng(gmp_randinit_default);

// Returns a divisor of N using Pollard's rho method.
mpz_class getDivisor(const mpz_class &N)
{
    mpz_class c = rng.get_z_range(N);
    mpz_class x = rng.get_z_range(N);
    mpz_class y = x;
    mpz_class d = 1;
    mpz_class z;

    while (d == 1) {
        x = (x*x + c) % N;
        y = (y*y + c) % N;
        y = (y*y + c) % N;
        z = x - y;
        mpz_gcd(d.get_mpz_t(), z.get_mpz_t(), N.get_mpz_t());
    }

    return d;
}

// Adds the prime factors of N to the given vector.
void factor(const mpz_class &N, std::vector<mpz_class> &factors)
{
    std::queue<mpz_class> to_factor;
    to_factor.push(N);

    while (!to_factor.empty()) {
        mpz_class n = to_factor.front();
        to_factor.pop();
        if (n == 1) {
            continue; // Trivial factor.
        } else if (mpz_probab_prime_p(n.get_mpz_t(), 5)) {
            // n is a prime.
            factors.push_back(n);
        } else {
            // n is a composite, so push its factors on the queue.
            mpz_class d = getDivisor(n);
            to_factor.push(d);
            to_factor.push(n/d);
        }
    }
}