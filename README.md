# Sistema Bancario



El presente repositorio contiene el proyecto final del curso IE-0217 del primer semestre de 2024. El objetivo central del programa es emular un sistema bancario que maneje cuentas de varios clientes y realice transacciones, además de incluir un sistema de crédito.
## Compilación Final

Para compilar el programa despues de clonar el repositorio ejecutar lo siguiente en la terminal:

```bash
make
```

Después, si se necesitan instalar dependecias:

```bash
make install
```

Para correr el programa:

```bash
make run
```

Para limpiar el directorio de _bin_:
```bash
make clean
```
## Documentación 
El link a la documentación es el siguiente:
[https://ie0217-proyectofinal.netlify.app](https://ie0217-proyectofinal.netlify.app)
## Cuentas Bancarías.

### ¿Qué es una cuenta bancaría?

Una cuenta bancaría es un espacio virtual donde el cliente interacciona con el banco, permitiendo que el usuario pueda almacenar su dinero en forma de depósito. Además, tiene control del dinero, dando libertad al beneficiario del servicio de gestionar su dinero para realizar pagos, recibiendo ingresos o bien, para efectuar retiros de efectivo.

Una cuenta bancaria se puede comprender como “*un contrato entre el cliente y el banco, donde el titular deposita una cantidad de dinero y la entidad adquiere el compromiso de custodiarlo*”Real, A.(2024). 

Donde la persona usuaria puede hacer uso del dinero en cualquier momento, permitiendo que este pueda realizar diferentes transacciones, como realizar pagos, retiros o ver los movimientos que ha realizado durante cierto periodo de tiempo.

### **Funcionamiento de cuentas bancarias.**
El funcionamiento principal de una cuenta bancaría es permitirle al usuario realizar operaciones y tener acceso a su dinero en cualquier momento, las cuentas pueden materializarse en diferentes tipos como  cuentas corrientes o de ahorro, dando diferentes funcionalidades y la posibilidad de ejecutar diversas transacciones.

### **Tipos de cuentas Bancarias.**
-	**Cuenta Corriente** :  Estas son de las cuentas más utilizadas por los usuarios, ya que permite realizar todas las operaciones que se necesitan a diario, dando una gran flexibilidad con el uso del dinero, es importante considerar que en su mayoría este tipo de cuentas no ofrecen remuneración.
-	**Cuenta de Ahorros**: Este tipo de cuentas, son también muy habituales, ya que permiten generar ahorros a los clientes cada tiempo establecido por el mismo, es un método bastante seguro y fácil. Además, a diferencia de las cuentas corrientes, en la mayoría de bancos, existe cierta remuneración al usuario en relación al saldo guardado por el mismo.
Cabe destacar que la persona puede recuperar su dinero en el momento que lo necesite sin que exista alguna penalización por sacarlo antes del plazo(Términos, que se deben consultar con la entidad bancaria, antes de generar una cuenta).
-	**Nómina**: La nómina es una cuenta bancaria similar a la cuenta corriente, la diferencia es que se tiene**domiciliada la nómina**, es decir, el salario del empleado se deposita directamente en la cuenta bancaria de manera automática cada cierto período, facilitando el proceso. Asimismo, este tipo de cuentas ofrecen algunos beneficios, como eliminar cierta comisiones, entre otras.
-	**Cuenta Remunerada**: Este tipo de cuentas son beneficiosas para algunos clientes, ya que ofrece intereses sobre el saldo depositado en ella que a diferencia de la cuenta corriente, que no genera intereses, este tipo permite que exista un incremento del dinero a través de la acumulación de intereses. El usuario puede tener acceso a su dinero en el momento que lo desee.
-	**Cuentas niños**: Este tipo de cuentas es especialmente utilizada para niños en donde los padres, quieren ir generando un capital para su futuro, son cuentas bastantes limitadas en sus funcionalidades, pero tiene la ventaja de no poseer comisiones.
-	**Cuenta Jóven**: Especialmente dirigida a personas entre 14 y 35 años, poseen comisiones bastante bajas y no tienen limitaciones en sus funciones como la cuenta de niños.	
-	**Cuenta Empresas**: Estas cuentas van dirigidas a empresas, ya que satisfacen necesidades que presentan las mismas, por lo que la entidad bancaria  ofrece ciertos beneficios, como permitir la gestión de pagos e ingresos de una manera fácil y eficiente, así como poder hacer transferencias nacionales e internacionales, entre otras. Cabe mencionar que usualmente tiene comisiones según términos y condiciones del banco.
-	**Cuenta mancumunadas**: Esta es una cuenta particular, que puede tener varios usuarios y existen dos modos:

    - Solidaria: cualquier persona integrante puede realizar tramites sin consentimiento.
    - Mancomunada: Debe tenerse el consentimiento de todos los integrantes para realizar una transacción.

-	**Cuenta moneda extranjera**: Este tipo de cuentas va dirigido a usuarios en que necesitan hacer uso de distintas divisas, es útil para esos clientes que realizan operaciones internacionales.

### **Dualidad de cuentas:**
Es importante mencionar, que un cliente puede poseer hasta dos cuentas bancarias, una en colones y otra en dólares, con el fin de que pueda gestionar sus ahorros con la entidad bancaria. Además, de poder tener certificados de depósito a plazo **CDP**.


### ¿Qué es Certificados de depósito a plazo **(CDP)**?
Un CDP es ”*un depósito que se pacta entre el banco y el dueño de los fondos, a un período de tiempo determinado*”Romero, C.(2022). Con base a lo anterior, este depósito que se realiza tiene una tasa de interés que está relacionada al monto y al período de tiempo, es importante saber que este tipo de depósitos no permite retiros ni incrementos de saldo y para retirarlo el usuario debe esperar a la fecha establecida.


### Operaciones Disponibles

Los usuarios, tienen acceso a diversas operaciones, tales como retiro, depósito, transferencias, pagos, entre otras. En esta sección se hará una descripción de las diferentes operaciones que se pueden realizar en las cuentas.

#### Retiro

Un retiro es cuando un cliente del banco, retira su dinero de su cuenta bancaria, esto se puede hacer en línea, mediante un cajero autómatico o bien, en el banco físico.

#### Depósito

El depósito es más bien cuando el usuario agrega dinero a su cuenta bancaria, esto puede hacerse mediante el uso de dinero en efectivo, cheque o mediante algún dispositivo.

#### Transferencias entre cuentas a otros

Esta operación lo que se encarga es de permitir al usuario hacer una tranferencia de fondos de una cuenta bancaria a otra del mismo banco o externo a a estede, este trámite se puede ejecutar en línea o en la sucursal.

#### Abonos a préstamos propios

Los abonos a préstamos propios, es cuando el cliente es el responsable del préstamo y realiza un pago del mismo, ya sea hipotecario o préstamo personal. La idea de realizar esta operación es reducir el saldo pendiente del préstamo como generar pago de intereses.

#### Abonos a préstamos de otras personas

Es en su esencia igual al abono de préstamos propios, pero su diferencia pricipal es que el pago se realiza al prétamo de otras personas.

## Registro de transacciones
El registro de transacciones es de vital importancia dentro de un sistema financiero, este vuelve al sistema más seguro, transparente y facilita la realización de análisis y reportes. Esta funcionalidad debe incluir algunos datos mínimos para asegurar su funcionalidad:
1.	Momento exacto en que se realizó la transacción, fecha y hora.
2.	El tipo de transacción ya sea un depósito, retiro, transferencia o pago de préstamo.
3.	Cantidad de dinero involucrada en la transacción.
4.	Identificador único del usuario que realizó la transacción.
5.	Identificador único de la transacción.
6.	Razón o detalles adicionales sobre la transacción.


## Prestamos

La Asociación Bancaria Costarricense (2011) menciona que el crédito es una forma de financiamiento del sistema financiero que permite al usuario adquirir bienes y servicios a cambio de devolver el monto prestado bajo los términos de plazo e intereses establecidos en el contrato de crédito.

En el desarrollo de un sistema de gestión bancaria en C++, es fundamental comprender y gestionar conceptos clave como la tasa de interés y los diversos tipos de préstamos. En este proyecto, abordaremos la implementación de estos conceptos en C++, asegurando que el sistema sea robusto, eficiente y fácil de usar para los usuarios finales.

**Palabras Clave**

- **Intereses corrientes**: Tasa de interés que se debe pagar por el monto prestado.

- **Intereses moratorios**: Intereses cobrados por atrasos en el pago.

- **Plazo**: Tiempo acordado para saldar la deuda.

- **Cuota**: Suma de dinero que se debe pagar periódicamente, compuesta por el interés más la amortización del capital.

- **Comisiones**: Pagos que se deben realizar para el estudio del banco antes de desembolsar el crédito.

- **Tasa nominal**: Según Trigueros (2021), es el monto que el banco declara como interés a pagar. Es un valor estático que no considera las fluctuaciones monetarias ni la frecuencia de capitalización del interés.

- **Tasa efectiva**: Es la que durante el periodo de pago genera al banco sus intereses capitalizables, similar al interés compuesto


### **Requisitos para el crédito**

El banco evalúa:

- Capacidad de pago: Si la persona cuenta con un ingreso estable para cumplir con los compromisos de pago.

- Garantía: Respaldo que obtiene el banco en caso de incumplimiento del contrato. Puede ser hipotecaria, fiduciaria o prendaria.

- Historial crediticio: El banco solicitará consultar el historial crediticio del solicitante en la central de información crediticia de la Superintendencia General de Entidades Financieras para verificar su responsabilidad en el pago de créditos. Una buena calificación se obtiene si se pagan las deudas en los plazos establecidos.


### **Modalidades**

- Crédito directo: Préstamo común, donde la entidad financiera otorga una cantidad de dinero al solicitante bajo las condiciones de monto, plazo, garantía y tasas de interés establecidas en el contrato de préstamo.

- Línea de crédito: El banco otorga al deudor un monto que puede utilizar total o parcialmente y luego abonar durante un tiempo determinado.

- Línea de crédito revolutivo: Funcionamiento básico de las tarjetas de crédito, donde el banco autoriza una cantidad de dinero que el solicitante puede usar hasta su límite y luego reiniciar el monto si paga el principal de la deuda.


### **Tipos de tasas de interés**
La tasa de interés es el porcentaje que se cobra sobre un monto prestado en un determinado plazo de tiempo. Según el contexto en que se trate, se pueden presentar variaciones en cómo se aplican estos intereses:

- Tasa de interés fija:  El porcentaje que se cobra sobre el dinero prestado, se mantiene constante durante todo el periodo de repago.

- Tasa de interés variable: La tase de interés puede variar durante el periodo de repago, esto sujeto a un determinado índice de referencia, por lo que el interés puede aumentar o disminuir.
(Visa, s. f.)

- Tasa combinada: La tasa permanece fija durante una parte del plazo y luego es variable.


La tasa de interés es simple cuando el interés que se obtiene al vencimiento no se suma al capital para generar nuevos intereses. Por lo que se calcula siempre sobre el capital inicial. Su fórmula es:

$$
I=P×r×t

$$
Donde:
- 𝐼 es el interés total.
- 𝑃 es el monto prestado.
- 𝑟 es la tasa de interés (expresada en forma decimal).
- 𝑡 es el tiempo en años.


En la tasa interés compuesto, los intereses generados durante cada período se suman al capital inicial, esto hace que se produzcan nuevos intereses. En este caso el capital aumenta al final de cada período y, por lo tanto, el interés calculado sobre un capital mayor también incrementa. Este fenómeno aunque puede ser muy beneficioso en productos de inversión que generan rentabilidad, también puede ser muy perjudicial en los créditos, ya que la deuda puede crecer de manera exponencial. Su fórmula es:

$$
A=P×(1+ r/n)^{(n×t)}
$$

Donde:
- 𝐴 es el monto total acumulado.
- 𝑃 es el monto inicial.
- 𝑟 es la tasa de interés (expresada en forma decimal).
- 𝑛 es el número de veces que se capitaliza el interés por período.
- 𝑡 es el tiempo en años.

(Waghorn P., 2020).




### **Garantías y Tipos de Crédito**
**Prestamos**

*Préstamo personal*

Los préstamos personales son los más habituales, en estos la entidad bancaria presta una determinada cantidad de dinero, la cual tiene que ser devuelta por el prestatario más los intereses en un determinado plazo de tiempo (Coopelianza, s. f.-a). Este tipo de préstamos son bastante prácticos para adquirir productos o servicios urgentes, pues no requieren de tantos tramites ni requisitos, además también ayudan a establecer un buen historial crediticio.

*Préstamo prendario*

Un préstamo prendario es similar a un préstamo personal, con la diferencia de que en este el prestatario utiliza un bien mueble como garantía, a este objeto físico se le denomina prenda, he de ahí el nombre de esta operación (Santander, s. f.).  Este tipo de préstamo presenta algunas ventajas sobre el préstamo personal, pues los términos de este se acuerdan de acuerdo con el bien prendando. 

*Préstamo hipotecario*

Los prestamos de tipo hipotecario son concedidos específicamente para la compra de un inmueble, el cual a su vez será la garantía en caso de incumplimiento por parte del prestatario (Coopelianza, s. f.-b).  Debido al costo 	que tienen las viviendas, estos prestamos son de mediano y largo plazo, y son bastante útiles pues la propiedad se puede habitar rápidamente y le evita al prestatario el pago de un alquiler.

**Garantía**

- Hipotecaria: Se pone como garantía un bien inmueble, como un terreno o edificio. Se utiliza para la construcción de una casa, compra de un lote, remodelaciones y compra de viviendas. Es una inversión a largo plazo con tasas de interés menores debido a la garantía de alto costo.

- Prendaria: Se pone como garantía un bien mueble, como un vehículo o cosecha. Se usa para adquirir autos, maquinaria para empresas o financiar inversiones como cosechas. Tiene tasas de interés relativamente bajas y se piensa para un mediano plazo.

- Personales: Normalmente tienen de garantía a un fiador, que se obliga a pagar la deuda en caso de incumplimiento del deudor. Permiten adquirir crédito sin justificar el destino del dinero y tienen trámites rápidos. No obstante, sus tasas de interés son más altas y se piensan para un corto plazo.

A continuación se presenta un cuadro con la comparación de las tasa de distintas entidades bancarias para los diferentes tipos de crédito:

| **Tipo de Crédito** 	| **Institución Bancaria** 	| **Tasa en Colones** 	| **Tasa en dólares** 	|
|---	|---	|---	|---	|
| Hipotecario 	| CoopeAnde 	| 8.5% Tasa fija durante 3 años Tasa de interes total anual (TITA) 10.09% 	| 7.5% Tasa fija durante 7 años Tasa de interés total anual (TITA) en  dólares de 8.39%. 	|
| Hipotecario 	| Davivienda 	| 35 cuotas mensuales a tasa fija de  11.25% TITA 35-239 cuotas de  tasa variable determinada  por la tasa básica pasiva  del Banco Central de Costa Rica.  Tasa mínima de 9.40 % 	| 35 cuotas mensuales a tasa fija de 8.50% TITA 35-239 cuotas de tasa variable  determinada por la tasa del New York Prime  vigente al momento del desembolso. Mínima de 7.5% 	|
| Prendario 	| CoopeAnde 	| 11.50% fijo durante 2 años.  Tasa de interés total anual (TITA) desde 16.34% 	|  6.50% fija durante 2 años  Tasa de interés total anual de 11.08% 	|
| Prendario 	| BAC 	| 8.30% para compra de vehículo 	| 7.45% para compra de vehículo 	|
| Personal(Garantía  Hipotecaria) 	| CoopeAnde 	| 13% fijo durante 3 años. Tasa de interés total anual (TITA) desde 14.58% 	| NA 	|
| Personal(Asociado a Activos) 	| CoopeAnde 	| Interés nominal desde el 15 %. Tasa de interés total anual (TITA) desde 16.3 	| NA 	|

Fuentes: [Davivienda](https://bienvenido.davivienda.cr/wps/wcm/connect/personasCR/eb9fbfc4-f3be-4ece-af28-72eccbd9cde8/Folleto_explicativo_Hipoteca.pdf?MOD=AJPERES&CVID=n.S7N74) , [CoopeAnde](https://www.coopeande1.com/productos-servicios/credito-prendario-dolares) , [BAC](https://www.baccredomatic.com/es-cr/personas/prestamos?categoria=vehiculos&bacid=CRIN-MULT-ACF-000007-GL-AW-PR-GG-A8-SR-00000/SEARCH-VEL-INSTITUCIONAL-VENTAS&gad_source=1&gclid=CjwKCAjw9cCyBhBzEiwAJTUWNbd7czAkO4HtSXMnLdln5kKmobKdZs1DH_5MHKPix7pVJAUPiRxTmxoCpvYQAvD_BwE)

### **¿Cómo funciona la cuota?**

Según (INA, 2020), esta se determina en función del monto de la deuda, la tasa de interés y el plazo. Las tasas de interés variables se actualizan según un índice de referencia, como la tasa básica pasiva establecida por el Banco Central de Costa Rica. Cualquier variación en este parámetro modifica la tasa de interés y, por tanto, la cuota a pagar. Este tipo de tasa es usual en créditos hipotecarios o prendarios. En créditos personales o de entidades no bancarias, suelen utilizarse tasas de interés fijas.

*La cuota mensual se define como cada uno de los pagos mensuales que hace el comprador para amortizar la deuda y pagar los intereses generados por el financiamiento*

(Artículo 2 del Decreto Ejecutivo 37899-MEIC, reglamento a la Ley N.7472, Ley de Promoción de la Competencia y Defensa Efectiva del Consumidor).

La amortización, o aporte al capital, es el pago del monto prestado. Cuando se realiza un pago, la entidad actualiza el saldo. La amortización comienza igual al monto prestado y disminuye a cero al final del plazo. La cuota se compone de la amortización más los intereses. Al final del crédito, el deudor habrá pagado la cantidad debida más los intereses.
Al inicio del crédito, la porción de interés es mayor que la amortización del capital. A medida que avanza el plazo, esta relación se invierte. Un deudor puede hacer pagos adicionales especificando que se destinen a la amortización, reduciendo así el saldo y los intereses. Si no se especifica, el adelanto se considera un pago de la cuota, cubriendo los intereses del siguiente plazo. En caso de morosidad, el siguiente pago cubrirá primero los intereses y luego la amortización.

# Diseño de la implementación

La implementación del proyecto se basa en un modelo modular con el objetivo de facilitar el trabajo colaborativo dentro del grupo. Se aprovecharán los conceptos de programación orientada a objetos para abstraer las distintas entidades que conforman el sistema bancario como instancias de clases, permitiendo así que interactúen entre sí. 

![UML Clases](https://github.com/Msolis314/Clases/blob/main/ClasesProyectoIE-0217.jpg)

Primero, se propone crear una clase abstracta que contenga métodos base, como la validación de datos y consultas al historial de la base de datos, que deben ser compartidos por diferentes entidades en el programa. Esta clase también incluirá métodos que deberán ser redefinidos por sus diferentes subclases; por ejemplo, el método de transacción, que debe adaptarse según se trate de un préstamo o de la actividad en una cuenta. Además, esta clase definirá cómo se accederá a la tabla que contiene la información de las tasas de interés, el cambio del dólar y otros datos relevantes para la ejecución del programa, los cuales pueden ser modificados externamente.

Las clases hijas de la entidad bancaria son los objetos principales que interactuarán dentro del sistema. El banco representa concretamente la interfaz donde se pueden agregar nuevos clientes, realizar operaciones entre usuarios y gestionar los pagos de préstamos. Un banco puede tener uno o más clientes, quienes constituyen otra clase dentro de la familia bancaria. Cada cliente tiene su propio identificador y métodos que le permiten gestionar sus cuentas, las cuales representan otra clase hija de la entidad bancaria. Estas cuentas reflejan los montos de dinero en dólares o colones que posee el cliente en el banco. Esta clase debe ser capaz de acceder a las cuentas del cliente en base a su identificación y realizar operaciones en ellas.

Otro aspecto relevante son los préstamos, ya que cada cliente puede tener uno o más préstamos en colones o dólares, cada uno con sus propios métodos y características. Se sigue un enfoque similar al definir una clase que gestione el acceso a la base de datos con esta información, identificando el id único de cada préstamo y el usuario al que pertenece.

Cabe señalar que este diseño se enfoca principalmente en manejar la información de los usuarios y el programa a través del sistema de bases de datos. Se busca mejorar la mantenibilidad a largo plazo del código y facilitar el proceso de colaboración, ya que la mayor parte del trabajo se centrará en cómo interactuar con las tablas de la base de datos y no en coordinar los datos dentro del código.
Finalmente, se espera utilizar, a lo largo del desarrollo e implementación, diversas herramientas aprendidas durante el curso. Además de la programación orientada a objetos, será necesario emplear memoria dinámica, estructuras de datos, un uso eficiente de los recursos computacionales y un manejo adecuado de excepciones para cumplir satisfactoriamente con los objetivos del proyecto.
El esquema de la base de datos se presenta a continuación:

![Esquema Base de Datos](https://github.com/Msolis314/Clases/blob/main/Bases%20de%20Datos.jpg)

## Cronograma

| **Fecha**      | **Entrega**| **Persona**         |
|----------------|------------|---------------------|
| viernes 24 de mayo | Investigación                       | Todos los integrantes           |
| sábado 25 de mayo  | Diagramas y Estructura del Proyecto | Todos los integrantes           |
| domingo 26 de mayo | Presentación                        | Todos los integrantes           |
| lunes 27 de mayo   | Presentación Primera Fase           | Todos los integrantes           |
| 5 de junio         | Header files de las clases y menu inicial | Todos los integrantes, Mariana menu inicial |
| viernes 7 de junio | Definir estructura de las bases de datos | Mariana                |
| lunes 10 de junio  | Definición de la clase Entidad Bancaria  | Esteban                |
| lunes 10 de junio  | Definición de la clase cliente          | Charlie                |
| lunes 10 de junio  | Definición de la clase banco            | Mariana                |
| martes 11 de junio | Definición de cuenta                    | Charlie                |
| viernes 14 de junio| Transacciones                           | Esteban, Mariana       |
| viernes 14 de junio| CDP                                     | Charlie                |
| sábado 15 de junio | Préstamo fase inicial                   | Todos los integrantes  |
| lunes 17 de junio  | Presentación del Avance                 | Todos los integrantes  |
| miércoles 19 de junio | Préstamo fase final                  | Todos los integrantes  |
| viernes 21 de junio| Interfaz con el usuario del programa    | Mariana                |
| viernes 28 de junio| Arreglos finales                        | Todos los integrantes  |
| jueves 4 de julio  | Presentación Final                      | Todos los integrantes  |

## Avance 

En el presente avance se completo la definición de la base de datos, la implementación de las clases Cliente, Banco y Entidad Bancaria y la creación del sistema de Login.

### Base de Datos
Debido a tiempo y cuestiones de implementación se tomó la desición de utilizar una base local (Squlite3) en vez de una remota para el manejo de los datos. Apesar que se pierde la opción de escalabilidad para el proyecto y la coloaboración simultanea en la base de datos se consideró que enfocarse en la modularidad y funcionamiento del código era de mayor relevancia. Especialmente considerando la importancia de que todos los integrante colaboren de forma independiente en una parte del proyecto. 
Además al esquema propuesto para la base de datos se agrego una nueva tabla con el objetivo de guardar las contraseñas de los clientes y su llave (Salt) de desencriptación. La encriptación de contraseñas se realizan mediante la librería `Openssl`. Los pasos para la encriptación se explican a continuación:

1. Generar un `SALT`, un valor único que garantiza que aunque dos personas tengan la misma contraseña su valor encriptado sea distinto. 
2. Hashear la contraseña con el método `PBKDF2`.
3. Guardar la contraseña encriptada en conjunto con el SALT asociados al ID del cliente en la tabla PASSWORDS. 
4. Para verificar una contraseña se le pide al usuario una entrada, se busca con el id su SALT en la tabla PASSWORDS y se encripta la entrada con dicho SALT. La contraseño es correcta si es igual a la encriptada dentro de la tabla. 

En la siguiente imagen se denota como luce la tabla PASSWORDS que contiene únicamente valores encriptados:

![TablaPasswords](https://github.com/Msolis314/Clases/blob/main/varios/PASSSS.png)

El nuevo esquema de la base de datos es el siguiente:

![Esquema Base de Datos Avance](https://github.com/Msolis314/Clases/blob/main/varios/Bases%20de%20Datos%20(3).jpg)

### Login

Para la implementación del sistema de _Login_ se procedió como detalla el diagrama de flujo siguiente:

![Diagrama _Login_](https://github.com/Msolis314/Clases/blob/main/varios/Flowchart.jpg)

**Ejemplo "Happy Path"**

A continuación se detallan imágenes del uso del sistema de login si se sigue el camino sin entradas problemáticas. 
- Menu inicial 
![https://github.com/Msolis314/Clases/blob/main/varios/MainEntry.png](https://github.com/Msolis314/Clases/blob/main/varios/MainEntry.png)

- Menu del banco
![https://github.com/Msolis314/Clases/blob/main/varios/BancoMenu.png](https://github.com/Msolis314/Clases/blob/main/varios/BancoMenu.png)

- Registro de usuario
![https://github.com/Msolis314/Clases/blob/main/varios/Registro.png](https://github.com/Msolis314/Clases/blob/main/varios/Registro.png)

**Casos Límite**

- Opción invalida en algún menu.

![InvalOP](https://github.com/Msolis314/Clases/blob/main/varios/InvalidOp.png)

- Cliente no existe en el sistema de login, se despliegan las opciones de la imagen

    ![https://github.com/Msolis314/Clases/blob/main/varios/ClienteNoexiste.png](https://github.com/Msolis314/Clases/blob/main/varios/ClienteNoexiste.png)

- Nombre inválido en el inicio de sesión:

    ![https://github.com/Msolis314/Clases/blob/main/varios/InvalidName2.png](https://github.com/Msolis314/Clases/blob/main/varios/InvalidName2.png)

## Compilación 

Se necesitan de algunas librerías adicionales a las estandar para ejecutar el programa. Se facilitó de un script que se encarga de descargar estás librerías en el sistema operativo linux. Seguir los siguientes pasos para completar la instalación: 
1. Dar permisos de ejecución al script

    ```bash
    chmod +x install.sh
    ```

2. Correr

    ```bash
    ./install.sh
    ```

Para está etapa se realizó un make file dentro del directorio src debido a que no todos los archivos estaban listos en un momento determinado. Para compilar el programa entrar a src y ejecutar:

```bash
make
```
Para ejecutar:

```bash
./main.exe
```

## Referencias 
Asociación Bancaria Costarricense. (2011). Credito y 
Garantías. Biblioteca Financiera Virtual.

BBVA. (s. f.). Qué es un préstamo financiero: tipos y diferencias con un crédito. BBVA. https://www.bbva.com/es/salud-financiera/que-es-un-prestamo-financiero-tipos-y-diferencias-con-un-credito/ 

Coopelianza. (s. f.-a). Préstamos hipotecarios: ¿Qué son y en qué casos aplican? https://coopealianza.fi.cr/prestamos-hipotecarios-que-son-y-en-que-casos-aplican/ 

Coopelianza. (s. f.-b). ¿Qué es y para qué se utiliza un préstamo personal? https://coopealianza.fi.cr/que-es-y-para-que-se-utiliza-un-prestamo-personal/ 


INA. (2020). Tipos de créditos y componente de la cuota. MEIC.

Santander. (s. f.). ¿Cuál es la diferencia entre un Préstamo Personal y un Préstamo Prendario. https://ayuda.santander.com.ar/en/K7CL2L27ZN-1/article/D8RBNIZ1JJ-cual-es-diferencia-entre-prestamo-personal-prestamo-prendario/ 

Meneses, C.(2018). *Análisis Financiero de Operaciones Bancarias*.Universidad de Valladolid,Facultad de Ciencias Económicas y
Empresariales. Recuperado de:
https://uvadoc.uva.es/bitstream/handle/10324/33994/TFG-E-463.pdf?sequence=1

Real, A.(2024). *Cuenta Bancaria*. recuperado de:
https://economiasimple.net/cuenta-bancaria.html

Romero, C.(2022).*Todo lo que necesitás saber sobre los certificados de depósito a plazo fijo*. Recuperado de:
https://plataconplatica.com/todo-lo-que-necesitas-saber-sobre-los-certificados-de-deposito-a-plazo-fijo/


Trigueros, G. (2021). TASAS DE INTERES NOMINAL Y EFECTIVA.

Visa. (s. f.). ¿Qué es y cómo funcionan los intereses? https://www.visa.co.cr/dirija-su-negocio/pequenas-medianas-empresas/notas-y-recursos/productividad/funcion-interes.html 

Waghorn P., G. (2020, mayo). INTERÉS SIMPLE Y COMPUESTO. colegioconcepcionsanpedro.cl. https://www.colegioconcepcionsanpedro.cl/wp-content/uploads/2020/05/MATEM%C3%81TICA-4%C2%BAC-G.WAGHORN-1-al-5-DE-JUNIO.pdf


