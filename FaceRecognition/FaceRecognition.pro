######################################################################
# Automatically generated by qmake (2.01a) jeu. 13. mai 11:07:53 2010
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH +="C:\Program Files\OpenCV\OpenCV210\lib" 
INCLUDEPATH +="C:\Program Files\OpenCV\OpenCV210\include\opencv"
LIBS += cv210.lib highgui210.lib cxcore210.lib cvaux210.lib
QT += sql
# Input
HEADERS +=cv.h cvaux.h highgui.h cxcore.h FaceRecognition.h Detection.h Extraction.h Recognition.h FaceDatabase.h Users.h 
SOURCES += main.cpp FaceRecognition.cpp Detection.cpp Extraction.cpp Recognition.cpp FaceDatabase.cpp Users.cpp