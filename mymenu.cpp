#include "mymenu.h"
#include <QEnterEvent>

void MyMenu::enterEvent(QEvent *event)
{
    emit myMenuMouseHover();

    enterEvent(static_cast<QEnterEvent*>(event));

}

void MyMenu::leaveEvent(QEvent *event)
{
    emit myMenuMouseLeave();

    QMenu::QWidget::leaveEvent(event);

}
