#include "utils.h"
#include "sysc_nums.h"
#include "sys_util.h"



unsigned int loops;


struct sched_attr {
	uint32_t size;

	uint32_t sched_policy;
	uint64_t sched_flags;

	/* SCHED_NORMAL, SCHED_BATCH */
	int32_t sched_nice;

	/* SCHED_FIFO, SCHED_RR */
	uint32_t sched_priority;

	/* SCHED_DEADLINE */
	uint64_t sched_runtime;
	uint64_t sched_deadline;
	uint64_t sched_period;
};

static void do_s_attrfuzzing(void)
{
	pid_t pid;
	unsigned int size;
	unsigned int flags;

	int flag = 0;
	struct addrtype faux_real;
	struct sched_attr attrs;

	struct sched_attr *fake = 0;

	while(loops--){
		if(trueorfalse()){
			size = sizeof(struct sched_attr);
			flag = 1;
		        faux_real.addr = &attrs;
			faux_real.type = FAKE; //just incase I code this wrong and pass this addr to free();
			
			attrs.size = size;
			/* note casts to int and does comparason from uint to int 
			 * rand will be fixed to give us a neg
			 */
			attrs.sched_policy = rand();
			attrs.sched_flags = rand64();
			attrs.sched_nice = rand();
			attrs.sched_priority = rand();
			attrs.sched_runtime = rand64();
			attrs.sched_deadline = rand64();
			attrs.sched_period = rand64();		       
		}

		if(!flag){
			size = rand() % 4097;
			generatefakeorrealaddr_64(&faux_real,size);
			if(faux_real.type == REAL &&
			   size >= sizeof(struct sched_attr)){
				fake = faux_real.addr;
				
				fake->size = size;
				
				fake->sched_policy = rand();
				fake->sched_flags = rand64();
				fake->sched_nice = rand();
				fake->sched_priority = rand();
				fake->sched_runtime = rand64();
				fake->sched_deadline = rand64();
				fake->sched_period = rand64();
			}
		}
		
		pid = getfakeorrealpid();
		flags = rand();
		syscall(__NR_schedsetattr, pid, faux_real.addr, flags);
		
		flag = 0;
	}
}


void sched_setattrfuzz(unsigned int amount)
{
	loops = amount;
	do_s_attrfuzzing();
}
