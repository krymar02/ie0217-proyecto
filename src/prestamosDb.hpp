#ifndef PRESTAMOSDB_HPP
#define PRESTAMOSDB_HPP

#include <sqlite3.h>
#include <string>

class PrestamoDB {
public:
    //Constructor
    PrestamoDB(const std::string& dbPath);
    //DEstructor
    ~PrestamoDB();

    //Metodo para crear tabla de cliente
    bool createTable();
    //Metodo agregar cliente
    bool addPrestamo(const std::string& clientId,const std::string& tipoPrestamo, double monto, const std::string& fecha);
    //Metodo eliminar cliente
    bool deletePrestamo(int id);
    //Metodo ver clientes
    void viewPrestamo();
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

#endif // PRESTAMOSDB_HPP
