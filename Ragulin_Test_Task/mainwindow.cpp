#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->points_textBrowser->setText("0");
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_clearButton_clicked() {
    ClearAll();
}

void MainWindow::ClearAll(){
    Paint.Points.clear();

    this->PointsQuant = 0;

    set_path("");

    upd();
}

void MainWindow::on_addButton_clicked() {
    bool ok;

    QString text = QInputDialog::getText(this, tr("Add Point"),
                                            tr("Input Coords:"), QLineEdit::Normal,
                                            "", &ok);
       if (ok && !text.isEmpty())
       {
           QStringList list;

           list = text.split(",");

           if(!AddCheck(list)) return ;

           Paint.Points.push_back(qMakePair(list[0].toInt(),list[1].toInt()));
           PointsQuant++;
           upd();
       }
}

void MainWindow::on_showButton_clicked() {
    if(Paint.Points.size()==0){

        QMessageBox msgBox;

        msgBox.setWindowTitle("Error");
        msgBox.setText("No points");

        msgBox.exec();

        return ;
    }

    Paint.show();
}

void MainWindow::upd(){

    ui->main_textBrowser->clear();
    ui->label->setText(get_path());

    bool c = 0;

    CheckGeometry();

    for (auto it = Paint.Points.begin() ; it!=Paint.Points.end() ; ++it ){
           if(c) ui->main_textBrowser->insertPlainText(",");
           c = true;
           ui->main_textBrowser->insertPlainText("(" + QString::number(it->first) + "," + QString::number(it->second) + ")");
    }

    ui->points_textBrowser->setText(QString::number(Paint.Points.size()));
}



void MainWindow::on_actionOpen_triggered() {
    set_path(QFileDialog::getOpenFileName(0,QObject::tr("Choose file"),QDir::homePath(), QObject::tr("All Files (*.*)")));
    readFile();
}

void MainWindow::on_actionSave_triggered(){
    set_path(QFileDialog::getOpenFileName(0,QObject::tr("Choose file"),QDir::homePath(), QObject::tr("All Files (*.*)")));

    QFile file(get_path());

    if(!file.open(QIODevice::WriteOnly)) return ;

    file.resize(0);

    QTextStream out(&file);

    for (auto it = Paint.Points.begin() ; it!=Paint.Points.end() ; ++it ){
           out << QString::number(it->first) << ", " << QString::number(it->second) << "\n";
    }

    file.close();
    upd();
}

