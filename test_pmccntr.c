#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

static inline uint64_t
read_pmccntr(void)
{
	uint64_t val;
	asm volatile("mrs %0, pmccntr_el0" : "=r"(val));
	return val;
}

void usage(const char *prog_name) {
    printf("Usage: %s [-r] [-d] [-n <iterations>]\n", prog_name);
    printf("Options:\n");
    printf("  -r, --read         Read the cycle counter once and print the value.\n");
    printf("  -d, --diff         Read the cycle counter twice and print the difference.\n");
    printf("  -n <iterations>  Read the cycle counter multiple times.\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    int opt;
    int read_once = 0;
    int read_diff = 0;
    int iterations = 0;

    if (argc < 2) {
        usage(argv[0]);
    }

    while ((opt = getopt(argc, argv, "rdn:")) != -1) {
        switch (opt) {
        case 'r':
            read_once = 1;
            break;
        case 'd':
            read_diff = 1;
            break;
        case 'n':
            iterations = atoi(optarg);
            break;
        default:
            usage(argv[0]);
        }
    }

    if (read_once) {
        printf("PMCCNTR: %llu\n", (unsigned long long)read_pmccntr());
    }

    if (read_diff) {
        uint64_t start = read_pmccntr();
        uint64_t end = read_pmccntr();
        printf("Cycle difference: %llu\n", (unsigned long long)(end - start));
    }

    if (iterations > 0) {
        for (int i = 0; i < iterations; i++) {
            printf("Iteration %d: PMCCNTR: %llu\n", i, (unsigned long long)read_pmccntr());
        }
    }

    return 0;
}
