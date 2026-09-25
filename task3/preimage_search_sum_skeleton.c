#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <stdint.h>  
#include <sys/wait.h>
#include <time.h>

struct timespec t0, t1;
/*
 * elapsed_sec
 * -----------
 * Computes the wall-clock time difference in seconds between two
 * timespec values (a = start, b = end) obtained from clock_gettime.
 * Useful for timing code execution with CLOCK_MONOTONIC.
 */
static double elapsed_sec(struct timespec a, struct timespec b)
{
    return (b.tv_sec - a.tv_sec) + (b.tv_nsec - a.tv_nsec) / 1e9;
}

/*
 * hash4
 * -------------
 * Takes 4 input bytes (unsigned char in[4])
 * and produces 3 output bytes (unsigned char out[3]).
 *
 * Treat the function like a black box. You do not need to understand anything in it.
 */
void hash4(const unsigned char input[4], unsigned char output[3])
{
    // Pack input bytes (little-endian) into a 32-bit integer
    uint32_t x =  ((uint32_t)input[0])
                | ((uint32_t)input[1] << 8)
                | ((uint32_t)input[2] << 16)
                | ((uint32_t)input[3] << 24);

    // Simple mixing for avalanche effect
    uint32_t z = x + 0x9E3779B9u;
    z ^= z >> 16;        z *= 0x85EBCA6Bu;
    z ^= z >> 13;        z *= 0xC2B2AE35u;
    z ^= z >> 16;

    // Extract lower 24 bits into 3 bytes (little-endian)
    output[0] =  z        & 0xFF;    // least significant byte
    output[1] = (z >> 8)  & 0xFF;
    output[2] = (z >> 16) & 0xFF;    // most significant of the 3
}

/*
 * simple_preimage_summation
 * -------------------------
 * Brute-forces the full 4-byte message space [0,255]^4 on a single process.
 * For each message m=(m0,m1,m2,m3), computes hash4(m) and, if it matches
 * the 3-byte target, adds (m0+m1+m2+m3) to an accumulator.
 *
 * Parameters:
 *   target  - 3-byte target hash to match (unsigned char[3]).
 *
 * Returns:
 *   The sum of (m0+m1+m2+m3) over all preimages in the full domain.
 *
 * Notes:
 *   - This is a baseline (single-core) implementation used for correctness
 *     and timing comparison against the forked version.
 *   - Runtime is proportional to 256^4 = 2^32 iterations.
 */
int simple_preimage_summation(const unsigned char target[3])
{
	unsigned char output[3];
	int preimage_sum = 0;

	for(int m0=0; m0<256; m0++)
	{
		for(int m1=0; m1<256; m1++)
		{
			for(int m2=0; m2<256; m2++)
			{
				for(int m3=0; m3<256; m3++)
				{
					unsigned char input[4] = {  (unsigned char)m0,
						                        (unsigned char)m1,
						                        (unsigned char)m2,
												(unsigned char)m3};
					
					hash4(input, output);
					
					int matching = 1;
					for(int i=0; i<3; i++)
					{
						if(target[i]!=output[i])
						{
							matching = 0;
							break;
						}
					}
					
					if(matching==1)
					{
						preimage_sum += (m0+m1+m2+m3);
					}
				}
			}
		}
	}

	return preimage_sum;
}

/*
 * forked_preimage_summation
 * -------------------------
 * Parallel brute-force using fork(). The parent spawns n children and
 * partitions the message space so that each child searches a disjoint set.
 * Each child accumulates the sum of (m0+m1+m2+m3) for all messages whose
 * hash4(m) equals the 3-byte target, then reports its partial sum back to
 * the parent (e.g., via pipe, shared memory, or a small temp file).
 * The parent waits for all children, aggregates partial sums, and returns
 * the total.
 *
 * Parameters:
 *   target  - 3-byte target hash to match (unsigned char[3]).
 *   n       - number of child processes to fork (n >= 1).
 *
 * Returns:
 *   The total sum of (m0+m1+m2+m3) over all matching messages in the
 *   searched domain (should equal the single-process result when the
 *   domain coverage is identical).
 */
int forked_preimage_summation(const unsigned char target[3], int n)
{
	// your code here
	return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 5) {
        printf("Usage: %s <h0> <h1> <h2> <n_children>\n", argv[0]);
        printf("  <h0>,<h1>,<h2> are integers 0�255 representing the 3-byte target hash.\n");
        printf("  <n_children> is the number of child processes to fork.\n");
        return 1;
    }

    int h0 = atoi(argv[1]);
    int h1 = atoi(argv[2]);
    int h2 = atoi(argv[3]);
    int n  = atoi(argv[4]);

    // Basic validation
    if (h0 < 0 || h0 > 255 || h1 < 0 || h1 > 255 || h2 < 0 || h2 > 255 || n < 1) {
        printf("Error: ensure 0 <= h <= 255 for all bytes and n => 1.\n");
        return 1;
    }

    unsigned char target[3] = { (unsigned char)h0,
                                (unsigned char)h1,
                                (unsigned char)h2 };
	
	clock_gettime(CLOCK_MONOTONIC, &t0);
    int simple_sum = simple_preimage_summation(target);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    printf("simple_sum = %d in %.2f seconds (wall)\n", simple_sum, elapsed_sec(t0,t1));
    fflush(stdout);
    
    // Uncomment code below when you forked_preimage_summation is complete!
    
//    clock_gettime(CLOCK_MONOTONIC, &t0);
//    int forked_sum = forked_preimage_summation(target, n);
//    clock_gettime(CLOCK_MONOTONIC, &t1);
//	printf("forked_sum = %d in %.2f seconds (wall)\n", forked_sum, elapsed_sec(t0,t1));
//	fflush(stdout);

    return 0;
}
