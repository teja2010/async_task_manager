#include <stdio.h>
#include "include/atm.h"
#include "include/atm_internal.h"

int main(int argc, char *argv[])
{
	printf("Started ATM");
	
	//1. connect to controller
	//2. fork processes to run tasks, share some memory with each process
	//   each process pins itself to a CPU, wait for tasks to get assigned
	//3. based on messages from controller, assign tasks.
	//4. collect information shared by processes to share information with
	//   the controller
	//5. If a process is dead, start another process
}


