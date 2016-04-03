from helper_functions import  Helper_Functions
from assembler          import  CF_Assembler

cf = CF_Assembler()
hf = Helper_Functions( cf )

cf.define_chain( "heart_beat",True)
hf.wait_time(500)
hf.one_step(" toggle_heart_beat")
hf.one_step("pat_watch_dog")
hf.reset()
cf.end_chain()

cf.generate_c_header()


