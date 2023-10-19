from lefdef import C_LefReader
from lefdef import C_DefReader

# lef_reader = C_LefReader()
# _lef = lef_reader.read("/home/alaie/Nangate.lef")
# _lef.print()

def_reader = C_DefReader()
_def = def_reader.read("/home/alaie/bsg_chip.def")
_def.print()