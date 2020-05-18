#ifndef FUNCIONES_PEDIDOS_H_INCLUDED
#define FUNCIONES_PEDIDOS_H_INCLUDED
void MenuPedidos()
{
    cls();
    setColor(WHITE);

    int opcion=-1;
    while ( opcion!=0)
    {
        cls();
        cout<<"-.-.-.-.-.-.-.Menú - Pedidos. -.-.-.-.-.-.-.-.-.-."<<endl;
        cout<<"-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-."<<endl;
        cout<<"-.-.-.-.-.-  .1 Nuevo Pedido.            .-.-.-.-."<<endl;
        cout<<"-.-.-.-.-.-  .2 Modificar Pedido.        .-.-.-.-."<<endl;
        cout<<"-.-.-.-.-.-  .3 Listar Pedido x ID.      .-.-.-.-."<<endl;
        cout<<"-.-.-.-.-.-  .4 Listar Todos los Pedidos..-.-.-.-."<<endl;
        cout<<"-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-."<<endl;
        cout<<"-.-.-.-.-.-  .0 Salir.                   .-.-.-.-."<<endl;
        cout<<"-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-."<<endl;
        cin>>opcion;

        cls();
        switch(opcion)
        {
        case 1:
        {
            Nuevo_Pedido();
        }
        break;
        case 2:
        {
            Modificar_Pedido();
        }
        break;
        case 3:
        {
            Listar_Pedido_ID();
        }
        break;
        case 4:
        {
            Listar_Pedidos();
        }
        break;
        case 0:
        {
            return;
        }
        break;
        case 99:
        {
            FILE *P;
            P=fopen(ArchivoPedidos,"wb");
            fclose(P);
        }
        break;
        }///finaldelswitch
        cout<<"Presione Cualquier tecla para continuar."<<endl;
        anykey();

    }///Final del while
}

void Nuevo_Pedido()
{
    cout<<"Pedido Nuevo!"<<endl;
    int error;
    Pedido aux;
    error=IngresoPedido(&aux);
    if(error<0)
    {
        cout<<"código de error "<<error<<" Presione cualquier tecla para continuar."<<endl;
        anykey();
        return;
    }
    error=Guardar_Pedido(aux);
    if(error<0)
    {
        cout<<"Código de error "<< error<<" Presione Cualquier tecla para continuar."<<endl;
        anykey();
        return;
    }
    cout<<"El pedido se Guardó Correctamente en el archivo."<<endl;
};

void Modificar_Pedido()
{
    int ID,error;
    Pedido reg;
    cout<<"A Modificar El estado del Pedido"<<endl;
    cout<<"Ingrese el ID del pedido a Modificar"<<endl;
    cout<<"ID :";
    cin>>ID;
    if(ID<0||ID%1!=0)
    {
        cout<<"Un ID entero y Positivo, por favor"<<endl;
        return;
    }
    reg=Validar_ID_Pedido(ID);
    if(reg.ID!=ID)
    {
        cout<<"Código de error "<<reg.ID<<" Presione Cualquier tecla para continuar.";
        anykey();
        return;
    }
    cout<<"El Pedido a Modificar es el siguiente: "<<endl;
    MostrarPedido(reg);
    cout<<"Ingrese el estado actual del pedido...(1 en progreso- 2 en preparación - 3 Completado)"<<endl;
    cout<<"Estado : ";
    cin>>reg.Estado;
    if(reg.Estado<0||reg.Estado>3)
    {
        cout<<"Estado invalido."<<endl;
    }
    error=Sobreescribir_Pedido(reg);
    if(error<0)
    {
        cout<<"código de error "<<error<<" Presione cualquier tecla para continuar."<<endl;
        anykey();
        return;
    }
    cout<<"El pedido se Sobreescribió Correctamente en el archivo."<<endl;

};
void Listar_Pedido_ID()
{
    int id;
    Pedido reg;
    cout<<"Ingrese el ID de pedido que desea ver."<<endl;
    cout<<"ID :"<<endl;
    cin>>id;
    if(id<0||id%1!=0)
    {
        cout<<"Un ID entero y positivo Por favor."<<endl;
        return;
    }
    reg=Validar_ID_Pedido(id);
    MostrarPedido(reg);

};
void Listar_Pedidos()
{
    cout<<"Mostrando Todos los Pedidos:"<<endl;
    Mostrar_Todos_Pedidos();



};
///Funciones Secundarias.

