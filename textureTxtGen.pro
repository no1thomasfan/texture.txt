#-------------------------------------------------
#
# Project created by QtCreator 2016-01-22T17:40:49
#
#-------------------------------------------------


QT       += core gui

win32:RC_ICONS += icon.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


#copydata.commands = $(COPY_DIR) \"$$shell_path($$PWD\\documents)\" \"$$shell_path($$OUT_PWD)\\debug\\documents\"
#first.depends = $(first) copydata
#export(first.depends)
#export(copydata.commands)
#QMAKE_EXTRA_TARGETS += first copydata


TARGET = textureTxtGen
TEMPLATE = app


SOURCES += main.cpp\
        gui.cpp \
    terms.cpp \
    settings.cpp \
    about.cpp \

HEADERS  += gui.h \
    terms.h \
    settings.h \
    about.h \

FORMS    += gui.ui \
    terms.ui \
    settings.ui \
    about.ui


RESOURCES += \
    resources.qrc
