TEMPLATE = app

CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = gfxtest



SOURCES += \
    ../gfx_layout.c \
    ../gfx_menu.c \
    ../gfx_utils.c \
    ../gfx_widget.c \
    main.cpp

HEADERS += \
    ../gfx_config.h \
    ../gfx_layout.h \
    ../gfx_menu.h \
    ../gfx_utils.h \
    ../gfx_widget.h \
    tst_gfx.h

INCLUDEPATH += "C:\\Program Files (x86)\\googletest\\1.8.1_x32\\include"
#INCLUDEPATH += "C:\\Program Files (x86)\\googletest\\1.8.1_x32\\include"

LIBS += -L"C:\\Program Files (x86)\\googletest\\1.8.1_x32\\bin" -lgtest


INCLUDEPATH += "../"
INCLUDEPATH += "../../utils"


