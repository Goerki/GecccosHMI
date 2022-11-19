#ifndef CHOOSEPROJECTWINDOW_H
#define CHOOSEPROJECTWINDOW_H

#include <QDialog>
#include <QFileDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class ChooseProjectWindow; }
QT_END_NAMESPACE

class ChooseProjectWindow : public QDialog
{
    Q_OBJECT

public:
    ChooseProjectWindow(QWidget *parent = nullptr);
    ~ChooseProjectWindow();
    QString projectFolder;

private slots:
    void on_CloseButton_clicked();

    void on_OpenButton_clicked();

    void on_NewButton_clicked();

private:
    Ui::ChooseProjectWindow *ui;
};
#endif // CHOOSEPROJECTWINDOW_H
