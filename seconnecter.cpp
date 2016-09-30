#include "seconnecter.h"
#include "ui_seconnecter.h"
#include <QSqlQuery>
#include <QMessageBox>
seConnecter::seConnecter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::seConnecter)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(".\\Boule.png"));
    this->setWindowTitle("Championnat de tennis");
    ui->bouton->setIcon(QIcon("Boule.png"));
    QObject::connect(ui->bouton,SIGNAL(clicked()),this,SLOT(authentification()));
}
 void seConnecter::authentification()
 {
     QString usr , mdp;
     usr=ui->pseudo->text();
     mdp=ui->motdepasse->text();
     QSqlQuery cmd;
     QString str = "SELECT * FROM admin WHERE username =  '"+usr+"'  and password =  '"+mdp+"'";
   if(cmd.exec(str))
       { if(cmd.next())
          {
            w=new MainWindow(this);
            w->setWindowTitle("Championnat de tennis");
            this->hide();
            ui->pseudo->clear();
            ui->motdepasse->clear();
            this->w->show();
          }
       else
          {
           qApp->beep();
           //QMessageBox::information(this, "Connexion", "Erreur : verifier votre identifiant ou votre mot de passe !!");
            ui->pseudo->clear();
            ui->motdepasse->clear();
          }
       }
 }

seConnecter::~seConnecter()
{
    delete ui;
}
