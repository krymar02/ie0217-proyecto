#ifndef CERTIFICADODEPOSITOPLAZO_HPP
#define CERTIFICADODEPOSITOPLAZO_HPP

#include <sqlite3.h>
#include <string>
#include <vector>
#include <tuple>

class CertificadoDepositoPlazo {
public:
    CertificadoDepositoPlazo(const std::string& dbPath);
    ~CertificadoDepositoPlazo();

    bool createTable();
    bool addCDP(int clientId, double monto, const std::string& tipoMoneda, double tasaInteres, int duracion, const std::string& fecha);
    bool deleteCDP(int id);
    void viewCDPs();
    bool idExiste(const std::string& id);
    //Determino los ids asociados a un clinte
    std::vector<std::string> cdpIdsCliente(const std::string& clientId);
    //Retorno monto, moneda y tasa interes.
    std::tuple<double, std::string, double> retornarInfo(const std::string& idCdp);

private:
    sqlite3* db;
    std::string dbPath;

    bool executeQuery(const std::string& query);
    static int callback(void* NotUsed, int argc, char** argv, char** azColName);
    static int idExisteCallback(void* data, int argc, char** argv, char** azColName);
    static int obtenerCdpsCallback(void* data, int argc, char** argv, char** azColName);
    static int retornarInfoCallback(void* data, int argc, char** argv, char** azColName);
};

#endif // CERTIFICADODEPOSITOPLAZO_HPP
