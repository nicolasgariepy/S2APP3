TEMPLATE     = vcapp
TARGET       = TestVisiTest
CONFIG      += warn_on qt debug_and_release windows console
HEADERS     += MonInterface.h
HEADERS		+= Vecteur.h
SOURCES     += TestVisiTest.cpp 
SOURCES		+= MonInterface.cpp
INCLUDEPATH += ./VisiTest
INCLUDEPATH += ./CommunicationFPGA/
LIBS		+= ./VisiTest/VisiTest.lib
LIBS		+= ./CommunicationFPGA/CommunicationFPGA.lib
QT += widgets
	