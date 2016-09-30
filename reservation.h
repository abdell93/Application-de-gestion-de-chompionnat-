#ifndef RESERVATION_H
#define RESERVATION_H
#include<QSqlQueryModel>
#include <QWidget>
#include "commande.h"

namespace Ui {
class reservation;
}

class reservation : public QWidget
{
    Q_OBJECT

public:
    explicit reservation(QWidget *parent = 0);
    ~reservation();

public slots :
     void partie_dispo();
     void somme();
     void reserver();
private:
    Ui::reservation *ui;
    commande *cmd=new commande;

};

#endif // RESERVATION_H
