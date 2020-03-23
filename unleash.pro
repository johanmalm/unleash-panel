TARGET = unleash-panel
QT += widgets x11extras
LIBS += -lX11 -lxcb
CONFIG += silent
QMAKE_CXXFLAGS += -std=c++11
INCLUDEPATH += include
DESTDIR = build
OBJECTS_DIR = build/.obj
MOC_DIR = build/.moc

HEADERS += $${INCLUDEPATH}/panel.h $${INCLUDEPATH}/filter.h

SOURCES += \
	background.cpp \
	filter.cpp \
	main.cpp \
	panel.cpp \
	settings.cpp \
	task.cpp \
	x11.cpp

