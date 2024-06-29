#include "CDP.hpp"


CDPintereses::CDPintereses(int plazo, PERIODOS_PAGO periodo,int moneda,float capital): plazo(plazo), periodo(periodo) , moneda(moneda), capital(capital){
    data = CDPData();
}

int CDPintereses::getMeses() {
    switch (periodo)
    {
    case MENSUAL:
        return 1;

        break;
    case TRIMESTRAL:
        return 3;
        break;
    case SEMESTRAL:
        return 6;
        break;
    case ANUAL:
        return 12;
        break;
    case FIN_PLAZO:
        return plazo;
        break;
    
    default:
        break;
    }
    return 0;
}


CDPfijaSimple::CDPfijaSimple(int plazo, PERIODOS_PAGO periodo, int moneda,float capital):
 CDPintereses(plazo, periodo, moneda,capital) {};



float CDPfijaSimple::calcularInteres(){
    /* Calcula el interes de un CDP con intereses fijos y calculados de forma simple 
    Para esto se debe dividir el plazo entre los meses del periodo de pago para obtener el numero de periodos
    luego dividir por 12 para obtener la fraccion de years y multiplicar por el capital
    Retorna el interes para el periodo de pago seleccionado */
    int periodos = plazo / getMeses();
    
    switch(moneda){
        
        case COLON:
            return capital * data.Interes_Colones * (periodos/12.0);
        case DOLAR:
            return capital * data.Interes_Dolares * (periodos/12.0);
            break;
        default:
            break;

    }
    return 0;
}


CDPfijaCompuesto::CDPfijaCompuesto(int plazo, PERIODOS_PAGO periodo, int moneda,float capital):
 CDPintereses(plazo, periodo, moneda,capital) {};


float CDPfijaCompuesto::calcularInteres(){
    /* Calcula el interes de un CDP con intereses fijos y calculados de forma compuesta 
    Para esto se debe dividir el plazo entre los meses del periodo de pago y multiplicar por el interes 
    Retorna el interes para el periodo de pago seleccionado */
    int periodos = plazo / getMeses();
    float tasaPorPeriodo;
    switch(moneda){
        
        case COLON:
        /*tasaPorPeriodo es la tasa de interes por periodo de pago

        La formula para calcular el interes compuesto es:
        Interes = Capital * (1 + tasaPorPeriodo)^plazo - Capital
        */
    
            tasaPorPeriodo = data.Interes_Colones / (12/getMeses());
            return capital * (pow(1 + tasaPorPeriodo, periodos) - 1);
        case DOLAR:
            tasaPorPeriodo = data.Interes_Dolares / (12/getMeses());
            return capital * (pow(1 + tasaPorPeriodo, periodos) - 1);
            break;
        default:
            break;

    }
    return 0;
}


CDPvariableSimple::CDPvariableSimple(int plazo, PERIODOS_PAGO periodo, int moneda,float capital):
 CDPintereses(plazo, periodo, moneda,capital) {};


float CDPvariableSimple::calcularInteres(){
    
    /* Calcula el interes de un CDP con intereses variables y calculados de forma simple 
    Para esto se debe dividir el plazo entre los meses del periodo de pago y multiplicar por el interes 
    Retorna el interes para el periodo de pago seleccionado */
    int periodos = plazo / getMeses();
    switch(moneda){
        
        case COLON:
            return capital * data.Interes_Colones * (periodos/12.0);
        case DOLAR:
            return capital * data.Interes_Dolares * (periodos/12.0);
            break;
        default:
            break;

    }
    return 0;
}



CDPvariableCompuesto::CDPvariableCompuesto(int plazo, PERIODOS_PAGO periodo, int moneda,float capital):
 CDPintereses(plazo, periodo, moneda,capital) {};


