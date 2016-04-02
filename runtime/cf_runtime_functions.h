/*

  File: cf_runtime_functions.h


*/

#ifndef _CF_RUNTIME_FUNCTIONS_H_
#define _CF_RUNTIME_FUNCTIONS_H_



#include "cf_chain_flow_support.h"
int terminate_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int halt_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int one_step_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int code_step_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int reset_fn( unsigned *local_storeage ,void *param1, void  *param2, void *param3, void *param4, unsigned event,void *event_data );
int send_event_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int wait_tod_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int wait_event_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int wait_time_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );   
int wait_condition_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int verify_condition_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int verify_not_timeout_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int verify_not_event_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int verify_not_tod_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int nop_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int enable_chain_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int disable_chain_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int change_state_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int system_reset_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int suspend_chain_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
int resume_chain_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data );
 






#endif
