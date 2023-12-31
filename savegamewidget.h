#ifndef SAVEGAMEWIDGET_H
#define SAVEGAMEWIDGET_H

#include <QDialog>
#include <QPushButton>
#include <QListWidget>

class SaveGameWidget : public QDialog // játék mentő ablak
{
    Q_OBJECT
public:
    explicit SaveGameWidget(QWidget *parent = nullptr);
    void setGameList(QVector<QString> saveGameList); // a játékok betöltése
    int selectedGame() const { return _listWidget->currentRow(); } // a kiválasztott játék lekérdezése

protected:
    QPushButton* _okButton;
    QPushButton* _cancelButton;
    QListWidget* _listWidget;

signals:
    void okButtonEnabler(bool);

private slots:
    void okButtonEnablerSlot();
};

#endif // SAVEGAMEWIDGET_H
