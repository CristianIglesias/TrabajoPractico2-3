#ifndef PROTOTIPOS_H_INCLUDED
#define PROTOTIPOS_H_INCLUDED
using namespace std;
///Funciones Principales.
void MostrarMenuPrincipal();
void MenuReportes();///no se usó?

void MenuConfiguracion();

void GenerarBackups();///Carga los archivos Backup con el contenido actual de los archivos.dat
void BackupPlatos();
void BackupClientes();  ///Cada una carga un vector de su tipo de datos correspondiente y con su archivo, y carga su backup.
void BackupPedidos();

int ContarBKPPlatos();
int ContarBKPPedidos();     ///Cuenta Los registros que están en cada archivo .bkp  y devuelve la cantidad que encuentra.
int ContarBKPClientes();

void RestaurarBackups();        ///Hace la restauración de archivos .bkp a los .dat


bool LeerPlatosBKP(Plato Vec[],int Cant);
bool LeerPedidosBKP(Pedido Vec[],int Cant);     ///Carga los vectores dinamicos con los registros de los archivos .bkp
bool LeerClientesBKP(Cliente Vec[],int Cant);

bool RecuperarPlatos(Plato Vec[],int Cant);
bool RecuperarPedidos(Pedido Vec[],int Cant);   ///Carga los archivos .dat con los registros que tienen cargados los vectores de los archivos .bkp
bool RecuperarClientes(Cliente Vec[],int Cant);

bool RestaurarPlatos();
bool RestaurarPedidos();        ///Cada una carga un vector con los registros en los archivos .bkp y los ingresan en los archivos .dat
bool RestaurarClientes();

///FUNCIONES PLATOS
void MenuPlatos();

void Nuevo_Plato();
void Editar_Plato();
void Listar_PlatoID();
void Platos_porRest();

///Funciones Secundarias Platos
int IngresoPlato(Plato *);///Permite el ingreso de un plato. Con ciertas restricciones. Devuelve -x dependiendo el error.
struct Plato validar_ID_Plato(int );///devuelve plato entero. si no lo encuentra, el ultimo plato del archivo.
void Listar_Plato(Plato);///Si el plato debe mostrarse, lo muestra.
int Buscar_Plato(int);///Busca Posición del Plato dentro del archivo
bool Guardar_Plato(Plato *);///Guarda registro Plato en el archivo.
bool Sobreescribir_Plato(Plato, int);///Guarda Plato modificado en archivo
void MostrarPlato(Plato);///muestra el registro que reciba, si este está habilitado para mostrarse
void MostrarPlatosRest(int);///Muestra todos los platos que pertenezcan a un restaurant y estén habilitados para mostrarse
void MostrarTODOS();///Muestra todos los platos que estén habilitados para mostrarse
bool ValidarIDR(int );///Recibe id de restaurante, devuelve true si existe en el archivo
void EliminarPlato();///Ejecuta los pasos previos a la baja logica
bool BajaLogica_Plato(Plato , int);///Hace la baja Lógica.
void MostrarPrevPlato(Plato Pla);///Muestra el Plato sin algunos campos durante el ingreso de un pedido.
int ContarPlatos();///Cuenta la cantidad de platos en el Archivo
int CargarVecDinPla(Plato VecDinPla[],int CantRegs);///Carga un Vector Dinamico de Platos, para hacer el backup del archivo.
int CargarPLATOSbkp(Plato VecDinPla[],int CantRegs);///Carga el archivo Backup de Platos.

///FUNCIONES  PRINCIPALES CLIENTES;

void MenuClientes();
void Nuevo_Cliente();
void Modificar_ClienteID();
void Listar_ClienteID();
void Listar_Clientes();
void Eliminar_Cliente();

///Funciones Secundarias Clientes.
int IngresoCliente(Cliente *reg );///Permite el ingreso de un Cliente. Con ciertas restricciones. Devuelve -x dependiendo el error.
int Generar_ID_Cliente();///Genera id autonumerico de Cliente
int Ingreso_Y_ValidacionMAIL(Cliente *reg);///Permite el ingreso y validación de un Email.
void Ingreso_Y_ValidacionFECHA(Fecha *aux);///Permite Ingrso y Validación de una fecha
bool Guardar_Cliente(Cliente *reg );///Guarda registro Cliente verificado en el archivo.
struct Cliente ValidarID_Cliente(int );///Busca ID de cliente en el archivo, devuelve el registro completo, si este está habilitado para ser mostrado.
int ContarClientes();///Cuenta la Cantidad de Clientes en el archivo.
bool CargarVecDinCl(Cliente Vec[],int Cant);///Carga Un vector dinamico de Clientes, Para ser ordenado y Mostrado.
void Ordenar_Vec_Din_Cl(Cliente Vec[],int Cant);///Ordena el Vector de Clientes, En orden alfabetico del campo Apellido.
void Mostrar_Todos_Clientes(Cliente Vec[], int Cant);///Muestra todos los clientes habilitados a ser mostrados.
int Buscar_Pos_Cliente(Cliente reg);///Busca la poscion de un cliente dentro del archivo.
bool Sobreescribir_Cliente(Cliente reg, int pos);///Guarda un cliente modificado en la posición en la que estaba.
bool Baja_LogicaCliente(Cliente reg);///Ejecuta la baja Lógica de un cliente.
void MostrarCliente(Cliente );///Muestra los campos de un cliente, si este está habilitado.
int CargarCLIENTESbkp(Cliente VecDinCli[],int CantRegs);///Carga el archivo Respaldo de Clientes.

///Funciones Pedidos!

void MenuPedidos();
void Nuevo_Pedido();
void Modificar_Pedido();
void Listar_Pedido_ID();
void Listar_Pedidos();

///Funciones Secundarias Pedidos
int IngresoPedido(Pedido *reg);///Permite el Ingreso de un pedido, Con ciertas restricciónes, devuelve -x dependiendo el error.
int Guardar_Pedido(Pedido reg);///Guarda el Pedido en el archivo.
struct Pedido Validar_ID_Pedido(int ID);///devuelve el Pedido completo si el id ingresado existe en el archivo.
void MostrarPedido(Pedido reg);///Muestra todos los campos del pedido.
int Generar_ID_Pedido();///Genera ID autonumérico para el pedido a ingresar.
struct Fecha Generar_Fecha_Sistema();///Devuelve struct fecha, armé esta función pensando que cuando se ingresaba el pedido la fecha se determinaba en base al sistema, pero bueno no se usó pobrecita.
int Sobreescribir_Pedido(Pedido reg);/// Guarda el Pedido con el campo estado modificado, en la misma posición en el archivo que se encontraba.
void Mostrar_Todos_Pedidos();///Muestra Todos los pedidos que haya dentro del archivo.
int ContarPedidos();///Cuenta los pedidos dentro del archivo.
int CargarVecDinPed(Pedido VecDinPed[],int CantRegs);///Carga un vector dinamico para guardarse en el backup.
int CargarPEDIDOSbkp(Pedido VecDinPed[],int CantRegs);///Carga el archivo Backup con el vector dinamico que copió el archivo previamente.

#endif // PROTOTIPOS_H_INCLUDED
