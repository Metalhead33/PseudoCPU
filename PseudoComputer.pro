TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/BaseFunc.cpp \
    src/Deadea8.cpp

HEADERS += \
    include/AbstractProcessor.hpp \
    include/BaseFunc.hpp \
    include/Deadea8.hpp
