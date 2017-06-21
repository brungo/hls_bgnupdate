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
   hls::AXIvideo2Mat(imseg, mat_imseg );
   hls::AXIvideo2Mat(festat,mat_festat);


   hls::Scalar<1, unsigned char> frame_read;
   hls::Scalar<1, unsigned char> seg_read;
   hls::Scalar<1, unsigned char> stat_read;
   hls::Scalar<1, unsigned char> out_write;
   unsigned char ptr;
   unsigned char ptr1;
   unsigned char ptr2;
   unsigned char aux;
   raw_iter:for (i=0; i < MAX_ROW; i++)
   {
      col_iter:for (int j=0; j < MAX_COL; j++)
      {
         frame_read  = mat_frameg.read();
    	 ptr = frame_read.val[0]        ;
    	 seg_read  = mat_imseg.read()   ;
    	 ptr1 = seg_read.val[0]         ;
    	 stat_read  = mat_festat.read() ;
    	 ptr2 = stat_read.val[0]        ;

         if (ptr==0)
         {
            if (ptr1 > ptr2){
               aux = (unsigned char)(ptr1-ptr2)/(2*_CHANGEFACTOR_BACKGROUND);
               ptr2 = ptr1- aux;
            }
            else if (ptr1 < ptr2){
               aux = (unsigned char)(ptr2-ptr1)/_CHANGEFACTOR_BACKGROUND;
               ptr2=ptr1+aux;
            }
         } else{
            cuenta++;
            if (ptr1 > ptr2){
               aux = (unsigned char)(ptr1-ptr2)/(2*_CHANGEFACTOR_FOREGROUND);
               ptr2=ptr2+aux;
            }
            else if (ptr1 < ptr2){
               aux = (unsigned char)(ptr2-ptr1)/_CHANGEFACTOR_FOREGROUND;
               ptr2=ptr2-aux;
            }
         }
         //Escribir el dato de salida
         out_write.val[0] = ptr2;
         mat_fondog.write(out_write);
      }
   }
   hls::Mat2AXIvideo(mat_fondog,fondog);
}

