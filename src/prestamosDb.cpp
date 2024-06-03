#include "prestamosDb.hpp"
#include <iostream>
//nuevo
#include <stdexcept>
//Constructor 
PrestamoDB::PrestamoDB(const std::string& dbPath) : dbPath(dbPath), db(nullptr) {
    //Verifica que la base de datos se abra en la ruta especificada
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    }
}

//Destructor
PrestamoDB::~PrestamoDB() {
    //Cierra base de datos
    if (db) {
        sqlite3_close(db);
    }
}

//Crea base de datos
// Crea la tabla de préstamos
bool PrestamoDB::createTable() {
    std::string query = 
        "CREATE TABLE IF NOT EXISTS prestamos ("
        "Prestamo_ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "client INTEGER, "
        "Tipo_Prestamo TEXT, "
        "monto REAL, "
        "fecha TEXT);";
    //Ejecutar comando en base de datos
    return executeQuery(query);
}

//Agregar préstamo
bool PrestamoDB::addPrestamo(const std::string& clientId,const std::string& tipoPrestamo, double monto, const std::string& fecha){
    //Columnas de db cliente, se debe agregas CDP
    std::string query = 
        "INSERT INTO prestamos (client, Tipo_Prestamo, monto, fecha) VALUES ('"
        + clientId + "', '"
        + tipoPrestamo + "', "
        + std::to_string(monto) + ", '"
        + fecha + "');";
    return executeQuery(query);
}

//Eliminar préstamo por id
bool PrestamoDB::deletePrestamo(int id) {
    std::string query = "DELETE FROM prestamos WHERE Prestamo_ID = " + std::to_string(id) + ";";
    return executeQuery(query);
}

//Ejecutar operaciones en db
bool PrestamoDB::executeQuery(const std::string& query) {
    char* errMsg = nullptr;
    int result = sqlite3_exec(db, query.c_str(), 0, 0, &errMsg);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

//Imprimir préstamos almacenados en db
void PrestamoDB::viewPrestamo() {
    std::string query = "SELECT * FROM prestamos;";
    char* errMsg = nullptr;
    int result = sqlite3_exec(db, query.c_str(), callback, 0, &errMsg);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

int PrestamoDB::callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

//Verificar que los préstamos existan en db
bool PrestamoDB::idExiste(const std::string& id) {
    //Filtro
    std::string query = "SELECT COUNT(*) FROM prestamos WHERE Prestamo_ID = '" + id + "';";
    int count = 0;
    int result = sqlite3_exec(db, query.c_str(), idExisteCallback, &count, nullptr);
    return count > 0;
}

int PrestamoDB::idExisteCallback(void* data, int argc, char** argv, char** azColName) {
    int* count = static_cast<int*>(data);
    if (argc > 0) {
        *count = std::stoi(argv[0]);
    }
    return 0;
}


