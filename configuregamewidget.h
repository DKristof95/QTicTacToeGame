#ifndef CONFIGUREGAMEWIDGET_H
#define CONFIGUREGAMEWIDGET_H

#include <QDialog>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>

class ConfigureGameWidget : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigureGameWidget(QWidget *parent = nullptr);
    int newSize();

protected:
    QPushButton* _newGameButton;
    QPushButton* _cancelButton;
    QGroupBox* _sizeGroupBox;
    QRadioButton* _smallSizeButton;
    QRadioButton* _mediumSizeButton;
    QRadioButton* _largeSizeButton;
};

#endif // CONFIGUREGAMEWIDGET_H
