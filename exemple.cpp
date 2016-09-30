#include <QWidget>
#include <QtWidgets>
#include <QSignalMapper>
#include "connection.h"
#include "exemple.h"
#include <QMap>
#include <QVector>
#include<QTableView>
#include <cstdlib> //pour rand()
#include <ctime> //pour time()
#include <QSqlQuery>
#include<QString>


bool  verif1(int x, QVector <int> h)
{
   int k=0 ;
    while(k<h.size())
    {if(x==h[k])
        return false ;
        k++;
    }
 return true ;
}
QString Partie::getTour(){
    return (tour);
}
QString Partie::getTable(){
    return (table);
}

int Partie::getPremier(){
    return (premier);
}

QGridLayout* Partie::getLayout(){
    return (layout);
}

int Partie::getDernier(){
    return (dernier);
}

//--------------------------------((Declaration des parties))----------------------------------------------//

Partie::Partie(QGridLayout *layout1,QString table1,QString tour1,int premier1=1,int dernier1=16): layout(layout1),table(table1),tour(tour1),premier(premier1),dernier(dernier1){


    //------------------------------->>>>>>>>>>>>  Insertion de prix
    this->setStyleSheet("QLineEdit { background-color: rgb(255,255,80);border-width: 2px;border-radius: 10px; }");

    lineEdit1 = new QLineEdit("Prix ticket en Dt",this);
    lineEdit1->setStyleSheet("QLineEdit {border-style: outset;border-width: 2px;border-radius: 10px;border-color: beige;font: bold 14px;min-width: 10em;padding: 6px;height:30px;}");

    label_errerur = new QLabel("",this);
    bouton2 = new QPushButton("Commencer partie",this);
    bouton2->setStyleSheet("QPushButton {background-color: green;border-style: outset;border-width: 2px;border-radius: 10px;border-color: beige;font: bold 14px;max-width: 10em;padding: 6px;height:30px;}");
    bouton2->setIcon(QIcon("start.png"));

    bouton2->setFont(QFont("Comic Sans MS", 16));
    bouton2->setCursor(Qt::PointingHandCursor);
    // m_bouton->setIcon(QIcon("smile.png"));

    layout->setHorizontalSpacing(10);
    bouton_affichage = new QPushButton("Afficher",this);
    bouton_affichage->setStyleSheet("QPushButton {background-color: green;border-style: outset;border-width: 2px;border-radius: 10px;border-color: beige;font: bold 14px;min-width: 10em;padding: 6px;height:30px;}");
    bouton_affichage->setCursor(Qt::PointingHandCursor);

        layout->addWidget(lineEdit1, 0, 1);
        layout->addWidget(bouton2, 0, 2);
        layout->addWidget(bouton_affichage, 0, 3);
        layout->addWidget(label_errerur,0,5);

        setLayout(layout);
        QObject::connect(bouton2,SIGNAL(clicked()),this,SLOT(remplissage_partie_eliminatoire()));
        QObject::connect(bouton_affichage,SIGNAL(clicked()),this,SLOT(affichage()));
    }

//--------------------------------------((Remplissage des matches))----------------------------------------------//


bool ajout_terminer(QString nom_partie){

    QSqlQuery cmd2;
    if(nom_partie=="table_eliminatoireA"){
        QString str4 = "SELECT COUNT(*) from joueur ";
        bool result2=cmd2.exec(str4);
        int row=0,com=1;

                if (result2 && cmd2.next())
                    {
                            row= cmd2.value(0).toInt();
                    }
                else  qDebug()<<"Erreur count !!!!"<<endl;
                return(row==32);
    }
    else return(true);
}

bool partie_commencer(QString nom_tour){

    QSqlQuery query;
    int nb_commencer=0;

        QString str = "SELECT commencer from avancement where tour='"+nom_tour+"'";
        if(query.exec(str))
        {
            qDebug()<<"hello"<<endl;
        while(query.next() )
              {
                  nb_commencer=query.value(0).toInt();

              }
        }
        else qDebug()<<"erreur !!!!!! 111"<<endl;
        qDebug ()<<"nb_commebcer="<<nb_commencer<<endl;
        return(nb_commencer==1);

}

