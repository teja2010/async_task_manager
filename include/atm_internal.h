/* Include file for ATM Internals
 */
#ifndef __ATM_INTERNAL_H_INCLUDE
#define __ATM_INTERNAL_H_INCLUDE

#include "include/atm.h"

struct node_opts {
	uint8_t priority;
	uint64_t flags;
};

typedef enum {
	E_NODE_INIT = -1,

	E_NODE_WAITING = 0,
	E_NODE_RUNNING = 1,
} node_state_t;

struct atm_node {
	struct atm_node *next;
	uint64_t node_id;
	node_state_t state;
	struct node_opts opts;
	
	//
	int (*fptr) (struct atm_arg *arg);
};


struct atm_pkt {
	struct atm_pkt *next;
	struct atm_arg arg;
	//TODO add metadata
};

struct atm_channel {
	uint64_t chan_id;
	uint64_t from_node_id;
	uint64_t to_node_id;

	struct atm_pkt *queue;
	struct chan_ops cop;
};

void run_tasks();

#endif