int IngresoPedido(Pedido *reg)
{
    int id,cant;
    Plato Pla;
    Cliente Cli;
    Fecha aux;
    id=Generar_ID_Pedido();
    if (id<0)
        return-1;
    cout<<"ID : "<<id<<endl;
    reg->ID=id;
    cout<<"Ingrese ID Cliente :";
    cin>>reg->IDCLIENTE;
    Cli=ValidarID_Cliente(reg->IDCLIENTE);
    if(Cli.ID!=reg->IDCLIENTE||Cli.estado==false)
    {
        cout<<"El Cliente No está registrado."<<endl;
        cout<<"Presione Cualquier tecla para continuar."<<endl;
        anykey();

        return-2;
    }
    cout<<"Hola! "<<Cli.Nombre<<" Contanos que Numero de Plato querías!"<<endl;
    cout<<"Ingrese ID Plato :";
    cin>>reg->IDPLATO;
    Pla=validar_ID_Plato(reg->IDPLATO);
    if(Pla.ID!=reg->IDPLATO||Pla.Estado==false)
    {
        cout<<"El Plato no existe en el archivo."<<endl;
        cout<<"Presione Cualquier tecla para continuar."<<endl;
        anykey();
        return -1;
    }
    cout<<"El Plato sería este."<<endl;
    MostrarPrevPlato(Pla);
    reg->Precio_Unitario=Pla.Valor_Venta;
    cout<<"Ingresese la Cantidad De platos que iba a pedir."<<endl;
    cout<<"Cantidad :";
    cin>>reg->CANTIDAD;
    if(reg->CANTIDAD<0||reg->CANTIDAD%1!=0)
    {
        cout<<"Una cantidad Entera y Positiva por favor"<<endl;
        return -3;
    }
    cout<<"Bueno, El precio Final del pedido sería este :$ "<<reg->Precio_Unitario*reg->CANTIDAD<<endl;
    cout<<"Fecha: ";
    Ingreso_Y_ValidacionFECHA(&aux);
    if(aux.dia<0)
    {
        cout<<"Fecha no valida."<<endl;
        return -2;
    }
    reg->Fecha_Pedido=aux;
    cout<<"Como te va gustando la app?"<<endl;
    cout<<"Calificanos del 0(muy mal!) al 10(super satisfeche!)"<<endl;
    cin>>reg->Valoracion;
    if(reg->Valoracion<0||reg->Valoracion>10)
    {
        cout<<"Un Numero del 0 al 10 porfis."<<endl;
        return -4;
    }
    reg->Estado=1;
    return 1;

};
int Guardar_Pedido(Pedido reg)
{
    bool funco;
    FILE *P;
    P=fopen(ArchivoPedidos,"ab");
    if(P==NULL)
    {
        cout<<"No se pudo abrir el archivo";
        return-1;
    }
    funco=fwrite(&reg,sizeof(Pedido),1,P);
    if(funco)
    {
        fclose(P);
        return 1;
    }
    fclose(P);
    cout<<"No se pudo escribir en el archivo.";
    return-2;
}
int Generar_ID_Pedido()
{
    int CantRegs, id;
    FILE *P;
    P=fopen(ArchivoPedidos,"rb");
    if(P==NULL)
    {
        cout<<"No se pudo abrir el archivo";
        return -1;
    }
    fseek(P,0,2);
    CantRegs=ftell(P)/sizeof(Pedido);
    id=CantRegs+1;
    return id;
}
struct Fecha Generar_Fecha_Sistema()
{
    Fecha fe;
    time_t t;
    t=time(NULL);
    struct tm *fech;
    fech=localtime(&t);
    fe.anio=fech->tm_year+1900;
    fe.dia=fech->tm_mday;
    fe.mes=fech->tm_mon+1;
    return fe;
};

struct Pedido Validar_ID_Pedido(int ID)
{
    Pedido reg;
    FILE *P;
    P=fopen(ArchivoPedidos,"rb");
    if(P==NULL)
    {
        cout<<"No se pudo abrir el archivo";
        reg.ID=-1;
        return reg ;
    }
    while(fread(&reg, sizeof(Pedido),1,P)==1)
    {
        if(reg.ID==ID)
        {
            return reg;
        }
    }
    cout<<"No se encontró el ID en el archivo"<<endl;
    fclose(P);
    return reg;
}

void MostrarPedido(Pedido reg)
{
    if(reg.Estado==1||reg.Estado==2||reg.Estado==3)
    {
        cout<<"|-----------------------------------------"<<endl;
        cout<<"|ID Pedido       : "<<reg.ID<<endl;
        cout<<"|ID Cliente      : "<<reg.IDCLIENTE<<endl;
        cout<<"|ID Plato        : "<<reg.IDPLATO<<endl;
        cout<<"|Fecha del Pedido: "<<reg.Fecha_Pedido.dia<<"/"<<reg.Fecha_Pedido.mes<<"/"<<reg.Fecha_Pedido.anio<<endl;
        cout<<"|Precio Plato    : "<<reg.Precio_Unitario<<endl;
        cout<<"|Cantidad Platos : "<<reg.CANTIDAD <<endl;
        cout<<"|Precio Final    : "<<reg.CANTIDAD*reg.Precio_Unitario<<endl;
        cout<<"|Valoración      : "<<reg.Valoracion<<endl;
        cout<<"|Estado          : "<<reg.Estado<<endl;
        cout<<"|-----------------------------------------"<<endl;
        return;

    }
    return;
};
int Sobreescribir_Pedido(Pedido reg)
{
    FILE *P;
    int error;
    P=fopen(ArchivoPedidos,"ab+");
    if(P==NULL)
    {
        cout<<"No se pudo abrir el archivo";
        return -1;
    }
    fseek(P,(sizeof(Pedido)*reg.ID)-1,0);
    error=fwrite(&reg,sizeof(Pedido),1,P);
    if(error!=1)
    {
        cout<<"No se pudo escribir en el archivo"<<endl;
        fclose(P);
        return -2;
    }
    fclose(P);
    return 1;
};
void Mostrar_Todos_Pedidos()
{
    Pedido reg;
    FILE *P;
    int cantPedidos;
    cantPedidos=ContarPedidos();
    if(cantPedidos==0)
    {
        cout<<"No hay pedidos cargados para mostrar "<<endl;
        return;
    }

    P=fopen(ArchivoPedidos,"rb");
    if(P==NULL)
    {
        fclose(P);
        cout<<"No se pudo abrir el archivo";
        return;
    }
    while(fread(&reg,sizeof(Pedido),1,P)==1)
    {
        MostrarPedido(reg);
    }
    fclose(P);
    return;
}
int ContarPedidos()
{
    int cantReg=0;
    Pedido aux;
    FILE *p;
    p=fopen(ArchivoPedidos,"rb");
    if(p==NULL)
    {
        fclose (p);
        return-1;
    }
    fseek(p,0,2);
    cantReg=ftell(p)/sizeof(Pedido);
    fclose(p);
    return cantReg;
}

