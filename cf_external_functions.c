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