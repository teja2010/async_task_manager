#include "include/atm.h"
#include "include/atm_internal.h"

/*
 *       Init
 *       |
 *  +--> Waiting <- recv from chan()
 *  |    |
 *  |    Copy args onto stack
 *  |    |
 *  |    Running
 *  |     ------- start f()
 *  |               |
 *  |     ------- end of f()
 *  |    |
 *  +----+
 *
 */

void run_tasks_cycle(int cycles)
{
}

void check_assignment()
{
}

void report_stats()
{
}

void run_tasks()
{
	//install signal handlers

	while(1) {
		check_assignment();

		run_tasks_cycle(0);

		report_stats();
	}
}
