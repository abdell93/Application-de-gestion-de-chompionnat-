#ifndef EXAM_H
#define EXAM_H
#include <QApplication>
#include <QtWidgets>
#include <QPushButton>
#include <QTabWidget>
#include <QGridLayout>
#include <QObject>
#include "connection.h"
#include "resultat.h"


class Partie : public QWidget // On hérite de QWidget (IMPORTANT)
{
Q_OBJECT
public:
Partie(QGridLayout *layout1,QString table1,QString tour1,int premier1,int dernier1);
QGridLayout* getLayout();
void insertion();
QString getTable();
QString getTour();
int getPremier();
int getDernier();

public slots:
     void clickedSlotA(int index);
     virtual  void remplissage_partie_eliminatoire ();
     void affichage ();

protected:
int dernier,premier;
QSignalMapper*  signalMapper;
QGridLayout *layout;
QString table,tour ;
QLineEdit *lineEdit1;
QLabel *label1 ;
QLabel *label_errerur ;
QPushButton *bouton2 ;
QPushButton *bouton_affichage;
};

class Partie_4_2_F : public Partie // On hérite de QWidget (IMPORTANT)
{
Q_OBJECT
public:
   Partie_4_2_F(QGridLayout *layout1,QString table1,QString tour1,int premier1,int dernier1);
public slots:
    void remplissage_partie_eliminatoire ();
};

class Partie_1_8 : public Partie // On hérite de QWidget (IMPORTANT)
{
Q_OBJECT
public:
    Partie_1_8(QGridLayout *layout1,QString table1,QString tour1,int premier1,int dernier1);
public slots:
    void remplissage_partie_eliminatoire ();
};



class Matches : public QWidget // On hérite de QWidget (IMPORTANT)
{
public:
Matches();
private:
QTabWidget *onglets;

Partie *eliminatoireA ;
Partie *eliminatoireB ;
Partie *eliminatoireC ;
Partie *partie8 ;
Partie *partie4 ;
Partie *partie2 ;
Partie *partieF ;

};


class Resultats : public QWidget // On hérite de QWidget (IMPORTANT)
{
public:
Resultats();
private:
QPushButton *m_bouton1;
QTabWidget *onglets;

resultat *eliminatoireA ;
resultat *eliminatoireB ;
resultat *eliminatoireC ;
resultat *partie8 ;
resultat *partie4 ;
resultat *partie2 ;
resultat *partie3 ;
resultat *partieF ;
};


class Fenetre : public QWidget // On hérite de QWidget (IMPORTANT)
{
public:
Fenetre();
private:
QTabWidget *onglets;

Matches *matches ;
Resultats *resultats;
};

#endif // EXAM_H

