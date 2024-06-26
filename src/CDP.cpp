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
            return capital * data.Interes_Colones * (periodos/12);
        case DOLAR:
            return capital * data.Interes_Dolares * (periodos/12);
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
            return capital * data.Interes_Colones * (periodos/12);
        case DOLAR:
            return capital * data.Interes_Dolares * (periodos/12);
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
    if (moneda == COLON){
        sql = "INSERT INTO DEPOSITO_PLAZO (ID_DEPOSITO,ID_CLIENTE,MONTO,MONEDA,PLAZO,PERIODO_PAGO,FECHA_INICIO,FECHA_FIN,TIPO_INTERES,INTERES)" 
        "VALUES (" + std::to_string(cliente.idCuentaC) + "," + std::to_string(cliente.id) + "," + std::to_string(monto) + ",'Colones'," + std::to_string(plazo) + ",'" + periodoPago + "','" + fechaCreacion + "','" + fechaVencimiento + "','" + tipoInteres + "'," + std::to_string(interes) + ");";
    } else {
        sql = "INSERT INTO DEPOSITO_PLAZO (ID_DEPOSITO,ID_CLIENTE,MONTO,MONEDA,PLAZO,PERIODO_PAGO,FECHA_INICIO,FECHA_FIN,TIPO_INTERES,INTERES)" 
        "VALUES (" + std::to_string(cliente.idCuentaD) + "," + std::to_string(cliente.id) + "," + std::to_string(monto) + ",'Dolares'," + std::to_string(plazo) + ",'" + periodoPago + "','" + fechaCreacion + "','" + fechaVencimiento + "','" + tipoInteres + "'," + std::to_string(interes) + ");";
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
    int rightChoice = 0;
   
    do {
        do {
            std::cout << "1. Agregar CDP" << std::endl;
            std::cout << "2. Retirar CDP" << std::endl;
            std::cout << "3. Desplegar CDP" << std::endl;
            std::cout << "4. Salir" << std::endl;
            std::cin >> opcion;
        } while (opcion < AGREGAR_CDP || opcion > SALIR_CDP|| std::cin.fail());
        
        switch (opcion)
        {
        case AGREGAR_CDP:
            displayMenuOptions();
            break;
        case RETIRAR_CDP:
            ///
            break;
        case DESPLEGAR_CDP:
            ///
            break;
        default:
            break;
        }

    } while (opcion != SALIR_CDP && rightChoice != RETURN);
    return;
}

#define SALIR_OP 5
void CDP::displayMenuOptions() {
    int opcion;
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
            std::cin >> opcion;
        } while (opcion < SIMPLE || opcion > SALIR_OP|| std::cin.fail());

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
    


}


std::string CDP::calcularFechaVencimiento(int plazo){
    //Calcula la fecha de vencimiento de un CDP
    std::string fecha = (this->cliente).getFecha();
    // fecha "mm/dd/yyyy"
    std::string year = fecha.substr(6,4);
    std::string month = fecha.substr(0,2);
    std::string day = fecha.substr(3,2);
    int yearInt = std::stoi(year);
    int monthInt = std::stoi(month);
    int dayInt = std::stoi(day);
    monthInt += plazo;
    if (monthInt > 12){
        yearInt += monthInt / 12;
        monthInt = monthInt % 12;
    }
    std::string newYear = std::to_string(yearInt);
    std::string newMonth = std::to_string(monthInt);
    std::string newDay = std::to_string(dayInt);
    return  newMonth + "/" + newDay + "/" + newYear;
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