bool partie_precedent_ne_pas_terminer(QString nom_table,QString nom_tour){

    QString partie_prec="";
    QSqlQuery query;
    int nb_terminer=0;

        if(nom_tour=="eliminatoireA")
            return(false);
        else if(nom_tour=="eliminatoireB"){
           partie_prec="eliminatoireA";
        }
        else if(nom_tour=="eliminatoireC"){
            partie_prec="eliminatoireB";
        }
        else if(nom_tour=="partie_1_8"){
            partie_prec="eliminatoireC";
        }
        else if(nom_tour=="partie_1_4"){
            partie_prec="partie_1_8";
        }
        else if(nom_tour=="partie_1_2"){
            partie_prec="partie_1_4";
        }
        else if(nom_tour=="finale"){
            partie_prec="partie_1_2";
        }


        QString str = "SELECT terminer from avancement where tour='"+partie_prec+"'";
        if(query.exec(str))
        {
        while(query.next() )
              {
                  nb_terminer=query.value(0).toInt();
              }
        }
        else qDebug()<<"erreur !!!!!! 140"<<endl;
        qDebug() <<"nb_terminer="<<nb_terminer<<endl;
        return(nb_terminer==0);
}
void remplissage_tab_avancement(QString nom_table,QString nom_tour,int debut,int fin){
    QString prim=QString::number(debut);
    QString der=QString::number(fin);
    //QString str = "SELECT length(gagnant)>0 from "+nom_table+" WHERE rowid>="+prim+" AND rowid<="+der+"";
    QString str = "SELECT gagnant from "+nom_table+" WHERE rowid>="+prim+" AND rowid<="+der+"";
    QSqlQuery query;
    int i=0;
    bool test=true ;
    QString qq;
    if(query.exec(str))
           {
           while(query.next() && test)
                 {
                     qq=query.value(0).toString();
                     if(qq==NULL)
                         test=false;
                 }
           }
    QString str1 = "UPDATE avancement SET terminer='1' WHERE tour='"+nom_tour+"'";
    QSqlQuery query1;
    if(test)
    {
        if(query1.exec(str1))
        {
        while(query1.next() )
              {
                  qDebug()<<"tour terminer"<<endl;
              }
         }
    }
   /*     if(query.exec(str))
        {
        while(query.next() )
              {
                  i+=query.value(0).toInt();
              }
        }
        else qDebug()<<"erreur !!!!!! 174"<<endl;
         qDebug()<<"nbre gagnant ="<<i<<endl;
int nbre = fin - debut;
        if(i==nbre){
//tour terminer
            QString str1 = "UPDATE avancement SET terminer='1' WHERE tour='"+nom_tour+"'";
            QSqlQuery query1;
                if(query1.exec(str1))
                {
                while(query1.next() )
                      {
                          qDebug()<<"tour terminer"<<endl;
                      }
                }
                else qDebug()<<"erreur !!!!!! 170"<<endl;
            }
*/
}




Partie_4_2_F::Partie_4_2_F(QGridLayout *layout1,QString table1,QString tour1,int premier1=0,int dernier1=8):Partie(layout1,table1,tour1,premier1,dernier1){}

