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
    include/arch/ProcessorState.hpp \
    include/arch/InstructionSet.hpp \
    include/arch/Processor.hpp

SOURCES += \
    src/mem/SharedMemory.cpp

DISTFILES +=
