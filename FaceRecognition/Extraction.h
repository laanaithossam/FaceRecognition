#ifndef EXTRACTION_H
#define EXTRACTION_H
#include <cv.h>
#include <highgui.h>

class Extraction
{
private:
    IplImage* Image;
    IplImage* FaceImage;
    IplImage* NewImage;
public:
    Extraction();
    Extraction(IplImage*);
    ~Extraction();
    bool Extract(const char*);
    void SetFaceSize(int=50, int=50);
    void SetFaceIllimunation();
    void SetROI(CvRect);
    void SetImage(IplImage*);
    IplImage* GetFaceImage();
    
};

#endif