void Partie_4_2_F::remplissage_partie_eliminatoire (){

   QString tab1[4],tab2[4],tab[8];
   int k1=0;
   int dif =getDernier()-getPremier()+1;
   int int_prim=getPremier()-dif*2;
   int int_fin=getDernier()-dif;
   QString nom_table="table_parties";
    QString nom_tour=getTour();
   QString prim=QString::number(int_prim);
    QString fin=QString::number(int_fin);
   QString strA="SELECT gagnant FROM table_parties WHERE rowid>="+prim+" AND rowid<="+fin+" ";
   QSqlQuery queryA,cmd2;
   QString str4 = "SELECT COUNT(*) from "+nom_table+" ";

       bool result2=cmd2.exec(str4);
                   int row=0;
                   if (result2 && cmd2.next())
                       {
                               row= cmd2.value(0).toInt();
                       }
                   else  qDebug()<<"Erreur count !!!!"<<endl;

                   if(partie_commencer(nom_tour)){
                       //affiche partie est deja commencer
                       QMessageBox::critical(this, "", "<font color=red><h2>La partie est déja commencée </h2></font>");
                   }
                   else if(partie_precedent_ne_pas_terminer(nom_table,nom_tour)){
                       //affiche la partie pr�cedent n'est pas encore terminer
                       QMessageBox::critical(this, "", "<font color=red><h2>La partie pr�cedent n'est encore termin�e </h2></font>");
                   }
                   else{

       if(queryA.exec(strA))
       {
           qDebug()<<"hello"<<endl;
       while(queryA.next()&& k1<int_fin )
             {
                 tab[k1]=queryA.value(0).toString();
                 k1++;
             }
       }
       else qDebug()<<"erreur !!!!!!"<<endl;


     QString prix="";
       for(int i=0;i<dif;i++)
       {
       QString joueur11=tab[i];
       QString joueur22=tab[i+dif];
      prix=lineEdit1->text();
       qDebug()<<joueur11<<"Vs"<<joueur22<<endl;

       //-----------------------((Insertion de contenu de tab1 et tab2 dans la table match))-----------------------//
       QString  ch("faux"),str3 = "INSERT INTO "+nom_table+" (joueur1,joueur2,jouer,prix_ticket) VALUES('"+joueur11+"','"+joueur22+"','"+ch+"','"+prix+"')";
       QSqlQuery query3;
           if(query3.exec(str3))
               qDebug()<<"insertion 1/4"<<endl;
           else {
               qDebug()<<"erreur 262 !!!!!!"<<endl;
               QMessageBox::critical(this, "", "<font color=red><h2>erreur</h2></font>");
               }
        }
       //-----------------------((Insertion de prix et de valeur 1 dans la table avancement))-----------------------//
           QString str5 = "UPDATE avancement SET commencer='1',prix_ticket='"+prix+"' WHERE tour='"+getTour()+"'";
           QSqlQuery query5;
           if(query5.exec(str5))
           {
               qDebug()<<"Nom de tour =="<<getTour()<<endl;

           qDebug()<<"insertion table commencer..."<<endl;
           }
           else {
            qDebug()<<"erreur !!!!!! 273"<<endl;
            label_errerur->setText("<font color=red><h2>Erreur </h2></font>" );}
       QMessageBox::information(this, "", "<font color=green><h2>La partie est commenc�e avec succ�e...</h2></font>");


    }
}



Partie_1_8::Partie_1_8(QGridLayout *layout1,QString table1,QString tour1,int premier1=0,int dernier1=8):Partie(layout1,table1,tour1,premier1,dernier1){}

