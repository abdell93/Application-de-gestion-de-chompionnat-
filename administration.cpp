#include "administration.h"
#include "ui_administration.h"

administration::administration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::administration)
{
    ui->setupUi(this);
   QObject::connect(ui->bouton,SIGNAL(clicked()),this,SLOT(deconnexion()));
}
void administration::deconnexion()
{
    QWidget *q= (((this->parentWidget())->parentWidget())->parentWidget())->parentWidget();
    QWidget *p=q->parentWidget();
    q->hide();
    p->show();
    delete(q);
}
administration::~administration()
{
    delete ui;
}
