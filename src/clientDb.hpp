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
    bool addCliente(const std::string& id,const std::string& nombre, double colones, double dolares, double cdp, const std::string& fecha);
    //Metodo eliminar cliente
    bool deleteCliente(int id);
    //Metodo ver clientes
    void viewClientes();
    //Metodo verificar que cliente existe
    bool idExiste(const std::string& nombre);
    //Metodo verificar que cliente existe
    bool actualizarCuenta(const std::string &id, double valorUsuario, const std::string &tipoDeCuenta, int tipoOperacion = -1);
    //Para pruebasKryss
    //Metodo para verificar si el saldo es suficiente
    bool verificarSaldoSuficiente(const std::string& id, double monto, const std::string& tipoDeCuenta);
    //Metodo para realizar la transferencia
    bool transferencia(const std::string& idOrigen, const std::string& cuentaOrigen, const std::string& cuentaDestino, double monto);
    //parea el nombre
    std::string obtenerNombreCliente(const std::string& id);  
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

#endif // CLIENTEDB_HPP
