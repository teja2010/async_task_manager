/* Include file for ATM controller
 */
#ifndef __ATM_CONTROL_H_INCLUDE
#define __ATM_CONTROL_H_INCLUDE

#include <errno.h>
#include "include/atm.h"

/* provide necessary arguments.
 * If successful, returns 0
 * else returns -1 and errno will be set.
 */

int add_node_from_file(char *bin_file, char *function_name, uint64_t *node_id);
int add_node_direct(int (*fptr) (struct atm_arg *arg), uint64_t *node_id);

int create_channel(struct chan_ops *ops, uint64_t *chan_id);
int connect_channel(uint64_t from_node_id, uint64_t to_node_id, uint64_t chan_id);


#endif
