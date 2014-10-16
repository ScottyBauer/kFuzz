#include "utils.h"
#include "sysc_nums.h"
#include "sys_util.h"



unsigned int loops;

enum kcmp_type {
	KCMP_FILE,
	KCMP_VM,
	KCMP_FILES,
	KCMP_FS,
	KCMP_SIGHAND,
	KCMP_IO,
	KCMP_SYSVSEM,
	KCMP_TYPES,
};

int arrayOfEnum[8] = {	KCMP_FILE, KCMP_VM, KCMP_FILES, 
			KCMP_FS, KCMP_SIGHAND, KCMP_IO,
			KCMP_SYSVSEM, KCMP_TYPES 
};


/*
 * 
 *       int kcmp(pid_t pid1, pid_t pid2, int type,
 *              unsigned long idx1, unsigned long idx2);
 */
static void do_kcmp_fuzzing(void)
{
	pid_t pid1, pid2;
	enum kcmp_type enum_types;
	unsigned long fd_idx1, fd_idx2;
	
	while(loops--){
		pid2 = getfakeorrealpid();
	        pid1 = getfakeorrealpid();
		enum_types = arrayOfEnum[rand() % 8]; //0->7
		fd_idx1 = rand64();
		fd_idx2 = rand64();
		syscall(__NR_kcmp, pid1, pid2, enum_types, fd_idx1,
			fd_idx2);
	}	
}



void kcmpfuzz(unsigned int amount){
	loops = amount;
	do_kcmp_fuzzing();
}
