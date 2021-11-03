#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "base.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow,Base
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_clearButton_clicked();
    void on_addButton_clicked();
    void on_showButton_clicked();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    virtual void upd();
    virtual void ClearAll();

};
#endif // MAINWINDOW_H
