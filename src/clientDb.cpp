#include "clientDb.hpp"
#include <iostream>

ClienteDB::ClienteDB(const std::string& dbPath) : dbPath(dbPath), db(nullptr) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    }
}

ClienteDB::~ClienteDB() {
    if (db) {
        sqlite3_close(db);
    }
}

bool ClienteDB::createTable() {
    std::string query = 
        "CREATE TABLE IF NOT EXISTS clientes ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "nombre TEXT, "
        "colones DOUBLE, "
        "dolares DOUBLE, "
        "personal DOUBLE, "
        "hipoteca DOUBLE, "
        "prendario DOUBLE, "
        "fecha TEXT);";
    return executeQuery(query);
}

bool ClienteDB::addCliente(const std::string& nombre, double colones, double dolares, double personal, double hipoteca, double prendario, const std::string& fecha) {
    std::string query = 
        "INSERT INTO clientes (nombre, colones, dolares, personal, hipoteca, prendario, fecha) VALUES ('"
        + nombre + "', "
        + std::to_string(colones) + ", "
        + std::to_string(dolares) + ", "
        + std::to_string(personal) + ", "
        + std::to_string(hipoteca) + ", "
        + std::to_string(prendario) + ", '"
        + fecha + "');";
    return executeQuery(query);
}

bool ClienteDB::deleteCliente(int id) {
    std::string query = "DELETE FROM clientes WHERE id = " + std::to_string(id) + ";";
    return executeQuery(query);
}

bool ClienteDB::executeQuery(const std::string& query) {
    char* errMsg = nullptr;
    int result = sqlite3_exec(db, query.c_str(), 0, 0, &errMsg);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}


void ClienteDB::viewClientes() {
    std::string query = "SELECT * FROM clientes;";
    char* errMsg = nullptr;
    int result = sqlite3_exec(db, query.c_str(), callback, 0, &errMsg);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

int ClienteDB::callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}


bool ClienteDB::nombreExiste(const std::string& nombre) {
    std::string query = "SELECT COUNT(*) FROM clientes WHERE nombre = '" + nombre + "';";
    int count = 0;
    int result = sqlite3_exec(db, query.c_str(), nombreExisteCallback, &count, nullptr);
    return count > 0;
}

int ClienteDB::nombreExisteCallback(void* data, int argc, char** argv, char** azColName) {
    int* count = static_cast<int*>(data);
    if (argc > 0) {
        *count = std::stoi(argv[0]);
    }
    return 0;
}


