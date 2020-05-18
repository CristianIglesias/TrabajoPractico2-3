#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <clocale>///para que permitan los "ñ" o tildes
#include "rlutil.h"
using namespace rlutil;
#include "estructuras.h"
#include "prototipos.h"
#include "Funciones_Platos.h"
#include "Funciones_Clientes.h"
#include "Funciones_Pedidos.h"
#include "funciones.h"
using namespace std;

int main()
{

    setlocale(LC_ALL,"spanish");
    bool salir=false;
    int opcion;
    while(!salir)
    {
        MostrarMenuPrincipal();
        cin>>opcion;
        switch(opcion)
        {
        case 1:
        {MenuPlatos();}
        break;
        case 2:
        {MenuClientes();} break;
        case 3:
        {MenuPedidos();} break;
        case 4:
        {MenuReportes();} break;
        case 5:
        {MenuConfiguracion();} break;
        case 0:
        {
            salir=true;
        }
        break;
        }
        anykey();
        ///final del switch
    }///salida del while*/
    return 0;
}
