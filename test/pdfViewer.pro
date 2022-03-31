QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pdfViewer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

win32 {
        LIB_EXT = a
        win32-msvc*:LIB_EXT = lib

        CONFIG(debug, debug|release) {
		DESTDIR = Debug
		MOC_DIR = Debug
		OBJECTS_DIR = Debug
		UI_DIR = Debug
		RCC_DIR = Debug
		UI_HEADER_DIR = Debug
		UI_SOURCES_DIR = Debug

		CONFIG += debug
         }

	CONFIG(release, debug|release){
		DESTDIR = Release
		MOC_DIR = Release
		OBJECTS_DIR = Release
		UI_DIR = Release
		RCC_DIR = Release
		UI_HEADER_DIR = Release
		UI_SOURCES_DIR = Release
	
		DEFINES += QT_NO_DEBUG 

		CONFIG += release
        }

        DEFINES -= UNICODE

	INCLUDEPATH += ../include/poppler-qt5
        LIBS += -L../lib_static -L../lib -lpoppler -lfreetype
}

else:unix {
	DESTDIR = bin

	MOC_DIR = tmp
	OBJECTS_DIR = tmp
	UI_DIR = tmp
	RCC_DIR = tmp
	UI_HEADER_DIR = tmp
	UI_SOURCES_DIR = tmp

	INCLUDEPATH += /usr/include/poppler/qt5
}

LIBS += -lpoppler-qt5


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui
