#include "clientDb.hpp"
#include <iostream>
// nuevo
#include <stdexcept>

// Constructor
ClienteDB::ClienteDB(const std::string &dbPath) : dbPath(dbPath), db(nullptr)
{
    // Verifica que la base de datos se abra en la ruta especificada
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK)
    {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    }
}

// Destructor
ClienteDB::~ClienteDB()
{
    // cierra base de datos
    if (db)
    {
        sqlite3_close(db);
    }
}
// PRUEBAS KRYSSIA (Faltan excepciones)

//Se verifica si hay saldo
bool ClienteDB::verificarSaldoSuficiente(const std::string& id, double monto, const std::string& tipoDeCuenta) {
    std::string selectQuery;
    std::string columnName;
    //Parte de seleccion de la cuenta de origen
    //1 para cuenta en colones
    if (tipoDeCuenta == "1") {
        selectQuery = "SELECT colones FROM clientes WHERE id = " + id + ";";
        columnName = "colones";
    //2 para cuenta en dolares
    } else if (tipoDeCuenta == "2") {
        selectQuery = "SELECT dolares FROM clientes WHERE id = " + id + ";";
        columnName = "dolares";
    //3 para cuenta de certificados de deposito a plazos    
    } else {
        selectQuery = "SELECT cdp FROM clientes WHERE id = " + id + ";";
        columnName = "cdp";
    }
    //declaracion de dato de tipo double
    double saldo = 0.0;

    auto selectCallback = [](void* data, int argc, char** argv, char** azColName) -> int {
        if (argc > 0) {
            double* value = static_cast<double*>(data);
            *value = argv[0] ? std::stod(argv[0]) : 0.0;
        }
        return 0;
    };

    char* errMsg = nullptr;
    int result = sqlite3_exec(db, selectQuery.c_str(), selectCallback, &saldo, &errMsg);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    //REtorna el monto
    return saldo >= monto;
}
//funcionalidad para las transferencias
//Se llama la cuenta de origen y la de destino
bool ClienteDB::transferencia(const std::string& idOrigen, const std::string& cuentaOrigen, 
                              const std::string& cuentaDestino, double monto) {
    // En esta parte se verifica si la cuenta de origen tiene suficiente saldo
    if (!verificarSaldoSuficiente(idOrigen, monto, cuentaOrigen)) {
        std::cerr << "Saldo insuficiente en la cuenta de origen." << std::endl;
        return false;
    }

    // Luego se debe actualizar el saldo en la cuenta de origen
    //se aplica un menos al monto de origen igual al monto que se va a transferir
    if (!actualizarCuenta(idOrigen, -monto, cuentaOrigen, 0)) {
        std::cerr << "Error al deducir el monto de la cuenta de origen." << std::endl;
        return false;
    }

    // Actualizar saldo en la cuenta de destino
    if (!actualizarCuenta(cuentaDestino, monto, cuentaDestino, 1)) {
        // Mensajes de éxito de la transferencia :)
        
        // Rollback: Agregar el monto deducido nuevamente a la cuenta de origen
        if (!actualizarCuenta(idOrigen, monto, cuentaOrigen, 1)) {
            std::cerr << "Error al revertir la deduccion en la cuenta de origen." << std::endl;
            // Espacio para agregar excepciones
        }
        return false;
        
    
    }
    

    return true;
}

// FINAL PRUEBAS KRYSSIA

// Crea base de datos
bool ClienteDB::createTable()
{
    // En caso de que db no exista se crea, se debe agregas CDP
    std::string query =
        "CREATE TABLE IF NOT EXISTS clientes ("
        "id INTEGER PRIMARY KEY NOT NULL, "
        "nombre TEXT, "
        "colones DOUBLE, "
        "dolares DOUBLE, "
        "cdp DOUBLE, "
        "fecha TEXT);";
    // Ejecuto comano en base de datos
    return executeQuery(query);
}

