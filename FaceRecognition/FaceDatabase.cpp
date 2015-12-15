#include "FaceDatabase.h"

FaceDatabase::FaceDatabase(QString hst, QString name, QString user, QString pass)
{
    Host=hst;
    Dbname=name;
    Username=user;
    Pwd=pass;
}

int FaceDatabase::dbConnexion()
{
    facedb=QSqlDatabase::addDatabase("QSQLITE");
    facedb.setDatabaseName(Dbname);
    
    if ( !facedb.open() )
        return -1;
    else
    {  
        QSqlQuery query;
        if(query.exec("SELECT * FROM Users;"))
        {
            query.exec("SELECT COUNT (Id) FROM Users;");
            query.next();
            iCount=query.value(0).toInt();
            return 1;
        }
        else
        {
            QString Erreur=facedb.lastError().text();
            InitDb();
            iCount=3;
            return 0;
        }   
    }
        
}
void FaceDatabase::InitDb()
{
    QSqlQuery query;
    //Requete de création de la table User
    query.exec("CREATE TABLE Users ( Id INTEGER(5) NOT NULL PRIMARY KEY,User TEXT(50) NOT NULL,Pass TEXT(50) NOT NULL, Nom TEXT(50) NOT NULL, Prenom TEXT(50) NOT NULL, Age INTEGER(2), Adresse TEXT(250) , Ville TEXT(50) , Cp INTEGER(5) , Url TEXT(250) );");
    //Requete d'insertion de l'utilisateur Default
    QString Erreur=facedb.lastError().text();
    query.exec("INSERT INTO Users VALUES ('1','laanaithossam','laanaithossam', 'Laanait', 'Hossam', '24', '4 chemin des Bourgognes Appt 198', 'Cergy', '95000', 'faceDB/Train/1.pgm');"); 
    query.exec("INSERT INTO Users VALUES ('2','lobryamelie','lobryamelie', 'Lobry', 'Amelie', '24', '4 chemin des Bourgognes Appt 198', 'Cergy', '95000', 'faceDB/Train/2.pgm');"); 
    query.exec("INSERT INTO Users VALUES ('3','khojanora','khojanora','Khoja', 'Nora', '23', '4 chemin des Bourgognes Appt 198', 'Cergy', '95000', 'faceDB/Train/3.pgm');"); 
}
int FaceDatabase::GetCount()
{
    return iCount;
}
void FaceDatabase::SetCount()
{
    iCount=iCount-1;
}
bool FaceDatabase::Insert(Users u)
{
    QSqlQuery query;
    if(query.exec("INSERT INTO Users VALUES ('" + QString::number(u.GetId()) + "','"+ u.GetUser() +"','"+ u.GetPass()+"','"+ u.GetNom()+
                                             "','" + u.GetPrenom()+"','" + QString::number(u.GetAge())+"','" + u.GetAdresse()+"','" +
                                             u.GetVille()+"','" + QString::number(u.GetCp()) +"', '" + u.GetUrl() +"');") 
      )
      {
        iCount=iCount+1;
        return true;
      }  
      else return false;
}

int FaceDatabase::Update(Users u)
{
    return 0;
}

int FaceDatabase::Delete(QString sId)
{
    return 0;
}