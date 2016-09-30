#ifndef RESULTAT_H
#define RESULTAT_H

#include <QWidget>
#include "connection.h"
namespace Ui {
class resultat;
}

class resultat : public QWidget
{
    Q_OBJECT

public:

    explicit resultat(QWidget *parent = 0);
    ~resultat();
    void set_donne(QString table1="table_parties",int premier1=1,int dernier1=16);
    int get_premier();
    int get_fin();
    QString get_table();
private slots:
    void on_pushButton_clicked();

private:
    Ui::resultat *ui;
protected:
QString table;
int premier ,dernier;

};

#endif // RESULTAT_H
