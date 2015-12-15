#include "Users.h"

Users::Users()
{
}

Users::Users(int iId,QString sUser,QString sPass,QString sNom,QString sPrenom,int iAge,QString sAdresse,QString sVille,int iCp,QString sUrl)
{
    Id=iId;
    User=sUser;
    Pass=sPass;
    Nom=sNom;
    Prenom=sPrenom;
    Age=iAge;
    Adresse=sAdresse;
    Ville=sVille;
    Cp=iCp;
    Url=sUrl;
}
Users::Users(const Users &u)
{
    Id=u.Id;
    User=u.User;
    Pass=u.Pass;
    Nom=u.Nom;
    Prenom=u.Prenom;
    Age=u.Age;
    Adresse=u.Adresse;
    Ville=u.Ville;
    Cp=u.Cp;
    Url=u.Url;
}
const Users& Users::operator=(const Users &u)
{
    Id=u.Id;
    User=u.User;
    Pass=u.Pass;
    Nom=u.Nom;
    Prenom=u.Prenom;
    Age=u.Age;
    Adresse=u.Adresse;
    Ville=u.Ville;
    Cp=u.Cp;
    Url=u.Url;
    return *this;
}

int Users::GetId()
{ 
    return Id;
}

void Users::SetId(int iId)
{
    Id=iId;
}

QString Users::GetUser()
{
    return User;
}
void Users::SetUser(QString sUser)
{ 
    User=sUser;
}

QString Users::GetPass()
{
    return Pass;
}
void Users::SetPass(QString sPass)
{ 
    Pass=sPass;
}

QString Users::GetNom()
{
    return Nom;
}
void Users::SetNom(QString sNom)
{ 
    Nom=sNom;
}
QString Users::GetPrenom() 
{
    return Prenom;
}
void Users::SetPrenom(QString sPrenom)
{
    Prenom=sPrenom;
}

int Users::GetAge()
{
    return Age;
}
void Users::SetAge(int sAge)
{
    Age=sAge;
}

QString Users::GetAdresse() 
{
    return Adresse;
}
void Users::SetAdresse(QString sAdresse)
{
    Adresse=sAdresse;
}

QString Users::GetVille() 
{
    return Ville;
}
void Users::SetVille(QString sVille)
{
    Ville=sVille;
}

int Users::GetCp()
{
    return Cp;
}
void Users::SetCp(int iCp)
{
    Cp=iCp;
}

QString Users::GetUrl() 
{
    return Url;
}
void Users::SetUrl(QString sUrl)
{
    Url=sUrl;
}

