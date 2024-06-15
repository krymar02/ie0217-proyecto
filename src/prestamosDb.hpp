#ifndef PRESTAMOSDB_HPP
#define PRESTAMOSDB_HPP

#include <sqlite3.h>
#include <string>

class PrestamoDB {
public:
    //Constructor
    PrestamoDB(const std::string& dbPath);
    //Destructor
    ~PrestamoDB();

    //Método para crear tabla de cliente
    bool createTable();
    //Método agregar préstamo
    int addPrestamo(const std::string& clientId,const std::string& tipoPrestamo, double monto, const std::string& fecha);
    //Método eliminar préstamo
    bool deletePrestamo(int id);
    //Método ver préstamos
    void viewPrestamo();
    //Método verificar que el préstamo existe
    bool idExiste(const std::string& id);

private:
    //Puntero a base de datos
    sqlite3* db;
    //Ruta a la que se abre la base de datos
    std::string dbPath;

    //Ejecución de operaciones y filtros en base de datos
    bool executeQuery(const std::string& query);
    static int callback(void* NotUsed, int argc, char** argv, char** azColName);
    static int idExisteCallback(void* data, int argc, char** argv, char** azColName);

};

// Función para calcular monto por mes
double calcularMensualidad(double monto, double tasaInteres, int cuotas);

#endif // PRESTAMOSDB_HPP
