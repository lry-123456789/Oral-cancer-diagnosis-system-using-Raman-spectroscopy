QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SqliteOperator.cpp \
    main.cpp \
    mainwindow.cpp \
    window_input_information.cpp \
    window_login.cpp \
    window_register.cpp

HEADERS += \
    SqliteOperator.h \
    mainwindow.h \
    window_input_information.h \
    window_login.h \
    window_register.h

FORMS += \
    mainwindow.ui \
    window_input_information.ui \
    window_login.ui \
    window_register.ui

TRANSLATIONS += \
    main_4_0_0_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
