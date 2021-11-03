#ifndef FRAMEWINDOW_H
#define FRAMEWINDOW_H

#include <QFrame>
#include <QPainter>

namespace Ui {
class FrameWindow;
}

class FrameWindow : public QFrame
{
    Q_OBJECT

public:
    explicit FrameWindow(QWidget *parent = nullptr);
    ~FrameWindow();

    QVector <QPair<int,int> > Points;

    void paintEvent(QPaintEvent *event);
    void drawLines(QPainter *qp);

private:

    Ui::FrameWindow *ui;
};

#endif // FRAMEWINDOW_H
