#ifndef _CF_ASSEMBLER_H_
#define _CF_ASSEMBLER_H_



#define CHAIN_NUM   2
#define LINK_NUM    7



char  chain_state[2];
char  link_state[7];
unsigned link_data[7];
const unsigned start_state[]={1,1};



const LINK_CELL CHAIN_heart_beat_LINKS[]= 
{
{ wait_time_fn,(CF_FUN_AUX)NULL,(unsigned)500,(unsigned)0,(unsigned)0},
{ one_step_fn,(CF_FUN_AUX) toggle_heart_beat,(unsigned)0,(unsigned)0,(unsigned)0},
{ one_step_fn,(CF_FUN_AUX)pat_watch_dog,(unsigned)0,(unsigned)0,(unsigned)0},
{ reset_fn,(CF_FUN_AUX)NULL,(unsigned)0,(unsigned)0,(unsigned)0},
};
const LINK_CELL CHAIN_measure_die_temperature_LINKS[]= 
{
{ one_step_fn,(CF_FUN_AUX)meaure_die_temperature,(unsigned)0,(unsigned)0,(unsigned)0},
{ wait_time_fn,(CF_FUN_AUX)NULL,(unsigned)10000,(unsigned)0,(unsigned)0},
{ reset_fn,(CF_FUN_AUX)NULL,(unsigned)0,(unsigned)0,(unsigned)0},
};



const CHAIN_LINK chain_control[] =
{
{ 0,0,4,CHAIN_heart_beat_LINKS},
{ 4,1,3,CHAIN_measure_die_temperature_LINKS}
};
#endif
