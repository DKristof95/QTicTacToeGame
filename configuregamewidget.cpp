#include "configuregamewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

ConfigureGameWidget::ConfigureGameWidget(QWidget *parent) :
    QDialog(parent)
{
    setFixedSize(300, 200);
    setWindowTitle("Amőba - Beállítások");

    _newGameButton = new QPushButton("Új játék");
    _cancelButton = new QPushButton("Mégse");

    _sizeGroupBox = new QGroupBox("Játéktér mérete");
    _smallSizeButton = new QRadioButton("Kicsi - 6*6");
    _smallSizeButton->setChecked(true);
    _mediumSizeButton = new QRadioButton("Közepes - 10*10");
    _largeSizeButton = new QRadioButton("Nagy - 14*14");

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(_smallSizeButton);
    vbox->addWidget(_mediumSizeButton);
    vbox->addWidget(_largeSizeButton);
    _sizeGroupBox->setLayout(vbox);

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addWidget(_newGameButton);
    hlayout->addWidget(_cancelButton);

    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->addWidget(_sizeGroupBox);
    vlayout->addLayout(hlayout);

    setLayout(vlayout);

    connect(_newGameButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

int ConfigureGameWidget::newSize(){
    if (_smallSizeButton->isChecked()){
        return 6;
    } else if (_mediumSizeButton->isChecked()){
        return 10;
    } else if (_largeSizeButton->isChecked()){
        return 14;
    } else {
        return 6;
    }
}
