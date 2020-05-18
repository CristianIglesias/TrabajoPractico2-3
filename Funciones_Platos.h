#ifndef FUNCIONES_PLATOS_H_INCLUDED
#define FUNCIONES_PLATOS_H_INCLUDED

void MenuPlatos()
{
    cls();
    int opcion=-1;
    while (opcion!=0)
    {
        cls();
        setColor(WHITE);
        cout<<"-....------------Opciones:---------------------....._-"<<endl;
        cout<<"-....-------------1) Nuevo Plato.--------------....._-"<<endl;
        cout<<"-....-------------2) Modificar Plato.----------....._-"<<endl;
        cout<<"-....-------------3) Listar Plato por ID.------....._-"<<endl;
        cout<<"-....-------------4) Platos por Restaurant.----....._-"<<endl;
        cout<<"-....-------------5) Eliminar Plato.-----------....._-"<<endl;
        cout<<"-....-------------6) Mostrar Todos Los Platos.-....._-"<<endl;
        cout<<"-....------------------------------------------....._-"<<endl;
        cout<<"-....-------------0) Volver al Menú Principal.-....._-"<<endl;
        cout<<"-....------------------------------------------....._-"<<endl;
        cin>>opcion;
        cls();
        switch (opcion)
        {
        case 1:
        {
            Nuevo_Plato();
        }
        break;
        case 2:
        {
            Editar_Plato();
        }
        break;
        case 3:
        {
            Listar_PlatoID();
        }
        break;
        case 4:
        {
            Platos_porRest();
        }
        break;
        case 5:
        {
            EliminarPlato();
        }
        break;
        case 6:
        {
            cout<<"Registros de Platos acumulados hasta el momento:"<<endl;
            MostrarTODOS();
        }
        break;
        case 0:
        {
            return;
        }
        break;
        default:
        {
            cout<<"Opción No valida."<<endl;
            cout<<"Presione Cualquier tecla para continuar."<<endl;
            anykey();
        }
        break;
        case 99:///Emergency Flush
        {
            FILE *P;
            P=fopen(ArchivoPlatos,"wb");
            fclose(P);
        }
        }///cierra el switch
        cout<<"Presione Cualquier tecla para continuar."<<endl;
        anykey();
    }///cierra el while
}
void Nuevo_Plato()
{

///completo
    bool escribio;
    int error;
    Plato reg;
    error=IngresoPlato(&reg);
    if (error<0)
    {
        cout<<"Fallaste en la validación nro "<<error<<", vamos denuevo"<<endl;
        return;
    }
    else
    {
        cout<<"El item se ingresó correctamente, ahora va al archivo"<<endl;
        escribio=Guardar_Plato(&reg);
        if(escribio)
        {
            cout<<"El item se guardó correctamente en el archivo de platos"<<endl;
        }
        else
        {
            cout<<"El item tuvo un error cuando se guardó en el archivo, intentar denuevo."<<endl;
        }
    }

}
///Funciones principales Platos
void Editar_Plato()
{
    int id,pos;
    Plato reg;
    cout<<"Ingresá el id del Plato a modificar."<<endl;
    cout<<"ID :";
    cin>>id;
    if(id<0||id%1!=0)
    {
        cout<<"un id positivo entero, acordate."<<endl;
        return;
    }
    reg=validar_ID_Plato(id);
    if(reg.ID!=id)
    {
        cout<<"hubo un error, no se encontró el plato"<<endl;
        return;
    }
    pos=Buscar_Plato(id);
    MostrarPlato(reg);
    cout<<"Ahora corrijamos el precio de venta."<<endl;
    cout<<"Precio de venta Nuevo $:"<<endl;
    cin>>reg.Valor_Venta;
    if(reg.Valor_Venta<=reg.Costo_Prep)
    {
        cout<<"Error, el precio de venta no puede ser menor al costo de preparacion.";
        return;
    }
    cout<<"ingrese ahora el tiempo de preparacion nuevo (?)"<<endl;
    cout<<"Tiempo de preparacion nuevo :";
    cin>>reg.Tiempo_Prep;
    if(reg.Tiempo_Prep<0||reg.Tiempo_Prep%1!=0)
    {
        cout<<"Error, el tiempo de preparacion tiene que ser un numero positivo y entero."<<endl;
        return;
    }

    if(Sobreescribir_Plato(reg,pos))
    {
        cout<<"Producto Modificado"<<endl;
    }
    else
    {
        cout<<"No se pudo modificar el producto"<<endl;
    }

}