float CDPvariableCompuesto::calcularInteres(){
    /* Calcula el interes de un CDP con intereses variables y calculados de forma compuesta 
    Para esto se debe dividir el plazo entre los meses del periodo de pago y multiplicar por el interes 
    Retorna el interes para el periodo de pago seleccionado */
    int periodos = plazo / getMeses();
    float tasaPorPeriodo;
    switch(moneda){
        
        case COLON:
        /*tasaPorPeriodo es la tasa de interes por periodo de pago

        La formula para calcular el interes compuesto es:
        Interes = Capital * (1 + tasaPorPeriodo)^plazo - Capital
        */
    
            tasaPorPeriodo = data.Interes_Colones / (12/getMeses());
            return capital * (pow(1 + tasaPorPeriodo, periodos) - 1);
        case DOLAR:
            tasaPorPeriodo = data.Interes_Dolares / (12/getMeses());
            return capital * (pow(1 + tasaPorPeriodo, periodos) - 1);
            break;
        default:
            break;

    }
    return 0;   
}

//Inicia la implementacion de la clase CDP

CDP::CDP(std::string nombre,std::string apellido, int id) : cliente(nombre, apellido, id) {
    Cliente cliente(nombre, apellido, id);
    data = CDPData();
}

void CDP::agregarCDP(){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql;
    int id_CDP = generarID();
    if (moneda == COLON){
        sql = "INSERT INTO DEPOSITO_PLAZO (ID_DEPOSITO,ID_CDP,ID_CLIENTE,MONTO,MONEDA,PLAZO,PERIODO_PAGO,FECHA_INICIO,FECHA_FIN,TIPO_INTERES,INTERES)" 
        "VALUES (" + std::to_string(cliente.idCuentaC) +  "," + std::to_string(id_CDP) +"," + std::to_string(cliente.id) + "," + std::to_string(monto) + ",'Colones'," + std::to_string(plazo) + ",'" + periodoPago + "','" + fechaCreacion + "','" + fechaVencimiento + "','" + tipoInteres + "'," + std::to_string(interes) + ");";
    } else {
        sql = "INSERT INTO DEPOSITO_PLAZO (ID_DEPOSITO,ID_CLIENTE,MONTO,MONEDA,PLAZO,PERIODO_PAGO,FECHA_INICIO,FECHA_FIN,TIPO_INTERES,INTERES)" 
        "VALUES (" + std::to_string(cliente.idCuentaD) +  "," + std::to_string(id_CDP) +"," + std::to_string(cliente.id) + "," + std::to_string(monto) + ",'Dolares'," + std::to_string(plazo) + ",'" + periodoPago + "','" + fechaCreacion + "','" + fechaVencimiento + "','" + tipoInteres + "'," + std::to_string(interes) + ");";
    }
   

    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc) {
        std::cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al insertar datos: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "..." << std::endl;
    }
    sqlite3_close(db);

}

void CDP::displayMenuCDP() {
    int opcion;
    std:: string opcionStr;
    int rightChoice = 0;
   
    do {
        do {

            std::cout << "\n1. Agregar CDP" << std::endl;
            std::cout << "2. Retirar CDP" << std::endl;
            std::cout << "3. Desplegar CDP" << std::endl;
            std::cout << "4. Eliminar" << std::endl;
            std::cout << "5. Salir" << std::endl;
            std::cin >> opcionStr;
            try {
                if (!cliente.validarEntrada(opcionStr,&opcion)){
                    throw std::invalid_argument("Opcion invalida");
                }
                if (opcion < AGREGAR_CDP || opcion > SALIR_CDP){
                    throw std::invalid_argument("Opcion invalida");
                }
                break;
            }
            catch (std::invalid_argument &e){
                rightChoice = cliente.returnMain(e.what());
            }
           
        } while (rightChoice != RETURN);
        
        switch (opcion)
        {
        case AGREGAR_CDP:
            displayMenuOptions();
           
            break;
        case RETIRAR_CDP:
            ///
            break;
        case DESPLEGAR_CDP:
            desplegarCDP();
            break;
        case ELIMINAR_CDP:
            retirarCDP();
            break;
        default:
            break;
        }

    } while (opcion != SALIR_CDP && rightChoice != RETURN);
    system("clear");
    return;
}

