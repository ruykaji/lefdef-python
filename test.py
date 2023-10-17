from lefdef import C_LefReader

lef_reader = C_LefReader()

lef = lef_reader.read("/home/alaie/Nangate.lef")

lef.print()