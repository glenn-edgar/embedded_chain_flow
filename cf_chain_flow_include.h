#ifndef _CF_ASSEMBLER_H_
#define _CF_ASSEMBLER_H_


#define CHAIN_NUM   1
#define LINK_NUM    3



#define  test_1   0
#define  test_2   1
#include "stdlib.h"
#include "cf_chain_flow_support.h"
#include "cf_runtime_functions.h"
#include "cf_external_functions.h"

char  chain_state[1];
char  link_state[3];
unsigned link_data[3];
const unsigned start_state[]={1};



const LINK_CELL CHAIN_HEART_BEAT_LINKS[]= 
{
{ (CF_FUN)wait_time_fn,NULL,500,0,0},
{ (CF_FUN)one_step_fn,(CF_FUN_AUX)toggle_heart_beat,0,0,0},
{ (CF_FUN)reset_fn,NULL,0,0,0 }
};



const CHAIN_LINK chain_control[] =
{
{ 0,0,3,CHAIN_HEART_BEAT_LINKS}

};
#endif
