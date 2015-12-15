#ifndef USERS_H
#define USERS_H
#include <QString>
using namespace std;
class Users
{
private :
    int Id;
    QString User;
    QString Pass;
    QString Nom;
    QString Prenom;
    int Age;
    QString Adresse;
    QString Ville;
    int Cp;
    QString Url;
public :
    Users();
    Users(const Users&);
    Users(int,QString,QString,QString,QString,int,QString,QString,int,QString);
    const Users& operator=(const Users&);
    
    int GetId();
    void SetId(int);
    QString GetUser();
    void SetUser(QString);
    
    QString GetPass();
    void SetPass(QString);
    
    QString GetNom();
    void SetNom(QString);
    
    QString GetPrenom();
    void SetPrenom(QString);
    
    int GetAge();
    void SetAge(int);
    
    QString GetAdresse();
    void SetAdresse(QString);
    
    QString GetVille();
    void SetVille(QString);
    
    int GetCp();
    void SetCp(int);
    
    QString GetUrl();
    void SetUrl(QString);
};
#endif