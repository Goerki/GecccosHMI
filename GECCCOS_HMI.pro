QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chooseprojectwindow.cpp \
    gecccoscomment.cpp \
    gecccoselement.cpp \
    gecccosfile.cpp \
    gecccoslist.cpp \
    gecccoslogger.cpp \
    gecccosmap.cpp \
    gecccosparameter.cpp \
    gecccospole.cpp \
    gecccospoles.cpp \
    gecccospolewidth.cpp \
    gecccosproject.cpp \
    gecccosstates.cpp \
    gecccostable.cpp \
    gecccostreeitem.cpp \
    main.cpp \
    mainwindow.cpp \
    newpolewindow.cpp \
    poledetaillayout.cpp \
    poledimensions.cpp

HEADERS += \
    chooseprojectwindow.h \
    gecccoscomment.h \
    gecccoselement.h \
    gecccosfile.h \
    gecccoslist.h \
    gecccoslogger.h \
    gecccosmap.h \
    gecccosparameter.h \
    gecccospole.h \
    gecccospoles.h \
    gecccospolewidth.h \
    gecccosproject.h \
    gecccosstates.h \
    gecccostable.h \
    gecccostreeitem.h \
    mainwindow.h \
    newpolewindow.h \
    poledetaillayout.h \
    poledimensions.h

FORMS += \
    chooseprojectwindow.ui \
    mainwindow.ui \
    newpolewindow.ui

TRANSLATIONS += \
    GECCCOS_HMI_en_001.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    config.json
