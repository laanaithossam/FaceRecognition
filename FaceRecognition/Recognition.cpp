#include "Recognition.h"
Recognition::Recognition()
{
    int iTrainFaces=0;
    int iEigens=0;
    IplImage** TabFace=NULL;
    CvMat* TabPerson=NULL;
    IplImage* AvgImg=NULL;
    IplImage** EigenVecArr=NULL;
    CvMat* EigenValMat=NULL;
    CvMat* ProjectedTrainFace=NULL;  
}

Recognition::~Recognition()
{
    cvReleaseImage(TabFace);
    cvReleaseMat(&TabPerson);
    cvReleaseImage(&AvgImg);
    cvReleaseImage(EigenVecArr);
    cvReleaseMat(&EigenValMat);
    cvReleaseMat(&ProjectedTrainFace);
}
int Recognition::Learn(int nFaces,Users **ListUser)
{
/*
  	1. 	chargement des données
  	2. 	Apliquer l'acp afin de trouver le sous espace des faceTrain
  	3. 	Projeter les face training dans l'espace acp
  	4. 	Enregistrement des données
  	  	
  	    a. 	Eigenvalues
  	    b. 	Eigenvectors
  	    c. 	The average training face image
  	    d. 	Projected faces
  	    e. 	Person ID numbers
*/
    int i;
    //Chargement des training data
    //The loadFaceImgArray() function loads face images and person ID numbers for both the learning and recognition phases
    // loadFaceImgArray() returns the number of face images loaded
    iTrainFaces=LoadFaceImgArray(nFaces,ListUser /*"faceDB/train.txt"*/);
    if(iTrainFaces<2)
    {
        //IL faut au moins deux images 
        return -3;   
    }
    
    //PCA sur les training faces
    ApplyPca();
    
    //Projeter les training faces dans le sous espace PCA

    ProjectedTrainFace=cvCreateMat(iTrainFaces,iEigens,CV_32FC1);
    for(i=0;i<iTrainFaces;i++)
    {
        cvEigenDecomposite(TabFace[i],iEigens,EigenVecArr,0,0,AvgImg,ProjectedTrainFace->data.fl +i*iEigens);
    }
    // store the recognition data as an xml file
    StoreTrainingData();
}
int Recognition::LoadFaceImgArray(int nFaces,Users **ListUser)
{
    int iFace;
    //Nombre de visage
    //Allocation du tableau des FaceImage
    TabFace = (IplImage **)cvAlloc( nFaces*sizeof(IplImage *) );
    //cvCreateMat(row,col,type)
	TabPerson = cvCreateMat( 1, nFaces, CV_32SC1 );
    // store the face images in array    
    for(iFace=0;iFace<nFaces;iFace++)
    {		
		*(TabPerson->data.i+iFace)=iFace+1;
		//load face image		
		TabFace[iFace]=cvLoadImage(ListUser[iFace]->GetUrl().toStdString().c_str(),CV_LOAD_IMAGE_GRAYSCALE);
		if( !TabFace[iFace] )
		{
			return -1;
		}
    }
    return nFaces;  
}
void Recognition::ApplyPca()
{
/*
Recherche du sous espace ACP: 
-----------------------------
-Appel de la fonction cvCalcEigenObjects() prédefinie dans OpenCv.
-Création des variables Output afin de récupérer les resultats retournés par la fonction cvCalcEigenObjects().
*/
    int i;
    CvTermCriteria CalcLimit;
    CvSize FaceImgSize;
//Initialisation de la variable iEigens
    iEigens=iTrainFaces-1; 
//Récupération des dimenssions des trainingfaces
    FaceImgSize.width=TabFace[0]->width;
    FaceImgSize.height=TabFace[0]->height;
    
/*
Allocation du tableau des eigenfaces:
------------------------------------
-Se sont des images de virgule flottante, avec une profondeur data depth = IPL_DEPTH_32F
-Après l'appel de la fonction cvCalcEigenObjects() chaque image du tableau contiendra un eigenvector
*/ 
    EigenVecArr=(IplImage**)cvAlloc(sizeof(IplImage*) * iEigens);
    
    for (i=0;i<iEigens;i++)
    {
        EigenVecArr[i]=cvCreateImage(FaceImgSize,IPL_DEPTH_32F,1);
    }
    
/*
Allocation du tableaux des eigenvalues:
---------------------------------------
-Nous avons besoin d'une nouvelle matrice - EigenValMat. Cette matrice contiendra les eigenvalues.
-Les eigenvalues sont des nombres de virgule flottante et on a besoin que d'un seul channel, le type de cette matrice est CV_32FC1.
-CV_32FC1 : une matrice d'un seul channel, de 32-bit, avec des valeurs de données de virgule flottante.
*/
    EigenValMat=cvCreateMat(1,iEigens,CV_32FC1);
    
/* 
Allocation de AvgImg "Image faite en moyenne":
----------------------------------------------
Le dataset doit être centré par rapport aux faceimage, ca veut dire chercher l'image faite en moyenne a l'aide de cvCalcEigenObjects().
*/
    AvgImg=cvCreateImage(FaceImgSize,IPL_DEPTH_32F,1);
/*
Set the pca termination criterion:
----------------------------------
    La dernière étape avant d'appeler la fonction  cvCalcEigenObjects()est de préparer la structure des données CvTermCriteria.  
    Calcul des eigenvalue 
    */
    CalcLimit =cvTermCriteria(CV_TERMCRIT_ITER,iEigens,1);
    //calcul de image en moyenne,eigenvelues,eigenvector
    /*
    Appel de la fonction cvCalcEigenObjects() pour calculer l'espace PCA des faceimages 
    */
    cvCalcEigenObjects(iTrainFaces,(void*)TabFace,(void*)EigenVecArr,CV_EIGOBJ_NO_CALLBACK,0,0,&CalcLimit,AvgImg,EigenValMat->data.fl);
}

