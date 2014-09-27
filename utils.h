#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>


#define REAL 1 /* real address from malloc */
#define FAKE 0 /* fake address from rand64() */

struct addrtype
{
	void* addr;
	unsigned char type;

};


void generatefakeorrealaddr_64(struct addrtype* save_to, size_t amount);
void freefakeorrealaddr_64(struct addrtype* save_to);