int CargarVecDinPed(Pedido VecDinPed[],int CantRegs)
{
    FILE *P;
    P=fopen(ArchivoPedidos,"rb");
    if(P==NULL)
    {
        fclose (P);
        return-1;
    }
    if(fread(VecDinPed,sizeof(Pedido),CantRegs,P)!=CantRegs)
    {
        fclose (P);
        return-2;
    }
    fclose(P);
    return 1;
}
int CargarPEDIDOSbkp(Pedido VecDinPed[],int CantRegs)
{
    FILE *p;
    p=fopen(RespaldoPedidos,"wb");
    if(p==NULL)
    {
        fclose(p);
        return-1;
    }
    if(fwrite(VecDinPed,sizeof(Pedido),CantRegs,p)!=CantRegs)
    {
        fclose(p);
        return-2;
    }
    fclose(p);
    return 1;
}
void BackupPedidos()
{

    int CantRegs,error;
    Pedido *VecDinPed;
    CantRegs=ContarPedidos();
    if(CantRegs<1)
    {
        cout<<"Codigo de error "<<CantRegs<<" Lo sentimos Rey."<<endl;
        return;
    }
    VecDinPed=(Pedido*)malloc(CantRegs*sizeof(Pedido));
    error=CargarVecDinPed(VecDinPed,CantRegs);
    if(error<1)
    {
        cout<<"Codigo de error "<<error<<"Lo siento Rey."<<endl;
        return;
    }
    error=CargarPEDIDOSbkp(VecDinPed,CantRegs);
    if(error<1)
    {
        cout<<"Codigo de error "<<error<<"Lo siento Rey."<<endl;
        return;
    }
    cout<<"Backup de Pedidos Creado con Éxito."<<endl;
}

int  ContarBKPPedidos()
{
    Pedido aux;
    int Cont=0;
    FILE*P;
    P=fopen(RespaldoPedidos,"rb");
    if(P==NULL)
    {
        cout<<"No se pudo abrir el archivo";
        fclose(P);
        return -1;
    }
    while(fread(&aux,sizeof(Pedido),1,P)==1)
    {
        Cont++;
    }
    fclose(P);
    return Cont;
}
bool LeerPedidosBKP(Pedido Vec[],int Cant)
{
    FILE *P;
    P=fopen(RespaldoPedidos,"rb");
    if(P==NULL)
    {
        cout<<"No se pudo abrir el archivo";
        fclose(P);
        return false;
    }
    if(fread(Vec,sizeof(Pedido),Cant,P)!=Cant)
    {
        cout<<"Hubo problemas de lectura.";
        fclose(P);
        return false;
    }
    fclose(P);
    return true;
}
bool RecuperarPedidos(Pedido Vec[],int Cant)
{
    FILE *P;
    P=fopen(ArchivoPedidos,"wb");
    if(P==NULL)
    {
        cout<<"No se pudo abrir el archivo";
        fclose(P);
        return false;
    }
    if(fwrite(Vec,sizeof(Pedido),Cant,P)!=Cant)
    {
        cout<<"Hubo problemas de escritura.";
        fclose(P);
        return false;
    }
    fclose(P);
    return true;
}
bool RestaurarPedidos()
{
    int CantRegs;
    bool funciona;
    CantRegs=ContarBKPPedidos();
    if(CantRegs<0)
    {
        return false;
    }
    Pedido *VecBKPPed;
    VecBKPPed=(Pedido *)malloc(sizeof(Pedido)*CantRegs);
    funciona=LeerPedidosBKP(VecBKPPed,CantRegs);
    if(!funciona)
        return false;
    funciona=RecuperarPedidos(VecBKPPed,CantRegs);
    if(!funciona)
        return false;
    cout<<"Recuperación de archivo Pedidos Completada."<<endl;
    return true;
}






#endif // FUNCIONES_PEDIDOS_H_INCLUDED
