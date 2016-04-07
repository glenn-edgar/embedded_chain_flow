/*
**
** File: cf_external_functions.c
** This file is manually generated
** 
**
*/
#include <device.h>
#include "cf_events.h"
#include "moving_average.h"
#include "cf_external_functions.h"
#include "a_to_d_functions.h"

#define TICK_INTERVAL          8

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



/*
** Die Temperature functions
**
*/
static int16    temp_die;
static MOVING_AVERAGE_STRUCT ma_die_temp;
int initialize_die_temp_measurement(unsigned link_id, unsigned param_1,
  unsigned param_2, unsigned param_3, unsigned event, unsigned data)
{
    ma_initialize( &ma_die_temp, .1 );
    
    return CF_DISABLE;
}

int meaure_die_temperature(unsigned link_id, unsigned param_1,
  unsigned param_2, unsigned param_3, unsigned event, unsigned data)
{
    int16 temp;
    DieTemp_1_GetTemp(&temp);
    temp = ((temp*9)/5)+32; 
    temp_die = ma_update( &ma_die_temp, temp);
    return CF_DISABLE;
}




/*
**
** Initialize Function
**
**
*/
CY_ISR_PROTO( sleep_timer_interrupt )
{
    SleepTimer_1_GetStatus();
    cf_send_interrupt_event(  CF_TIME_TICK_EVENT, TICK_INTERVAL );
    
}

int initialize_eeprom(unsigned link_id, unsigned param_1,
  unsigned param_2, unsigned param_3, unsigned event, unsigned data)
{
    EEPROM_1_Start();
    EEPROM_1_UpdateTemperature();
    return CF_DISABLE;
}


int start_watchdog(unsigned link_id, unsigned param_1,
  unsigned param_2, unsigned param_3, unsigned event, unsigned data)
{
    //CyWdtStart( CYWDT_1024_TICKS, CYWDT_LPMODE_NOCHANGE ); // 2 -3 second interval
    return CF_DISABLE;
}




int initialize_analog(unsigned link_id, unsigned param_1,
  unsigned param_2, unsigned param_3, unsigned event, unsigned data)
{
    ad_init_se(); 
    ad_init_de();
    DAC_1_Start();
    DAC_2_Start();
    WaveDAC8_1_Start();
    ad_setup_interrupt();
    return CF_DISABLE;
}

int enable_timer_interrupt(unsigned link_id, unsigned param_1,
  unsigned param_2, unsigned param_3, unsigned event, unsigned data)
{

    isr_1_StartEx(sleep_timer_interrupt); 
    SleepTimer_1_Start();
    return CF_DISABLE;
}

int enable_interrupts(unsigned link_id, unsigned param_1,
  unsigned param_2, unsigned param_3, unsigned event, unsigned data)
{
   CyGlobalIntEnable;
   return CF_DISABLE;
}

int update_eeprom_temp(unsigned link_id, unsigned param_1,
  unsigned param_2, unsigned param_3, unsigned event, unsigned data)
{
   EEPROM_1_UpdateTemperature();
   return CF_DISABLE;   
}

