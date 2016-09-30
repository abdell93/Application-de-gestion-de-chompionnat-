#include "reservation.h"
#include "ui_reservation.h"

reservation::reservation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reservation)
{
    ui->setupUi(this);
     QObject::connect(ui->bouton_choisir, SIGNAL(clicked()), this, SLOT(partie_dispo()));
     QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(somme()));
     QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(reserver()));

}

void reservation::partie_dispo()
{   ui->partie->clear();
    QSqlQuery q1=cmd->tour();
    QString a1;
    int a2,a3;
    while(q1.next())
    {
       a1=q1.value(0).toString();
       a2=q1.value(1).toInt();
       a3=q1.value(2).toInt();
       if(a2==1 && a3==0)
             {
                ui->partie->setText(a1);
                QSqlQueryModel *l = new QSqlQueryModel;
                l=cmd->match_dispo(a1);
                ui->tableView->setModel(l);
                QString c,ch("select prix_ticket from avancement where tour=='"+a1+"'");
                QSqlQuery q2;
                q2.exec(ch);
                if(q2.next())
                    {   c=q2.value(0).toString();
                        ui->label_2->setText(c);
                    }
                qDebug()<<a1<<endl;
             }
    }
}
void reservation::somme()
{
    QString s,tour;
    tour =ui->partie->text();
    int somme=0,prix;
    prix =ui->label_2->text().toInt();
    somme=ui->spinBox->value()*prix;
    s=QString::number(somme);
    ui->label_5->setText(s);
}

void reservation::reserver()
{
    QString t,tour,ch,ch1,ch2;
    QSqlQuery q1,q2,q3;
    tour=ui->partie->text();
    int i,nb,x,y,z;
    nb=ui->spinBox->value();
    i=ui->spinBox_2->value();
    QString chi=QString::number(i);

    if(tour=="eliminatoireA")
            {
                ch1="SELECT terrain,nb_spectateur FROM table_eliminatoireA where rowid="+chi;
            }
    else if(tour=="eliminatoireB")
            {
                ch1="SELECT terrain,nb_spectateur FROM table_eliminatoireB where rowid="+chi;
            }
    else  if(tour=="eliminatoireC")
            {
                ch1="SELECT terrain,nb_spectateur FROM table_eliminatoireC where rowid="+chi;
            }
    else
            {
                ch1="SELECT terrain,nb_spectateur FROM table_parties where rowid="+chi;
            }
    q2.exec(ch1);
     while( q2.next())
     {
    t = q2.value(0).toString();

    y=q2.value(1).toInt();qDebug()<<y;
     }
     ch=("select capacite from terrain where nom_terrain='"+t+"'");qDebug()<<tour<<endl;
   q1.exec(ch);

   while(q1.next()  )
   {
                x=q1.value(0).toInt();qDebug()<<x;
                QString chaine;chaine=QString::number(y+nb);
                if (x >= (y+nb))
                    {   if(tour=="eliminatoireA")
                    {
                        ch2="update table_eliminatoireA set nb_spectateur='"+chaine+"' where rowid="+chi;
                    }
            else if(tour=="eliminatoireB")
                    {
                        ch2="update table_eliminatoireB set nb_spectateur='"+chaine+"' where rowid="+chi;
                    }
            else  if(tour=="eliminatoireC")
                    {
                        ch2="update table_eliminatoireC set nb_spectateur='"+chaine+"' where rowid="+chi;
                    }
            else
                    {
                        ch2="update table_parties set nb_spectateur='"+chaine+"' where rowid="+chi;
                    }
                    q3.exec(ch2);
                        ui->label_8->setText("Réservation avec succés .");
                    }

   }
}

reservation::~reservation()
{
    delete ui;
}
