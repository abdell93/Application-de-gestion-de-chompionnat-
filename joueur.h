#ifndef JOUEUR_H
#define JOUEUR_H
#include <QLabel>
#include "commande.h"
#include <QVector>
#include <QWidget>
#include<QSqlQueryModel>
#include <cstdlib>


namespace Ui {
class joueur;
}

class joueur : public QWidget
{
    Q_OBJECT

public:


    explicit joueur(QWidget *parent = 0);

    ~joueur();

public slots :
    void ajouter();
    void supprimer();
    void chercher();

private:
    Ui::joueur *ui;
    QSqlQueryModel *model = new QSqlQueryModel;
    int nbr_joueur;
    commande *comd=new commande;
};
bool  verif(int x ,QVector <int> h ) ;
void jouer();


#endif // JOUEUR_H
