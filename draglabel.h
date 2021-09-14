#ifndef DRAGLABEL_H
#define DRAGLABEL_H

#include <QLabel>

class DragLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DragLabel(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QPoint dragStartPosition;
signals:

};

#endif // DRAGLABEL_H