void Recognition::StoreTrainingData()
{
    CvFileStorage* FileStorage;
    int i;
    //Création de la structure d'enregistrement
    /*
    cvOpenFileStorage() ouvre le fichier facedata.xml. le dernier parmetre defini le mode d'acces.
    CV_STORAGE_WRITE: Création ou ecrasment du fichier xml.
    */
    FileStorage=cvOpenFileStorage("FaceData.xml",0,CV_STORAGE_WRITE);
    //Récupération des données 
    cvWriteInt(FileStorage,"iEigens",iEigens);
    cvWriteInt(FileStorage,"iTrainFaces",iTrainFaces);
    cvWrite(FileStorage,"TabPerson",TabPerson,cvAttrList(0,0));
    cvWrite(FileStorage,"EigenValMat",EigenValMat, cvAttrList(0,0));
    cvWrite(FileStorage,"ProjectedTrainFace",ProjectedTrainFace,cvAttrList(0,0));
    cvWrite(FileStorage,"AvgImg",AvgImg,cvAttrList(0,0));
    for(i=0;i<iEigens;i++)
    {
        char varname[200];
        sprintf(varname,"eigenVect_%d",i);
        cvWrite(FileStorage,varname,EigenVecArr[i],cvAttrList(0,0));
    }
    //désalouer la variable filstorage
    cvReleaseFileStorage(&FileStorage);
}
int Recognition::Recognize(IplImage *img)
{
    /*
    The recognition phase
    */
    float* ProjectedTestFace=0;
    int iNearest; 
    //Load the save training data
    if(!LoadTrainingData(&TabPerson)) return -1;
    ProjectedTestFace=(float*)cvAlloc(iEigens*sizeof(float));
    //Projeter l'image test dans le sous espace pca
    cvEigenDecomposite(img,iEigens,EigenVecArr,0,0,AvgImg,ProjectedTestFace);
    iNearest=FindNearestNeighbor(ProjectedTestFace); 
    return iNearest;
}
int Recognition::LoadTrainingData(CvMat** pTrainPersonNumMat)
{
    CvFileStorage* FileStorage;
    int i;
    
    //Creation du fichier xml
    FileStorage=cvOpenFileStorage("FaceData.xml",0,CV_STORAGE_READ);
    if(!FileStorage)
    {
        return 0;
    }
    iEigens=cvReadIntByName(FileStorage,0,"iEigens",0);
    iTrainFaces=cvReadIntByName(FileStorage,0,"iTrainFaces",0);
    TabPerson=(CvMat *)cvReadByName(FileStorage,0,"TabPerson",0);
    EigenValMat=(CvMat *)cvReadByName(FileStorage,0,"EigenValMat",0);
    ProjectedTrainFace=(CvMat *)cvReadByName(FileStorage,0,"ProjectedTrainFace",0);
    AvgImg=(IplImage*)cvReadByName(FileStorage,0,"AvgImg",0);
    EigenVecArr=(IplImage**)cvAlloc(iTrainFaces*sizeof(IplImage*));
    for (i=0;i<iEigens;i++)
    {
        char varname[200];
        sprintf( varname, "eigenVect_%d", i );
		EigenVecArr[i] = (IplImage *)cvReadByName(FileStorage, 0, varname, 0);
    }
}
int Recognition::FindNearestNeighbor(float * ProjectedTestFace)
{
	double LeastDistSq = DBL_MAX;
	int i, iTrain, iNearest = 0;

	for(iTrain=0; iTrain<iTrainFaces; iTrain++)
	{
		double distSq=0;

		for(i=0; i<iEigens; i++)
		{
			float d_i =ProjectedTestFace[i] -ProjectedTrainFace->data.fl[iTrain*iEigens + i];
			distSq += d_i*d_i / EigenValMat->data.fl[i];
		}

		if(distSq < LeastDistSq)
		{
			LeastDistSq = distSq;
			iNearest = iTrain;
		}
	}
    if (LeastDistSq<0.1)
	    return iNearest;
	else 
	    return -1;
}
