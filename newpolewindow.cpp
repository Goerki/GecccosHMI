#include "newpolewindow.h"
#include "ui_newpolewindow.h"

NewPoleWindow::NewPoleWindow(QWidget *parent, GecccosPoles *poles) :
    QDialog(parent),
    ui(new Ui::NewPoleWindow)
{
    ui->setupUi(this);
    ui->jDropBown->addItems(poles->getAvailableConfigurations());
}

NewPoleWindow::~NewPoleWindow()
{
    delete ui;
}

void NewPoleWindow::on_buttonBox_accepted()
{
    valueSet = ui->jDropBown->currentText();
    this->close();
}


void NewPoleWindow::on_buttonBox_rejected()
{
    valueSet = "";
    this->close();
}


QString NewPoleWindow::getValue(){
    return valueSet;
}
