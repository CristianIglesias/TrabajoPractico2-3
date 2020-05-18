#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED
using namespace std;
struct Plato{
int ID;
int Tiempo_Prep;
int ID_Restaurante;
int Comision_Restaurante;
int ID_Categoria;
char Nombre[30];
float Costo_Prep,Valor_Venta;
bool Estado;
};
struct Fecha{
int dia;
int mes;
int anio;
};
struct Cliente{
int ID,CodPost;
char Apellido[50],Nombre[50],Mail[50],Domicilio[100];
Fecha FechaNacimiento;
bool estado;
};
struct Pedido{
int ID,IDCLIENTE,IDPLATO,CANTIDAD;
float Precio_Unitario,Valoracion;
Fecha Fecha_Pedido;
int Estado;
};
const char *ArchivoPlatos="platos.dat";
const char *ArchivoClientes="clientes.dat";
const char *ArchivoPedidos="pedidos.dat";
const char *RespaldoPlatos="Platos.bkp";
const char *RespaldoClientes="Clientes.bkp";
const char *RespaldoPedidos="Pedidos.bkp";

#endif // ESTRUCTURAS_H_INCLUDED
