#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
using namespace std;
void MostrarMenuPrincipal()
{
    cls();
    setColor(WHITE);
    cout<<"------------------------------------------Menú Principal.--------------------------------------------"<<endl;
    cout<<"-----------------------------------------------------------------------------------------------------"<<endl;
    cout<<"------------------------------------------1)-Platos--------------------------------------------------"<<endl;
    cout<<"------------------------------------------2)-Clientes------------------------------------------------"<<endl;
    cout<<"------------------------------------------3)-Pedidos-------------------------------------------------"<<endl;
    cout<<"------------------------------------------4)-Reportes------------------------------------------------"<<endl;
    cout<<"------------------------------------------5)-Configuración-------------------------------------------"<<endl;
    cout<<"-----------------------------------------------------------------------------------------------------"<<endl;
    setColor(RED);
    cout<<"------------------------------------------0) Salir Del Programa.-------------------------------------"<<endl;
    setColor(WHITE);
    return;
}
void MenuReportes() {};
void MenuConfiguracion()
{

    cls();
    setColor(WHITE);

    int opcion=-1;
    while ( opcion!=0)
    {
        cls();
        cout<<"-.-.-.-.-.-.-.Menú - Configuración. -.-.-.-.-.-.-.-.-.-."<<endl;
        cout<<"-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-."<<endl;
        cout<<"-.-.-.-.-.- .1 Realizar Copia de Seguridad-.-.-.-."<<endl;
        cout<<"-.-.-.-.-.- .2 Restaurar Copia de Seguridad.-.-.-."<<endl;
        cout<<"-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-."<<endl;
        cout<<"-.-.-.-.-.- .0 Salir.                   .-.-.-.-."<<endl;
        cout<<"-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-."<<endl;
        cin>>opcion;

        cls();
        switch(opcion)
        {
        case 1:
        {
            GenerarBackups();

            return;
        }
        break;
        case 2:
        {
            RestaurarBackups();
            return;


        }
        break;
        case 0:
        {} break;
        default:
        {
            cout<<"Opción No valida"<<endl;
        }
        break;
        }

        cout<<"Presione Cualquier tecla para continuar."<<endl;
        anykey();

    }
};

void GenerarBackups()
{
    BackupPlatos();
    BackupClientes();
    BackupPedidos();
}
void RestaurarBackups()
{   bool funciona;
    funciona=RestaurarPlatos();
    if(!funciona)return;
    funciona=RestaurarPedidos();
    if(!funciona)return;
    funciona=RestaurarClientes();
    if(!funciona)return;

}






#endif // FUNCIONES_H_INCLUDED
