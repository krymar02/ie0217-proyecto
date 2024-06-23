#include "transactionDb.hpp"
#include <iostream>
//nuevo
#include <stdexcept>

//Constructor 
TransactionDB::TransactionDB(const std::string& dbPath) : dbPath(dbPath), db(nullptr) {
    //Verifica que la base de datos se abra en la ruta especificada
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    }
}

//Destructor
TransactionDB::~TransactionDB() {
    //cierra base de datos
    if (db) {
        sqlite3_close(db);
    }
}

//Crea base de datos
bool TransactionDB::createTable() {
    
    std::string query = 
        "CREATE TABLE IF NOT EXISTS transferencias ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "client INTEGER NOT NULL, "
        "Operacion TEXT, "
        "monto DOUBLE, "
        "Prestamo_ID INTEGER, "
        "fecha TEXT, "
        "FOREIGN KEY (client) REFERENCES clientes (id) ON DELETE CASCADE);";;
    //Ejecuto comando en base de datos
    return executeQuery(query);
}

//Agrego transaccion
bool TransactionDB::addTransaction(const std::string& clientId, const std::string& tipoOperacion, double monto, int idPrestamo,const std::string& fecha){
    
    //En caso de que idPrestamo sea -1, se agrega un valor nulo en la db, caso sontrario, se agrega id prestamo
    std::string idPrestamoStr = (idPrestamo == -1) ? "NULL" : std::to_string(idPrestamo);
    //Columnas de db transferencias
    std::string query = 
        "INSERT INTO transferencias (client, Operacion, monto, Prestamo_ID, fecha) VALUES ('" 
        + clientId + "', '" 
        + tipoOperacion + "', " 
        + std::to_string(monto) + ", " 
        + idPrestamoStr + ", '" 
        + fecha + "');";
    return executeQuery(query);
}

//Elimino cliente por id
bool TransactionDB::deleteTransaction(int id) {
    std::string query = "DELETE FROM transferencias WHERE ID = " + std::to_string(id) + ";";
    return executeQuery(query);
}

//Ejecutooperaciones en db
bool TransactionDB::executeQuery(const std::string& query) {
    char* errMsg = nullptr;
    int result = sqlite3_exec(db, query.c_str(), 0, 0, &errMsg);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

//Imprimo transferencias almacenados en db
void TransactionDB::viewTransaction() {
    std::string query = "SELECT * FROM transferencias;";
    char* errMsg = nullptr;
    int result = sqlite3_exec(db, query.c_str(), callback, 0, &errMsg);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

int TransactionDB::callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

//Verifico que los transferencias existan en db
bool TransactionDB::idExiste(const std::string& id) {
    //Filtro
    std::string query = "SELECT COUNT(*) FROM transferencias WHERE ID = '" + id + "';";
    int count = 0;
    int result = sqlite3_exec(db, query.c_str(), idExisteCallback, &count, nullptr);
    return count > 0;
}

int TransactionDB::idExisteCallback(void* data, int argc, char** argv, char** azColName) {
    int* count = static_cast<int*>(data);
    if (argc > 0) {
        *count = std::stoi(argv[0]);
    }
    return 0;
}


