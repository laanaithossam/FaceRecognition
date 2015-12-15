#ifndef FACEDATABASE_H
#define FACEDATABASE_H

#include <QtSql/QtSql>
#include <QMessageBox>
#include <QString>
#include <QVariant>
#include "Users.h"

class FaceDatabase
{
private:
    QString Host;
    QString Dbname;
    QString Username;
    QString Pwd;
    int iCount;
public:
    FaceDatabase();
    FaceDatabase(QString,QString,QString,QString);
    QSqlDatabase facedb;
    int dbConnexion();
    void InitDb();
    bool createConnection();
    int GetCount();
    void SetCount();
    bool Insert(Users);
    int Update(Users);
    int Delete(QString);
};

#endif