/*
**
** File: cf_external_functions.c
** This file is manually generated
** 
**
*/
#include <device.h>
#include "cf_external_functions.h"


int toggle_heart_beat(unsigned link_id, unsigned param_1,
                               unsigned param_2, unsigned param_3, 
			       unsigned event, unsigned data)
{
	
           
   heart_beat_pin_Write( !heart_beat_pin_Read() );
   return CF_DISABLE;       

}

int  pat_watch_dog(unsigned link_id, unsigned param_1,
  unsigned param_2, unsigned param_3, unsigned event, unsigned data)
{
    CyWdtClear();
    return CF_DISABLE;
}



int16    temp_die;
int meaure_die_temperature(unsigned link_id, unsigned param_1,
  unsigned param_2, unsigned param_3, unsigned event, unsigned data)
{
    DieTemp_1_GetTemp(&temp_die);
    temp_die = ((temp_die*9)/5)+32;                     ;

    return CF_DISABLE;
}
