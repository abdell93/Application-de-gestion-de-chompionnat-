
#include <QApplication>
#include "connection.h"
#include "seconnecter.h"
#include <QSqlQuery>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    connection c;
    seConnecter m;

    if(c.createconnexion())
    {
    }

m.show();
    return a.exec();
}
