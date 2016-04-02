#ifndef _CF_ASSEMBLER_H_
#define _CF_ASSEMBLER_H_



#define CHAIN_NUM   2
#define LINK_NUM    9



#define  test_1   0
#define  test_2   1



char  chain_state[2];
char  link_state[9];
unsigned link_data[9];
const unsigned start_state[]={1,0};



const LINK_CELL CHAIN_test_1_LINKS[]= 
{
{ enable_chain_fn,(void *)test_1,(void *)test_2,(void *)-1,(void *)-1},
{ disable_chain_fn,(void *)test_1,(void *)test_2,(void *)-1,(void *)-1},
{ suspend_chain_fn,(void *)test_1,(void *)test_2,(void *)-1,(void *)-1},
{ resume_chain_fn,(void *)test_1,(void *)test_2,(void *)-1,(void *)-1},
{ system_reset_fn,(void *)0,(void *)0,(void *)0,(void *)0},
{ reset_fn,(void *)0,(void *)0,(void *)0,(void *)0},
};
const LINK_CELL CHAIN_test_2_LINKS[]= 
{
{ send_event_fn,(void *)TEST_EVENT,(void *)23,(void *)0,(void *)0},
{ wait_event_fn,(void *)TEST_EVENT,(void *)0,(void *)0,(void *)0},
{ reset_fn,(void *)0,(void *)0,(void *)0,(void *)0},
};



const CHAIN_LINK chain_control[] =
{
{ 0,0,6,CHAIN_test_1_LINKS},
{ 6,1,3,CHAIN_test_2_LINKS}
};
#endif
