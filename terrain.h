#ifndef TERRAIN_H
#define TERRAIN_H
#include "commande.h"
#include<QSqlQueryModel>
#include <QWidget>

namespace Ui {
class terrain;
}

class terrain : public QWidget
{
    Q_OBJECT

public:
    explicit terrain(QWidget *parent = 0);
    ~terrain();

public slots :
    void ajouter();
    void supprimer();
    void chercher();

private:
    Ui::terrain *ui;
    QSqlQueryModel *model = new QSqlQueryModel;
    commande *comd=new commande;
};

#endif // TERRAIN_H
