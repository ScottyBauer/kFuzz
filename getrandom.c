#include "utils.h"
#include "sys_util.h"
#include "sysc_nums.h"
//#include "logging.h"


#define GRND_BLOCK	0x0001
#define GRND_RANDOM	0x0002
#define DEFAULT         0x0003


static unsigned int FLAGS[3] = {GRND_BLOCK, GRND_RANDOM, DEFAULT};

static unsigned int loops;

static void do_gr_fuzzing(void)
{

	size_t count;
	//	long ret;
	struct addrtype faux_real;
	

	while(loops--){
		count = rand() % 257;
		generatefakeorrealaddr_64(&faux_real,count);
		//writeLog("getrandom", gr_prettyprint, &faux_real);

		/* TODO SOMETHING WITH RET? */
		 syscall(__NR_getrandom,faux_real.addr,
			count, FLAGS[rand() % 3]);
      
		freefakeorrealaddr_64(&faux_real);
	}

}


void getrandom_fuzz(int amount)
{
	loops = amount;
	do_gr_fuzzing();
}


