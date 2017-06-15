#include "bgnupdate.h"

void backgroundUpdate(const IplImage* frameg, const IplImage* imseg, IplImage* festat, 
                      IplImage* fondog)
{
   const int MINRUIDO=10;
   int cuenta=0;
   int i=0;


   for (i=0; i < frameg->height; i++)
   {
      uchar* ptr=(uchar*)(imseg->imageData + i*imseg->widthStep);
      uchar* ptr1=(uchar*)(frameg->imageData + i*frameg->widthStep);
      uchar* ptr2=(uchar*)(fondog->imageData + i*fondog->widthStep);

      for (int j=0; j < frameg->width; j++)
      {
         /*Actualización del fondo
         si es fondo actualizo con la última muestra pero adecuadamente*/
         if (ptr[j]==0)
         {
            if (ptr1[j] > ptr2[j])
               ptr2[j]=ptr1[j]-ceil((ptr1[j]-ptr2[j])/(2*_CHANGEFACTOR_BACKGROUND));
            else if (ptr1[j] < ptr2[j])
               ptr2[j]=ptr1[j]+ceil((ptr2[j]-ptr1[j])/_CHANGEFACTOR_BACKGROUND);
         } else{
            cuenta++;
            if (ptr1[j] > ptr2[j])
               ptr2[j]=ptr2[j]+ceil((ptr1[j]-ptr2[j])/(2*_CHANGEFACTOR_FOREGROUND));
            else if (ptr1[j] < ptr2[j])
               ptr2[j]=ptr2[j]-ceil((ptr2[j]-ptr1[j])/_CHANGEFACTOR_FOREGROUND);
         }
      }
   }
   if (cuenta<MINRUIDO) cvCopy(frameg,festat);
}