void Partie_1_8::remplissage_partie_eliminatoire (){

    QMap<QString, int> occurrences;
       QString ch;
      QString tab1[8],tab2[8],tab[16],tab3[16];
      int k1=0,k2=0,k3=0;
   QString nom_table=getTable();

      QString strA="SELECT gagnant FROM table_eliminatoireA";
      QString strB="SELECT gagnant FROM table_eliminatoireB";
      QString strC="SELECT gagnant FROM table_eliminatoireC";
      QSqlQuery queryA,queryB,queryC,cmd2;
      QString str4 = "SELECT COUNT(*) from "+nom_table+"";
      bool result2=cmd2.exec(str4);
                  int row=0;
                  if (result2 && cmd2.next())
                      {
                              row= cmd2.value(0).toInt();
                      }

                  if(partie_commencer(getTour())){
                      //affiche partie est deja commencer
                      QMessageBox::critical(this, "", "<font color=red><h2>La partie est d�ja commence� </h2></font>");
                  }
                  else if(partie_precedent_ne_pas_terminer(nom_table,getTour())){
                      //affiche la partie pr�cedent n'est pas encore terminer
                      QMessageBox::critical(this, "", "<font color=red><h2>La partie pr�cedent n'est encore termin�e </h2></font>");
                  }
                  else{

      if(queryA.exec(strA))
      {
          qDebug()<<"hello"<<endl;
      while(queryA.next()&& k1<16 )
            {
                ch=queryA.value(0).toString();
                ++occurrences[ch];
                k1++;
            }
      }
      else qDebug()<<"erreur !!!!!!"<<endl;

      if(queryB.exec(strB))
      {
          qDebug()<<"hello"<<endl;
      while(queryB.next()&& k2<16 )
            {
                ch=queryB.value(0).toString();
               ++occurrences[ch];
                k2++;
            }
      }
      else qDebug()<<"erreur !!!!!!"<<endl;
      if(queryC.exec(strC))
      {
          qDebug()<<"hello"<<endl;
      while(queryC.next()&& k3<16 )
            {
                ch=queryC.value(0).toString();
               ++occurrences[ch];
                k3++;
            }
      }
      else qDebug()<<"erreur !!!!!!"<<endl;

          //   remplissage de aleatoire de tab1 et tab2

   QMap<QString, int>::const_iterator i = occurrences.constBegin();
   int k=0;
   while (i != occurrences.constEnd()) {

       if(i.value()==3 ||i.value()==2 )
         {
               tab[k]=i.key();
               k++;
                qDebug ()<<"-----------"<<i.value()<<i.key();
         }
        qDebug ()<<i.key()<<i.value();
        ++i;
   }
    qDebug ()<<k;

    if(k!=16)
        {
            QMap<QString, int>::const_iterator j = occurrences.constBegin();

            while (j != occurrences.constEnd()&& k<16) {

                if(j.value()==1 )
                  {
                        tab[k]=j.key();
                        k++;
                  }
                j++;
            }

        }


 QString prix="";
    for(int i=0;i<8;i++)
    {
    QString joueur11=tab[i];
    QString joueur22=tab[i+8];
    prix=lineEdit1->text();
    qDebug()<<joueur11<<"Vs"<<joueur22<<prix<<endl;

    //-----------------------((Insertion de contenu de tab1 et tab2 dans la table match))-----------------------//
    QString str3 = "INSERT INTO table_parties (joueur1,joueur2,jouer) VALUES('"+joueur11+"','"+joueur22+"','faux')";


    QSqlQuery query3;
    if(query3.exec(str3))
     qDebug()<<"insertion table 1/8..."<<endl;
    else {
        qDebug()<<"erreur 467 !!!!!!"<<endl;
    }
        }
    //-----------------------((Insertion de prix et de valeur 1 dans la table avancement))-----------------------//
        QString str5 = "UPDATE avancement SET commencer='1',prix_ticket='"+prix+"' WHERE tour='"+getTour()+"'";
        QSqlQuery query5;
        if(query5.exec(str5))
        {
        qDebug()<<"insertion table commencer..."<<endl;
        }
        else {
         qDebug()<<"erreur !!!!!! 478"<<endl;
         label_errerur->setText("<font color=red><h2>Erreur </h2></font>" );}
    QMessageBox::information(this, "", "<font color=green><h2>La partie est commenc�e avec succ�e...</h2></font>");

                  }
}



