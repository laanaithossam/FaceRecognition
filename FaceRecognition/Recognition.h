#ifndef RECOGNITION_H
#define RECOGNITION_H
#include <cv.h>
#include <highgui.h>
#include <cvaux.h>
#include <stdio.h>
#include "Users.h"

class Recognition
{
private:
    int iTrainFaces; //Nombre des training face
    int iEigens; //Nombre des eignevalues
    IplImage** TabFace; //Tableau des images
    CvMat* TabPerson; // Tableau de personnes
    IplImage* AvgImg;// Image moyenne
    IplImage** EigenVecArr;// eigenvectors
    CvMat* EigenValMat; // eigenvalues
    CvMat* ProjectedTrainFace;// Faceimages projetées   
public:
    Recognition();
    ~Recognition();
    int Learn(int,Users**);
    int Recognize(IplImage *Image);
    void ApplyPca();
    void StoreTrainingData();
    int LoadTrainingData(CvMat** pTrainPersonNumMat);
    int FindNearestNeighbor(float *ProjectedTestFace);
    int LoadFaceImgArray(int,Users**);
    
};

#endif