QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += multimedia


CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    draglabel.cpp \
    droplabel.cpp \
    game.cpp \
    hearts.cpp \
    items.cpp \
    main.cpp \
    questions.cpp \
    score.cpp

HEADERS += \
    draglabel.h \
    droplabel.h \
    game.h \
    hearts.h \
    items.h \
    questions.h \
    score.h

FORMS += \
    game.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background_main.qrc

DISTFILES +=
