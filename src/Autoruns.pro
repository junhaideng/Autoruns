QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    bootexecute.cpp \
    dlls.cpp \
    driver.cpp \
    logon.cpp \
    main.cpp \
    autoruns.cpp \
    service.cpp \
    tasks.cpp \
    utils.cpp

HEADERS += \
    about.h \
    autoruns.h \
    bootexecute.h \
    dlls.h \
    driver.h \
    logon.h \
    service.h \
    tasks.h \
    utils.h

FORMS += \
    about.ui \
    autoruns.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -lVersion \
        -ltaskschd \
        -lole32 \
        -luser32 \
        -loleaut32 \
        -lwintrust
