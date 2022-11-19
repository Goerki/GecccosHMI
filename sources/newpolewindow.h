#ifndef NEWPOLEWINDOW_H
#define NEWPOLEWINDOW_H

#include <QDialog>
#include "gecccospoles.h";

namespace Ui {
class NewPoleWindow;
}

class NewPoleWindow : public QDialog
{
    Q_OBJECT

public:
    explicit NewPoleWindow(QWidget *parent = nullptr, GecccosPoles *poles = nullptr);
    ~NewPoleWindow();
    QString getValue();


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::NewPoleWindow *ui;
    QString valueSet;
};

#endif // NEWPOLEWINDOW_H
