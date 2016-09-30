#include "resultat.h"
#include "ui_resultat.h"
#include <QSqlQueryModel>
#include <QSqlQuery>
resultat::resultat(QWidget *parent ) :
    QWidget(parent),   ui(new Ui::resultat)

{
    ui->setupUi(this);
}

resultat::~resultat()
{
    delete ui;
}
QString resultat::get_table(){
    return(table);
}

void resultat::on_pushButton_clicked()
{
    QString table_name=get_table();
    QString  db=QString ::number(get_premier()),fin=QString ::number(get_fin());
     QString str="SELECT date,joueur1,score1,joueur2,score2,terrain,gagnant,prix_ticket FROM "+table_name+" where rowid>="+db+" AND rowid<="+fin+"";
    QSqlQueryModel *model=new QSqlQueryModel();
        QSqlQuery query1;
        if(query1.exec(str))
        {
            int i;
        qDebug()<<i<<endl;
        }
        else qDebug()<<"erreur !!!!!!"<<endl;
        model->setQuery(query1);
        ui->tableView->setModel(model);


}
void resultat::set_donne(QString table1,int premier1,int dernier1){
    table=table1;
    premier=premier1;
    dernier=dernier1;
}

int resultat::get_premier(){
    return(premier);
}

int resultat::get_fin(){
    return(dernier);
}


