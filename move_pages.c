#include "utils.h"
#include "sysc_nums.h"
#include "sys_util.h"




unsigned int loops;
int page_size;


/* TODO fake addresses from realorfake in utils.h 
 *  Also lets send some weird mapped addresses from funky syscalss like:
 *  
 *  normal mmap
 *  android binder's mmap();
 *  the new memfd_create syscall.
 */ 
 
static struct addrtype* map_page(void)
{
	struct addrtype *page = malloc(sizeof(page*));
	if(!page){
		printf("Failed to malloc memory for addr type struct\n");
		exit(EXIT_FAILURE);
	}

	/* TODO check ret from mem_align so when we pass to free we dont shit ourselfs */
	posix_memalign(&page->addr, page_size, page_size);
	page->type = PAGED;
	

	return page;
}


/*

       long move_pages(int pid, unsigned long count, void **pages,
                       const int *nodes, int *status, int flags);
 */
/* MAX_NODES is 64 */
static void do_move_move_pages_fuzzing(void)
{
	pid_t pid;
	unsigned long count;
	
	struct addrtype **addr_list;
	int addr_listsize = rand() % 65;
	int temp = 0;
	void **pages;
	int *nodes;
	int *stats;
	int flag = 0;

	addr_list =  malloc(sizeof(*addr_list) * 64);
	if(!addr_list){
		printf("Failed to allocate an array for 64 addrytypes\n");
		return;
	}
	pages = malloc(sizeof(void*) * 64);
	if(!pages){
		printf("Failed to allocate 64 void*'s for pages\n");
		free(addr_list);
		return;
	}
	
        nodes = malloc(sizeof(int) * 64);
	stats = malloc(sizeof(int) * 64);
	
	if(!nodes || !stats){
		printf("Failed to allocate nodes or stats\n");
		free(pages);
		free(addr_list);
		/* dunno what one failed, if not both try and free anyway */
		free(nodes);
		free(stats);
	       
		return;
	}


	while(loops--){
		pid = getfakeorrealpid();
		while(temp < addr_listsize){
			/* Fill up the addr_list of mem aligned addresses */
			addr_list[temp] = map_page();
			pages[temp] = addr_list[temp]->addr;
			++temp;
		}

		temp = 0;
		while(temp < addr_listsize){
			nodes[temp] = rand() % 65;
			//Randomly go out side of API
			if(trueorfalse() && trueorfalse()){
				nodes[temp] = rand();
			}
			++temp;
		}
		flag = getrandomflags();
		syscall(__NR_movepages, pid,addr_listsize, pages, 
			nodes, stats, flag);


		/* clean up */
		temp = 0;
		while(temp < addr_listsize){
			free(pages[temp]);
		}
		temp = 0;
		addr_listsize = rand() % 65;
	}
	

	/* end of function clean up */
	
	free(addr_list);
	free(pages);
	free(nodes);
	free(stats);
	return;
}



void move_pagesfuzz(unsinged int amount)
{
	loops = amount;
	page_size = getpagesize();
	do_move_pages_fuzzing();

}
