#-------------------------------------------------
#
# Project created by QtCreator 2013-02-27T19:31:23
#
#-------------------------------------------------

QT       += core gui multimedia

CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = purr
TEMPLATE = app


SOURCES += main.cpp \
    purrwindow.cpp \
    tagger.cpp \
    playlist.cpp

HEADERS  += purrwindow.hpp \
    tagger.hpp \
    taginfo.hpp \
    playlist.hpp \
    iplaylistformatprovider.hpp

FORMS    += purrwindow.ui

OTHER_FILES += \
    README.md
