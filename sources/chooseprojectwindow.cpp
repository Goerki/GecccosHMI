#include "chooseprojectwindow.h"
#include "ui_chooseprojectwindow.h"

ChooseProjectWindow::ChooseProjectWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChooseProjectWindow)
{
    ui->setupUi(this);
}

ChooseProjectWindow::~ChooseProjectWindow()
{
    delete ui;
}


void ChooseProjectWindow::on_CloseButton_clicked()
{
    exit(0);
}


void ChooseProjectWindow::on_OpenButton_clicked()
{

    projectFolder =  QFileDialog::getExistingDirectory(this,
        tr("Select Directory"), "/home/jana");
    this->close();

}


void ChooseProjectWindow::on_NewButton_clicked()
{
    projectFolder = QFileDialog::getExistingDirectory(this,tr("Select Directory"), "/home/jana");
    this->close();
}

