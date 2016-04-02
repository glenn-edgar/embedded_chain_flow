/*

File: cf_runtime_functions.c
Implements of codes for cf_runtime_functions.c


*/

#include <stdint.h>
#include <stdlib.h>
#include "cf_chain_flow_support.h"

#include "cf_runtime_functions.h"
#include "cf_events.h"


int terminate_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
   return CF_TERMINATE;
}


int halt_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{

  return CF_HALT;
}


 
int reset_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
   
   return CF_RESET;

}

int one_step_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
   CF_FUN  funct_ptr;

   funct_ptr = (CF_FUN) param1;

   if( event== CF_INIT_EVENT )
   {
     funct_ptr(local_storeage, param1, param2,param3,param4,event,event_data );
   }
   return CF_DISABLE; 
}

int code_step_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
   CF_FUN  funct_ptr;

   funct_ptr = (CF_FUN) param1;

   
   return funct_ptr(local_storeage, param1, param2,param3,param4,event,event_data );

}


int send_event_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
   intptr_t temp;
   temp = (intptr_t)param1;
   if( event== CF_INIT_EVENT )
   {
      cf_send_event( (unsigned)temp,param2);
   }
   return CF_DISABLE;
}


int wait_tod_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
  
   return CF_DISABLE;  // implemented on specific system

}

  
int wait_event_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
   int      return_value;
   intptr_t temp;
   temp = (intptr_t)param1;

   if( event == temp )
   {
      return_value = CF_DISABLE;
   }
   else
   {
      return_value = CF_HALT;
   }
   return return_value;   

}



int wait_time_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
  int return_value;

  return_value = CF_HALT;
  if( event == CF_INIT_EVENT )
  {
     *local_storeage = 0;
  }
  else if( event == CF_TIME_TICK_EVENT )
  {
     *local_storeage += (intptr_t)(event_data);
     if(*local_storeage > (intptr_t)param1 )
     {
       return_value = CF_DISABLE;
     }
  }
  else
  {
    ; // do noting
  }
  return return_value;

}

     
int wait_condition_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
   int return_value;
   CF_FUN  funct_ptr;

   funct_ptr = (CF_FUN) param1;
   if( funct_pr( local_storeage , param1, param2, param3, param4, event,event_data ) != 0)
   {
     return_value = CF_DISABLE;
   }
   else
   {
     return_value = CF_HALT;
   } 

}

int verify_condition_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
   int return_value;
   CF_FUN  funct_ptr;

   if( funct_pr( local_storeage , param1, param2, param3, param4, event,event_data ) != 0)
   {
     return_value = CF_RESET;
   }
   else
   {
     return_value = CF_CONTINUE;
   } 

}
 
int verify_not_timeout_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
  int return_value;

  return_value = CF_CONTINUE;
  if( event == CF_INIT_EVENT )
  {
     *local_storeage = 0;
  }
  else if( event == CF_TIME_TICK_EVENT )
  {
     *local_storeage += (intptr_t)(event_data);
     if(*local_storeage > (intptr_t)param1 )
     {
       return_value = CF_RESET;
     }
  }
  else
  {
    ; // do noting
  }
  return return_value;

}

int verify_not_event_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
   unsigned temp;
   int    return_value;
   temp = (intptr_t)param1;
   if( event == temp )
   {
      return_value = CF_RESET;
   }
   else
   {
      return_value = CF_CONTINUE;
   }
   return return_value;   

}

int verify_not_tod_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
  
   return CF_DISABLE;  // implemented on specific system

}

int nop_fn( unsigned *local_storeage ,void *param1, void  *param2, void *param3, void *param4, unsigned event,void *event_data )
{
  return CF_DISABLE;
}
 

 
int change_state_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
   if( event == CF_INIT_EVENT )
   {
      cf_change_state((intptr_t)param1);
   }
   return CF_DISABLE;


}

int system_reset_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
   exit(0);
}

int enable_chain_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
   if( event == CF_INIT_EVENT )
   {
      cf_enable_chain((intptr_t)param1);
      cf_enable_chain((intptr_t)param2);
      cf_enable_chain((intptr_t)param3);
      cf_enable_chain((intptr_t)param4);
   }
   return CF_DISABLE;

}
  
int disable_chain_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
   if( event == CF_INIT_EVENT )
   {
      cf_disable_chain((intptr_t)param1);
      cf_disable_chain((intptr_t)param2);
      cf_suspend_chain((intptr_t)param3);
      cf_suspend_chain((intptr_t)param4);
   }
   return CF_DISABLE;


}
int suspend_chain_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
   if( event == CF_INIT_EVENT )
   {
      cf_suspend_chain((intptr_t)param1);
      cf_suspend_chain((intptr_t)param2);
      cf_suspend_chain((intptr_t)param3);
      cf_suspend_chain((intptr_t)param4);
   }
   return CF_DISABLE;
}

int resume_chain_fn( unsigned *local_storeage ,void *param1, void *param2, void *param3, void *param4, unsigned event,void *event_data )
{
   if( event == CF_INIT_EVENT )
   {
      cf_resume_chain((intptr_t)param1);
      cf_resume_chain((intptr_t)param2);
      cf_resume_chain((intptr_t)param3);
      cf_resume_chain((intptr_t)param4);
   }
   return CF_DISABLE;

}







