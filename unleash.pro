TARGET = unleash-panel
QT += widgets x11extras
LIBS += -lX11 -lxcb
CONFIG += silent
INCLUDEPATH += include
DESTDIR = build
OBJECTS_DIR = build/.obj
MOC_DIR = build/.moc

HEADERS += $${INCLUDEPATH}/panel.h $${INCLUDEPATH}/filter.h

SOURCES += \
	main.cpp \
	globals.cpp \
	filter.cpp \
	panel.cpp \
	background.cpp \
	task.cpp \
	x11.cpp

