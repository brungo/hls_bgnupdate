############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
set_directive_interface -mode s_axilite -bundle CONTROL_BUS "backgroundUpdate"
set_directive_interface -mode axis -register -register_mode both "backgroundUpdate" frameg
set_directive_interface -mode axis -register -register_mode both "backgroundUpdate" imseg
set_directive_interface -mode axis -register -register_mode both "backgroundUpdate" festat
set_directive_interface -mode axis -register -register_mode both "backgroundUpdate" fondog
set_directive_interface -mode s_axilite -offset 0x14 -bundle CONTROL_BUS "backgroundUpdate" rows
set_directive_interface -mode ap_stable "backgroundUpdate" rows
set_directive_interface -mode s_axilite -offset 0x1C -bundle CONTROL_BUS "backgroundUpdate" cols
set_directive_interface -mode ap_stable "backgroundUpdate" cols
set_directive_dataflow "backgroundUpdate"
set_directive_pipeline "backgroundUpdate/col_iter"
set_directive_dataflow "backgroundUpdate"
