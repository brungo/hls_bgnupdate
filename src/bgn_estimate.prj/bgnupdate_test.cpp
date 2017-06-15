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


   src = cvLoadImage(INPUT_IMAGE,CV_LOAD_IMAGE_GRAYSCALE);
   seg = cvLoadImage(SEGMENTED_IMAGE,CV_LOAD_IMAGE_GRAYSCALE);
   seed= cvLoadImage(SEED_BGN,CV_LOAD_IMAGE_GRAYSCALE);
   golden = cvLoadImage(OUTPUT_IMAGE_GOLDEN,CV_LOAD_IMAGE_GRAYSCALE);
   dst = cvCreateImage(cvSize(src->width,src->height), src->depth, src->nChannels);

//   cv::Mat Src    = cv::cvarrToMat(src   );
//   cv::Mat Seg    = cv::cvarrToMat(seg   );
//   cv::Mat Seed   = cv::cvarrToMat(seed  );
//   cv::Mat Golden = cv::cvarrToMat(golden);

   printf("Tamaño de las imagen de entrada   : %d x %d\n"  , src->height, src->width);
   printf("Tamaño de las imagen segmentada   : %d x %d\n"  , seg->height, seg->width);
   printf("Tamaño de las imagen de referencia: %d x %d\n\n", seed->height, seed->width);


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
