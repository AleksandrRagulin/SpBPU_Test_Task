#include "framewindow.h"
#include "ui_framewindow.h"
#include <QPainter>

FrameWindow::FrameWindow(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameWindow)
{
    ui->setupUi(this);
}

FrameWindow::~FrameWindow() {
    delete ui;
}

void FrameWindow::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e);

  QPainter qp(this);

  drawLines(&qp);
}

void FrameWindow::drawLines(QPainter *qp) {
  QPen penline(Qt::black, 2, Qt::SolidLine);
  QPen penpoint(QBrush(QColor(Qt::red)), 5 );

  int x1,x2,y1,y2;

  for (auto it = Points.begin()+1 ; it!=Points.end() ; ++it ){
      x1 = (it-1)->first;
      y1 = 500 -(it-1)->second;
      x2 = it->first;
      y2 = 500 -it->second;

      qp->setPen(penline);
      qp->drawLine(x1, y1, x2, y2);
      qp->setPen(penpoint);
      qp->drawPoint( x1, y1 );

      if(it==Points.end()-1){
        qp->setPen(penpoint);
        qp->drawPoint( x2, y2 );
    }
  }
}
