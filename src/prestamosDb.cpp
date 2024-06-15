#include "prestamosDb.hpp"
#include <iostream>
//nuevo
#include <stdexcept>
#include <cmath> // Librería pra calcular el pago mensual
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
        "fecha TEXT, "
        "cuotas INTEGER, "
        "tasa_interes DOUBLE);";
    //Ejecutar comando en base de datos
    return executeQuery(query);
}

// Implementación para calcular la mensualidad del préstamo
double calcularMensualidad(double monto, double tasaInteres, int cuotas) {
    double tasaMensual = tasaInteres / 12.0 / 100.0; // Para obtener la tasa de interés mensual
    return (monto * tasaMensual) / (1 - std::pow(1 + tasaMensual, -cuotas));
}

// Agregar préstamo
int PrestamoDB::addPrestamo(const std::string& clientId, const std::string& tipoPrestamo, double monto, const std::string& fecha, int cuotas) {
    double tasaInteres;
    // Cálculo para cada tipo de préstamo, se elige un tasa fija (se puede modificar)
    if (tipoPrestamo == "Personal") {
        tasaInteres = 20.0;
    } else if (tipoPrestamo == "Prendario") {
        tasaInteres = 16.0;
    } else if (tipoPrestamo == "Hipotecario") {
        tasaInteres = 9.0;
    } else {
        std::cerr << "Tipo de préstamo no válido.\n";
        return -1;
    }

    double mensualidad = calcularMensualidad(monto, tasaInteres, cuotas);

    std::string query = 
        "INSERT INTO prestamos (client, Tipo_Prestamo, monto, fecha, cuotas, tasa_interes) VALUES ('"
        + clientId + "', '"
        + tipoPrestamo + "', "
        + std::to_string(monto) + ", '"
        + fecha + "', "
        + std::to_string(cuotas) + ", "
        + std::to_string(tasaInteres) + ");";
    
    if (!executeQuery(query)) {
        return -1;
    }

    return sqlite3_last_insert_rowid(db);
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


