#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <chooseprojectwindow.h>
#include <gecccosproject.h>
#include <QTreeView>
#include <QWidget>
#include <gecccosfile.h>
#include <QTableView>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QBoxLayout>
#include <typeinfo>
#include "newpolewindow.h"
#include "poledetaillayout.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    ChooseProjectWindow *window = new ChooseProjectWindow();
    GecccosProject *project = NULL;
    QModelIndex activeFileSelection;
    QTableView* polesTable;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void startMainWindow();
    QMap<QWidget*, GecccosElement*> visibleWidgets;
    QList<QLayout*> visibleLayouts;
    GecccosFile* activeFile;
    PoleDetailLayout* poleDetailLayout;


public slots:
    void on_fileView_clicked(const QModelIndex &index);
    void changedList(const QStandardItem* item);
    void changedPole(const QStandardItem* item);
    void changedTable(const QStandardItem* item);
    void polePressed(const QModelIndex &index);
    void textChanged();
    void parameterChanged();
    void on_fileView_pressed(const QModelIndex &index);

private slots:
    void on_saveButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void showFile(GecccosFile* file);
    void showListOnLayout(GecccosList* list);
    void showTableOnLayout(GecccosTable* list);
    void showPolesOnLayout(GecccosPoles* list);
    void showParameterOnLayout(GecccosParameter* list,QVBoxLayout* parentLayout);
    void showMapOnLayout(GecccosMap* list);
    void clearLayout();
    void addRowToActiveList();
    void addRowToActiveTable();
    void addRowToActivePolesTable();
    void showTextOnLayout();
    QGridLayout* createEmptyLayoutForPole();
    QGridLayout* createLayoutForSelectedPole(GecccosPoleWidth* width);


};

#endif // MAINWINDOW_H
