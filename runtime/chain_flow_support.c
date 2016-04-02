/*
**
** File: cf_chain_flow_support.c
**
**
*/

#include "cf_chain_flow_support.h"

#include "cf_runtime_functions.h"
#include "cf_events.h"
#include "cf_chain_flow_include.h"

#include <string.h>



#define CHAIN_ENABLE_MASK  1
#define CHAIN_RESUME_MASK 2
#define CHAIN_ACTIVE_MASK  3

#define LINK_ACTIVE_MASK 1
#define LINK_INIT_MASK   2
#define LINK_RESET_STATE 1

static void chain_execute_chain( unsigned chain_id, unsigned event, unsigned *event_data );
static unsigned execute_cell( unsigned link_index,  const LINK_CELL *cell_ptr, unsigned event, unsigned *event_data );
static unsigned check_return_code( unsigned chain_id, unsigned link_offset, unsigned return_code );

static inline int  chain_enable_for_event( unsigned chain_id )
{
   int return_value;
   if( chain_state[chain_id] == CHAIN_ACTIVE_MASK )
   {
         return_value = 1;
   }
   else
   {
          return_value = 0;
   }
}


static inline int  chain_get_link_number( unsigned chain_id )
{
   return chain_control[chain_id].link_number;
}

static inline int  chain_get_link_offset( unsigned chain_id )
{
   return chain_control[chain_id].link_index;
}

static inline const LINK_CELL *get_cell_pointer( unsigned chain_id )
{
  return chain_control[chain_id].link_cells;
}

static inline void reset_all_links( int chain_id )
{
    unsigned link_number;
    unsigned link_offset;
    unsigned i;

    link_offset = chain_control[ chain_id ].link_index;
    link_number = chain_control[ chain_id ].link_number;
    for( i = 0; i< link_number; i++ )
    {
        link_state[link_offset] = LINK_RESET_STATE;
    }
    
}

static inline unsigned is_link_active( unsigned link_offset )
{
   return link_state[ link_offset] &LINK_ACTIVE_MASK;
}

static inline unsigned is_link_initialized( unsigned link_offset )
{
   return link_state[ link_offset] &LINK_INIT_MASK;
}

static inline void mark_disable_link( unsigned link_offset )
{
   link_state[ link_offset] &= ~LINK_ACTIVE_MASK;
}

static inline void mark_initialize_link( unsigned link_offset )
{
   link_state[ link_offset ] |= LINK_INIT_MASK;
}

void initialize_cf_system( void )
{
   int i;
   cf_initialize_event_manager();
   memset(link_state,0,sizeof(link_state));
   memset(link_data,0,sizeof(start_state));
   for( i = 0; i < CHAIN_NUM; i++ )
   {
     if( start_state[i] != 0 )
     {
        cf_enable_chain( i );
        
     }
     else
     {
        chain_state[i] &= ~CHAIN_ACTIVE_MASK;
     }
   }
}

void cf_enable_chain(unsigned chain_id )
{
   assert(chain_id<CHAIN_NUM);
   chain_state[chain_id] |= CHAIN_ACTIVE_MASK;
   reset_all_links(chain_id);
}

void cf_disable_chain(unsigned chain_id )
{
   assert(chain_id<CHAIN_NUM);
   chain_state[chain_id] &= ~CHAIN_ENABLE_MASK;
   
}



void cf_resume_chain(unsigned chain_id )
{
    assert(chain_id<CHAIN_NUM);
   chain_state[chain_id] |= CHAIN_RESUME_MASK;

}

void cf_suspend_chain(unsigned chain_id )
{
   assert(chain_id<CHAIN_NUM);
   chain_state[chain_id] &= ~CHAIN_RESUME_MASK;

}

void cf_process_cf_event( void )
{
   unsigned event;
   unsigned *event_data;
   int i;

   if(  cf_rx_event( &event, &event_data ) != 0 )
   {
      for( i = 0; i < CHAIN_NUM; i++ )
      {
         if( chain_enable_for_event( i ) != 0 )
         {
            chain_execute_chain( i, event, event_data );
         }


      }

  }

}





static void chain_execute_chain( unsigned chain_id, unsigned event, unsigned *event_data )
{
   unsigned        return_code;
   unsigned        link_number;
   unsigned        link_offset;
   unsigned        i;
   const LINK_CELL *cell_ptr;

   if( chain_enable_for_event( chain_id ) == 0 )
   {
       return;
   }
   link_number = chain_get_link_number( chain_id );
   link_offset = chain_get_link_offset( chain_id );
   cell_ptr    = get_cell_pointer( chain_id );
   for( i = 0; i < link_number; i++ )
   {
      if( is_link_active( link_offset ) != 0 )
      {
         return_code = execute_cell( link_offset, cell_ptr, event,event_data );
         if( check_return_code( i, link_offset,return_code ) == 0 )
         {
            break;
         }
      }
      cell_ptr++;
      link_offset++;
   }
}


static unsigned execute_cell(  unsigned link_index,  const LINK_CELL *cell_ptr, unsigned event, unsigned *event_data )
{
    unsigned return_code;

    if( is_link_initialized( link_index ) == 0 )
    {
       cell_ptr->func( &link_data[ link_index], cell_ptr->param_1, 
                       cell_ptr->param_2, cell_ptr->param_3,cell_ptr->param_4, CF_INIT_EVENT, NULL );
       

    }
    return_code = cell_ptr->func( &link_data[ link_index], cell_ptr->param_1, 
                  cell_ptr->param_2, cell_ptr->param_3,cell_ptr->param_4, event, event_data );

    return return_code;
}

static unsigned check_return_code( unsigned chain_id, unsigned link_offset, unsigned return_code )
{
      unsigned return_value;

      switch( return_code )
      {
          case CF_CONTINUE:
                return_value = 1;
                break;

          case CF_HALT:
                return_value = 0;
                break;

          case CF_DISABLE:
               return_value = 1;
               mark_disable_link( link_offset );
               break;

          case CF_RESET:
               return_value = 0;
               reset_all_links(chain_id);
               break;

           case CF_TERMINATE:
               return_value = 0;
               cf_disable_chain( chain_id );
               break;

           default:
                assert(0); // should not happen
     }
     return return_value;
}
                           




