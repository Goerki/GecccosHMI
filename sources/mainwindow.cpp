#include "mainwindow.h"
#include "chooseprojectwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startMainWindow(){

    this->show();
    window->exec();
    QString folder = window->projectFolder;

    project = new GecccosProject(folder,folder+"\\hmi_config.json",true);

    ui->fileView->setModel(project->getStdModel());
    ui->fileView->setColumnWidth(0,150);
    ui->fileView->setColumnWidth(1,200);
}

void MainWindow::on_fileView_clicked(const QModelIndex &index)
{

    int itemIndex = index.data(1).toInt();
    activeFileSelection=index;
    if (itemIndex!= 0){
        GecccosFile* file = project->getItem(itemIndex)->getFile();
        if (file == nullptr){
            // nullpointer
        } else {
        showFile(file);
        }
    }
    return;
}

void MainWindow::showFile(GecccosFile *file){
    //TODO: Clear
    clearLayout();
    activeFile = file;
    /*QPushButton *btn1 = new QPushButton("knoepfele");
    ui->verticalLayout->addWidget(btn1);
    */
    for (int i=0; i< file->getNumberLists(); i++){
        showListOnLayout(file->getList(i));
    }
    for (int i=0; i< file->getNumberTables(); i++){
        showTableOnLayout(file->getTable(i));
    }
    for (int i=0; i< file->getNumberParameters(); i++){
        showParameterOnLayout(file->getParam(i), ui->verticalLayout);
    }
    for (int i=0; i< file->getNumberMaps(); i++){
        showMapOnLayout(file->getMap(i));
    }
    for (int i=0; i< file->getNumberPoles(); i++){
        showPolesOnLayout(file->getPoles(i));
    }

    if (file->hasText()){
        showTextOnLayout();
    }

}

void MainWindow::showListOnLayout(GecccosList *list){
    QLabel *ListLabel = new QLabel();
    ListLabel->setText(list->getName());
    ListLabel->setToolTip(list->getDescription());
    ui->verticalLayout->addWidget(ListLabel);
    QTableView *newTable = new QTableView;
    QStandardItemModel *model = list->getModel();
    bool ok = connect(model, &QStandardItemModel::itemChanged,this,&MainWindow::changedList);
    Q_ASSERT(ok);
    newTable->setModel(model);
    newTable->setFixedWidth(700);
    newTable->horizontalHeader()->setStretchLastSection(true);
    ui->verticalLayout->addWidget(newTable);
    QPushButton *addRowButton = new QPushButton();
    addRowButton->setText("Add new Entry");
    addRowButton->setToolTip("add row to the list displayed");
    connect(addRowButton, &QPushButton::clicked, this, MainWindow::addRowToActiveList);
    ui->verticalLayout->addWidget(addRowButton);

    //visibleWidgets.append(ListLabel);
    visibleWidgets[ListLabel]=list;
    visibleWidgets[addRowButton]=list;
    visibleWidgets[newTable]=list;
}

void MainWindow::addRowToActiveList(){
    activeFile->activeList()->addEntryToList();
    for (int i=0; i<visibleWidgets.keys().size(); i++){
        QTableView *table = dynamic_cast<QTableView*>(visibleWidgets.keys()[i]);
        //GecccosElement* listPointer = visibleWidgets[visibleWidgets.keys()[i]];
        if (table && visibleWidgets[visibleWidgets.keys()[i]]==activeFile->activeList()){
            QStandardItemModel* model = activeFile->activeList()->getModel();
            bool ok = connect(model, &QStandardItemModel::itemChanged,this,&MainWindow::changedList);
            table->setModel(model);
            return;
        }
    }

    return;
}

void MainWindow::addRowToActiveTable(){
    activeFile->activeTable()->addEntryToTable();
    for (int i=0; i<visibleWidgets.keys().size(); i++){
        QTableView *table = dynamic_cast<QTableView*>(visibleWidgets.keys()[i]);
        //GecccosElement* listPointer = visibleWidgets[visibleWidgets.keys()[i]];
        if (table && visibleWidgets[visibleWidgets.keys()[i]]==activeFile->activeTable()){
            QStandardItemModel* model = activeFile->activeTable()->getModel();
            bool ok = connect(model, &QStandardItemModel::itemChanged,this,&MainWindow::changedTable);
            Q_ASSERT(ok);
            table->setModel(model);
            return;
        }
    }

    return;
}

