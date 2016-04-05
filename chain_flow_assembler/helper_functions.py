


class Helper_Functions:

   def __init__( self, assembler):
      self.asm  = assembler

   def  one_step( self, function, param1=0,parm2=0,parm3=0 ):       
        self.asm.define_link("One_Step" , function, param1,parm2,parm3)
	self.asm.foriegn_helper_functions[function] = function 
   
   def  code_step( self, function, param1=0,parm2=0,parm3= 0 ):	
       self.asm.define_link("One_Step" , function, param1,parm2,parm3)
       self.asm.foriegn_helper_functions[function] = function 
       
   def  reset( self ):            
        self.asm.define_link_a("Reset" )

   def  send_event( self ,event,data):              
        self.asm.define_link_a("SendEvent",event,data)

   def  wait_tod( self,dow,hr,minute,sec ):         
        self.asm.define_link_a("WaitTod",hr,minute,sec )

   def  wait_event( self, event ):           
        self.asm.define_link_a("WaitEvent",event)

   def  wait_time( self,time_ticks ):         
        self.asm.define_link_a("WaitTime" ,time_ticks )

   def  wait( self,wait_function ):            
        self.asm.define_link_a("Wait", wait_functions)

   def  verify_not_tod( self,dow,hr,minute,sec ):         
        self.asm.define_link_a("Verify_Not_Tod",hr,minute,sec )

   def  verify_not_event( self, event ):           
        self.asm.define_link_a("Verify_Not_Event",event)

   def  verify_not_time( self,time_ticks ):         
        self.asm.define_link_a("Verify_Not_Timeout" ,time_ticks )


   def  verify( self,verify_function ):          
        self.asm.define_link_a("Verify",verify_functions) 



   def  nop( self ):          
        self.asm.define_link_a("Nop")

   def  enable_chain( self ,chain_1 = -1, chain_2 = -1, chain_3 = -1 ):                   
        self.asm.define_link_a("Enable_Chain",chain_1,chain_2,chain_3)

   def  disable_chain( self, chain_1 = -1, chain_2 = -1, chain_3 = -1):        
        self.asm.define_link_a("Disable_Chain",chain_1,chain_2,chain_3)


   def  change_state( self , link_number ):     
        self.asm.define_link_a("Change_State",link_number) 

   def  reset_system( self ):    
        self.asm.define_link_a("Reset_System")

   def  suspend_chain( self, chain_1 = -1, chain_2 = -1, chain_3 = -1 ):     
        self.asm.define_link_a("Suspend_Chain", chain_1, chain_2, chain_3)

   def  resume_chain_a( self ,chain_1 = -1, chain_2 = -1, chain_3 = -1 ):   
        self.asm.define_link("Resume_Chain",chain_1,chain_2,chain_3)
      



