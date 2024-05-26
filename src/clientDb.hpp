#ifndef CLIENTDB_HPP
#define CLIENTDB_HPP

#include <sqlite3.h>
#include <string>

class ClienteDB {
public:
    //Constructor
    ClienteDB(const std::string& dbPath);
    //DEstructor
    ~ClienteDB();

    //Metodo para crear tabla de cliente
    bool createTable();
    //Metodo agregar cliente
    bool addCliente(const std::string& nombre, double colones, double dolares, double cdp, double personal, double hipoteca, double prendario, const std::string& fecha);
    //Metodo eliminar cliente
    bool deleteCliente(int id);
    //Metodo ver clientes
    void viewClientes();
    //Metodo verificar que cliente existe
    bool nombreExiste(const std::string& nombre);

private:
    //Puntero a base de datos
    sqlite3* db;
    //Ruta a la que se abre la base de datos
    std::string dbPath;

    //Ejecucion de operaciones y filtros en base de datos
    bool executeQuery(const std::string& query);
    static int callback(void* NotUsed, int argc, char** argv, char** azColName);
    static int nombreExisteCallback(void* data, int argc, char** argv, char** azColName);

};

#endif // CLIENTEDB_HPP
