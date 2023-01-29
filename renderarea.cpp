#include "renderarea.h"
#include <QPainter>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{
}

void RenderArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QColor color(230, 50, 170);
    painter.setBrush(color);

    painter.drawRect(0, 0, width()-1, height()-1);
    QColor color2(60, 210, 70);
    painter.setBrush(color2);
    QPoint point(width()/2 + 9, height()/2 - 9);
    QPoint point1(width()/2 + 3, height()/2 - 5);
    QPoint point2(width()/2 + -9, height()/2 + 9);
    QPoint point3(width()/2 - 5, height()/2 + 3);
    painter.drawEllipse(point, 15, 20);
    painter.drawEllipse(point1, 15, 20);
    painter.drawEllipse(point2, 15, 20);
    painter.drawEllipse(point3, 15, 20);
}