void Listar_PlatoID()
{
///completo
    int ID;
    Plato reg;
    cout<<"Vamos a buscar un ID, y devolver el registro Completo."<<endl;
    cout<<"ID: ";
    cin>>ID;
    if (ID<0||ID%1!=0)
    {
        cout<<"un id positivo entero, acordate."<<endl;
        return;
    }
    reg=validar_ID_Plato(ID);
    if(reg.ID<0)
    {
        cout<<"El id no existe, intente denuevo."<<endl;
        return;
    }
    MostrarPlato(reg);
}

void Platos_porRest()
{
///Completo
    bool existe;
    int IDR;
    cout<<"Vamos a buscar todos los platos que estén a nombre de un restaurante en particular."<<endl;
    cout<<"ID RESTAURANTE: ";
    cin>>IDR;
    if(IDR<0||IDR%1!=0)
    {
        cout<<"un id positivo entero, acordate."<<endl;
        return;
    }
    existe=ValidarIDR(IDR);
    if(!existe)
    {
        cout<<"El Restaurante con ID:"<<IDR<<"No existe en el archivo."<<endl;
        cout<<"intente denuevo"<<endl;
    }
    MostrarPlatosRest(IDR);
}

void EliminarPlato()///Tiene errores creo.
{
    int ID,pos,confirmacion;
    bool funciono;
    Plato Aux;
    cout<<"Vamos a eliminar el plato que vos quieras."<<endl;
    cout<<"ID Plato: ";
    cin>>ID;
    if(ID<=0||ID%1!=0)
    {
        cout<<"un id positivo entero, acordate."<<endl;
        return;
    }
    Aux=validar_ID_Plato(ID);
    pos=Buscar_Plato(ID);
    cout<<"El plato a eliminar es el siguiente.";
    MostrarPlato(Aux);
    cout<<"Está seguro que desea eliminar este plato?"<<endl;
    cout<<"Ingrese 1 para eliminar plato. ingrese otro numero para cancelar operacion."<<endl;
    cout<<"CONFIRMACIÓN: ";
    cin>>confirmacion;
    if(confirmacion==1)
    {
        funciono=BajaLogica_Plato(Aux,pos);
        if (funciono)
        {
            cout<<"Funcionó,Plato Eliminado"<<endl;
        }
        else
        {
            cout<<"No funcionó, hubo un error"<<endl;
            return;
        }
    }
    else
    {
        cout<<"Eliminacion cancelada.";
        return;
    }
}

///Funciones llamadas por las principales

