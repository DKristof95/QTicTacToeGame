#ifndef MYMENU_H
#define MYMENU_H

#include <QMenu>

class MyMenu : public QMenu
{
    Q_OBJECT
public:
    using QMenu::QMenu;

signals:
    void myMenuMouseHover();
    void myMenuMouseLeave();

protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};

#endif // MYMENU_H
