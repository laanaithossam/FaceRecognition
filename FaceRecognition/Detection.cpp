#include"Detection.h"
#define CASCADE_NAME  "haarcascade/haarcascade_frontalface_default.xml"

Detection::Detection()
{
    pImage=NULL;
    pCapture=NULL;
    pStorage=NULL;
    pCascade=(CvHaarClassifierCascade*)cvLoad(CASCADE_NAME);
}

Detection::~Detection()
{
    //cvReleaseImage(&pImage);
    //cvReleaseMemStorage(&pStorage);
    cvReleaseCapture(&pCapture);
}

void Detection::SetImage(IplImage* pImg)
{
    pImage=pImg;
}
IplImage* Detection::GetImage()
{
    return pImage;
}

void Detection::SetCapture(CvCapture* pCpt)
{
    pCapture=pCpt;
}
CvCapture* Detection::GetCapture()
{
    return pCapture;
}

void Detection::SetCascade(char * CASCADE_FILE_NAME)
{
  pCascade=(CvHaarClassifierCascade*)cvLoad(CASCADE_FILE_NAME);
}
CvHaarClassifierCascade* Detection::GetCascade()
{
    return pCascade;
}

void Detection::SetStorage(CvMemStorage* pStr)
{
    pStorage=pStr;
}
CvMemStorage* Detection::GetStorage()
{
    return pStorage;
}

int Detection::GrabFrame(CvCapture *Capture)
{
    return cvGrabFrame(Capture);
}

CvRect Detection::Detect()
{
    int i = 0;
    int scale_width,scale_height;
    scale_width=pImage->width/4;
    scale_height=scale_width;

    pStorage=cvCreateMemStorage(0);
    cvClearMemStorage(pStorage);
    CvRect* r = NULL;
    if( pCascade )
    {
        CvSeq* faces = cvHaarDetectObjects( pImage, pCascade, pStorage,1.1,3, CV_HAAR_DO_CANNY_PRUNING,cvSize(scale_width,scale_height));
        r = (CvRect*)cvGetSeqElem( faces, i );
        if(r) 
        {
         return cvRect(r->x,r->y,r->width,r->height);
        } 
         else 
        {
           return cvRect(-1,-1,0,0);
        }
    }
    else 
    {
        return cvRect(-1,-1,0,0);
    }
    
    cvReleaseHaarClassifierCascade(&pCascade);
	cvReleaseMemStorage(&pStorage);
}