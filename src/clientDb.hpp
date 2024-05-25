#ifndef CLIENTDB_HPP
#define CLIENTDB_HPP

#include <sqlite3.h>
#include <string>

class ClienteDB {
public:
    ClienteDB(const std::string& dbPath);
    ~ClienteDB();

    bool createTable();
    bool addCliente(const std::string& nombre, double colones, double dolares, double personal, double hipoteca, double prendario, const std::string& fecha);
    bool deleteCliente(int id);
    void viewClientes();
    bool nombreExiste(const std::string& nombre);

private:
    sqlite3* db;
    std::string dbPath;

    bool executeQuery(const std::string& query);
    static int callback(void* NotUsed, int argc, char** argv, char** azColName);
    static int nombreExisteCallback(void* data, int argc, char** argv, char** azColName);

};

#endif // CLIENTEDB_HPP
