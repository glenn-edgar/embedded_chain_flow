import copy
import opcodes
class CF_Assembler:

   def __init__( self ):
       self.chain_active   = False
       self.cf_definition  = {}
       self.chain_name     = None
       self.links          = []
       self.opcodes        = opcodes.Opcodes()
       self.chain_list     = []    
       self.link_number    = 0
       self.link_list      = []
       self.start_flag_list = []

   def define_chain( self, chain_name, start_flag = False ):
       if self.chain_active == True:
          raise ValueError("end_chain needed before define_chain")
       if self.cf_definition.has_key( chain_name ):
            raise ValueError("duplicate chain name")
       self.chain_active = True
       self.chain_name = chain_name
       self.links      = []
       self.link_list.append(self.link_number)
       self.start_flag_list.append(start_flag)

   def define_link( self, opcode_name, param1 = 0, param2 = 0, param3 = 0, param4 = 0 ):
       if self.opcodes.has_key( opcode_name ) == False:
           raise ValueError("improper opcode "+opcode_name )
       self.links.append({ "opcode":self.opcodes.get_opcode(opcode_name),"param1":param1,"param2":param2,"param3":param3,"param4":param4 })
       self.link_number = self.link_number+1

   def end_chain( self ):
       self.chain_list.append(self.chain_name)
       self.cf_definition[self.chain_name] = self.links
       self.chain_active = False
       self.chain_name = self.chain_name
       self.links      = []

   def generate_chain_elements(self):
       links_elements = []
       chain_elements = []
       chain_elements.append("const CHAIN_LINK chain_control[] =")
       chain_elements.append("{")

     
       for i in range(0, len(self.chain_list)):
          chain_name = self.chain_list[i]
          defs = self.cf_definition[chain_name]
          link_index = self.link_list[i]
          if i == (len(self.chain_list)-1):
              chain_elements.append("{ "+str(link_index)+","+str(i)+","+str(len(defs))+",CHAIN_"+chain_name+"_LINKS}")
          else:
              chain_elements.append("{ "+str(link_index)+","+str(i)+","+str(len(defs))+",CHAIN_"+chain_name+"_LINKS},")


       chain_elements.append("};")
       return chain_elements
     
   def generate_link_elements( self ):
       link_elements = []
       for i in range(0,len(self.chain_list)):
          chain_name = self.chain_list[i]
          defs = self.cf_definition[chain_name]
          link_elements.append("const LINK_CELL CHAIN_"+chain_name+"_LINKS[]= ")
          link_elements.append("{")
          for j in range(0,len(defs)):
              de = defs[j]
              temp = "{ "+str(de["opcode"])+",(void *)"+str(de["param1"])+",(void *)"+str(de["param2"])
              temp = temp +",(void *)"+str(de["param3"])+",(void *)"+str(de["param4"])+"}"
              if i == (len(defs)-1):
                link_elements.append(temp)
              else:
                link_elements.append(temp+",")

          link_elements.append("};")
       return link_elements
 

   def generate_c_header( self  ):
       output_file = "cf_chain_flow_include.h"
       fh = open(output_file , "w")
       
       fh.write("#ifndef _CF_ASSEMBLER_H_\n")
       fh.write("#define _CF_ASSEMBLER_H_\n")
       fh.write("\n\n\n") 
       fh.write("#define CHAIN_NUM   "+str(len(self.chain_list))+"\n")
       fh.write("#define LINK_NUM    "+str(self.link_number)+"\n" )
       fh.write("\n\n\n")
       for i in range(0,len(self.chain_list)):
           fh.write("#define  "+self.chain_list[i]+"   "+ str(i)+"\n")
       
        
       fh.write("\n\n\n")
       
       fh.write("char  chain_state["+str(len(self.chain_list)) +"];\n")
       fh.write("char  link_state["+str(self.link_number)+"];\n") 
       fh.write("unsigned link_data["+str(self.link_number)+"];\n")
       temp =[]
       for i in range( 0,len(self.start_flag_list)):
          
             if self.start_flag_list[i] == True:
                temp.append("1")
             else:
                temp.append("0")
       fh.write("const unsigned start_state[]={"+",".join(temp)+"};\n")
       fh.write("\n\n\n")
       link_data = self.generate_link_elements()
        
       for i in link_data:
          fh.write(i+"\n")

       fh.write("\n\n\n")
       chain_data = self.generate_chain_elements()
       
       for i in chain_data:
          fh.write(i+"\n")
       fh.write("#endif\n")
       fh.close() 

# test code
if __name__ == "__main__":
   from helper_functions import Helper_Functions
   cf = CF_Assembler()
   hf = Helper_Functions( cf )

   cf.define_chain( "test_1",True)
   hf.enable_chain("test_1","test_2")
   hf.disable_chain("test_1","test_2")
   hf.suspend_chain("test_1","test_2")
   hf.resume_chain("test_1","test_2")
   hf.reset_system()
   hf.reset()
   cf.end_chain()

   cf.define_chain( "test_2",False)
   hf.send_event("TEST_EVENT",23)
   hf.wait_event("TEST_EVENT")
   hf.reset()
   
   cf.end_chain()



   cf.generate_c_header()


     