#define SALIR_OP 5
void CDP::displayMenuOptions() {
    int opcion;
    std::string opStr;
    int opcionPlazo;
    std::string opcionStr;
    std::string montoStr;
    int rightChoice = 0;
    do {
        do {
            std::cout << "1. Interes Simple tasa fija" << std::endl;
            std::cout << "2. Interes Compuesto tasa fija" << std::endl;
            std::cout << "3. Interes Simple tasa variable" << std::endl;
            std::cout << "4. Interes Compuesto tasa variable" << std::endl;
            std::cout << "5. Salir" << std::endl;
            try {
                std::cin >> opStr;
                if (!cliente.validarEntrada(opStr,&opcion)){
                    throw std::invalid_argument("Opcion invalida");
                }
                if (opcion < SIMPLE || opcion > SALIR_OP){
                    throw std::invalid_argument("Opcion invalida");
                }
                break;
            } catch (std::invalid_argument &e){
                rightChoice = cliente.returnMain(e.what());
            }
        } while (rightChoice != RETURN);

        do {
            std::cout << "Ingrese el monto de la inversion" << std::endl;
            std::cin >> montoStr;
            try{
                if (!cliente.validarDatos(montoStr,&monto)){
                    throw std::invalid_argument("Monto invalido");
                }
                break;
            } catch (std::invalid_argument &e){
                rightChoice = cliente.returnMain(e.what());
            }
            break;
        } while (rightChoice != RETURN);

        this->fechaCreacion = (this->cliente).getFecha();

        do {
            std::cout << "Ingrese el plazo de la inversion" << std::endl;
            std::cin >> opcionStr;
            try {
                if (!cliente.validarEntrada(opcionStr,&plazo)){
                    throw std::invalid_argument("Plazo invalido");
                }
                break;
            } catch (std::invalid_argument &e){
                rightChoice = cliente.returnMain(e.what());
                if (rightChoice == RETURN){
                    return ;
                }   
            }
            break;
        } while (rightChoice != RETURN);
        

        PERIODOS_PAGO oplazo = displayMenuPeriodosPago(opcionPlazo);

        this->periodo = oplazo;

        this->fechaVencimiento = calcularFechaVencimiento(plazo);
        this->moneda = elegirCuenta();
        //Si se selecciona salir se termina el proceso
        if (moneda == 0){
            return;
        }
        CDPfijaSimple cdpSimple(plazo,oplazo,moneda,monto);
        CDPfijaCompuesto cdpCompuesto(plazo,oplazo,moneda,monto);
        CDPvariableSimple cdpSimpleVariable(plazo,oplazo,moneda,monto);
        CDPvariableCompuesto cdpCompuestoVariable(plazo,oplazo,moneda,monto);

        switch (opcion)
        {
        case SIMPLE:
            this->tipoInteres = "Simple";
            
            this->interes= cdpSimple.calcularInteres();
            break;
        case COMPUESTO:
            this->tipoInteres = "Compuesto";
            this->interes = cdpCompuesto.calcularInteres();
            break;
        case SIMPLE_VARIABLE:
            this->tipoInteres = "SimpleVariable";
            this->interes=cdpSimpleVariable.calcularInteres();
            break;
        case COMPUESTO_VARIABLE:
            this->tipoInteres = "CompuestoVariable";
            this->interes = cdpCompuestoVariable.calcularInteres();
            break;
        default:
            break;
        }

        agregarCDP();
        rightChoice = cliente.returnMain("CDP agregado con exito");
        this->monto = 0;
        this->plazo = 0;
        this->interes = 0;
        this->fechaCreacion = "";
        this->fechaVencimiento = "";
        this->periodoPago = "";
        this->tipoInteres = "";
        this->moneda = 0;
    

        
    } while (opcion != SALIR_CDP && rightChoice != RETURN);
}