void Partie::remplissage_partie_eliminatoire (){

 srand(time(0));

  QString tab1[16],tab2[16],tab[32];
  int k1=0;
  QString nom_table=this->getTable();
  QString str="SELECT nom_j FROM joueur";
  QSqlQuery query1,query2,query3,cmd2;

  QString str4 = "SELECT COUNT(*) from "+nom_table+"";
  bool result2=cmd2.exec(str4);
  int row=0;


          if (result2 && cmd2.next())
              {
                      row= cmd2.value(0).toInt();
              }
          else  qDebug()<<"Erreur count !!!!"<<endl;


          if(!ajout_terminer(nom_table)){
              //affiche terminer dabord l'ajout des joueurs
              QMessageBox::critical(this, "", "<font color=red><h2>Terminer dabord l'ajout des joueurs </h2></font>");
          }
      else if(partie_commencer(getTour())){
          //affiche partie est deja commencer
          QMessageBox::critical(this, "", "<font color=red><h2>La partie est d�ja commence� </h2></font>");
      }
      else if(partie_precedent_ne_pas_terminer(nom_table,getTour())){
          //affiche la partie pr�cedent n'est pas encore terminer
          QMessageBox::critical(this, "", "<font color=red><h2>La partie pr�cedent n'est encore termin�e </h2></font>");
      }
      else{
    //  commencer la partie
    QString prix=lineEdit1->text();
          if(query1.exec(str))
          {
              qDebug()<<"hello"<<endl;
          while(query1.next()&& k1<32 )
                {
                    tab[k1]=query1.value(0).toString();
                    k1++;
                }
          }
          else qDebug()<<"erreur !!!!!!"<<endl;

     //   remplissage de aleatoire de tab1 et tab2
           int x=0;
          QVector<int> T;
          for(int i=0;i<16;i++)
          {
              while(!verif1(x,T))
              x=rand()% 32;
              T.push_back(x);
              tab1[i]=tab[x];
          }

          for(int i=0;i<16;i++)
          {
              while(!verif1(x,T))
              x=rand()% 32;
              T.push_back(x);
              tab2[i]=tab[x];
          }
       QString joueur11="";
       QString joueur22="";
         for(int i=0;i<16;i++)
         {
         QString joueur11=tab1[i];
         QString joueur22=tab2[i];
         qDebug()<<joueur11<<"Vs"<<joueur22<<endl;

     //-----------------------((Insertion de contenu de tab1 et tab2 dans les tables eliminatoire))-----------------------//
         QString str3 = "INSERT INTO "+nom_table+" (joueur1,joueur2,jouer) VALUES('"+joueur11+"','"+joueur22+"','faux')";
         QSqlQuery query3;
         if(query3.exec(str3))
         {
         qDebug()<<"insertion..."<<endl;

         }
         else {qDebug()<<"erreur !!!!!!"<<endl;
          label_errerur->setText("<font color=red><h2>Erreur !!!!</h2></font>" );}
         }
         //-----------------------((Insertion de prix et de valeur 1 dans la table avancement))-----------------------//
             QString str5 = "UPDATE avancement SET commencer='1',prix_ticket='"+prix+"' WHERE tour='"+getTour()+"'";
             QSqlQuery query5;
             if(query5.exec(str5))
             {

             qDebug()<<"insertion table commencer..."<<endl;
             }
             else {
              qDebug()<<"erreur !!!!!! 491"<<endl;
              label_errerur->setText("<font color=red><h2>Erreur </h2></font>" );}

             QMessageBox::information(this, "", "<font color=green><h2>La partie est commencée avec succée...</h2></font>");
                 }

}


