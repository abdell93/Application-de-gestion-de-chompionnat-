#include "partie.h"
#include "ui_partie.h"

partie::partie(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::partie)
{
    ui->setupUi(this);

}

partie::~partie()
{
    delete ui;
}
