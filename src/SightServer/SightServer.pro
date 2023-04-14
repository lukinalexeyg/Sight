QT += core gui network widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

win32-msvc* {
    QMAKE_CXXFLAGS += /utf-8
}

TARGET = SightServer

VERSION = 1.0

QMAKE_TARGET_PRODUCT = "Sight Server"
QMAKE_TARGET_COMPANY = "LukinAlexey"
QMAKE_TARGET_COPYRIGHT = "Copyright (c) 2022 Lukin Alexey"

DEFINES += APP_NAME=\"\\\"$$QMAKE_TARGET_PRODUCT\\\"\"
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
DEFINES += APP_COMPANY=\\\"$$QMAKE_TARGET_COMPANY\\\"

SOURCES += \
    application.cpp \
    main.cpp \
    mainwindow.cpp \
    network.cpp \
    slider.cpp

HEADERS += \
    application.h \
    mainwindow.h \
    network.h \
    slider.h

SUBMODULES_PATH = $$PWD/../submodules

include(../SightCommon/SightCommon.pri)
include($$SUBMODULES_PATH/LSettings/src/LSettings.pri)
include($$SUBMODULES_PATH/LWorker/src/LWorker.pri)

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