//------------------------------->>>>>>>>>>>>  Affichage des matches
void Partie::affichage(){

    layout=this->getLayout();
    QString tab1[16],tab2[16];
    int k1=0;
    QString nom_table=getTable();
    QString prim=QString::number(getPremier());
    QString fin=QString::number(getDernier());
    QString strA="SELECT gagnant FROM table_parties WHERE rowid>="+prim+" AND rowid<="+fin+" ";

    QString str="SELECT joueur1,joueur2 FROM "+nom_table+" WHERE rowid>="+prim+" AND rowid<="+fin+"";
    qDebug()<<"-------------------------------------"<<str<<endl;

    QSqlQuery query1,cmd2;
    QString str2 = "SELECT COUNT(*) from "+nom_table+"";
    int dif =getDernier()-getPremier()+1;
    QString tour= getTour();
    bool result2=cmd2.exec(str2);
                int row=0;
                if (result2 && cmd2.next())
                    {
                            row= cmd2.value(0).toInt();
                    }

                 qDebug()<<"nbre ="<<dif<<endl;
     if(partie_commencer(getTour())){
//partie commencer

    if(query1.exec(str))
    {
        qDebug()<<"hello"<<endl;
    while(query1.next()&& k1<dif )
          {
              tab1[k1]=query1.value(0).toString();   qDebug()<<tab1[k1]<<endl;
              tab2[k1]=query1.value(1).toString();  qDebug()<<tab1[k1]<<endl;
              k1++;
          }
    }
    else qDebug()<<"erreur !!!!!!"<<endl;

    for (int i=0;i<dif;i++){
            QString joueur11=tab1[i];
            QString joueur22=tab2[i];
            qDebug()<<joueur11<<endl;
            qDebug()<<"Vs"<<endl;qDebug()<<joueur22<<endl;
            QString ch1 = QString::number(i+1);
            QLabel *num= new QLabel("<font color=green><h1>"+ch1+"</h1></font>",this);
            QDateTimeEdit *date= new QDateTimeEdit(QDate::currentDate());
            date->setStyleSheet("QDateTimeEdit{ background-color: rgb(255,255,80);border-width: 5px; }");

            QLineEdit *score_joueur1 = new QLineEdit("");
            score_joueur1->setMaximumSize(200,50);
            QCheckBox *joueur1=new QCheckBox(joueur11);
            joueur1->setStyleSheet("QCheckBox {background-color:rgb(219,240,224); ;border-style: outset;border-width: 2px;border-radius: 10px;border-color: beige;font: bold 14px;min-width: 10em;padding: 6px;}");

            QLabel *Vs= new QLabel("<font color=green><h2>              Vs          </h2></font>",this);
            QCheckBox *joueur2=new QCheckBox(joueur22);
            joueur2->setStyleSheet("QCheckBox {background-color:rgb(219,240,224); ;border-style: outset;border-width: 2px;border-radius: 10px;border-color: beige;font: bold 14px;min-width: 10em;padding: 6px;}");

            QLineEdit *score_joueur2 = new QLineEdit("");
            score_joueur2->setMaximumSize(200,50);
            //affcihe list de terrain
            QString nom_terrain,str3="SELECT nom_terrain FROM terrain ";
            QSqlQuery query3;
             QComboBox *terrain = new QComboBox(this);
            if(query3.exec(str3))
            {
                qDebug()<<"hello"<<endl;
            while(query3.next() )
                  {
                      nom_terrain=query3.value(0).toString();
                      qDebug()<<"terrain::"<<nom_terrain<<endl;
                       terrain ->addItem(nom_terrain);

                  }
            }
            else qDebug()<<"erreur !!!!!!"<<endl;

            QPushButton *enregistrer=new QPushButton("Enregistrer");

            enregistrer->setStyleSheet("QPushButton {background-color: #3498db;border-style: outset;border-width: 2px;border-radius: 10px;border-color: beige;font: bold 14px;color:white;min-width: 5em;padding: 3px;}");
            enregistrer->setCursor(Qt::PointingHandCursor);

            layout->addWidget(num,i+1,0);
            layout->addWidget(date,i+1,1);
            layout->addWidget(score_joueur1,i+1,2);
            layout->addWidget(joueur1,i+1,3);
            layout->addWidget(Vs,i+1, 4);
            layout->addWidget(joueur2,i+1, 5);
            layout->addWidget(score_joueur2,i+1, 6);
            layout->addWidget(terrain,i+1, 7);
            layout->addWidget(enregistrer, i+1, 8);
    }
   setLayout(layout);
                        }
     else {
//partie non commencer
         QMessageBox::critical(this, "", "<font color=red><h2>Commencer d'abord la partie </h2></font>");
     }
 this->insertion();
}

