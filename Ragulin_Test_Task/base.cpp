#include "base.h"

Base::Base()
{

}

bool Base::AddCheck(const QStringList &list){
    auto err = CheckCoords(list);

    if(err != 0) {
        QMessageBox msgBox;
        QString error_type;

        msgBox.setWindowTitle("Error");

        if(err == 1) error_type = "incorrect number of points";
        else if(err == 2) error_type = "incorrect type";
        else error_type = "incorrect value";

        msgBox.setText(error_type);
        msgBox.exec();

        return false;
    }
    return true;
}

int Base::CheckCoords(const QStringList &list){
    if(list.size()!=2) return 1 ;

    bool norm1,norm2;
    auto x = list[0].toInt(&norm1);
    auto y = list[1].toInt(&norm2);

    if(!(norm1&&norm2)) return 2;

    if(x > 500 || x < 0 || y > 500 || y < 0) return 3;

    return 0;
}

bool Base::lineFileCheck(const QStringList &list, int line){
    auto err = CheckCoords(list);

    if(err != 0) {
        QMessageBox msgBox;
        QString error_type;

        msgBox.setWindowTitle("Error");

        if(err == 1) error_type = "incorrect number of points in line: ";
        else if (err == 2) error_type = "incorrect type in line: ";
        else error_type = "incorrect value in line";

        error_type += QString::number(line);

        msgBox.setText(error_type);

        msgBox.exec();

        return false;
        }
    return true;
}

void Base::CheckGeometry(){
    if(Paint.Points.size() < 2) return ;

    if(Paint.Points.size() == 2){
        if((Paint.Points.begin()->first == Paint.Points.end()->first) &&  (Paint.Points.begin()->second == Paint.Points.end()->second))
            Paint.Points.pop_back();
        return ;
    }

    int Ax,Ay,Bx,By,Px,Py;
    double AB,AP,BP;

    for (auto it = Paint.Points.begin() + 1  ; it!=Paint.Points.end() - 1 ; it++ ){
        Ax = (it-1)->first;
        Ay = (it-1)->second;
        Px = it->first;
        Py = it->second;
        Bx = (it+1)->first;
        By = (it+1)->second;
        AB = sqrt((Ax-Bx)*(Ax-Bx) + (Ay-By)*(Ay-By));
        AP = sqrt((Ax-Px)*(Ax-Px) + (Ay-Py)*(Ay-Py));
        BP = sqrt((Bx-Px)*(Bx-Px) + (By-Py)*(By-Py));
        if(AB == (AP + BP)) Paint.Points.erase(it--);
    }
}

void Base::readFile(){
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly)) return ;

    QTextStream in(&file);
    auto delimiter = ",";
    QString line;
    QStringList list;

    while (!in.atEnd()) {
        line = in.readLine();
        list = line.split(delimiter);

        if(!lineFileCheck(list,PointsQuant++)) return ;
     }

     file.close();
     file.open(QIODevice::ReadOnly);

     Paint.Points.clear();
     PointsQuant = 0;
     QTextStream in1(&file);

     while (!in1.atEnd()) {
        line = in1.readLine();
        list = line.split(delimiter);
        Paint.Points.push_back(qMakePair(list[0].toInt(),list[1].toInt()));
     }

     upd();
     file.close();
}