int IngresoPlato(Plato *reg)
{
    cls();
    int id;
    Plato aux;
    cout<<"Ingresa el ID del Plato NUEVO que querés agregar."<<endl<<"ID: ";
    cin>>id;
    if (id<0||id%1!=0)
        return -1;
    reg->ID=id;
    aux=validar_ID_Plato(id);
    if(aux.ID==reg->ID)
    {
        return -1;
    }
    cout<<"Ahora que eso salió bien, ingresa el nombre."<<endl<<"Nombre: ";
    cin.ignore();
    cin.getline(reg->Nombre,29);
    cout<<"Cuanto tenés de costo para hacer este plato?."<<endl<<"Costo del plato :$";
    cin>>reg->Costo_Prep;
    if(reg->Costo_Prep<0)
        return-3;
    cout<<"A cuanto tenías pensado venderlo?"<<endl<<"Precio de venta: $";
    cin>>reg->Valor_Venta;
    if(reg->Valor_Venta<reg->Costo_Prep||reg->Valor_Venta<0)
        return-4;
    cout<<"Y cuanto tardás en hacerlo?(MINUTOS)"<<endl<<"Tiempo De Preparación :";
    cin>>reg->Tiempo_Prep;
    if(reg->Tiempo_Prep<0||reg->Tiempo_Prep%1!=0)
        return -5;
    cout<<"ID del Restaurante :";
    cin>>reg->ID_Restaurante;
    if(reg->ID_Restaurante<0||reg->ID_Restaurante%1!=0)
        return-6;
    cout<<"Cuanto es la comisión del restaurante: "<<endl;///A CHEQUEAR CON EL PROFE
    cin>>reg->Comision_Restaurante;
    if(reg->Comision_Restaurante<0||reg->Comision_Restaurante>100)
        return -7;
    cout<<"De que categoría es este plato?"<<endl<<"Categoría: "<<endl;
    cin>>reg->ID_Categoria;
    if(reg->ID_Categoria<0)
        return-8;
    reg->Estado=true;
    cls();
    return 0;
}
struct Plato validar_ID_Plato(int id)
{
    Plato aux;
    FILE *P;
    P=fopen("platos.dat","rb");
    while(fread(&aux,sizeof(Plato),1,P)==1)
    {
        if (id==aux.ID)
        {
            return aux;
        }
    }
    aux.ID=-1;
    fclose(P);
    return aux;
}
bool Guardar_Plato(Plato *reg)
{
    bool Funciona;
    FILE *P;
    P=fopen(ArchivoPlatos,"ab");
    if(P==NULL)
        return false;
    Funciona=fwrite(reg,sizeof(Plato),1,P);
    fclose(P);
    return Funciona;
}
void MostrarPlato(Plato reg)
{
    if(reg.Estado)
    {
        cout<<"- - - - - - - - - - - - - - - - - - -"<<endl;
        cout<<"El plato con ID                   :"<<reg.ID<<endl;
        cout<<"Tiene de nombre                   :"<<reg.Nombre<<endl;
        cout<<"Pertenece al restaurante Nro      :"<<reg.ID_Restaurante<<endl;
        cout<<"Pertenece a la categoría Nro      :"<<reg.ID_Categoria<<endl;
        cout<<"Tiene un costo de preparacion de  :$"<<reg.Costo_Prep<<endl;
        cout<<"Tiene un Tiempo de preparacion de :"<<reg.Tiempo_Prep<<" Minutos"<<endl;
        cout<<"Tiene un valor de venta de        :$"<<reg.Valor_Venta<<endl;
        cout<<"Comisiona un porcentaje del       :%"<<reg.Comision_Restaurante<<endl;
        cout<<"- - - - - - - - - - - - - - - - - - -"<<endl;
    }
}
void MostrarPlatosRest(int IDR)
{
    FILE *P;
    Plato aux;
    P=fopen(ArchivoPlatos,"rb");
    if(P==NULL)
    {
        cout<<"No se pudo abrir el archivo"<<endl;
        return;
    }
    while(fread(&aux,sizeof(Plato),1,P)==1)
    {
        if(IDR==aux.ID_Restaurante)
        {
            MostrarPlato(aux);
        }
    }
    fclose(P);
}
void MostrarTODOS()
{
    FILE *P;
    Plato reg;
    P=fopen(ArchivoPlatos,"rb");
    while(fread(&reg,sizeof(Plato),1,P)==1)
    {
        if(reg.Estado)
        {
            MostrarPlato(reg);
        }
    }
}
bool ValidarIDR(int IDR)
{
    FILE *p;
    Plato reg;
    p=fopen(ArchivoPlatos,"rb");
    while(fread(&reg,sizeof(Plato),1,p)==1)
    {
        if(IDR==reg.ID_Restaurante)
        {
            return true;
        }
    }
    fclose(p);
    return false;

}
int Buscar_Plato(int id)
{
    Plato reg;
    int CantidadRegistros;
    FILE*P;
    P=fopen(ArchivoPlatos,"rb");
    CantidadRegistros=(ftell(P)/sizeof(Plato));
    for(int i=0; i<CantidadRegistros; i++)
    {
        fread(&reg,sizeof(Plato),1,P);
        if(reg.ID==id)
        {
            fclose(P);
            return i;
        }
    }
    fclose(P);
    return -1;
}
bool Sobreescribir_Plato(Plato reg, int pos)
{
    FILE*P;
    bool escribio;
    P=fopen(ArchivoPlatos,"rb+");
    if (P==NULL)
        return false;
    fseek(P,pos*sizeof(Plato),0);
    escribio=fwrite(&reg,sizeof(Plato),1,P);
    fclose(P);
    return escribio;
}
bool BajaLogica_Plato(Plato reg, int pos)///tiene errores creo.
{
    reg.Estado=false;
    FILE *P;
    bool escribio;
    P=fopen(ArchivoPlatos,"rb+");
    if(P==NULL)
        return false;
    fseek(P,pos*sizeof(Plato),0);

    escribio=fwrite(&reg,sizeof(Plato),1,P);
    fclose(P);
    return escribio;
}
void MostrarPrevPlato(Plato Pla)
{
    if(Pla.Estado)
    {
        cout<<"- - - - - - - - - - - - - - - - - - -"<<endl;
        cout<<"El De ID                            :"<<Pla.ID<<endl;
        cout<<"Tiene de nombre                     :"<<Pla.Nombre<<endl;
        cout<<"Pertenece al restaurante Nro        :"<<Pla.ID_Restaurante<<endl;
        cout<<"Pertenece a la categoría Nro        :"<<Pla.ID_Categoria<<endl;
        cout<<"Tiene un Tiempo de preparacion de   :"<<Pla.Tiempo_Prep<<" Minutos"<<endl;
        cout<<"Tiene un valor de venta unitario de :$"<<Pla.Valor_Venta<<endl;
        cout<<"- - - - - - - - - - - - - - - - - - -"<<endl;
    }
}
int ContarPlatos()
{
    int cantRegs;
    FILE *P;
    P=fopen(ArchivoPlatos,"rb");
    if(P==NULL)
    {
        fclose(P);
        return -1;
    }
    fseek(P,0,2);
    cantRegs=ftell(P)/sizeof(Plato);
    fclose(P);
    return cantRegs;
}
int CargarVecDinPla(Plato VecDinPla[],int CantRegs)
{
    Plato aux;
    FILE *p;
    p=fopen(ArchivoPlatos,"rb");
    if(p==NULL)
    {
        fclose(p);
        return-1;
    }
    if(fread(VecDinPla,sizeof(Plato),CantRegs,p)!=CantRegs)
    {
        fclose(p);
        return-2;
    }

    fclose(p);
    return 1;
}
int CargarPLATOSbkp(Plato VecDinPla[],int CantRegs)
{
    FILE *p;
    p=fopen(RespaldoPlatos,"wb");
    if(p==NULL)
    {
        fclose(p);
        return-1;
    }
    if(fwrite(VecDinPla,sizeof(Plato),CantRegs,p)!=CantRegs)
    {
        fclose(p);
        return-2;
    }
    fclose(p);
    return 1;
}
void BackupPlatos()
{
    int CantRegs,error;
    Plato *VecDinPla;
    CantRegs=ContarPlatos();
    if(CantRegs<1)
    {
        cout<<"Codigo de error "<<CantRegs<<" Lo sentimos Rey."<<endl;
        return;
    }
    VecDinPla=(Plato*)malloc(CantRegs*sizeof(Plato));
    error=CargarVecDinPla(VecDinPla,CantRegs);
    if(error<1)
    {
        cout<<"Codigo de error "<<error<<" Lo Sentimos Rey."<<endl;
        return;
    }
    error=CargarPLATOSbkp(VecDinPla,CantRegs);
    if(error<1)
    {
        cout<<"Codigo de error "<<error<<"Lo siento Rey."<<endl;
        return;
    }
    cout<<"Backup de Platos Creado Con Éxito."<<endl;
    free(VecDinPla);
}
int  ContarBKPPlatos()
{
    Plato aux;
    int Cont=0;
    FILE*P;
    P=fopen(RespaldoPlatos,"rb");
    if(P==NULL)
    {
        cout<<"No se pudo abrir el archivo";
        fclose(P);
        return -1;
    }
    while(fread(&aux,sizeof(Plato),1,P)==1)
    {
        Cont++;
    }
    fclose(P);
    return Cont;
}

