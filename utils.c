#include "utils.h"


int trueorfalse(void)
{
	return rand() % 2;
}

pid_t getfakeorrealpid(void)
{
	if(trueorfalse())
		return getpid();
	return rand() % 32768; //usually max pid on most systems
}

unsigned long long rand64(void){

	/* TODO
	   RAND will return the MSB AS ZERO, << by 33? 
	*/
	unsigned long long result = rand();
	result <<= 32;
	result |= rand();
	return result;
}


void freefakeorrealladdr_64(struct addrtype* inc)
{
	assert(inc != NULL);
	if(inc->type == REAL){
		free(inc->addr);
	}
	return;
}

void generatefakeorrealaddr_64(struct addrtype* save_to, size_t amount){
	assert(save_to != NULL);
	
	if(trueorfalse()){
		save_to->type = REAL;
		save_to->addr = malloc(amount);
		assert(save_to->addr != NULL);
		return;
	}

	save_to->type = FAKE;
	save_to->addr = (void*) rand64();
	return;
}
