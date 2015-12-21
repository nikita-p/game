TEMPLATE = app
CONFIG -= qt
CONFIG += console
SOURCES += \
    ships_in_space.cpp \
    main.cpp \
    economy.cpp \
    graph.cpp \
    menu.cpp \
    data.cpp \
    return-graphic.cpp

LIBS += -L/home/nikitap/SFML-2.3.2/

CONFIG (release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

CONFIG (debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += /home/nikitap/SFML-2.3.2/include
DEPENDPATH += /home/nikitap/SFML-2.3.2/include

HEADERS += \
    header.h
