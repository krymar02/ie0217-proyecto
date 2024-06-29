//transactionDb.hpp

#ifndef TRANSACTIONDB_HPP
#define TRANSACTIONDB_HPP

#include <sqlite3.h>
#include <string>

class TransactionDB {
public:
    //Constructor
    TransactionDB(const std::string& dbPath);
    //DEstructor
    ~TransactionDB();

    //Metodo para crear tabla de cliente
    bool createTable();
    //Metodo agregar cliente
    bool addTransaction(const std::string& clientId,const std::string& tipoOperacion, double monto, int idPrestamo,const std::string& fecha);
    //Metodo eliminar cliente
    bool deleteTransaction(int id);
    //Metodo ver clientes
    void viewTransaction();
    //Metodo verificar que cliente existe
    bool idExiste(const std::string& nombre);

private:
    //Puntero a base de datos
    sqlite3* db;
    //Ruta a la que se abre la base de datos
    std::string dbPath;

    //Ejecucion de operaciones y filtros en base de datos
    bool executeQuery(const std::string& query);
    static int callback(void* NotUsed, int argc, char** argv, char** azColName);
    static int idExisteCallback(void* data, int argc, char** argv, char** azColName);

};

#endif // TransactionDB_HPP
