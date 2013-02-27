#-------------------------------------------------
#
# Project created by QtCreator 2013-02-27T19:31:23
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = purr
TEMPLATE = app


SOURCES += main.cpp\
        purrwindow.cpp \
    filedialog.cpp

HEADERS  += purrwindow.hpp \
    filedialog.hpp

FORMS    += purrwindow.ui \
    filedialog.ui

OTHER_FILES += \
    README.asciidoc