bool LeerPlatosBKP(Plato Vec[],int Cant)
{
    FILE *P;
    P=fopen(RespaldoPlatos,"rb");
    if(P==NULL)
    {
        cout<<"No se pudo abrir el archivo";
        fclose(P);
        return false;
    }
    if(fread(Vec,sizeof(Plato),Cant,P)!=Cant)
    {
        cout<<"Hubo problemas de lectura.";
        fclose(P);
        return false;
    }
    fclose(P);
    return true;
}


bool RecuperarPlatos(Plato Vec[],int Cant)
{
    FILE *P;
    P=fopen(ArchivoPlatos,"wb");
    if(P==NULL)
    {
        cout<<"No se pudo abrir el archivo";
        fclose(P);
        return false;
    }
    if(fwrite(Vec,sizeof(Plato),Cant,P)!=Cant)
    {
        cout<<"Hubo problemas de escritura.";
        fclose(P);
        return false;
    }
    fclose(P);
    return true;
}
bool RestaurarPlatos()
{
    int CantRegs;
    bool funciona;
    CantRegs=ContarBKPPlatos();
    if(CantRegs<0)
    {
        return false;
    }
    Plato *VecBKPPlat;
    VecBKPPlat=(Plato *)malloc(sizeof(Plato)*CantRegs);
    funciona=LeerPlatosBKP(VecBKPPlat,CantRegs);
    if(!funciona)
        return false;
    funciona=RecuperarPlatos(VecBKPPlat,CantRegs);
    if(!funciona)
        return false;
    cout<<"Recuperación de archivo Platos Completada."<<endl;
    return true;
}







#endif // FUNCIONES_PLATOS_H_INCLUDED
