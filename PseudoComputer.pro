TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    src/BaseFunc.cpp \
    src/StdStream.cpp \
    src/DeaDea16.cpp

HEADERS += \
    include/BaseFunc.hpp \
    include/AbstractMemcontainer.hpp \
    include/AbstractFread.hpp \
    include/AbstractFwrite.hpp \
    include/StdStream.hpp \
    Global.hpp \
    include/AbstractProcessor.hpp \
    include/DeaDea16.hpp