void MainWindow::addRowToActivePolesTable(){

    NewPoleWindow *poleWindow = new NewPoleWindow(this,activeFile->activePoles());
    poleWindow->exec();
    QString set = poleWindow->getValue();
    if (set!=""){

    activeFile->activePoles()->addEntryToTable(set);
    for (int i=0; i<visibleWidgets.keys().size(); i++){
        QTableView *table = dynamic_cast<QTableView*>(visibleWidgets.keys()[i]);
        //GecccosElement* listPointer = visibleWidgets[visibleWidgets.keys()[i]];
        if (table && visibleWidgets[visibleWidgets.keys()[i]]==activeFile->activePoles()){
            QStandardItemModel* model = activeFile->activePoles()->getModel();
            bool ok = connect(model, &QStandardItemModel::itemChanged,this,&MainWindow::changedTable);
            Q_ASSERT(ok);
            table->setModel(model);
            return;
        }
    }
    }

    return;
}

void MainWindow::showParameterOnLayout(GecccosParameter *param, QVBoxLayout* parentLayout){
    QHBoxLayout *paramLayout = new QHBoxLayout();
    QLabel *paramLabel = new QLabel();
    paramLabel->setText(param->getName());
    paramLabel->setToolTip(param->getDescription());
    paramLayout->addWidget(paramLabel);
    QLineEdit *valueEdit = new QLineEdit();
    valueEdit->insert(param->getValue());
    valueEdit->setToolTip(param->getDescription());
    activeFile->addParamEdit(valueEdit, param);
    bool ok = connect(valueEdit, &QLineEdit::editingFinished,this,&MainWindow::parameterChanged);
    paramLayout->addWidget(valueEdit);
    parentLayout->addLayout(paramLayout);
    visibleLayouts.append(paramLayout);
    visibleWidgets[paramLabel] = param;
    visibleWidgets[valueEdit] = param;
}

void MainWindow::showMapOnLayout(GecccosMap *map){
    QVBoxLayout *mapLayout = new QVBoxLayout();
    QLabel *mapLabel = new QLabel();
    mapLabel->setText(map->getName());
    mapLayout->addWidget(mapLabel);
    for (int i=0; i<map->getSize(); i++){
        showParameterOnLayout(map->getParam(i), mapLayout);
    }
    visibleLayouts.append(mapLayout);
    ui->verticalLayout->addLayout(mapLayout);
}


void MainWindow::showPolesOnLayout(GecccosPoles *poles){
    QLabel *tableLabel = new QLabel();
    tableLabel->setText(poles->getName());
    tableLabel->setToolTip(poles->getDescription());
    polesTable = new QTableView;
    QStandardItemModel *model = poles->getModel();
    polesTable->setModel(model);
    //newTable->setFixedWidth(700);
    //newTable->setSizeAdjustPolicy();
    polesTable->resizeColumnsToContents();
    polesTable->horizontalHeader()->setStretchLastSection(true);
    polesTable->setSortingEnabled(false);
    polesTable->setSelectionMode(QAbstractItemView::SingleSelection);
    bool ok = connect(model, &QStandardItemModel::itemChanged,this,&MainWindow::changedPole);
    Q_ASSERT(ok);
    ok = connect(polesTable, &QTableView::clicked, this, &MainWindow::polePressed);
    Q_ASSERT(ok);

    ui->verticalLayout->addWidget(tableLabel);
    ui->verticalLayout->addWidget(polesTable);

    visibleWidgets[tableLabel]=poles;
    visibleWidgets[polesTable]=poles;
    QPushButton *addRowButton = new QPushButton();
    addRowButton->setText("Add new Entry");
    addRowButton->setToolTip("add a new pole to the poles displayed");
    connect(addRowButton, &QPushButton::clicked, this, MainWindow::addRowToActivePolesTable);

    ui->verticalLayout->addWidget(addRowButton);
    poleDetailLayout= new PoleDetailLayout();
    //ui->verticalLayout->addLayout(poleDetailLayout);
    //create grid layout for selection details

    visibleWidgets[addRowButton]=poles;
}




