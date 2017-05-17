TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    metric.cpp \
    derivedmetrics.cpp \
    dsstring.cpp \
    directoryIterator.cpp

HEADERS += \
    metric.h \
    derivedmetrics.h \
    vector.h \
    hashtable.h \
    linkedlist.h \
    directoryiterator.h \
    DSString.h \
    stack.h \
    avltree.h

