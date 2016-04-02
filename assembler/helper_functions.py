


class Helper_Functions:

   def __init__( self, assembler):
      self.asm  = assembler

   def  one_step( self, function, param1=0,parm2=0,parm3=0 ):       
        self.asm.define_link("One_Step" , function, param1,param2,parm3)

   def  reset( self ):            
        self.asm.define_link("Reset" )

   def  send_event( self ,event,data):              
        self.asm.define_link("SendEvent",event,data)

   def  wait_tod( self,dow,hr,minute,sec ):         
        self.asm.define_link("WaitTod",dow,hr,minute,sec )

   def  wait_event( self, event ):           
        self.asm.define_link("WaitEvent",event)

   def  wait_time( self,time_ticks ):         
        self.asm.define_link("WaitTime" ,time_ticks )

   def  wait( self,wait_function ):            
        self.asm.define_link("Wait", wait_functions)

   def  verify_not_tod( self,dow,hr,minute,sec ):         
        self.asm.define_link("Verify_Not_Tod",dow,hr,minute,sec )

   def  verify_not_event( self, event ):           
        self.asm.define_link("Verify_Not_Event",event)

   def  verify_not_time( self,time_ticks ):         
        self.asm.define_link("Verify_Not_Timeout" ,time_ticks )


   def  verify( self,verify_function ):          
        self.asm.define_link("Verify",verify_functions) 



   def  nop( self ):          
        self.asm.define_link("Nop")

   def  enable_chain( self ,chain_1 = -1, chain_2 = -1, chain_3 = -1, chain_4 = -1 ):                   
        self.asm.define_link("Enable_Chain",chain_1,chain_2,chain_3,chain_4)

   def  disable_chain( self, chain_1 = -1, chain_2 = -1, chain_3 = -1, chain_4 = -1 ):        
        self.asm.define_link("Disable_Chain",chain_1,chain_2,chain_3,chain_4)


   def  change_state( self , link_number ):     
        self.asm.define_link("Change_State",link_number) 

   def  reset_system( self ):    
        self.asm.define_link("Reset_System")

   def  suspend_chain( self, chain_1 = -1, chain_2 = -1, chain_3 = -1, chain_4 = -1 ):     
        self.asm.define_link("Suspend_Chain", chain_1, chain_2, chain_3, chain_4)

   def  resume_chain( self ,chain_1 = -1, chain_2 = -1, chain_3 = -1, chain_4 = -1 ):   
        self.asm.define_link("Resume_Chain",chain_1,chain_2,chain_3,chain_4)
      



