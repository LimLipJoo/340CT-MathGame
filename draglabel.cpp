#include "draglabel.h"
#include <QLabel>
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>

DragLabel::DragLabel(QWidget *parent) : QLabel(parent)
{

}

void DragLabel::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton)
            dragStartPosition = event->pos();
}

void DragLabel::mouseMoveEvent(QMouseEvent *event){
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - dragStartPosition).manhattanLength()
         < QApplication::startDragDistance())
        return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    mimeData->setText(this->text());
    drag->setMimeData(mimeData);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
}