//----------((Insertion des donn�es du matche))-----------//
void Partie::insertion(){

    qDebug() << "proc insertion "<<endl;
          layout=this->getLayout();




    qDebug() << "Layout count before clearing it: " << layout->count();

          int count = layout->count();
          int colums = layout->columnCount();
          int rows = layout->rowCount();
    qDebug()<<colums;
    qDebug ()<<rows;
    qDebug()<<count;


    for(int j=1; j<rows; j++)
        {
        signalMapper = new QSignalMapper(this);
        QWidget* item_button = layout->itemAtPosition(j,8)->widget();
        QPushButton* button = qobject_cast<QPushButton*>( item_button );
        connect(button, SIGNAL(clicked()), signalMapper, SLOT(map()));
        if ( button )
            {
            signalMapper->setMapping(button,j);
            connect(signalMapper, SIGNAL(mapped(int)),this, SLOT(clickedSlotA(int)));

            }

        }
}

void Partie::clickedSlotA(int index)
{
  layout=this->getLayout();
    QWidget* item_linEdit1 = layout->itemAtPosition(index, 2)->widget();
    QLineEdit* score1 = qobject_cast<QLineEdit*>( item_linEdit1 );
    QString sscr1=score1->text();

    QWidget* item_linEdit2 = layout->itemAtPosition(index, 6)->widget();
    QLineEdit* score2 = qobject_cast<QLineEdit*>( item_linEdit2 );
    QString sscr2=score2->text();

    QWidget* item_chek_box1 = layout->itemAtPosition(index,3)->widget();
    QCheckBox* chek_box1 = qobject_cast<QCheckBox*>( item_chek_box1 );
    QString nom_joueur1=chek_box1->text();

    QWidget* item_chek_box2 = layout->itemAtPosition(index,5)->widget();
    QCheckBox* chek_box2 = qobject_cast<QCheckBox*>( item_chek_box2 );
    QString nom_joueur2=chek_box2->text();

    QWidget* item_date_time = layout->itemAtPosition(index,1)->widget();
    QDateTimeEdit* date_time = qobject_cast<QDateTimeEdit*>( item_date_time );
    QString datime=date_time->text();

    QWidget* item_terrain = layout->itemAtPosition(index,7)->widget();
    QComboBox* terrain = qobject_cast<QComboBox*>( item_terrain );
    QString ter=terrain->currentText();

    QString jr_gagnant="",test="vrai";

if(chek_box1->isChecked())
  jr_gagnant=chek_box1->text();
else if (chek_box2->isChecked())
  jr_gagnant=chek_box2->text();
else test="faux";
   QString nom_table=getTable();

    qDebug()<<getPremier()<<"        "<<getDernier()<<endl;
   QString str=" UPDATE "+nom_table+" SET date='"+datime+"',terrain='"+ter+"',gagnant='"+jr_gagnant+"',score1='"+sscr1+"',score2='"+sscr2+"',jouer='"+test+"' WHERE (joueur1='"+nom_joueur1+"' AND  joueur2='"+nom_joueur2+"')or(joueur1='"+nom_joueur2+"' AND  joueur2='"+nom_joueur1+"')";
   QSqlQuery query1;
   if(query1.exec(str))
    {
       label_errerur->setText("<font color=red><h2>insertion...</h2></font>" );
    }
   else
   {
       qDebug()<<"erreur !!!!!!"<<endl;
      label_errerur->setText("<font color=red><h2>Erreur !!!</h2></font>" );
   }
   if(jr_gagnant !=""){

      remplissage_tab_avancement(nom_table,getTour(),getPremier(),getDernier());
   }

}

Fenetre::Fenetre() : QWidget()
{
    // 1 : Cr�er le QTabWidget
    onglets = new QTabWidget(this);
    onglets->setGeometry(20,10,1230,650);
    // 2 : Cr�er les pages, en utilisant un widget parent pour contenir chacune des pages
    matches = new Matches;
    resultats = new Resultats;
    onglets->addTab(matches , "Matches");
    onglets->addTab(resultats , "Resultats ");
}