void MainWindow::showTableOnLayout(GecccosTable *table){
    QLabel *tableLabel = new QLabel();
    tableLabel->setText(table->getName());
    tableLabel->setToolTip(table->getDescription());
    ui->verticalLayout->addWidget(tableLabel);
    QTableView *newTable = new QTableView;
    newTable->setModel(table->getModel());
    newTable->setFixedWidth(700);
    newTable->resizeColumnsToContents();
    newTable->setSortingEnabled(true);
    newTable->horizontalHeader()->setStretchLastSection(true);
    bool ok = connect(table->getModel(), &QStandardItemModel::itemChanged,this,&MainWindow::changedTable);
    Q_ASSERT(ok);
    ui->verticalLayout->addWidget(tableLabel);
    ui->verticalLayout->addWidget(newTable);

    visibleWidgets[tableLabel]=table;
    visibleWidgets[newTable]=table;
    QPushButton *addRowButton = new QPushButton();
    addRowButton->setText("Add new Entry");
    connect(addRowButton, &QPushButton::clicked, this, MainWindow::addRowToActiveTable);
    addRowButton->setToolTip("add a new row to the currently displayed table");
    ui->verticalLayout->addWidget(addRowButton);
    visibleWidgets[addRowButton]=table;
}


void MainWindow::showTextOnLayout(){
    QTextEdit* textEdit = new QTextEdit();
    textEdit->setText(activeFile->getText());
    bool ok = connect(textEdit, &QTextEdit::textChanged,this,&MainWindow::textChanged);
    Q_ASSERT(ok);
    ui->verticalLayout->addWidget(textEdit);

    visibleWidgets[textEdit]=nullptr;
}


void MainWindow::clearLayout(){
    for (int i=0; i<visibleWidgets.size(); i++){

        ui->verticalLayout->removeWidget(visibleWidgets.keys()[i]);
        visibleWidgets.keys()[i]->close();


    }
    visibleWidgets.clear();
    ui->verticalLayout->removeWidget(this->poleDetailLayout);

    for (int i=0; i<visibleLayouts.size(); i++){
        ui->verticalLayout->removeItem(visibleLayouts[i]);
    }
    visibleLayouts.clear();
    activeFile=nullptr;
    if (this->poleDetailLayout == nullptr){
        this->activeFile=nullptr;
    }
    if (this->poleDetailLayout != nullptr && this->poleDetailLayout->isVisible()){
        this->poleDetailLayout->showEmptyPole();
        ui->verticalLayout->removeWidget(this->poleDetailLayout);
        poleDetailLayout->setVisible(false);
    }


}

void MainWindow::on_fileView_pressed(const QModelIndex &index)
{

}


void MainWindow::changedList(const QStandardItem* item){
    int row = item->row();
    QString value = item->data(0).toString();
    activeFile->activeList()->changeItem(row, value);
}

void MainWindow::changedTable(const QStandardItem* item){
    int row = item->row();
    int col = item->column();
    QString value = item->data(0).toString();
    activeFile->activeTable()->changeItem(row,col, value);
}


void MainWindow::changedPole(const QStandardItem* item){
    int row = item->row();
    int col = item->column();
    QString value = item->data(0).toString();
    if (col==4){
        if (item->checkState() == Qt::Checked){
            value="true";
        } else {
            value="false";
        }

    }

    activeFile->activePoles()->changeItem(row,col, value);
}


void MainWindow::polePressed(const QModelIndex &index){
    int row = index.row();
    int col = index.column();
    if (col >= 7){
    GecccosPoles* activePole = this->activeFile->activePoles();
    GecccosPoleWidth* selectedPole= activePole->getPoleForIndex(index);
    poleDetailLayout->changeValues();
    this->poleDetailLayout->setVisible(true);
    if (selectedPole==nullptr){
        //TODO: show empty details
        this->poleDetailLayout->showEmptyPole();
        ui->verticalLayout->removeWidget(this->poleDetailLayout);
        poleDetailLayout->setVisible(false);
    } else {
        this->poleDetailLayout->showPole(selectedPole, activePole->getIsPrototype());
        poleDetailLayout->setVisible(true);
        ui->verticalLayout->addWidget(this->poleDetailLayout);
    }
    polesTable->setModel(this->activeFile->activePoles()->getModel());
    polesTable->selectionModel()->select( index, QItemSelectionModel::Select );
    } else {
        this->poleDetailLayout->setVisible(false);
    }
}

void MainWindow::parameterChanged(){
    QLineEdit* edit = dynamic_cast<QLineEdit*>(sender());
    activeFile->getParamForEdit(edit)->setValue(edit->text());

}

void MainWindow::textChanged(){
    QTextEdit* edit = dynamic_cast<QTextEdit*>(sender());
    activeFile->setText(edit->toPlainText());
}

void MainWindow::on_saveButton_clicked()
{
    this->project->print();
}

void MainWindow::on_pushButton_clicked()
{
    QString folder = project->getFolder();
    project = new GecccosProject(folder,folder+"/hmi_config.json",true);
    on_fileView_clicked(activeFileSelection);
}

