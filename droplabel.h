#ifndef DROPLABEL_H
#define DROPLABEL_H

#include <QLineEdit>

class DropLabel : public QLineEdit
{
    Q_OBJECT
public:
    explicit DropLabel(QWidget *parent = nullptr);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
signals:

};

#endif // DROPLABEL_H
