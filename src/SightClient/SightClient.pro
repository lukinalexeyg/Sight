QT += core gui network svg widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32-msvc* {
    QMAKE_CXXFLAGS += /utf-8
}

TARGET = SightClient

VERSION = 1.0

QMAKE_TARGET_PRODUCT = "Sight Clientr"
QMAKE_TARGET_COMPANY = "LukinAlexey"
QMAKE_TARGET_COPYRIGHT = "Copyright (c) 2022 Lukin Alexey"

DEFINES += APP_NAME=\"\\\"$$QMAKE_TARGET_PRODUCT\\\"\"
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += APP_COMPANY=\\\"$$QMAKE_TARGET_COMPANY\\\"

SOURCES += \
    application.cpp \
    aspectratiowidget.cpp \
    main.cpp \
    mainwindow.cpp \
    network.cpp

HEADERS += \
    application.h \
    aspectratiowidget.h \
    mainwindow.h \
    network.h

include(../SightCommon/SightCommon.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DESTDIR = bin
MOC_DIR = moc
OBJECTS_DIR = obj
RCC_DIR = rcc

win32-msvc* {
    QMAKE_EXTRA_TARGETS += before_build makefilehook
    makefilehook.target = $(MAKEFILE)
    makefilehook.depends = .beforebuild
    PRE_TARGETDEPS += .beforebuild
    before_build.target = .beforebuild
    before_build.depends = FORCE
    before_build.commands = chcp 1251
}

RESOURCES += resources.qrc
