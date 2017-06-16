#include "bgnupdate.h"
using namespace cv;
using namespace std;

int main (int argc, char** argv) {

   IplImage* src ;
   IplImage* seg ;
   IplImage* seed;
   IplImage* golden;
   IplImage* dst;
   int retval=0, i;


   src    = cvLoadImage(INPUT_IMAGE,        CV_LOAD_IMAGE_GRAYSCALE);
   seg    = cvLoadImage(SEGMENTED_IMAGE,    CV_LOAD_IMAGE_GRAYSCALE);
   seed   = cvLoadImage(SEED_BGN,           CV_LOAD_IMAGE_GRAYSCALE);
   golden = cvLoadImage(OUTPUT_IMAGE_GOLDEN,CV_LOAD_IMAGE_GRAYSCALE);

   dst    = cvCreateImage(cvSize(src->width,src->height), src->depth, src->nChannels);

   cv::Mat Src    = cvarrToMat(src   );
   cv::Mat Seg    = cvarrToMat(seg   );
   cv::Mat Seed   = cvarrToMat(seed  );
   cv::Mat Golden = cvarrToMat(golden);

   hls::Mat<MAX_ROW,MAX_COL,HLS_8UC1> hlsSrc(Src.rows,Src.cols);
   hls::Mat<MAX_ROW,MAX_COL,HLS_8UC1> hlsSeg(Seg.rows,Seg.cols);
   hls::Mat<MAX_ROW,MAX_COL,HLS_8UC1> hlsSeed(Seed.rows,Seed.cols);
   hls::Mat<MAX_ROW,MAX_COL,HLS_8UC1> hlsGolden(Golden.rows,Golden.cols);

   cvMat2hlsMat(Src,hlsSrc);
   cvMat2hlsMat(Seg,hlsSeg);
   cvMat2hlsMat(Seed,hlsSeed);
   cvMat2hlsMat(Golden,hlsGolden);

   for(i=0;i<src->width;i++) printf("%d\n",hlsSrc.read());


//   printf("Tamaño de la imagen hlsMat de entrada   : %d x %d\n"  , hlsSrc.rows , hlsSrc.cols );
   printf("Tamaño de la imagen hlsMat segmentada   : %d x %d\n"  , Seg.rows , Seg.cols );
//   printf("Tamaño de la imagen hlsMat de referencia: %d x %d\n\n", hlsSeed.rows, hlsSeed.cols);

   backgroundUpdate(src, seg, seed, dst);

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
