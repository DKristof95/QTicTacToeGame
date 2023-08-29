#include "loadgamewidget.h"
#include <QMessageBox>

LoadGameWidget::LoadGameWidget(QWidget *parent) :
    SaveGameWidget(parent)
{
    setWindowTitle("Amőba - Játék betöltése");

    // ellenőrzést is végzünnk az OK gomb lenyomására
    disconnect(_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(_okButton, SIGNAL(clicked()), this, SLOT(okButton_Clicked()));
}

void LoadGameWidget::okButton_Clicked()
{
    if (_listWidget->currentItem()->text() == "üres")
    {
        // ha üres mezőt választott, akkor nem engedjük tovább
        QMessageBox::warning(this, tr("Amőba"), tr("Nincs játék kiválasztva!"));
        return;
    }

    accept(); // különben elfogadjuk a dialógust
}
