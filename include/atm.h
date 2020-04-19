#ifndef __ATM_H_INCLUDE
#define __ATM_H_INCLUDE

#include <stdint.h>

struct atm_arg {
	void *data;
	unsigned int data_len;
};

struct chan_ops {
	uint8_t chan_type; // within a machine shared mem, external UDP?
	int (*recv)(struct atm_arg *arg);
	int (*send)(struct atm_arg *arg);
};

#endif
