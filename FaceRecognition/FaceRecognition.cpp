#include "FaceRecognition.h"
#define ICONE_APP_NAME  "Icon/FaceRecognition.ico"
#define BG_APP_NAME  "Icon/Bg.jpg"
#define ICON_CAPTURE_NAME  "Icon/Capture.png"
#define ICON_STOP_CAPTURE_NAME  "Icon/StopCapture.png"
#define ICON_ADD_NAME  "Icon/Add.png"
#define ICON_DELETE_NAME  "Icon/Delete.png"
#define ICON_UPDATE_NAME  "Icon/Update.png"
#define ICON_LOGON_NAME  "Icon/Logon.png"
#define ICON_LOGOUT_NAME  "Icon/Logout.png"
#define ICON_QUIT_NAME  "Icon/Quit.png"
//QCoreApplication::applicationDirPath()
FaceRecognition::FaceRecognition(QString hst, QString name, QString user, QString pass):QMainWindow(),qTimer(this)
{
    //Initialisation de la fenêtre d'authentification : type dialog
    dAuthentification=new QDialog;
    fAuthentification=new QFormLayout(dAuthentification);
    UserLogin_Txt=new QLineEdit;
    PassLogin_Txt= new QLineEdit;
    bValidate=new QPushButton("Sign in");
    //Initialisation de la zone centrale de la mainwindow
    CentralWidget=new QWidget;
    setCentralWidget(CentralWidget);
    //Initialisation du conteneur global : Layout
    VLayout=new QVBoxLayout(CentralWidget);
    //Initialisation du formulaire
    wForm=new QWidget;
    //Initialisation du layout formulaire
    fFrom= new QFormLayout;
    //Initialisation des champs de saisie 
    Id_Txt = new QLineEdit;
    User_Txt= new QLineEdit;
    Pass_Txt=new QLineEdit;
    Confirm_Txt=new QLineEdit;
    Nom_Txt = new QLineEdit;
    Prenom_Txt = new QLineEdit;
    Age_Txt = new QLineEdit;
    Adresse_Txt = new QLineEdit;
    Ville_Txt = new QLineEdit;
    Cp_Txt = new QLineEdit;
    Url_Txt = new QLineEdit;
    //Initialisation du conteneur Label
    lCapture=new QLabel();
    //Initialisation de l'objet Detector
    Detector=new Detection();
    //Initialisation de l'objet Extractor
    Extractor=new Extraction();
    //Initialisation de l'objet Recognizer
    Recognizer=new Recognition();
    //Initialisation de l'objet FaceDb
    FaceDb=new FaceDatabase(hst,name,user,pass);
    //Initialisation des menus
    mFichier=menuBar()->addMenu("&Fichier");
    mUser=menuBar()->addMenu("&Utilisateur");
	//Initialisation des toolbars
	tFichier=addToolBar("Fichier");
	tUser=addToolBar("Utilisateur");
	//Initialisation de la statusbar
	sBarre=statusBar();
	//Initialisation des widget
	InitWidget();
	//Signaux & Slot
	connect(aCapturer, SIGNAL(triggered()), this, SLOT(InitCapture()));
	connect(aStopCapturer,SIGNAL(triggered()),this,SLOT(StopCapture()));
	connect(aQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
	
	connect(aAdd,SIGNAL(triggered()),this,SLOT(AddUser()));
	connect(aDelete,SIGNAL(triggered()),this,SLOT(DeleteUser()));
	connect(aUpdate,SIGNAL(triggered()),this,SLOT(UpdateUser()));
	connect(aLogOn,SIGNAL(triggered()),this,SLOT(LogOn()));
	connect(aLogOut,SIGNAL(triggered()),this,SLOT(LogOut()));
	
	connect(dAuthentification,SIGNAL(rejected()),this,SLOT(Start()));
	connect(bValidate,SIGNAL(clicked()),this,SLOT(Authentification()));
	connect(&qTimer,SIGNAL(timeout()), this,SLOT(Capture()));
}
void FaceRecognition::InitWidget()
{
    //Main Window
    setWindowIcon(QIcon(ICONE_APP_NAME));
    setIconSize(QSize(20,20));
    //Background
    lCapture->setPixmap(QPixmap(BG_APP_NAME));
    //Formulaire
    Id_Txt->hide();
    Pass_Txt->setEchoMode(QLineEdit::Password);
    Confirm_Txt->setEchoMode(QLineEdit::Password);
    fFrom->addRow("Username *",User_Txt);
    fFrom->addRow("Mot de passe *",Pass_Txt);
    fFrom->addRow("Confirmer votre mot de passe *",Confirm_Txt);
    fFrom->addRow("Nom",Nom_Txt);
    fFrom->addRow("Prenom",Prenom_Txt);
    fFrom->addRow("Age",Age_Txt);
    fFrom->addRow("Adresse",Adresse_Txt);
    fFrom->addRow("Ville",Ville_Txt);
    fFrom->addRow("Cp",Cp_Txt);
    //Formulaire Authentification
    PassLogin_Txt->setEchoMode(QLineEdit::Password);
    fAuthentification->addRow("Username :",UserLogin_Txt);
    fAuthentification->addRow("Password :",PassLogin_Txt);
    fAuthentification->addRow(bValidate);
    //Integration des widget
    VLayout->addWidget(lCapture);
    wForm->setLayout(fFrom);
    wForm->hide();
    VLayout->addWidget(wForm);
    CentralWidget->setLayout(VLayout);
    
    //Initialisation du Menu Fichier
    aCapturer = mFichier->addAction(QIcon(ICON_CAPTURE_NAME),"&Capturer");
    aCapturer->setStatusTip("Lancer la detection");
    aStopCapturer = mFichier->addAction(QIcon(ICON_STOP_CAPTURE_NAME),"&Arreter la capture");
    aStopCapturer->setEnabled(false);    
    aStopCapturer->setStatusTip("Arrêter la detection");
    mFichier->addSeparator();
    aQuitter = mFichier->addAction(QIcon(ICON_QUIT_NAME),"&Quitter");
	aQuitter->setStatusTip("Quitter l'application");
	
	//Initialisation du Menu User
    aAdd=mUser->addAction(QIcon(ICON_ADD_NAME),"&Inscription");
    aAdd->setStatusTip("S'inscrire");
    aAdd->setEnabled(false);
    
    aDelete=mUser->addAction(QIcon(ICON_DELETE_NAME),"&Désinscription");
    aDelete->setStatusTip("Se désinscrire");
    aDelete->setEnabled(false);
    
    aUpdate=mUser->addAction(QIcon(ICON_UPDATE_NAME),"&Mise à jour");
    aUpdate->setStatusTip("Mettre à jour le profil");
    aUpdate->setEnabled(false);
    mUser->addSeparator();
    
    aLogOn=mUser->addAction(QIcon(ICON_LOGON_NAME),"&LogOn");
    aLogOn->setStatusTip("Logon");
    aLogOn->setEnabled(false);
    
    aLogOut=mUser->addAction(QIcon(ICON_LOGOUT_NAME),"&LogOut");
    aLogOut->setStatusTip("Logout");
    aLogOut->setEnabled(false);

	//ToolBar
	tFichier->setIconSize(QSize(30,30));
	tFichier->addAction(aCapturer);
	tFichier->addAction(aStopCapturer);
	tFichier->addSeparator();
	tFichier->addAction(aQuitter);
	
	tUser->setIconSize(QSize(30,30));
	tUser->addAction(aAdd);
	tUser->addAction(aDelete);
	tUser->addAction(aUpdate);
	tUser->addSeparator();
	tUser->addAction(aLogOn);
	tUser->addAction(aLogOut);
	//StatusBar
	sBarre->showMessage("Bienvenue sur FaceRecognition,copyright Hossam LAANAIT 2010");
}
FaceRecognition::~FaceRecognition()
{
    delete Detector;
}

//Convertit iplImage en Qimage
//A commenter
QImage FaceRecognition::CVtoQT(const IplImage *newImage)
{
	QImage qtemp;
	if (newImage && cvGetSize(newImage).width > 0)
	{
		int x;
		int y;
		char* data = newImage->imageData;
		qtemp= QImage(newImage->width, newImage->height,QImage::Format_RGB32 );
		for( y = 0; y < newImage->height; y++, data +=newImage->widthStep )
			for( x = 0; x < newImage->width; x++)
			{
				uint *p = (uint*)qtemp.scanLine (y) + x;
				*p = qRgb(data[x * newImage->nChannels+2],data[x * newImage->nChannels+1],
				               data[x * newImage->nChannels]);
			}
	}
	return qtemp;	
}

void FaceRecognition::StopCapture()
{
    //Arrêt du timer
    qTimer.stop();
    Found=false;
    aLogOn->setEnabled(false); 
    LogOut();
    lCapture->setPixmap(QPixmap(BG_APP_NAME));
    wForm->hide();
    CentralWidget->resize(lCapture->width(), lCapture->height());
	this->resize(lCapture->width(), lCapture->height());
    aStopCapturer->setEnabled(false);
    aCapturer->setEnabled(true);
}

void FaceRecognition::InitCapture()
{   
    int SqlStatus;
    //Initialisation de la variable global Found
    Found=false;  
    aLogOn->setEnabled(true);  
    //Connexion à la base de données
    SqlStatus=FaceDb->dbConnexion();
    
    sBarre->showMessage("Connexion à la base de données...");
    //Erreur d'ouverture de la base Sqlite
    if(SqlStatus==-1)
    {
        QMessageBox::critical(this, "Erreur Ouverture", FaceDb->facedb.lastError().text());   
        return;
    }
    //Ouverture Ok, mais base nouvellement créee
    else if(SqlStatus==0)
    {
        SetUserList();
        Recognizer->Learn(FaceDb->GetCount(),ListUser);
    }
    //Ouverture de base Ok, et existance de cette dernière
    else
    {
        SetUserList();
    }
    sBarre->showMessage("Initialisation de la detection...");
    //Capturer le flux de la webcam
	Detector->SetCapture(cvCreateCameraCapture(CV_CAP_ANY));
	//Tester si la capture a réussi
    if (!Detector->GetCapture()) 
    {
        QMessageBox::critical(this,"Erreur Webcam!","Acune webcam n'a été détécté merci de verifier la présence de celle-ci");
        return;
    }	
    //Saisir l'image dans la capture
	if(!cvGrabFrame(Detector->GetCapture()))
	{
        QMessageBox::critical(this,"Erreur Webcam!","Impossible de saisir l'image dans la capture");
        return;
	}
	//Initialise l'attribut iplImage avec l'image ulterieurement saisie par la fonction cvGrabFrame(),                    
	Detector->SetImage(cvRetrieveFrame(Detector->GetCapture()));
	//Redim du conteneur avec les dimenssions de l'image recuperée 
	lCapture->resize(Detector->GetImage()->width, Detector->GetImage()->height);
	CentralWidget->resize(lCapture->width(), lCapture->height());
	this->resize(lCapture->width(), lCapture->height());
	//Désactivation du menu "Capture" et activation de "Arret" 
	aCapturer->setEnabled(false);
	aStopCapturer->setEnabled(true);
	//Declenchement du timer sur la fonction Capture()
	sBarre->showMessage("Detection en cours ...");
	qTimer.start(100);
}
void FaceRecognition::Capture() 
{

    int iUser=-1;
    //Création du nom de l'image test
    QString ImageFileName;
    ImageFileName="faceDB/Test/" + ImageFileName.setNum(ListUser[FaceDb->GetCount()-1]->GetId()+1) + ".pgm";
    //Tester si l'attribut de la classe Detector, CvCapture est initialisé
    if (!Detector->GetCapture()) 
	{
		QMessageBox::critical(this,"Erreur Webcam!","Votre webcam n'est plus detectée par l'application.");
        return;
	}	
	//Saisir l'image dans la capture
	if(!cvGrabFrame(Detector->GetCapture()))
	{
        QMessageBox::critical(this,"Erreur Webcam!","Impossible de saisir l'image dans la capture");
        return;
	}
	//Initialise l'attribut iplImage avec l'image ulterieurement saisie par la fonction cvGrabFrame(),    
	Detector->SetImage(cvRetrieveFrame((Detector->GetCapture())));
	//Conversion de l'iplImage en QImage
	qImage = CVtoQT(Detector->GetImage());   
	//Detection du visage et récupération de la région du visage sous la forme d'un cadre 
	CvRect r = Detector->Detect();
	//Si Detection OK
	if(r.x>-1)
    { 
        //Si la FaceImage n'a pas encore été reconnu
        if(Found==false)
        {
        //Dessiner le cadre
        Draw(r);
	    qTimer.stop();
	        //Enregistrer l'image capturée
	        if (SaveImageTest(r,ImageFileName))
            {
                //Lancer le Processus de recognition
                //Si FaceImage correspondant à une FaceImage de la base
                if ((iUser=Recognizer->Recognize(Extractor->GetFaceImage()))!=-1)
                {   
                    //Recognition reussie
                    Recognition_Ok(iUser);
                    //Continuer la detection 
                    qTimer.start();              
                }
                //Sinon si FaceImage ne correspondant à aucune FaceImage de la base
                else
                {
                //Afficher le bouton inscription,et celui d'identification, Afficher et activer la wForm,
                    wForm->show();
                    wForm->setEnabled(true);
                    aAdd->setEnabled(true);
                    aLogOn->setEnabled(true);
                    //Continuer la detection 
                    qTimer.start();   
                }   
	        }
	    }
	    //Sinon si FaceImage a été reconnu,Masquer Inscription + désactiver la saisie d'information
	    else
	    {
	        //Affichage de la capture
	        lCapture->setPixmap(QPixmap::fromImage(qImage.scaled(lCapture->width(),lCapture->height()),Qt::AutoColor));
	        aAdd->setEnabled(false);
	        wForm->setEnabled(false);
	    }
	}
	//Sinon si aucun visage n'a été detecté dans la capture
	else
	{  
	    aAdd->setEnabled(false);
	    LogOut();
	    lCapture->setPixmap(QPixmap::fromImage(qImage.scaled(lCapture->width(),lCapture->height()),Qt::AutoColor));
	    resize(lCapture->width(),lCapture->height());
	}

}
//A commenter
void FaceRecognition::Draw(CvRect r)
{
        faceLoc = QRect(QPoint(r.x,r.y),QSize(r.width,r.height));
        lCapture->resize(qImage.width(),qImage.height());
        resize(lCapture->width(),lCapture->height());
	    lCapture->setPixmap(QPixmap::fromImage(qImage.scaled(lCapture->width(),lCapture->height()),Qt::AutoColor));
	    QPainter painter((QPaintDevice*)lCapture->pixmap());
        painter.setBrush(Qt::NoBrush);
        painter.setPen(Qt::white);
        painter.drawRect(QRect(faceLoc.x(),faceLoc.y(),faceLoc.width(),faceLoc.height()));
}
//Extraction de l'image saisie
bool FaceRecognition::SaveImageTest(CvRect r,QString ImageFileName)
{
    Extractor->SetImage(Detector->GetImage());
    Extractor->SetROI(r);
    if(Extractor->Extract(ImageFileName.toStdString().c_str()))
        return true;
    else 
        return false;
}
//Ajout d'un nouvelle utilisateur
void FaceRecognition::AddUser()
{
    //Initialisation des noms des fichiers dst et src
    QString ImageFileNameDst;
    QString ImageFileNameSrc;
    ImageFileNameSrc="faceDB/Test/" + ImageFileNameSrc.setNum(ListUser[FaceDb->GetCount()-1]->GetId()+1) + ".pgm";
    ImageFileNameDst="faceDB/Train/" + ImageFileNameDst.setNum(ListUser[FaceDb->GetCount()-1]->GetId()+1) + ".pgm";
    if(User_Txt->text()=="" || Pass_Txt->text()=="")
    {
        QMessageBox::warning(this,"Erreur!","Veuillez saisir l'ensemble des champs");
        return;
    }
    if(Pass_Txt->text()!=Confirm_Txt->text())
    {
        Pass_Txt->setText("");
        Confirm_Txt->setText("");
        QMessageBox::warning(this,"Erreur!","Veuillez verifier votre mot de passe");
        return;
    }
    //Initialisation d'un objet user
    Users u(ListUser[FaceDb->GetCount()-1]->GetId()+1,User_Txt->text(),Pass_Txt->text(), Nom_Txt->text(),Prenom_Txt->text(),Age_Txt->text().toInt(),
            Adresse_Txt->text(),Ville_Txt->text(),Cp_Txt->text().toInt(),ImageFileNameDst);
    //Ajout du nouvel utilisateur dans la base
    if(FaceDb->Insert(u))
    {
        SetUserList();
        QFile::copy(ImageFileNameSrc,ImageFileNameDst);
        QFile::remove(ImageFileNameSrc);
        Recognizer->Learn(FaceDb->GetCount(),ListUser);
        QMessageBox::information(this,"Mise à jour","L'enregistrement a été effectué avec succès");
    }
    else
    {
        QMessageBox::critical(this,"Erreur!","L'enregistrement n'a pas été effectué veuillez réessayer");
    }
}
//Suppresion de profil
void FaceRecognition::DeleteUser()
{
    QString sFileName;
    QString sId;
    QSqlQuery query;
    
    int iReponse=QMessageBox::question(this,"Suppresion","Voulez vraiment supprimer votre profil?",QMessageBox::Yes|QMessageBox::No);
    
    if(iReponse==QMessageBox::Yes)
    {
        sId=Id_Txt->text();
        sFileName=Url_Txt->text();
        QFile::remove(sFileName);
        query.exec("DELETE FROM Users WHERE Id=" + sId + ";");
        SetUserList();
        LogOut();
        QMessageBox::information(this,"Suppression","Suppresion effectuée");
    }
}
//Mise à jour de la photo du user
void FaceRecognition::UpdateUser()
{
    //Initialisation des noms des fichiers dst et src
    QString ImageFileNameDst;
    QString ImageFileNameSrc;
    ImageFileNameSrc="faceDB/Test/" + ImageFileNameSrc.setNum(ListUser[FaceDb->GetCount()-1]->GetId()+1) + ".pgm";
    ImageFileNameDst="faceDB/Train/" + Id_Txt->text() + ".pgm";
    QFile::remove(ImageFileNameDst);
    if(QFile::copy(ImageFileNameSrc,ImageFileNameDst))
    {   
        Recognizer->Learn(FaceDb->GetCount(),ListUser);
        QMessageBox::information(this,"Mise à jour","Votre photo a été mise à jour avec succès");
    }
    else
    {
        QMessageBox::critical(this,"Mise à jour","Erreur de mise à jour");
    }
        
}
void FaceRecognition::LogOn()
{
    qTimer.stop();
    dAuthentification->show();
}
void FaceRecognition::Authentification()
{
    
    QSqlQuery query;
    
    if (query.exec("SELECT * FROM Users WHERE User='" + UserLogin_Txt->text() + "' AND Pass='" + PassLogin_Txt->text() + "';"))
    {
        if (query.next())
        {
            Id_Txt->setText(query.value(0).toString());
            User_Txt->setText(query.value(1).toString());
            Pass_Txt->setText(query.value(2).toString());
            Nom_Txt->setText(query.value(3).toString());
            Prenom_Txt->setText(query.value(4).toString());
            Age_Txt->setText(query.value(5).toString());
            Adresse_Txt->setText(query.value(6).toString());
            Ville_Txt->setText(query.value(7).toString());
            Cp_Txt->setText(query.value(8).toString());
            Url_Txt->setText(query.value(9).toString());
            Confirm_Txt->setText(Pass_Txt->text());
            Found=true;
            dAuthentification->hide();
            qTimer.start();
            User_On();
         }
         else
         {
            Found=false;
            QMessageBox::critical(dAuthentification,"Erreur","Veuillez verifier votre identifiant ainsi que votre mot de passe");
         }
    }
    
}
void FaceRecognition::LogOut()
{
    User_Out();
    Id_Txt->setText("");
    User_Txt->setText("");
    Pass_Txt->setText("");
    Confirm_Txt->setText("");
    Nom_Txt->setText("");
    Prenom_Txt->setText("");
    Age_Txt->setText("");
    Adresse_Txt->setText("");
    Ville_Txt->setText("");
    Cp_Txt->setText("");
    Url_Txt->setText("");
}
void FaceRecognition::Recognition_Ok(int iUsers)
{
    
    User_On();
    Id_Txt->setText(QString::number(ListUser[iUsers]->GetId()));
    User_Txt->setText(ListUser[iUsers]->GetUser());
    Pass_Txt->setText(ListUser[iUsers]->GetPass());
    Nom_Txt->setText(ListUser[iUsers]->GetNom());
    Prenom_Txt->setText(ListUser[iUsers]->GetPrenom());
    Age_Txt->setText(QString::number(ListUser[iUsers]->GetAge()));
    Adresse_Txt->setText(ListUser[iUsers]->GetAdresse());
    Ville_Txt->setText(ListUser[iUsers]->GetVille());
    Cp_Txt->setText(QString::number(ListUser[iUsers]->GetCp()));
    Url_Txt->setText(ListUser[iUsers]->GetUrl());
    Confirm_Txt->setText(Pass_Txt->text());
}
void FaceRecognition::User_On()
{
    Found=true;
    wForm->show();
    wForm->setEnabled(false);
    aLogOut->setEnabled(true);
    aDelete->setEnabled(true);
    aUpdate->setEnabled(true);
    aLogOn->setEnabled(false);
    aAdd->setEnabled(false);
}

void FaceRecognition::User_Out()
{   
    Found=false;
    wForm->hide();
    aLogOut->setEnabled(false);
    aDelete->setEnabled(false);
    aUpdate->setEnabled(false);
    aLogOn->setEnabled(false);
    aAdd->setEnabled(false);
}
void FaceRecognition::SetUserList()
{
    QSqlQuery query;
    ListUser= new Users*[FaceDb->GetCount()];
    int i=0;
    if(query.exec("Select * From Users;"))
    {
        while(query.next())
        {
        
           ListUser[i]=new Users(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toString(),
                                 query.value(4).toString(),query.value(5).toInt(),query.value(6).toString(),query.value(7).toString(),
                                 query.value(8).toInt(),query.value(9).toString());
            i++;
        }
    }
}
void FaceRecognition::mouseDoubleClickEvent (QMouseEvent *)
{
	if (isWindow()) {
		if (isFullScreen())
			showNormal();
		else
			showFullScreen();
	}
	else {
		emit doubleclick();
	}
}

void FaceRecognition::Start()
{
    qTimer.start();
}
