TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    ArbreHuffmanBranche.cpp \
    ArbreHuffmanFeuille.cpp \
    Labo1.cpp \
    Labo1_tools.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ArbreHuffman.h \
    ArbreHuffmanBranche.h \
    ArbreHuffmanFeuille.h \
    Labo1_tools.h

