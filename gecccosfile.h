#ifndef GECCCOSFILE_H
#define GECCCOSFILE_H

#include <QObject>
#include <QFile>
#include <gecccoselement.h>
#include <gecccosparameter.h>
#include <gecccostext.h>
#include <gecccoslist.h>
#include <gecccosmap.h>
#include <gecccostable.h>
#include <gecccospoles.h>
#include <gecccoscomment.h>
#include <QLineEdit>
#include <QTextEdit>


class GecccosFile
{
    QString filePath;
    QString description;
    QString name;
    QList<GecccosMap*> mapList;
    QList<GecccosParameter*> paramList;
    QList<GecccosTable*> tableList;
    QList<GecccosList*> listList;
    QList<GecccosPoles*> polesList;
    QList<GecccosComment*> commentList;
    QList<GecccosElement*> elementOrder;
    QString text;
    QMap<QLineEdit*, GecccosParameter*> paramLink;

public:
    GecccosFile(QString nameVar, QString descriptionVar);
    void addElementFromJsonObject(QJsonObject object, QString folder);
    void getDataFromFolder(QString folderPath, QString folder);
    QString getName() const;
    QString getDescription() const;
    int getNumberLists();
    int getNumberMaps();
    int getNumberParameters();
    int getNumberTables();
    int getNumberPoles();
    GecccosList* activeList();
    GecccosTable* activeTable();
    GecccosList* getList(int index);
    GecccosMap* getMap(int index);
    GecccosParameter* getParam(int index);
    GecccosTable* getTable(int index);
    GecccosPoles* getPoles(int index);
    GecccosPoles* activePoles();
    void addParamEdit(QLineEdit* edit,GecccosParameter* parameter);
    GecccosParameter* getParamForEdit(QLineEdit* edit);
    void print();
    bool hasText();
    QString getText();
    void setText(QString text);
private:
    void appendTable(GecccosTable* table);
    void setFileOrder(QTextStream* stream);
};

#endif // GECCCOSFILE_H
