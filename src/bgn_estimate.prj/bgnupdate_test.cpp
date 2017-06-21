#include "bgnupdate.h"
#include <hls_opencv.h>
using namespace cv;
using namespace std;

int main (int argc, char** argv) {

   IplImage* src ;
   IplImage* seg ;
   IplImage* seed;
   IplImage* golden;
   IplImage* dst;
   int retval=0, i;

   AXI_STREAM axi_src;
   AXI_STREAM axi_seg;
   AXI_STREAM axi_seed;
   AXI_STREAM axi_dst;

   src    = cvLoadImage(INPUT_IMAGE,        CV_LOAD_IMAGE_GRAYSCALE);
   seg    = cvLoadImage(SEGMENTED_IMAGE,    CV_LOAD_IMAGE_GRAYSCALE);
   seed   = cvLoadImage(SEED_BGN,           CV_LOAD_IMAGE_GRAYSCALE);
   golden = cvLoadImage(OUTPUT_IMAGE_GOLDEN,CV_LOAD_IMAGE_GRAYSCALE);

   dst    = cvCreateImage(cvSize(src->width,src->height), src->depth, src->nChannels);

   cv::Mat Src    = cvarrToMat(src   );
   cv::Mat Seg    = cvarrToMat(seg   );
   cv::Mat Seed   = cvarrToMat(seed  );
   cv::Mat Golden = cvarrToMat(golden);

   hls::Mat<2*MAX_ROW,2*MAX_COL,HLS_8UC1> hlsSrc(Src.rows,Src.cols);
   hls::Mat<2*MAX_ROW,2*MAX_COL,HLS_8UC1> hlsSeg(Seg.rows,Seg.cols);
   hls::Mat<2*MAX_ROW,2*MAX_COL,HLS_8UC1> hlsSeed(Seed.rows,Seed.cols);
   hls::Mat<2*MAX_ROW,2*MAX_COL,HLS_8UC1> hlsGolden(Golden.rows,Golden.cols);

   cvMat2hlsMat(Src,hlsSrc);
   cvMat2hlsMat(Seg,hlsSeg);
   cvMat2hlsMat(Seed,hlsSeed);
   cvMat2hlsMat(Golden,hlsGolden);

   //for(i=0;i<src->width;i++) printf("%d\n",hlsSrc.read());


   printf("Tamaño de la imagen hlsMat segmentada   : %d x %d\n"  , Seg.rows , Seg.cols );

   IplImage2AXIvideo(src,axi_src)  ;
   IplImage2AXIvideo(seg,axi_seg)  ;
   IplImage2AXIvideo(seed,axi_seed);

   while(hlsSrc.empty() && hlsSeg.empty() && hlsSeed.empty());

   backgroundUpdate(axi_src, axi_seg, axi_seed, axi_dst,MAX_ROW, MAX_COL);


   AXIvideo2IplImage(axi_dst, dst);


   uchar* ptr_dst    = (uchar*) (dst->imageData);
   uchar* ptr_golden = (uchar*) (golden->imageData);
   for(i=0;i<i++; dst->height * dst->width){
      if(ptr_dst[i] != ptr_golden[i]){
          printf("    *** *** *** *** \n");
          printf("    BAD!! %d \n", retval);
          printf("    *** *** *** *** \n");
    	  return 2;
      }
   }
   cvSaveImage(OUTPUT_IMAGE, dst );

   printf("    *** *** *** *** \n");
   printf("    Results are good \n");
   printf("    *** *** *** *** \n");
   return retval;
 
}


