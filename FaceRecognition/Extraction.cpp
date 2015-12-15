#include "Extraction.h"

Extraction::Extraction()
{
    
}
Extraction::Extraction(IplImage * InputImage)
{
    Image=InputImage;
}
Extraction::~Extraction()
{
    cvReleaseImage(&FaceImage);
    cvReleaseImage(&Image);
    cvReleaseImage(&NewImage);
}
IplImage* Extraction::GetFaceImage()
{
    return FaceImage;
}
void Extraction::SetROI(CvRect faceRectangle)
{
    cvSetImageROI(Image,faceRectangle);
	FaceImage = cvCreateImage(cvSize(faceRectangle.width,faceRectangle.height),Image->depth,1);
	cvConvertImage(Image,FaceImage);
	cvResetImageROI(Image);
}
bool Extraction::Extract(const char* OutputImage)
{   
    SetFaceSize();
    SetFaceIllimunation();
    IplImage* CurrentImage = 0;
	bool status = false;
	CurrentImage = GetFaceImage();
	if (!CurrentImage) return false;
	if(cvSaveImage(OutputImage,CurrentImage)) status = true;
	return status;
}
void Extraction::SetFaceSize(int width, int height)
{
    if(!FaceImage) return;
	NewImage = cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1); 
	cvResize(FaceImage,NewImage,CV_INTER_LINEAR);
	cvReleaseImage(&FaceImage);
	FaceImage = NewImage;
}
void Extraction::SetFaceIllimunation()
{
    if(!FaceImage) return;
	if( strcmp(FaceImage->colorModel,(char*)"GRAYGRAY") ) return;
	 cvEqualizeHist( FaceImage, FaceImage);
}
void Extraction::SetImage(IplImage * InputImage)
{
    Image=InputImage;
}