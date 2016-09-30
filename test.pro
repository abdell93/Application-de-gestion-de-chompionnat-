#-------------------------------------------------
#
# Project created by QtCreator 2015-06-20T12:10:36
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connection.cpp \
    joueur.cpp \
    terrain.cpp \
    reservation.cpp \
    administration.cpp \
    partie.cpp \
    seconnecter.cpp \
    commande.cpp \
    exemple.cpp \
    resultat.cpp



HEADERS  += mainwindow.h \
    resultat.h \
    resultat.h \
    connection.h \
    joueur.h \
    terrain.h \
    reservation.h \
    administration.h \
    partie.h \
    seconnecter.h \
    commande.h \
    exemple.h

FORMS    += mainwindow.ui \
    resultat.ui \
    joueur.ui \
    terrain.ui \
    reservation.ui \
    administration.ui \
    partie.ui \
    seconnecter.ui
