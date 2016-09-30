#ifndef COMMANDE_H
#define COMMANDE_H
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>

class commande
{
public:
    commande();
     int nbr_joueur();
     bool ajout_joueur(QString nom,QString prenom,QString pays,QString date);
     QSqlQuery  tour();

     QSqlQueryModel * supprimer(QString id);
     QSqlQueryModel * afficher();
     QSqlQueryModel * rechercher(QString rech,QString re);
     bool ajout_terrain(QString nom_t,QString capacite_t);
     bool verif_championnat();
     QSqlQueryModel * afficher_terrain();
     QSqlQueryModel * match_dispo(QString a1);
     QSqlQueryModel * supprimer_terrain(QString id);
     QSqlQueryModel * chercher_terrain(QString chaine);
     QSqlQueryModel * match_non_jouer(QString tour);


};

#endif // COMMANDE_H
