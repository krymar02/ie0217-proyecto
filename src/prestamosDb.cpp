#include "prestamosDb.hpp"
#include <iostream>

//Constructor 
PrestamoDB::PrestamoDB(const std::string& dbPath) : dbPath(dbPath), db(nullptr) {
    //Verifica que la base de datos se abra en la ruta especificada
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    }
}

//Destructor
PrestamoDB::~PrestamoDB() {
    //cierra base de datos
    if (db) {
        sqlite3_close(db);
    }
}

//Crea base de datos
bool PrestamoDB::createTable() {
    
    std::string query = 
        "CREATE TABLE IF NOT EXISTS prestamos ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "client INTEGER, "
        "Tipo_Prestamo TEXT, "
        "monto DOUBLE, "
        "fecha TEXT);";
    //Ejecuto comando en base de datos
    return executeQuery(query);
}

//Agrego cliente
bool PrestamoDB::addPrestamo(const std::string& clientId,const std::string& tipoPrestamo, double monto, const std::string& fecha){
    //Columnas de db cliente, se debe agregas CDP
    std::string query = 
    "INSERT INTO prestamos (client, Tipo_Prestamo, monto, Prestamo_ID, fecha) VALUES ('"
    + clientId + "', '"
    + tipoPrestamo + "', "
    + std::to_string(monto) + ", '"
    + fecha + "');";
    return executeQuery(query);
}

//Elimino cliente por id
bool PrestamoDB::deletePrestamo(int id) {
    std::string query = "DELETE FROM prestamos WHERE ID = " + std::to_string(id) + ";";
    return executeQuery(query);
}

//Ejecutooperaciones en db
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

//Imprimo prestamos almacenados en db
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

//Verifico que los prestamos existan en db
bool PrestamoDB::idExiste(const std::string& id) {
    //Filtro
    std::string query = "SELECT COUNT(*) FROM prestamos WHERE ID = '" + id + "';";
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


