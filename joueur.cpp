#include "joueur.h"
#include "ui_joueur.h"
#include <QSqlQuery>
#include <vector>
#include <QScrollBar>
#include <QPushButton>
#include <QLabel>
#include <QSignalMapper>
#include <QDebug>
joueur::joueur(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::joueur)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(".\\Boule.png"));
    nbr_joueur=comd->nbr_joueur();
     QObject::connect(ui->bouton_ajouter, SIGNAL(clicked()), this, SLOT(ajouter()));
     model=comd->afficher();model->setHeaderData(0,Qt::Horizontal,tr("id"));
     ui->tableView->setModel(model);
     QObject::connect(ui->bouton_supprimer,SIGNAL(clicked()),this,SLOT(supprimer()));
     QObject::connect(ui->bouton_chercher,SIGNAL(clicked()),this,SLOT(chercher()));
}

 void joueur::supprimer()
 {   commande *cmd=new commande;
     int row=cmd->verif_championnat();
     if(row)
     {
         ui->label_rq->setText("<font color=red>la suppression est impossible ! Le championnat a déja commencé !</font>" );
     }
     else
     {
        QString id=ui->id_supprimer->text();
        model=comd->supprimer(id);
        QSqlQueryModel *m = new QSqlQueryModel;
        m=comd->afficher();
        m->setHeaderData(0,Qt::Horizontal,tr("id"));
        ui->tableView->setModel(m);

     }
}


 void joueur::chercher()

 {
     QString chaine=ui->combo_chercher->currentText();
     QString chaine2=ui->j_chercher->text();
      QSqlQueryModel *l = new QSqlQueryModel;
     l=comd->rechercher(chaine,chaine2);
    ui->tableView_2->setModel(l);

 }

void joueur::ajouter()
{
QString nom_j,prenom_j,pays_j,date_j;
    nom_j=ui->b_nom->text();
    prenom_j=ui->b_prenom->text();
    pays_j=ui->b_pays->text();
    date_j=ui->b_date->text();
    commande *cmd=new commande;
    int nb_j=cmd->nbr_joueur();
    int row=cmd->verif_championnat();
    if(row)
    {
        ui->label_ajout->setText("<font color=red>l'ajout est impossible ! Le championnat a déja commencé !</font>" );
    }
    else
    {
            if(nom_j=="" or prenom_j=="" or pays_j=="")
                {
                     ui->label_ajout->setText("<font color=red>tout les champs sont obligatoires !</font>" );
                     jouer();
                }
            else {


                        if ( nb_j < 32)
                           {bool cmd1=cmd->ajout_joueur(nom_j,prenom_j,pays_j,date_j);
                            qDebug()<<nb_j<<endl;
                             if(cmd1 )
                                 {
                                   ui->label_ajout->setText("ajout réussi " );
                                   ui->b_nom->clear();
                                   ui->b_prenom->clear();
                                   ui->b_pays->clear();
                                   ui->b_date->clear();
                                   QSqlQueryModel *m = new QSqlQueryModel;
                                   m=comd->afficher();
                                   m->setHeaderData(0,Qt::Horizontal,tr("id"));
                                    ui->tableView->setModel(m);

                                 }
                             else qDebug()<<"hello"<<endl;
                           }
                        else
                                 {
                                     ui->label_ajout->setText("Ajout impossible ! la liste contient 32 joueurs");
                                 }
          }
   }
 }


joueur::~joueur()
{
    delete ui;
}




bool  verif(int x, QVector <int> h)
{
   int k=0 ;
    while(k<h.size())
    {if(x==h[k])
        return false ;
        k++;
    }
 return true ;
}


void jouer ()
{
    commande *cmd=new commande;
    int nb_j=cmd->nbr_joueur();
    if(nb_j==32)
      {
           int i,j,x,k=0;
            QVector<int> T,S,B;
            QString tab1[16],tab2[16];
            QString tab[32];
            QString str="SELECT nom_j FROM joueur ";
            QSqlQuery query1;
            if(query1.exec(str))
            {
               qDebug()<<"hello"<<endl;
                while(query1.next())
                    {
                        tab[k]=query1.value(0).toString();
                        k++;
                    }
            }
           else qDebug()<<"erreurZZZZZZZZZZZZZZ"<<endl;
           for(i=0;i<16;i++)
                {
                    while(x<0 || x>=32 || !verif(x,T))
                        x=rand();
                    T.push_back(x);
                    tab1[i]=tab[x];

                }

            for(i=0;i<16;i++)
                {
                    while(x<0 || x>=32 || !verif(x,T))
                        x=rand();
                    T.push_back(x);
                    tab2[i]=tab[x];

                }
            qDebug()<<"********* (( 1 )) **********"<<endl;
                    for(j=0;j<16;j++)
                        qDebug()<<tab1[j]<<" VS "<<tab2[j]<<endl<<endl;

                    for(i=0;i<16;i++)
                        {
                            while(x<0 || x>=32 || !verif(x,B))
                            x=rand();
                            B.push_back(x);
                            tab1[i]=tab[x];

                        }
            for(i=0;i<16;i++)
            {
                while(x<0 || x>=32 || !verif(x,B))
                x=rand();
                B.push_back(x);
                tab2[i]=tab[x];

            }
            qDebug()<<"************ DEUXI2ME TOUR ************"<<endl;
            for(j=0;j<16;j++)
            qDebug()<<tab1[j]<<" VS "<<tab2[j]<<endl<<endl;

            for(i=0;i<16;i++)
            {
                while(x<0 || x>=32 || !verif(x,S))
                x=rand();
                S.push_back(x);
                tab1[i]=tab[x];

            }
            for(i=0;i<16;i++)
            {
                while(x<0 || x>=32 || !verif(x,S))
                x=rand();
                S.push_back(x);
                tab2[i]=tab[x];

            }
            qDebug()<<"************ 3éme TOUR ************"<<endl;
            for(j=0;j<16;j++)
            qDebug()<<tab1[j]<<" VS "<<tab2[j]<<endl<<endl;
       }
    else
        qDebug()<<"Nombre de joueurs insuffisable"<<nb_j;

}
