#include "utils.h"
#include "sysc_nums.h"
#include "sys_util.h"


unsigned int loops;

//static unsigned int FLAGS[] = {};


static void do_g_attrfuzzing(void)
{
	
	pid_t pid;
	struct addrtype faux_real;
	unsigned int size; 
	unsigned int flags;
	

	while(loops--){
		
		size = rand() % 4097;
		flags = rand();
		pid = getfakeorrealpid();
		generatefakeorrealaddr_64(&faux_real);

		syscall(__NR_schedgetattr, pid, faux_real.addr, 
			size, flags);

		freefakeorrealaddr_64(&faux_real);
	
	}


}


void sched_getattrfuzz(int amount)
{
	loops = amount;
	do_g_attrfuzzing();
}
