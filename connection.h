#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtDebug>
#include <QSqlDatabase>

class connection
{private:
    QSqlDatabase db;
public:
    connection();
    bool createconnexion();

};

#endif // CONNECTION_H
