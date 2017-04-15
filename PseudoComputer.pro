TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += $$PWD/include
LIBS += -lpthread

SOURCES += main.cpp \
    src/BaseFunc.cpp \
    src/StdStream.cpp \
    src/Bitwise.c \
    src/Interrupt.cpp \
    src/memory/SharedMemoryAccess.cpp \
    src/memory/DirectMemoryAccess.cpp \
    src/abstract/AbstractMemoryHandler.cpp \
    src/arch/DeaDea16.cpp

HEADERS += \
    include/BaseFunc.hpp \
    include/StdStream.hpp \
    include/Bitwise.h \
    include/Global.hpp \
    include/Interrupt.hpp \
    include/abstract/AbstractFread.hpp \
    include/abstract/AbstractFwrite.hpp \
    include/abstract/AbstractInterruptHandler.hpp \
    include/abstract/AbstractMemoryHandler.hpp \
    include/abstract/AbstractProcessorCore.hpp \
    include/abstract/AbstractProcessorState.hpp \
    include/memory/DirectMemoryAccess.hpp \
    include/memory/SharedMemoryAccess.hpp \
    include/arch/DeaDea16.hpp \
    include/abstract/AbstractProcessorArchitecture.hpp \
    include/abstract/AbstractProcessor.hpp
