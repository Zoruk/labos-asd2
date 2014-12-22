TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    wordgenerartor.cpp \
    worddictionarystl.cpp \
    worddictionary.cpp \
    spellingchecker.cpp \
    wrongword.cpp \
    worddictionarytst.cpp \
    ternarysearchtrie.cpp \
    ternarysearchtriebis.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    AVLTree.h \
    BinarySearchTree.h \
    wordgenerartor.h \
    worddictionarystl.h \
    worddictionary.h \
    spellingchecker.h \
    wrongword.h \
    worddictionarytst.h \
    ternarysearchtrie.h \
    ternarysearchtriebis.h

