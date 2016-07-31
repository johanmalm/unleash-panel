TARGET = jgpanel
QT += widgets x11extras
LIBS += -lX11 -lxcb

CONFIG += silent

HEADERS += \
	globals.h \
	server.h \
	filter.h \
	panel.h \
	splash.h \
        dock.h \
	client.h

SOURCES += \
	main.cpp \
	globals.cpp \
	server.cpp \
	filter.cpp \
	panel.cpp \
	splash.cpp \
        dock.cpp \
	client.cpp

target.path = /usr/bin
INSTALLS += target
