############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project bgn_update.prj
set_top backgroundUpdate
add_files bgnupdate.cpp
add_files -tb bgnupdate_test.cpp -cflags "-DHW_COSIM"
open_solution "solution1"
set_part {xc7z020clg484-1} -tool vivado
create_clock -period 10 -name default
source "./bgn_update.prj/solution1/directives.tcl"
csim_design -clean -compiler gcc
csynth_design
cosim_design
export_design -format ip_catalog
