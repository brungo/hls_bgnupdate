#include "bgnupdate.h"

void backgroundUpdate(AXI_STREAM& frameg, AXI_STREAM& imseg, AXI_STREAM& festat,
		              AXI_STREAM& fondog, int rows, int cols)
{
   #pragma HLS INTERFACE axis port=frameg bundle=INPUT_STREAM
   #pragma HLS INTERFACE axis port=imseg  bundle=INPUT_STREAM
   #pragma HLS INTERFACE axis port=festat bundle=INPUT_STREAM
   #pragma HLS INTERFACE axis port=fondog bundle=OUTPUT_STREAM
   #pragma HLS INTERFACE s_axilite port=rows bundle=CONTROL_BUS offset=0x14
   #pragma HLS INTERFACE s_axilite port=cols bundle=CONTROL_BUS offset=0x1C
   #pragma HLS INTERFACE s_axilite port=return bundle=CONTROL_BUS
   #pragma HLS INTERFACE ap_stable port=rows
   #pragma HLS INTERFACE ap_stable port=cols

   const int MINRUIDO=10;
   int cuenta=0;
   int i=0;

   hls::Mat<2*MAX_ROW,2*MAX_COL,HLS_8UC1> mat_frameg(MAX_ROW,MAX_COL);
   hls::Mat<2*MAX_ROW,2*MAX_COL,HLS_8UC1> mat_imseg(MAX_ROW,MAX_COL) ;
   hls::Mat<2*MAX_ROW,2*MAX_COL,HLS_8UC1> mat_festat(MAX_ROW,MAX_COL);
   hls::Mat<2*MAX_ROW,2*MAX_COL,HLS_8UC1> mat_fondog(MAX_ROW,MAX_COL);

   #pragma HLS dataflow
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
   raw_iter:for (i=0; i < MAX_ROW; i++)
   {
      col_iter:for (int j=0; j < MAX_COL; j++)
      {

         frame_read  = mat_frameg.read();
    	 ptr = frame_read.val[0]        ;
    	 seg_read  = mat_imseg.read()   ;
    	 ptr1 = frame_read.val[0]       ;
    	 stat_read  = mat_festat.read() ;
    	 ptr2 = stat_read.val[0]        ;

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
         //Escribir el dato de salida
         out_write.val[0] = ptr2;
         mat_fondog.write(out_write);
      }
   }
//   if (cuenta<MINRUIDO) cvCopy(frameg,festat);
   hls::Mat2AXIvideo(mat_fondog,fondog);
}