PERIODOS_PAGO CDP::displayMenuPeriodosPago(int & opcion){
    
    std::string opcionStr;

    do {
        std::cout << "Seleccione el periodo de pago" << std::endl;
        std::cout << "1. Mensual" << std::endl;
        std::cout << "2. Trimestral" << std::endl;
        std::cout << "3. Semestral" << std::endl;
        std::cout << "4. Anual" << std::endl;
        std::cout << "5. Fin de plazo" << std::endl;
        try{
            std::cin >> opcionStr;
            if (!cliente.validarEntrada(opcionStr,&opcion)){
                throw std::invalid_argument("Opcion invalida");
            }
            if (opcion < MENSUAL || opcion > FIN_PLAZO){
                throw std::invalid_argument("Opcion invalida");
            }
            break;
        }
        catch (std::invalid_argument &e){
            std::cout << e.what() << std::endl;
            continue;
        }

    } while(true);

    switch (opcion)
    {
    case MENSUAL:
        this->periodoPago = "Mensual";
        return MENSUAL;
        break;
    case TRIMESTRAL:
        this->periodoPago = "Trimestral";
        return TRIMESTRAL;
        break;
    case SEMESTRAL:
        this->periodoPago = "Semestral";
        return SEMESTRAL;
        break;
    case ANUAL:
        this->periodoPago = "Anual";
        return ANUAL;
        break;
    case FIN_PLAZO:
        this->periodoPago = "Fin de plazo";
        return FIN_PLAZO;
        break;
    default:
        break;
    }

    return ERROR;
    


}


std::string CDP::calcularFechaVencimiento(int plazo) {
    // Calcula la fecha de vencimiento de un CDP
    std::string fecha = (this->cliente).getFecha();
    // fecha formato "mm/dd/yyyy"
    std::string year = fecha.substr(6, 4);
    std::string month = fecha.substr(0, 2);
    std::string day = fecha.substr(3, 2);
    
    int yearInt = std::stoi(year);
    int monthInt = std::stoi(month);
    int dayInt = std::stoi(day);
    
    // a;adir el plazo al mes
    monthInt += plazo;
    
    // A;adir un a;o por cada 12 meses
    while (monthInt > 12) {
        yearInt++;
        monthInt -= 12;
    }

    // Febrero tiene 29 dias si es a;o bisiesto
    if (monthInt == 2) {
        if ((yearInt % 4 == 0 && yearInt % 100 != 0) || (yearInt % 400 == 0)) {
            if (dayInt > 29) {
                dayInt = 29;
            }
        } else {
            if (dayInt > 28) {
                dayInt = 28;
            }
        }
    }
    // meses 30 dias
    else if (monthInt == 4 || monthInt == 6 || monthInt == 9 || monthInt == 11) {
        if (dayInt > 30) {
            dayInt = 30;
        }
    }

    // Fmm/dd/yyyy
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << monthInt << "/"
        << std::setw(2) << std::setfill('0') << dayInt << "/"
        << yearInt;
    
    return oss.str();
}


int CDP::elegirCuenta(){
    int opcion;
    int rightChoice = 0;
    std::string opcionStr;
    do {
        do {
            std::cout << "Seleccione la cuenta a la que desea agregar el CDP" << std::endl;
            std::cout << "1.Cuenta en colones" << std::endl;
            std::cout << "2.Cuenta en dolares" << std::endl;
            try {
                std::cin >> opcionStr;
                if (!cliente.validarEntrada(opcionStr,&opcion)){
                    throw std::invalid_argument("Opcion invalida");
                }
                if (opcion < COLON || opcion > DOLAR){
                    throw std::invalid_argument("Opcion invalida");
                }
                break;
            } catch (std::invalid_argument &e){
                rightChoice = cliente.returnMain(e.what());
            }
        } while (true);

        switch (opcion)
        {
        case COLON:
            if(cliente.getIDCuenta(COLON) == 0){
                
                rightChoice = cliente.returnMain("No se ha encontrado una cuenta en colones");
                continue;
            }
            return COLON;
            break;
        case DOLAR:
            if(cliente.getIDCuenta(DOLAR) == 0){
                rightChoice = cliente.returnMain("No se ha encontrado una cuenta en dolares");
                continue;
            }
            return DOLAR;
            break;
        
        default:
            break;
        }
    
    } while (rightChoice != RETURN);
    return 0;

}

