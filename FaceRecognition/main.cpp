#include <QApplication>
#include "FaceRecognition.h"
using namespace std;

///<summary>
/// test
///</summary>
int main(int argc, char **argv)
{  
    //Cr�er un nouvel objet de type QApplication
    QApplication app(argc,argv);
    
    
    QString host = "localhost";
    QString dbname = "facedb.db";
    QString username = "root";
    QString pwd = "";
    
    //Cr�ation et affichage de l'objet FaceRecognition
    FaceRecognition FR(host, dbname, username, pwd);
    qApp->addLibraryPath(".");
	FR.show();
	//Execution du programme
	return app.exec();

}