#include "CertificadoDepositoPlazo.hpp"
#include <iostream>

CertificadoDepositoPlazo::CertificadoDepositoPlazo(const std::string& dbPath) : dbPath(dbPath), db(nullptr) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    }
}

CertificadoDepositoPlazo::~CertificadoDepositoPlazo() {
    if (db) {
        sqlite3_close(db);
    }
}

bool CertificadoDepositoPlazo::createTable() {
    std::string query = 
        "CREATE TABLE IF NOT EXISTS cdp ("
        "CDP_ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "client_id INTEGER NOT NULL, "
        "monto DOUBLE NOT NULL, "
        "tipo_moneda TEXT NOT NULL, "
        "tasa_interes DOUBLE NOT NULL, "
        "duracion INTEGER NOT NULL, "
        "fecha TEXT NOT NULL, "
        "FOREIGN KEY(client_id) REFERENCES clientes(id) ON DELETE CASCADE);";
    return executeQuery(query);
}

bool CertificadoDepositoPlazo::addCDP(int clientId, double monto, const std::string& tipoMoneda, double tasaInteres, int duracion, const std::string& fecha) {
    std::string query = 
        "INSERT INTO cdp (client_id, monto, tipo_moneda, tasa_interes, duracion, fecha) VALUES ("
        + std::to_string(clientId) + ", "
        + std::to_string(monto) + ", '"
        + tipoMoneda + "', "
        + std::to_string(tasaInteres) + ", "
        + std::to_string(duracion) + ", '"
        + fecha + "');";
    return executeQuery(query);
}

bool CertificadoDepositoPlazo::deleteCDP(int id) {
    std::string query = "DELETE FROM cdp WHERE CDP_ID = " + std::to_string(id) + ";";
    return executeQuery(query);
}

void CertificadoDepositoPlazo::viewCDPs() {
    std::string query = "SELECT * FROM cdp;";
    char* errMsg = nullptr;
    int result = sqlite3_exec(db, query.c_str(), callback, 0, &errMsg);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

//Verificar que los CertificadoDepositoPlazo existan en db
bool CertificadoDepositoPlazo::idExiste(const std::string& id) {
    //Filtro
    std::string query = "SELECT COUNT(*) FROM cdp WHERE client_id = '" + id + "';";
    int count = 0;
    int result = sqlite3_exec(db, query.c_str(), idExisteCallback, &count, nullptr);
    return count > 0;
}

int CertificadoDepositoPlazo::idExisteCallback(void* data, int argc, char** argv, char** azColName) {
    int* count = static_cast<int*>(data);
    if (argc > 0) {
        *count = std::stoi(argv[0]);
    }
    return 0;
}

//Este metodo retorna un vector de strings con los id asociados al id del cliente
std::vector<std::string> CertificadoDepositoPlazo::cdpIdsCliente(const std::string& clientId){
    std::string query = "SELECT CDP_ID FROM cdp WHERE client_id = '" + clientId + "';";
    std::vector<std::string> prestamos;
    int result = sqlite3_exec(db, query.c_str(), obtenerCdpsCallback, &prestamos, nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    }
    return prestamos;
}

int CertificadoDepositoPlazo::obtenerCdpsCallback(void* data, int argc, char** argv, char** azColName) {
    std::vector<std::string>* prestamos = static_cast<std::vector<std::string>*>(data);
    for (int i = 0; i < argc; i++) {
        prestamos->push_back(argv[i]);
    }
    return 0;
}

std::tuple<double, std::string, double> CertificadoDepositoPlazo::retornarInfo(const std::string& idCdp) {
    std::string query = "SELECT monto, tipo_moneda, tasa_interes FROM cdp WHERE CDP_ID = " + idCdp + ";";
    std::tuple<double, std::string, double> info;
    int result = sqlite3_exec(db, query.c_str(), retornarInfoCallback, &info, nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    }
    
    return info;
}

int CertificadoDepositoPlazo::retornarInfoCallback(void* data, int argc, char** argv, char** azColName) {
    auto* info = static_cast<std::tuple<double, std::string, double>*>(data);
    if (argc == 3) {
        std::get<0>(*info) = std::stod(argv[0]);
        std::get<1>(*info) = argv[1];
        std::get<2>(*info) = std::stod(argv[2]);
    }
    return 0;
}

bool CertificadoDepositoPlazo::executeQuery(const std::string& query) {
    char* errMsg = nullptr;
    int result = sqlite3_exec(db, query.c_str(), 0, 0, &errMsg);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

int CertificadoDepositoPlazo::callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}
