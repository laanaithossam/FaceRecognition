#ifndef DETECTION_H
#define DETECTION_H
#include <cv.h>
#include <highgui.h>
class Detection
{
private:
    IplImage* pImage;
	CvCapture* pCapture;
	CvMemStorage* pStorage;
	CvHaarClassifierCascade* pCascade;	
public:
    Detection();
    ~Detection();
    
    CvRect Detect();
    
    IplImage* GetImage();
    void SetImage(IplImage*);
    
    CvCapture* GetCapture();
    void SetCapture(CvCapture*);
    
    CvMemStorage* GetStorage();
    void SetStorage(CvMemStorage*);
    
    CvHaarClassifierCascade* GetCascade();
    void SetCascade(char*);
    int GrabFrame(CvCapture *);
};

#endif