from lefdef import readLef

lef = readLef("/home/alaie/stuff/skywater-pdk/libraries/sky130_fd_sc_hd/latest/cells/buf/sky130_fd_sc_hd__buf_4.lef")

print(lef.name)