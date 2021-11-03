#ifndef BASE_H
#define BASE_H

#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QPair>
#include <QVector>
#include <QTextStream>
#include <QFile>
#include <QInputDialog>
#include <QMessageBox>
#include <QMainWindow>
#include "framewindow.h"

class Base
{
public:
    Base();

private:

    QString path;

public:

    FrameWindow Paint;

    int PointsQuant = 0;
    int CheckCoords(const QStringList &list); //errors: 1- incorrect number of points 2- incorrect type 3-incorrect value


    bool AddCheck(const QStringList &list); //check coords wanted to add
    bool lineFileCheck(const QStringList &list, int line); //check one line of file

    void readFile();
    void CheckGeometry();
    void set_path(QString p){path = p;};

    QString get_path(){return path;};

    virtual void ClearAll() = 0 ;
    virtual void upd() = 0;


};

#endif // BASE_H
