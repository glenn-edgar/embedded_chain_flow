/*

File: cf_runtime_functions.c
Implements of codes for cf_runtime_functions.c


*/

#include <stdint.h>
#include <stdlib.h>
#include "cf_chain_flow_support.h"

#include "cf_runtime_functions.h"
#include "cf_events.h"


int terminate_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
   return CF_TERMINATE;
}


int halt_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{

  return CF_HALT;
}


 
int reset_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
   
   return CF_RESET;

}

int one_step_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
  



   if( event== CF_INIT_EVENT )
   {
      param_1(link_id, param_2,param_3,param_4,event,event_data );
   }
   return CF_DISABLE; 
}

int code_step_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
   
   return param_1( link_id, param_2,param_3,param_4,event,event_data );

}


int send_event_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
 
   if( event== CF_INIT_EVENT )
   {
      cf_send_event( param_2, param_3 );
   }
   return CF_DISABLE;
}


int wait_tod_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
  
   return CF_DISABLE;  // implemented on specific system

}

  
int wait_event_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
   int      return_value;

   if( event == param_2 )
   {
      return_value = CF_DISABLE;
   }
   else
   {
      return_value = CF_HALT;
   }
   return return_value;   

}



int wait_time_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
  int return_value;
  unsigned value;
  
  if( event == CF_INIT_EVENT )
  {
       cf_store_cell_value( link_id , 0 );

  }
  else if( event == CF_TIME_TICK_EVENT )
  {
     value = cf_get_cell_value( link_id );
     value += event_data;
     cf_store_cell_value(link_id, value);

     if( value >= param_2 )
     {
       return_value = CF_DISABLE;
     }
     else
     {
        return_value = CF_HALT;
     }
  }
  else
  {
       return_value = CF_HALT;
  }
  return return_value;

}
int wait_condition_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
   int return_value;
  
   
   if( param_1( link_id , param_2, param_3, param_4, event,event_data ) != 0)
   {
     return_value = CF_DISABLE;
   }
   else
   {
     return_value = CF_HALT;
   } 
   return return_value;

}     

int verify_condition_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
   int return_value;
  
   
   if( param_1( link_id , param_2, param_3, param_4, event,event_data ) != 0)
   {
     return_value = CF_CONTINUE;
   }
   else
   {
     return_value = CF_RESET;
   } 
   return return_value;

}    
 
int verify_not_timeout_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
  int return_value;
  unsigned value;
  
  if( event == CF_INIT_EVENT )
  {
       cf_store_cell_value( link_id , 0 );

  }
  else if( event == CF_TIME_TICK_EVENT )
  {
     value = cf_get_cell_value( link_id );
     value += event_data;
     cf_store_cell_value(link_id, value);

     if( value >= param_2 )
     {
       return_value = CF_RESET;
     }
     else
     {
        return_value = CF_CONTINUE;
     }
  }
  else
  {
       return_value = CF_CONTINUE;
  }
  return return_value;

}


int verify_not_event_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
  
   int    return_value;
   
   if( event == param_2 )
   {
      return_value = CF_RESET;
   }
   else
   {
      return_value = CF_CONTINUE;
   }
   return return_value;   

}

int verify_not_tod_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
  
   return CF_DISABLE;  // implemented on specific system

}

int nop_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
  return CF_DISABLE;
}
 

 
int change_state_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
   if( event == CF_INIT_EVENT )
   {
      cf_change_state(param_2, (unsigned)(intptr_t)param_3);
   }
   return CF_DISABLE;


}

int system_reset_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
   exit(0);
}

int enable_chain_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
   if( event == CF_INIT_EVENT )
   {
      
      cf_enable_chain((intptr_t)param_2);
      cf_enable_chain((intptr_t)param_3);
      cf_enable_chain((intptr_t)param_4);
   }
   return CF_DISABLE;

}
  
int disable_chain_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
   if( event == CF_INIT_EVENT )
   {

      cf_disable_chain((intptr_t)param_2);
      cf_suspend_chain((intptr_t)param_3);
      cf_suspend_chain((intptr_t)param_4);
   }
   return CF_DISABLE;


}
int suspend_chain_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
   if( event == CF_INIT_EVENT )
   {
 
      cf_suspend_chain((intptr_t)param_2);
      cf_suspend_chain((intptr_t)param_3);
      cf_suspend_chain((intptr_t)param_4);
   }
   return CF_DISABLE;
}

int resume_chain_fn( unsigned link_id, CF_FUN_AUX param_1, unsigned param_2, 
    unsigned param_3, unsigned param_4,  unsigned event, unsigned event_data)
{
   if( event == CF_INIT_EVENT )
   {
      
      cf_resume_chain((intptr_t)param_2);
      cf_resume_chain((intptr_t)param_3);
      cf_resume_chain((intptr_t)param_4);
   }
   return CF_DISABLE;

}







