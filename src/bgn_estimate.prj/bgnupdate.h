//#ifndef __BGNUPDATE_H__
//#define __BGNUPDATE_H__
#include <hls_video.h>
#include <iostream>
#include <hls_video.h>
#include <hls_opencv.h>

//Prototipo de la funcion de actualizacion de fondo
void backgroundUpdate(const IplImage* frameg, const IplImage* imseg, IplImage* festat, 
                      IplImage* fondog);

#define _CHANGEFACTOR_BACKGROUND 24
#define _CHANGEFACTOR_FOREGROUND 35
#define INPUT_IMAGE      "/home/bruno/Documentos/WorkSpace/Vivado/bgn_estimate.prj/imgin.jpg"
#define SEGMENTED_IMAGE  "/home/bruno/Documentos/WorkSpace/Vivado/bgn_estimate.prj/segm.jpg"
#define SEED_BGN         "/home/bruno/Documentos/WorkSpace/Vivado/bgn_estimate.prj/bgmodel.jpg"
#define OUTPUT_IMAGE     "/home/bruno/Documentos/WorkSpace/Vivado/bgn_estimate.prj/output.jpg"
#define OUTPUT_IMAGE_GOLDEN  "/home/bruno/Documentos/WorkSpace/Vivado/bgn_estimate.prj/golden_output.jpg"

//#endif __BGNUPDATE_H__
