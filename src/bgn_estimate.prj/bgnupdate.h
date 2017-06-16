//#ifndef __BGNUPDATE_H__
//#define __BGNUPDATE_H__
#include <iostream>
#include <hls_video.h>

//Prototipo de la funcion de actualizacion de fondo
void backgroundUpdate(AXI_STREAM& frameg, AXI_STREAM& imseg, AXI_STREAM& festat,
		              AXI_STREAM& fondog, int rows, int cols)

#define _CHANGEFACTOR_BACKGROUND 24
#define _CHANGEFACTOR_FOREGROUND 35
#define MAX_ROW 240
#define MAX_COL 352
#define INPUT_IMAGE      "/home/bruno/Documentos/WorkSpace/Vivado/bgn_estimate.prj/imgin.jpg"
#define SEGMENTED_IMAGE  "/home/bruno/Documentos/WorkSpace/Vivado/bgn_estimate.prj/segm.jpg"
#define SEED_BGN         "/home/bruno/Documentos/WorkSpace/Vivado/bgn_estimate.prj/bgmodel.jpg"
#define OUTPUT_IMAGE     "/home/bruno/Documentos/WorkSpace/Vivado/bgn_estimate.prj/output.jpg"
#define OUTPUT_IMAGE_GOLDEN  "/home/bruno/Documentos/WorkSpace/Vivado/bgn_estimate.prj/golden_output.jpg"

//#endif __BGNUPDATE_H__