void CDP::desplegarCDP(){
    std::string monedaStr;
    int rightChoice = 0;
    int Moneda;
    do {
        std::cout << "Seleccione la cuenta de donde quiere consultar los CDPs" << std::endl;
        std::cout << "1.Cuenta en colones" << std::endl;
        std::cout << "2.Cuenta en dolares" << std::endl;
        try {
            std::cin >> monedaStr;
            if (!cliente.validarEntrada(monedaStr,&Moneda)){
                throw std::invalid_argument("Opcion invalida");
            }
            if (Moneda < COLON || Moneda > DOLAR){
                throw std::invalid_argument("Opcion invalida");
            }
            break;
        } catch (std::invalid_argument &e){
            rightChoice = cliente.returnMain(e.what());
        }
    } while (true);
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql;
    if (Moneda == COLON){
        sql = "SELECT * FROM DEPOSITO_PLAZO WHERE ID_CLIENTE = " + std::to_string(cliente.id) + " AND MONEDA = 'Colones';";
    } else {
        sql = "SELECT * FROM DEPOSITO_PLAZO WHERE ID_CLIENTE = " + std::to_string(cliente.id) + " AND MONEDA = 'Dolares';";
    }
    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc) {
        std::cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_exec(db, sql.c_str(), callbackgetCDP, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al desplegar datos " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "..." << std::endl;
    }
    sqlite3_close(db);
}







int callbackgetCDP(void *NotUsed, int argc, char **argv, char **azColName) {
    static bool headerPrinted = false;
    const int columnWidth = 15; // Ancho de las columnas

    // Si no hay datos
    if (argc == 0) {
        std::cout << "No hay CDPs para mostrar" << std::endl;
        return 0;
    }
    //Imprimir los nombres de las columnas
    if (!headerPrinted) {
        for (int i = 0; i < argc; i++) {
            std::cout << std::setw(columnWidth) << std::left << azColName[i] << "|";
        }
        std::cout << std::endl;
        for (int i = 0; i < argc; i++) {
            std::cout << std::setfill('-') << std::setw(columnWidth) << "" << "|";
        }
        std::cout << std::setfill(' ') << std::endl; // Resetear el fill
        headerPrinted = true;
    }
    
    //Imprimir los valores de las columnas
    for (int i = 0; i < argc; i++) {
        std::cout << std::setw(columnWidth) << std::left << (argv[i] ? argv[i] : "NULL") << "|";
    }
    std::cout << std::endl;

    return 0;
}



void CDP::retirarCDP(){
    //Retira un CDP de la base de datos
    std::string idCDP;
    std::string montoRetiro;
    int rightChoice = 0;
    int idCDPInt;

    //Preguntar por el ID del CDP
    do {
        std::cout << "Ingrese el ID de la cuenta donde desea retirar los CDPs" << std::endl;
        std::cin >> idCDP;
        try {
            if (!cliente.validarEntrada(idCDP,&idCDPInt)){
                throw std::invalid_argument("ID invalido");
            }
            if (!cliente.checkIDCuentaExists(idCDPInt,COLON) && !cliente.checkIDCuentaExists(idCDPInt,DOLAR)){
                throw std::invalid_argument("ID no encontrado");
            }
            break;
        } catch (std::invalid_argument &e){
            rightChoice = cliente.returnMain(e.what());
        }
    } while (rightChoice != RETURN);
    
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    std::string sql;
    sql = "DELETE FROM DEPOSITO_PLAZO WHERE ID_DEPOSITO = " + idCDP + " AND ID_CLIENTE = " + std::to_string(cliente.id) + ";";
    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc) {
        std::cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al retirar CDP " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "..." << std::endl;
    }
    sqlite3_close(db);
    std::cout << "CDP retirado con exito" << std::endl;
    system("clear");

}


int CDP::generarID(){
    // Genera un ID para un CDP
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    int id = 0;
    std::string sql = "SELECT MAX(ID_CDP) FROM DEPOSITO_PLAZO;";
    rc = sqlite3_open("SistemaBancario.db", &db);
    if (rc) {
        std::cerr << "Error al abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 0;
    }

    rc = sqlite3_exec(db, sql.c_str(), intCallback, &id, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al generar ID " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);

    if (id == 0) {
        return 1;
    }
    return id + 1;

}

float CDP::getInteres(){

}