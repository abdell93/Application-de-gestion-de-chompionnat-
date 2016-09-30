#include "terrain.h"
#include "ui_terrain.h"
terrain::terrain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::terrain)
{
    ui->setupUi(this);
    QObject::connect(ui->bouton_ajouter, SIGNAL(clicked()), this, SLOT(ajouter()));
    model=comd->afficher_terrain();model->setHeaderData(0,Qt::Horizontal,tr("id"));model->setHeaderData(1,Qt::Horizontal,tr("terrain"));
    ui->tableView->setModel(model);
    QObject::connect(ui->bouton_supprimer,SIGNAL(clicked()),this,SLOT(supprimer()));
    QObject::connect(ui->bouton_chercher,SIGNAL(clicked()),this,SLOT(chercher()));

}

terrain::~terrain()
{
    delete ui;
}
  void terrain::supprimer()
  {commande *cmd=new commande;
      int row=cmd->verif_championnat();
      if(row)
      {
          ui->label_rq->setText("<font color=red>la suppression est impossible ! Le championnat a déja commencé !</font>" );
      }
      else
      {
      QString id=ui->id_supprimer->text();
      model=comd->supprimer_terrain(id);
      QSqlQueryModel *m = new QSqlQueryModel;
      m=comd->afficher_terrain();
      m->setHeaderData(0,Qt::Horizontal,tr("id"));
       m->setHeaderData(1,Qt::Horizontal,tr("terrain"));
       ui->tableView->setModel(m);
       }
  }

  void terrain::chercher()
  {
      QString chaine=ui->t_chercher->text();
       QSqlQueryModel *l = new QSqlQueryModel;
      l=comd->chercher_terrain(chaine);
     ui->tableView_2->setModel(l);
  }

  void terrain::ajouter()
  {
      QString nom_t,capacite_t;
          nom_t=ui->nom_terrain->text();
          capacite_t=ui->capacite_terrain->text();
          commande *cmd=new commande;
               bool row=cmd->verif_championnat();
               if(row)
               {
                   ui->label_5->setText("<font color=red>l'ajout est impossible ! Le championnat a déja commencé !</font>" );
               }
               else
               {
                    if(nom_t=="" or capacite_t=="" )
                        {
                            ui->label_5->setText("<font color=red>tout les champs sont obligatoires !</font>" );

                        }
                     else
                        {qDebug()<<nom_t<<endl<<capacite_t;
                            bool cmd1=cmd->ajout_terrain(nom_t,capacite_t);
                                       if(cmd1 )
                                           {
                                             ui->label_5->setText("ajout réussi " );
                                             ui->nom_terrain->clear();
                                             ui->capacite_terrain->clear();
                                            QSqlQueryModel *m = new QSqlQueryModel;
                                            m=comd->afficher_terrain();
                                            m->setHeaderData(0,Qt::Horizontal,tr("id"));
                                            m->setHeaderData(1,Qt::Horizontal,tr("terrain"));
                                            ui->tableView->setModel(m);

                                            }
                        }

  }
}
