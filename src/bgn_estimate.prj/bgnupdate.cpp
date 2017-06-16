#include "bgnupdate.h"

void backgroundUpdate(AXI_STREAM& frameg, AXI_STREAM& imseg, AXI_STREAM& festat,
		              AXI_STREAM& fondog, int rows, int cols)
{
   const int MINRUIDO=10;
   int cuenta=0;
   int i=0;

   hls::Mat<MAX_ROW,MAX_COL,HLS_8UC1> mat_frameg(MAX_ROW,MAX_COL);
   hls::Mat<MAX_ROW,MAX_COL,HLS_8UC1> mat_imseg(MAX_ROW,MAX_COL) ;
   hls::Mat<MAX_ROW,MAX_COL,HLS_8UC1> mat_festat(MAX_ROW,MAX_COL);
   hls::Mat<MAX_ROW,MAX_COL,HLS_8UC1> mat_fondog(MAX_ROW,MAX_COL);

   hls::AXIvideo2Mat(frameg,mat_frameg);
   hls::AXIvideo2Mat(imseg,mat_imseg);
   hls::AXIvideo2Mat(festat,mat_festat);
   hls::AXIvideo2Mat(fondog,mat_fondog);

   uchar ptr;
   uchar ptr1;
   uchar ptr2;
   for (i=0; i < 240; i++)
   {
      for (int j=0; j < frameg->width; j++)
      {
         ptr  = mat_imseg.read() ;
         ptr1 = mat_frameg.read();
         ptr2 = mat_fondog.read();
             	  /*Actualización del fondo
         si es fondo actualizo con la última muestra pero adecuadamente*/
         if (ptr==0)
         {
            if (ptr1 > ptr2)
               ptr2=ptr1-ceil((ptr1-ptr2)/(2*_CHANGEFACTOR_BACKGROUND));
            else if (ptr1 < ptr2)
               ptr2=ptr1+ceil((ptr2-ptr1)/_CHANGEFACTOR_BACKGROUND);
         } else{
            cuenta++;
            if (ptr1 > ptr2)
               ptr2=ptr2+ceil((ptr1-ptr2)/(2*_CHANGEFACTOR_FOREGROUND));
            else if (ptr1 < ptr2)
               ptr2=ptr2-ceil((ptr2-ptr1)/_CHANGEFACTOR_FOREGROUND);
         }
      }
   }
//   if (cuenta<MINRUIDO) cvCopy(frameg,festat);
}

