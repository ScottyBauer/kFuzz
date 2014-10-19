#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <sys/types.h>


#define REAL 1 /* real address from malloc */
#define FAKE 0 /* fake address from rand64() */
#define PAGED 2

struct addrtype
{
	void* addr;
	unsigned char type;

};


pid_t getfakeorrealpid(void);
void generatefakeorrealaddr_64(struct addrtype* save_to, size_t amount);
void freefakeorrealaddr_64(struct addrtype* save_to);
unsigned long long rand64(void);
