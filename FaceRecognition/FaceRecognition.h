#ifndef FACERECOGNITION_H
#define FACERECOGNITION_H

#include <QtGui/QtGui>
#include <QtCore/QFile>
#include <map>
#include "Detection.h"
#include "Extraction.h"
#include "Recognition.h"
#include "FaceDatabase.h"
#include "Users.h"
// *********************************************	
class FaceRecognition : public QMainWindow
{
Q_OBJECT
    
protected:
		void mouseDoubleClickEvent (QMouseEvent * event);
		
private:
//IHM
    //Formulaire
    QWidget* wForm;
    QFormLayout* fFrom;
    QLineEdit *Id_Txt;
    QLineEdit *User_Txt;
    QLineEdit *Pass_Txt;
    QLineEdit *Confirm_Txt;
    QLineEdit *Nom_Txt;
    QLineEdit *Prenom_Txt;
    QLineEdit *Age_Txt;
    QLineEdit *Ville_Txt;
    QLineEdit *Adresse_Txt;
    QLineEdit *Cp_Txt;
    QLineEdit *Url_Txt;
    //Dialog Authentification
    QDialog *dAuthentification;
    QFormLayout* fAuthentification;
    QLineEdit *UserLogin_Txt;
    QLineEdit *PassLogin_Txt;
    QPushButton* bValidate;
    //Window
    QVBoxLayout* VLayout;
    QLabel* lCapture;
    QWidget* CentralWidget;	
    QMenu* mFichier;
    QMenu* mUser;
    QAction *aCapturer;
    QAction *aStopCapturer;
    QAction *aQuitter;
    
    QAction *aAdd;
    QAction *aDelete;
    QAction *aUpdate;
    QAction *aLogOn;
    QAction *aLogOut;
    
    QToolBar *tFichier;
    QToolBar *tUser;
    QStatusBar *sBarre;
//Trt Image & OpenCV
   	QImage  qImage;
   	QRect faceLoc;
	QTimer qTimer;	
	int counter_;
	Detection* Detector;
	Extraction* Extractor;
	Recognition* Recognizer;
//Database
	FaceDatabase* FaceDb;
	Users **ListUser;
	
public:	
	FaceRecognition(QString, QString, QString, QString );	
	~FaceRecognition();
	void Draw(CvRect);		
	void InitWidget();
	bool SaveImageTest(CvRect,QString);
    void SetUserList();
	QImage CVtoQT(const IplImage *);	
	bool Found;

public slots:
    void Capture();	
	void InitCapture();	
	void StopCapture();	
	void AddUser();	
	void DeleteUser();
	void LogOn();
	void LogOut();	
	void Recognition_Ok(int);
	void User_On();
	void User_Out();
	void Authentification();
	void UpdateUser();
	void Start();
		
signals:
	void doubleclick();
	
};

#endif

