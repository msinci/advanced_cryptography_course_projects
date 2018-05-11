#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <gmp.h>

/*
	gcc -O3 factor.c -o factor -lgmp -lm
*/

// Divide n by d, forming a quotient q and remainder r
// f means floor rounding
// mpz_fdiv_qr(q,r,n,d);


int power_of_2(uint64_t number)
{
        uint64_t count = 0;

        if (number == 0)
                return 0;

        while(number > 0)
        {
                if (number & 1 == 1)
                        count++;
                number = number >> 1;
        }

	if (count == 1)
                return 1;
	else
		return 0;
}

void pollard_iterate(mpz_t *new_x, mpz_t *x, mpz_t *n)
{
	mpz_t one;
	mpz_init(one);
	mpz_set_str(one, "1", 10);

	mpz_mul(*new_x, *x, *x);
	mpz_add(*new_x, *new_x, one);
	mpz_fdiv_r(*new_x, *new_x, *n);
	mpz_clear(one);
}

int main(int argc, char *argv[])
{
	mpz_t n;		// number to factor
	mpz_t r;		// gcd result (previously used as remainder)
	mpz_t seed;		// initially the seed, also used to store current Xi
	mpz_t y;		// used to store current Xi + length value
	mpz_t test_factor;	// result of Xi minus Xi + length
	mpz_t one;		// constant one
	mpz_t temp;		// temp value

	uint64_t length;		// length size
	uint64_t x_index = 0;		// index of xi

        if (argc != 3)
	{
		printf("Usage: factor <seed> <big number>\n");
		return 0;
	}


	mpz_init(n);
	mpz_init(r);
	mpz_init(test_factor);
	mpz_init(seed);
	mpz_init(y);
	mpz_init(one);
	mpz_init(temp);

	// mpz_set_str(var, "big number", base);
	mpz_set_str(seed, argv[1], 10);
	mpz_set_str(n, argv[2], 10);
	mpz_set_str(one, "1", 10);
	mpz_set(y, seed);
	mpz_set(temp, seed);

	for(length = 1; ; length++)
	{
		uint64_t y_index = x_index + length;

		if (y_index == 0)
		{
			printf("Overflow of 64 bit integer\n");
			return 0;
		}

		mpz_set(temp, y);
		pollard_iterate(&y, &temp, &n);

		mpz_sub(test_factor, seed, y);
//		printf("Testing factor %u-%u length %u %s\n", x_index, y_index, length,  mpz_get_str(NULL, 10, test_factor) );
		mpz_gcd(r, n, test_factor);
		if ( mpz_cmp(r, one) > 0)
		{
			printf("Found factor %s\n", mpz_get_str(NULL, 10, r));
			return 0;
		}

		if ( power_of_2(y_index) )
		{
			uint64_t j;

			mpz_set(temp, seed);

			for(j = x_index; j < y_index; j++)
			{
				pollard_iterate(&seed, &temp, &n);
				mpz_set(temp, seed);
			}

			x_index = y_index - 1;
			mpz_set(y, seed);
		}
	}

	return 0;
}