// Agrego cliente
bool ClienteDB::addCliente(const std::string &id, const std::string &nombre, double colones, double dolares, double cdp, const std::string &fecha)
{
    // Columnas de db cliente, se debe agregas CDP
    std::string query =
        "INSERT INTO clientes (id, nombre, colones, dolares, cdp, fecha) VALUES ('" + id + "', '" + nombre + "', " + std::to_string(colones) + ", " + std::to_string(dolares) + ", " + std::to_string(cdp) + ", '" + fecha + "');";
    return executeQuery(query);
}

// Elimino cliente por id
bool ClienteDB::deleteCliente(int id)
{
    std::string query = "DELETE FROM clientes WHERE id = " + std::to_string(id) + ";";
    return executeQuery(query);
}

// Ejecutooperaciones en db
bool ClienteDB::executeQuery(const std::string &query)
{
    char *errMsg = nullptr;
    int result = sqlite3_exec(db, query.c_str(), 0, 0, &errMsg);
    if (result != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

// Imprimo clientes almacenados en db
void ClienteDB::viewClientes()
{
    std::string query = "SELECT * FROM clientes;";
    char *errMsg = nullptr;
    int result = sqlite3_exec(db, query.c_str(), callback, 0, &errMsg);
    if (result != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

bool ClienteDB::actualizarCuenta(const std::string &id, double valorUsuario, const std::string &tipoDeCuenta, int tipoOperacion)
{
    // Stirngs que almacenan la operacion de consulta y el nombre de la columna
    std::string selectQuery;
    std::string columnName;

    // Crear la consulta SQL para obtener el valor actual en la columna colones, dolares o cdp
    if (tipoDeCuenta == "1")
    {
        selectQuery = "SELECT colones FROM clientes WHERE id = " + id + ";";
        columnName = "colones";
    }
    else if (tipoDeCuenta == "2")
    {
        selectQuery = "SELECT dolares FROM clientes WHERE id = " + id + ";";
        columnName = "dolares";
    }
    else
    {
        selectQuery = "SELECT cdp FROM clientes WHERE id = " + id + ";";
        columnName = "cdp";
    }

    double currentValue = 0.0;

    // Callback para obtener el valor actual de la columna 'colones, dolares o cdp'
    auto selectCallback = [](void *data, int argc, char **argv, char **azColName) -> int
    {
        if (argc > 0)
        {
            double *value = static_cast<double *>(data);
            *value = argv[0] ? std::stod(argv[0]) : 0.0;
        }
        return 0;
    };

    char *errMsg = nullptr;
    int result = sqlite3_exec(db, selectQuery.c_str(), selectCallback, &currentValue, &errMsg);
    if (result != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    if (tipoOperacion == 0)
    {
        // Caso de retiro
        // En este caso deseo retirar monto mayor al almacnado en las cuentas
        if (currentValue < valorUsuario)
        {
            std::cout << "Monto ingresaddo excede limite de la cuenta." << std::endl;
            return false;
        }
        currentValue -= valorUsuario;
    }
    else
    {

        // Caso de deposito
        // Sumo el valor contenido en la columna selecionada con el valor ingresado por el usuario
        currentValue += valorUsuario;
    }
    // Actualizo la columna selecionada con el valor ingresado por el usuario
    std::string updateQuery =
        "UPDATE clientes SET " + columnName + " = " + std::to_string(currentValue) + " WHERE id = " + id + ";";

    // Ejecuto la actualizacion
    return executeQuery(updateQuery);
}

int ClienteDB::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

// Verifico que los clientes existan en db
bool ClienteDB::idExiste(const std::string &id)
{
    // Filtro
    std::string query = "SELECT COUNT(*) FROM clientes WHERE id = '" + id + "';";
    int count = 0;
    int result = sqlite3_exec(db, query.c_str(), idExisteCallback, &count, nullptr);
    return count > 0;
}

int ClienteDB::idExisteCallback(void *data, int argc, char **argv, char **azColName)
{
    int *count = static_cast<int *>(data);
    if (argc > 0)
    {
        *count = std::stoi(argv[0]);
    }
    return 0;
}