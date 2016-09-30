#include "connection.h"

connection::connection()
{

}
bool connection::createconnexion()
{
bool test=true;
db=QSqlDatabase::addDatabase("QSQLITE");
db.setDatabaseName("C:/Users/abdel/Desktop/testt/basededonne.sqlite");
if(!db.open())test=false;
return test;
}
