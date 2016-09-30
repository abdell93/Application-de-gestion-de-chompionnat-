#include "commande.h"

commande::commande()
{

}

QSqlQuery  commande::tour()
 {
    QSqlQuery query1( "SELECT tour,commencer,terminer from avancement");
       query1.exec();
       return query1;
 }


int commande::nbr_joueur()
{    int x;
    QSqlQuery query1( "SELECT COUNT(*) from joueur");
       query1.exec();
       if(query1.next())
       {       x=query1.value(0).toInt();
               return x;
       }
}

QSqlQueryModel * commande::supprimer(QString id)
{
    QSqlQueryModel *model = new QSqlQueryModel; //bool
    model->setQuery("delete from joueur where id_j="+id+"");
    return model;
}

QSqlQueryModel * commande::rechercher(QString rech, QString re)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    if(rech=="Nom")
    model->setQuery("SELECT id_j,nom_j,prenom_j,pays,d_naissance FROM joueur where nom_j='"+re+"'");
    else if(rech=="Prénom")
    model->setQuery("SELECT id_j,nom_j,prenom_j,pays,d_naissance FROM joueur where prenom_j='"+re+"'");
    else
    model->setQuery("SELECT id_j,nom_j,prenom_j,pays,d_naissance FROM joueur where pays='"+re+"'");
    return model;
}

QSqlQueryModel * commande::match_dispo(QString a1)
{
    QSqlQueryModel *model = new QSqlQueryModel;QString ch("faux");
    if(a1=="eliminatoireA")
            {
                model->setQuery("SELECT rowid,joueur1,joueur2,date,terrain FROM table_eliminatoireA where jouer =='"+ch+"'");
            }
    else if(a1=="eliminatoireB")
            {
                model->setQuery("SELECT rowid,joueur1,joueur2,date,terrain FROM table_eliminatoireB where jouer =='"+ch+"'");
            }
    else  if(a1=="eliminatoireC")
            {
                model->setQuery("SELECT rowid,joueur1,joueur2,date,terrain FROM table_eliminatoireC where jouer =='"+ch+"'");
            }
    else if(a1=="partie_1_8")
            {
                model->setQuery("SELECT rowid,joueur1,joueur2,date,terrain FROM table_parties where jouer =='"+ch+"' and rowid > 0 and rowid < 9 ");
            }
    else if(a1=="partie_1_4")
            {
                model->setQuery("SELECT id,joueur1,joueur2,date,terrain FROM table_parties where jouer =='"+ch+"' and rowid > 8 and rowid < 13 ");
            }
    else if(a1=="partie_1_2")
            {
                model->setQuery("SELECT id,joueur1,joueur2,date,terrain FROM table_parties where jouer =='"+ch+"' and rowid > 12 and rowid < 15 ");
            }
    else
            {
                model->setQuery("SELECT id,joueur1,joueur2,date,terrain FROM table_parties where jouer =='"+ch+"' and rowid==15 ");
            }

    return model;
}

QSqlQueryModel * commande::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT id_j,nom_j,prenom_j,pays,d_naissance FROM joueur");

    return model;
}

QSqlQueryModel * commande::afficher_terrain()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT id_terrain,nom_terrain,capacite FROM terrain");

    return model;
}

QSqlQueryModel * commande::supprimer_terrain(QString id)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("delete from terrain where id_terrain="+id+"");

    return model;
}

QSqlQueryModel * commande::chercher_terrain(QString chaine)
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT id_terrain,nom_terrain,capacité FROM terrain where nom_terrain='"+chaine+"'");
    return model;
}

bool commande::ajout_terrain(QString nom_t, QString capacite_t)
{
    QSqlQuery qrt;
    QString srt="INSERT INTO terrain (nom_terrain,capacite) VALUES('"+nom_t+"','"+capacite_t+"')";
      bool result=qrt.exec(srt);
               return result;
}
bool commande::ajout_joueur(QString nom, QString prenom, QString pays, QString date)
{
    QSqlQuery qrt;
    QString srt="INSERT INTO joueur (nom_j,prenom_j,pays,d_naissance) VALUES('"+nom+"','"+prenom+"','"+pays+"','"+date+"')";
      bool result=qrt.exec(srt);
               return result;
}

bool commande::verif_championnat()
{
    QSqlQuery qrt;
    int x;
    QString ch="eliminatoireA";
    QString srt="select commencer from avancement where tour='"+ch+"'";
    qrt.exec(srt);
    while(qrt.next())
        {
            x=qrt.value(0).toInt();
        }
    if(x)
        return true ;
    else
        return false;
}
