TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    wordgenerartor.cpp \
    worddictionarystl.cpp \
    worddictionary.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    AVLTree.h \
    BinarySearchTree.h \
    wordgenerartor.h \
    worddictionarystl.h \
    worddictionary.h

