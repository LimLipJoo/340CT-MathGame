#include "droplabel.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QDropEvent>

DropLabel::DropLabel(QWidget *parent) : QLineEdit(parent)
{
    setAcceptDrops(true);
}
void DropLabel::dragEnterEvent(QDragEnterEvent *event){
    if(event->mimeData()->hasFormat("text/plain"))
        event->acceptProposedAction();
}
void DropLabel::dropEvent(QDropEvent *event){
    setText(event->mimeData()->text());
    event->acceptProposedAction();
}