Resultats::Resultats() : QWidget()
{
    // 1 : Cr�er le QTabWidget
    onglets = new QTabWidget(this);
    setStyleSheet(" QTabBar::tab {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);border: 2px solid #C4C4C3;border-bottom-color: #C2C7CB;border-top-left-radius: 4px;border-top-right-radius: 4px;min-width: 8ex;padding: 2px;}");
   onglets->setStyleSheet(" QTabBar::tab:selected, QTabBar::tab:hover {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #fafafa, stop: 0.4 #f4f4f4,stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);}");
   onglets->setGeometry(20,10,1200,670);
    // 2 : Cr�er les pages, en utilisant un widget parent pour contenir chacune des pages
    eliminatoireA  = new resultat;
    eliminatoireA->set_donne("table_eliminatoireA ");
    eliminatoireB  = new resultat;
    eliminatoireB->set_donne("table_eliminatoireB");
    eliminatoireC  = new resultat;
    eliminatoireC->set_donne("table_eliminatoireC");
    partie8  = new resultat;
    partie8->set_donne("table_parties",1,8);
    partie4  = new resultat;
    partie4->set_donne("table_parties",9,12);
    partie2  = new resultat;
    partie2->set_donne("table_parties",13,14);
    partieF  = new resultat;
    partieF->set_donne("table_parties",15,15);

    // 4 : ajouter les onglets au QTabWidget, en indiquant la page qu'ils contiennent
    onglets->addTab(eliminatoireA , "Eliminatoire_A ");
    onglets->addTab(eliminatoireB , "Eliminatoire_B ");
    onglets->addTab(eliminatoireC , "Eliminatoire_C ");
    onglets->addTab(partie8  , "Partie_1_8");
    onglets->addTab(partie4  , "Partie_1_4");
    onglets->addTab(partie2  , "Partie_1_2");
    onglets->addTab(partieF  , "Partie_finale");
}

Matches::Matches() : QWidget()
{
// 1 : Cr�er le QTabWidget
onglets = new QTabWidget(this);
setStyleSheet(" QTabBar::tab {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);border: 2px solid #C4C4C3;border-bottom-color: #C2C7CB;border-top-left-radius: 4px;border-top-right-radius: 4px;min-width: 8ex;padding: 2px;}");
onglets->setStyleSheet(" QTabBar::tab:selected, QTabBar::tab:hover {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #fafafa, stop: 0.4 #f4f4f4,stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);}");
onglets->setGeometry(20,10,1200,610);
// 2 : Cr�er les pages, en utilisant un widget parent pour contenir chacune des pages
QGridLayout *layoutA = new QGridLayout;
QGridLayout *layoutB = new QGridLayout;
QGridLayout *layoutC = new QGridLayout;
QGridLayout *layout8 = new QGridLayout;
QGridLayout *layout4 = new QGridLayout;
QGridLayout *layout2 = new QGridLayout;
QGridLayout *layoutF = new QGridLayout;

    eliminatoireA  = new Partie(layoutA,"table_eliminatoireA","eliminatoireA",1,16);
    eliminatoireB  = new Partie(layoutB,"table_eliminatoireB","eliminatoireB",1,16);
    eliminatoireC  = new Partie(layoutC,"table_eliminatoireC","eliminatoireC",1,16);
    partie8  = new Partie_1_8(layout8,"table_parties","partie_1_8",1,8);
    partie4  = new Partie_4_2_F(layout4,"table_parties","partie_1_4",9,12);
    partie2  = new Partie_4_2_F(layout2,"table_parties","partie_1_2",13,14);
    partieF  = new Partie_4_2_F(layoutF,"table_parties","finale",15,15);

    // 4 : ajouter les onglets au QTabWidget, en indiquant la page qu'ils contiennent
    onglets->addTab(eliminatoireA , "Eliminatoire_A ");
    onglets->addTab(eliminatoireB , "Eliminatoire_B ");
    onglets->addTab(eliminatoireC , "Eliminatoire_C ");
    onglets->addTab(partie8  , "Partie_1_8");
    onglets->addTab(partie4  , "Partie_1_4");
    onglets->addTab(partie2  , "Partie_1_2");
    onglets->addTab(partieF  , "Partie_finale");


}
