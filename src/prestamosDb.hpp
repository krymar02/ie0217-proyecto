//prestamosDb.hpp

#ifndef PRESTAMOSDB_HPP
#define PRESTAMOSDB_HPP

#include <sqlite3.h>
#include <string>
#include <vector>

struct PagoProgreso {
    double totalPagado;
    double totalAporteCapital;
    double totalIntereses;
};

class PrestamoDB {
public:
    //Constructor
    PrestamoDB(const std::string& dbPath);
    //Destructor
    ~PrestamoDB();

    //Método para crear tabla de cliente
    bool createTable();
    //Método agregar préstamo
    int addPrestamo(const std::string& clientId,const std::string& tipoPrestamo, double monto, const std::string& fecha, int cuotas, const std::string& tipoMoneda);
    //Método eliminar préstamo
    bool deletePrestamo(int id);
    //Método ver la tabla de préstamos asociados a un cliente
    void viewPrestamo(const std::string& clientID);
    //Método verificar que el préstamo existe para un cliente
    bool idExiste(const std::string& id);
    //Determino los ids asociados a un clinte
    std::vector<std::string> prestamosIdsCliente(const std::string& clientId);
    //Método retorna el monto mensual del prestamo
    std::pair<double, std::string> obtenerMonto(const std::string& prestamoId);
    //Metdo que reduce en 1 la cantidad de cuotas y determina si el prestamo ya se pago
    void abonarPrestamo(const std::string& prestamoId);
    // Método para agregar cuota pagada
    bool addCuotaPagada(int prestamoID, const std::string& fechaPago, double aporteCapital, double interesesAbonados);
    // Método para calcular el progreso del préstamo
    PagoProgreso calcularProgresoPrestamo(int prestamoID);


private:
    //Puntero a base de datos
    sqlite3* db;
    //Ruta a la que se abre la base de datos
    std::string dbPath;

    //Ejecución de operaciones y filtros en base de datos
    bool executeQuery(const std::string& query);
    static int callback(void* NotUsed, int argc, char** argv, char** azColName);
    static int idExisteCallback(void* data, int argc, char** argv, char** azColName);
    static int obtenerPrestamosCallback(void* data, int argc, char** argv, char** azColName);
    static int obtenerMontoCallback(void* data, int argc, char** argv, char** azColName);
    static int obtenerCuotasCallback(void* data, int argc, char** argv, char** azColName);
    static int calcularProgresoCallback(void* data, int argc, char** argv, char** azColName);
    std::string obtenerFechaActual();
};

// Función para calcular monto por mes
double calcularMensualidad(double monto, double tasaInteres, int cuotas);

#endif // PRESTAMOSDB_HPP
