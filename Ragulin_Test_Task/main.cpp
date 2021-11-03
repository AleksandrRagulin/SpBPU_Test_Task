#include "high.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>



int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    High win;

    win.start();

    return app.exec();
}
