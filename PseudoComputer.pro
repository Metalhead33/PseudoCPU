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
    include/mem/Bitbuffer.hpp \
    include/abstract/AbstractFread.hpp \
    include/abstract/AbstractFwrite.hpp \
    StdStream.hpp \
    include/abstract/Global.hpp \
    include/abstract/AbstractDeclarations.hpp \
    include/abstract/AbstractMemoryDevice.hpp \
    include/abstract/AbstractProcessor.hpp \
    include/abstract/AbstractArchitecture.hpp \
    include/abstract/AbstractExtendedArchitecture.hpp \
    include/abstract/ProcessorTemplate.hpp \
    include/ArithmeticalInstructions.hpp \
    include/ControlFlowInstructions.hpp \
    include/arch/Arrpee8.hpp \
    include/arch/Arrpee16.hpp \
    include/arch/Arrpee16plus.hpp \
    include/arch/Arrpee32.hpp \
    include/arch/Arrpee8plus.hpp \
    include/mem/SharedMemoryBuffer.hpp

SOURCES += \
    StdStream.cpp \
    main.cpp \
    src/abstract/AbstractMemoryDevice.cpp \
    src/abstract/AbstractProcessor.cpp \
    src/abstract/AbstractArchitecture.cpp \
    src/abstract/AbstractExtendedArchitecture.cpp \
    src/ArithmeticalInstructions.cpp \
    src/ControlFlowInstructions.cpp \
    src/arch/Arrpee8.cpp \
    src/arch/Arrpee16.cpp \
    src/arch/Arrpee32.cpp \
    src/arch/Arrpee16plus.cpp \
    src/arch/Arrpee8plus.cpp \
    src/mem/SharedMemoryBuffer.cpp

DISTFILES +=
