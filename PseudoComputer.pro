TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -L"/usr/lib/"
LIBS += -L"/usr/local/lib/"
include(qmake_modules/findSFML.pro)
INCLUDEPATH += $$PWD/include
LIBS += -lpthread

HEADERS += \
    include/mem/SharedMemory.hpp \
    include/mem/Bitbuffer.hpp \
    include/abstract/AbstractFread.hpp \
    include/abstract/AbstractFwrite.hpp \
    StdStream.hpp \
    include/abstract/ProcessorState.hpp \
    include/abstract/InstructionSet.hpp \
    include/abstract/Processor.hpp \
    include/arch/Arrpee8.hpp

SOURCES += \
    src/mem/SharedMemory.cpp \
    StdStream.cpp \
    src/arch/Arrpee8.cpp

DISTFILES +=
