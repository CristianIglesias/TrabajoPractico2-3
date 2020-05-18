#ifndef FUNCIONES_CLIENTES_H_INCLUDED
#define FUNCIONES_CLIENTES_H_INCLUDED
void MenuClientes()
{
    setColor(WHITE);
    int opcion=-1;
    while (opcion!=0)
    {
        cls();
        setColor(WHITE);
        cout<<".-.-.-.-.-.-_._._._._.MENU CLIENTES._._._._._._.-.-.-.-.-.-.-.-."<<endl;
        cout<<".-.-.-.-.-.-_._._._._.1-Nuevo Cliente._._._._._._.-.-.-.-.-.-.-."<<endl;
        cout<<".-.-.-.-.-.-_._._._._.2-Modificar Cliente._._._._.-.-.-.-.-.-.-."<<endl;
        cout<<".-.-.-.-.-.-_._._._._.3-Listar Cliente X ID.-.-.-.-.-.-.-.-.-.-."<<endl;
        cout<<".-.-.-.-.-.-_._._._._.4-Listar Todos los Clientes.-.-.-.-.-.-.-."<<endl;
        cout<<".-.-.-.-.-.-_._._._._.5-Eliminar Cliente_._._._._.-.-.-.-.-.-.-."<<endl;
        cout<<".-.-.-.-.-.-_._._._._._._._._._._._._._._._._._._.-.-.-.-.-.-.-."<<endl;
        cout<<".-.-.-.-.-.-_._._._._.0-Volver al Menú Principal-.-.-.-.-.-.-.-."<<endl;
        cin>>opcion;
        cls();
        switch (opcion)
        {
        case 1:
        {
            Nuevo_Cliente();
        }
        break;
        case 2:
        {
            Modificar_ClienteID();
        }
        break;
        case 3:
        {
            Listar_ClienteID();
        }
        break;
        case 4:
        {
            Listar_Clientes();
        }
        break;
        case 5:
        {
            Eliminar_Cliente();
        }
        break;
        case 0:
        {
            return;
        }
        break;
        case 99: ///Emergency flush
        {
            FILE *P;
            P=fopen(ArchivoClientes,"wb");
            fclose(P);
        }
        break;
        default:
        {
            cout<<"Opción No valida, intente denuevo"<<endl;
        }
        break;
        }
        cout<<"Presione Cualquier tecla para continuar."<<endl;
        anykey();
        ///cierre switch.
    }///cierre while.
}///cierre funcion.

void Nuevo_Cliente()
{
    cout<<"Ingresar un Cliente Nuevo."<<endl;
    bool escribio;
    int error;
    Cliente reg;
    error=IngresoCliente(&reg);
    if (error<0)
    {
        cout<<"Fallaste en la validación nro "<<error<<", vamos denuevo."<<endl;
        return;
    }
    else
    {
        cout<<"El Cliente se ingresó correctamente, ahora va al archivo."<<endl;
        escribio=Guardar_Cliente(&reg);
        if(escribio)
        {
            cout<<"El Cliente se guardó correctamente en el archivo de Clientes."<<endl;
        }
        else
        {
            setColor(RED);
            cout<<"Hubo un error cuando se guardó en el archivo, intentar denuevo."<<endl;
        }
    }
}
void Modificar_ClienteID()
{
    cout<<"Ingrese el ID del Cliente a Modificar."<<endl;
    Cliente aux;
    bool funco;
    int id,pos;
    cout<<"ID :";
    cin>>id;
    if(id<0||id%1!=0)
    {
        setColor(RED);
        cout<<"Un id entero y positivo por favor."<<endl;
        return;
    }
    aux=ValidarID_Cliente(id);
    switch(aux.ID)
    {
    case -1:
    {
        setColor(RED);
        cout<<"No se encontró el Cliente en el archivo."<<endl;
        return;
    }
    break;
    case -2:
    {
        setColor(RED);
        cout<<"No se pudo abrir el archivo de Clientes."<<endl;
        return;
    }
    break;
    default:
    {
        cout<<"El cliente a modificar es el siguiente:"<<endl;
        MostrarCliente(aux);
        cout<<"Ingrese su nuevo Domicilio: ";
        cin.ignore();
        cin.getline(aux.Domicilio,99);
        pos=id-1;
        funco=Sobreescribir_Cliente(aux,pos);
        if(funco)
        {
            cout<<"Archivo Guardado Correctamente"<<endl;
            return;
        }
        else
        {
            setColor(RED);
            cout<<"Hubo un error. Operación cancelada"<<endl;
            return;
        }
        break;
    }
    }
};

void Listar_ClienteID()
{
    cout<<"Vamos a mostrar El cliente que usted diga."<<endl;
    int id;
    Cliente aux;
    cout<<"ID :";
    cin>>id;
    if(id<0||id%1!=0)
    {
        setColor(RED);
        cout<<"Un id entero y positivo por favor"<<endl;
        return;
    }
    aux=ValidarID_Cliente(id);
    if (aux.ID==id)
    {
        MostrarCliente(aux);
    }
    else if(aux.ID==0)
    {
        setColor(RED);
        cout<<"Hubo un error y no se pudo chequear que el id exista."<<endl;
        return;
    }
    else if(aux.ID==-1)
    {
        setColor(RED);
        cout<<"El id Buscado no existe dentro del archivo"<<endl;
        return;
    }

};

void Listar_Clientes()
{
    cout<<"Entonces Mostrar Clientes, ordenados por apellido"<<endl;
    bool funciono;
    int CantReg;
    Cliente *VecDin;
    CantReg=ContarClientes();
    VecDin=(Cliente *)malloc(CantReg*sizeof(Cliente));
    if(VecDin==NULL)
    {
        setColor(RED);
        cout<<"Hubo un error asignando memoria."<<endl;
        anykey();
        return;
    }
    funciono =CargarVecDinCl(VecDin, CantReg);
    if (!funciono)
    {
        return;
    };
    Ordenar_Vec_Din_Cl(VecDin,CantReg);
    Mostrar_Todos_Clientes(VecDin,CantReg);
    free(VecDin);
};
void Eliminar_Cliente()
{
    int ID,confirmacion;
    Cliente aux;
    bool funciono;
    cout<<"Ingrese el id del Cliente que desea Eliminar."<<endl;
    cout<<"ID: "<<endl;
    cin>>ID;
    if(ID<0||ID%1!=0)
    {
        setColor(RED);
        cout<<"Un id Entero y Positivo por favor"<<endl;
        return;
    }
    aux=ValidarID_Cliente(ID);
    if(aux.ID!=ID)
    {
        setColor(RED);
        cout<<"El id no se encontró en el archivo. Intente denuevo"<<endl;
        return;
    }
    cout<<"El cliente a Eliminar es el siguiente"<<endl;
    MostrarCliente(aux);
    cout<<"INGRESE 1 SI DESEA ELIMINARLO."<<endl;
    cin>>confirmacion;
    if(confirmacion!=1)
    {
        setColor(RED);
        cout<<"Eliminacion Cancelada"<<endl;
        return;
    }
    funciono=Baja_LogicaCliente(aux);
    if(!funciono)
    {
        return;
    }
    cout<<"Eliminacion Completada."<<endl;



};
///Funciones Secundarias Clientes.

int IngresoCliente(Cliente *reg)
{
    int id, paso;
    Fecha Fech;
    id=Generar_ID_Cliente();///genera el id autonumerico.
    reg->ID=id;
    cout<<"ID Cliente: "<<reg->ID<<endl;
    cout<<"Ingrese el Apellido del Nuevo Cliente."<<endl;
    cout<<"Apellido  :";
    cin.ignore();
    cin.getline(reg->Apellido,49);
    if(reg->Apellido[0]=='\0')
        return -1;
    cout<<"Ingrese el Nombre del Nuevo Cliente."<<endl;
    cout<<"Nombre    :";
    cin.getline(reg->Nombre,49);
    if(reg->Nombre[0]=='\0')
        return -2;
    cout<<"Ahora ingrese el correo Electronico."<<endl;
    paso=Ingreso_Y_ValidacionMAIL(reg);///Ingreso y validación mail
    if(paso<0)
        return -3;
    cout<<"Ahora ingrese la Dirección del Cliente."<<endl;
    cout<<"Dirección :";
    cin.getline(reg->Domicilio,99);
    if(reg->Domicilio[0]=='\0')
        return-4;
    cout<<"Ahora ingrese el Código Postal."<<endl;
    cout<<"Codigo Postal:";
    cin>>reg->CodPost;
    if(reg->CodPost<1000||reg->CodPost>9999)
        return-5;
    cout<<"Ahora la fecha de nacimiento del cliente."<<endl;
    Ingreso_Y_ValidacionFECHA(&Fech);///Funcion ingreso & validación fecha.
    if(Fech.dia<0)
        return -6;
    reg->FechaNacimiento=Fech;
    reg->estado=true;
    return 1;
}

int Generar_ID_Cliente()
{
    int id,cantRegistros=0;
    FILE *p;
    Cliente aux;
    p=fopen(ArchivoClientes,"rb");
    if(p==NULL)
        return -1;
    while(fread(&aux,sizeof(Cliente),1,p)==1)
    {
        cantRegistros++;
    }
    id=cantRegistros+1;
    fclose(p);
    return id;
}

int Ingreso_Y_ValidacionMAIL(Cliente *reg)
{
    cout<<"Email    :";
    cin.getline(reg->Mail,49);
    int tam=strlen(reg->Mail),pos;
    char *poschar;
    if(reg->Mail[0]=='@'||reg->Mail[0]=='.')
    {
        return -3;   ///Que no empiece ni con arroba ni con punto
    }
    poschar=strchr(reg->Mail,'@');
    if(poschar==NULL)
    {
        return-3;   ///que tenga un arroba
    }
    if(strrchr(reg->Mail,'@')!=poschar)
    {
        return -3;   ///que solo tenga UN arroba
    }
    pos=poschar-reg->Mail;
    if((isalnum(reg->Mail[pos+1]!=0))&&(isalnum(reg->Mail[pos-1]!=0)))
    {
        return-3;   ///Que tenga chares alfanumericos al rededor de arroba.
    }
    poschar=strchr(reg->Mail,'.');          ///Que tenga un punto
    if(poschar==NULL)
    {
        return -3;
    }
    pos=reg->Mail-poschar;
    if(reg->Mail[pos+1]=='.')
    {
        return-3;   ///Que no tenga dos seguidos
    }

    if(reg->Mail[tam-1]=='.')
    {
        return-3;   ///que no termine en punto.
    }
    return 1;
}

void Ingreso_Y_ValidacionFECHA(Fecha *aux)
{
    cout<<"Ingrese el día, Mes y año:"<<endl;
    cout<<"|";
    cin>>aux->dia;
    cout<<"/";
    cin>>aux->mes;
    cout<<"/";
    cin>>aux->anio;
    cout<<"|"<<endl;
    if((aux->mes>0&&aux->mes<13)&&(aux->anio>1920&&aux->anio<=2020))
    {
        switch(aux->mes)
        {
        case  1 :
        case  3 :
        case  5 :
        case  7 :
        case  8 :
        case 10 :
        case 12 :
            if ( aux->dia >= 1 && aux->dia <= 31 )
            {
                return;
            }
            else
            {
                aux->dia=-1;
                return;
            }
        case  4 :
        case  6 :
        case  9 :
        case 11 :
            if ( aux->dia >= 1 && aux->dia <= 30 )
            {

                return ;
            }
        case  2 :
            if( aux->anio % 4 == 0 && aux->anio % 100 != 0 || aux->anio % 400 == 0 )
                if ( aux->dia >= 1 && aux->dia <= 29 )
                {

                    return;
                }
                else
                {
                    aux->dia=-1;
                    return;
                }
            else if ( aux->dia >= 1 && aux->dia <= 28 )
            {
                return;
            }
            else
            {
                aux->dia=-1;
                return;
            }

        }
    }
    else
    {
        aux->dia=-1;
        return;
    }
}

bool Guardar_Cliente(Cliente *reg)
{
    bool Funciona;
    FILE *P;
    P=fopen(ArchivoClientes,"ab");
    if(P==NULL)
        return false;
    Funciona=fwrite(reg,sizeof(Cliente),1,P);
    fclose(P);
    return Funciona;
}


Cliente ValidarID_Cliente(int ID)
{
    Cliente aux;
    FILE *P;
    P=fopen(ArchivoClientes,"rb");
    if(P==NULL)
    {
        aux.ID=0;
        return aux;
    }
    while(fread(&aux,sizeof(Cliente),1,P)==1)
    {
        if(aux.ID==ID)
        {
            fclose(P);
            return aux;
            break;
        }
    }
    fclose(P);
    aux.ID=-1;
    return aux;
}

void  MostrarCliente(Cliente aux)
{
    if(aux.estado)
    {
        setColor(GREEN);
        cout<<"------------------------------------------------"<<endl;
        cout<<"El cliente Con ID  :  "<<aux.ID<<"              "<<endl;
        cout<<"Tiene de Nombre    :  "<<aux.Nombre<<"          "<<endl;
        cout<<"Su Apellido es     :  "<<aux.Apellido<<"        "<<endl;
        cout<<"Su Email es        :  "<<aux.Mail<<"            "<<endl;
        cout<<"Su dirección es    :  "<<aux.Domicilio<<"       "<<endl;
        cout<<"Su código Postal es:  "<<aux.CodPost<<"         "<<endl;
        cout<<"Su fecha de nacimiento es el "<<aux.FechaNacimiento.dia<<" del mes "<<aux.FechaNacimiento.mes<<"del año "<<aux.FechaNacimiento.anio<<endl;
        cout<<"------------------------------------------------"<<endl;
    }
}

bool Sobreescribir_Cliente(Cliente reg, int pos)
{
    FILE*P;
    bool escribio;
    P=fopen(ArchivoClientes,"rb+");
    if (P==NULL)
        return false;
    fseek(P,pos*sizeof(Plato),0);
    escribio=fwrite(&reg,sizeof(Plato),1,P);
    fclose(P);
    return escribio;
}

int ContarClientes()
{
    int Cant;
    FILE *P;
    P=fopen(ArchivoClientes,"rb");
    fseek(P,SEEK_SET,SEEK_END);
    Cant=(ftell(P)/sizeof(Cliente));
    fclose(P);
    return Cant;
}

bool CargarVecDinCl(Cliente Vec[],int Cant)
{
    FILE *P;
    P=fopen(ArchivoClientes,"rb");
    if(P==NULL)
    {
        setColor(RED);
        cout<<"Hubo un problema leyendo el archivo... Toque Cualquier Tecla para continuar."<<endl;
        anykey();
        return false;
    }
    if(fread(Vec,sizeof(Cliente),Cant,P)==Cant)
    {
        fclose(P);
        return true;
    }
    fclose(P);
    setColor(RED);
    cout<<"Hubo un problema leyendo el archivo... Toque cualquier tecla para continuar.";
    anykey();
    return false;
}
void Ordenar_Vec_Din_Cl(Cliente Vec[],int Cant)
{
    int i,j,pos;
    Cliente aux;
    for(i=0; i<Cant-1; i++)
    {
        pos=i;
        for(j=i+1; j<Cant; j++)
        {
            if(strcmp(Vec[j].Apellido,Vec[pos].Apellido)<0)
            {
                pos=j;
            }
        }
        aux=Vec[i];
        Vec[i]=Vec[pos];
        Vec[pos]=aux;
    }
}
void Mostrar_Todos_Clientes(Cliente Vec[], int Cant)
{
    int i;
    for(i=0; i<Cant; i++)
    {
        MostrarCliente(Vec[i]);
    }
    return;
}
bool Baja_LogicaCliente(Cliente reg)
{
    int pos=reg.ID-1;
    reg.estado=false;
    FILE *P;
    P=fopen(ArchivoClientes,"rb+");
    if(P==NULL)
    {
        setColor(RED);
        cout<<"No se pudo abrir el archivo"<<endl;
        return false;
    }
    fseek(P,sizeof(Cliente)*pos,0);
    if(fwrite(&reg,sizeof(Cliente),1,P)!=1)
    {
        setColor(RED);
        cout<<"Hubo un error escribiendo."<<endl;
        return false;
    }
    fclose(P);
    return true;
}
int CargarCLIENTESbkp(Cliente VecDinCli[],int CantRegs)
{
    FILE *p;
    p=fopen(RespaldoClientes,"wb");
    if(p==NULL)
    {
        fclose(p);
        return-1;
    }
    if(fwrite(VecDinCli,sizeof(Cliente),CantRegs,p)!=CantRegs)
    {
        fclose(p);
        return-2;
    }
    fclose(p);
    return 1;
}

void  BackupClientes()
{
    bool funca;
    int CantRegs,error;
    Cliente *VecDinCli;
    CantRegs=ContarClientes();
    if(CantRegs<1)
    {
        cout<<"Codigo de error "<<CantRegs<<" Lo sentimos Rey."<<endl;
        return;
    }
    VecDinCli=(Cliente*)malloc(CantRegs*sizeof(Cliente));
    funca=CargarVecDinCl(VecDinCli,CantRegs);
    if(!funca)
    {
        return;
    }
    error=CargarCLIENTESbkp(VecDinCli,CantRegs);
    if(error<1)
    {
        cout<<"Codigo de error "<<error<<"Lo siento Rey."<<endl;
        return;
    }
    cout<<"Backup de Clientes Creado Con Éxito."<<endl;
    free(VecDinCli);
}
int  ContarBKPClientes(){
 Cliente aux;
 int Cont=0;
 FILE*P;
 P=fopen(RespaldoClientes,"rb");
 if(P==NULL){cout<<"No se pudo abrir el archivo";fclose(P);return -1;}
 while(fread(&aux,sizeof(Cliente),1,P)==1)
 {
     Cont++;
 }
fclose(P);
return Cont;
}

bool LeerClientesBKP(Cliente Vec[],int Cant)
{
FILE *P;
P=fopen(RespaldoClientes,"rb");
 if(P==NULL){cout<<"No se pudo abrir el archivo";fclose(P);return false;}
if(fread(Vec,sizeof(Cliente),Cant,P)!=Cant)
{
    cout<<"Hubo problemas de lectura.";fclose(P);return false;
}
fclose(P);
return true;
}
bool RecuperarClientes(Cliente Vec[],int Cant)
{
    FILE *P;
    P=fopen(ArchivoClientes,"wb");
    if(P==NULL)
    {
        cout<<"No se pudo abrir el archivo";
        fclose(P);
        return false;
    }
    if(fwrite(Vec,sizeof(Cliente),Cant,P)!=Cant)
    {
        cout<<"Hubo problemas de escritura.";
        fclose(P);
        return false;
    }
    fclose(P);
    return true;
}
bool RestaurarClientes()
{
    int CantRegs;bool funciona;
    CantRegs=ContarBKPClientes();
    if(CantRegs<0)
    {
        return false;
    }
    Cliente *VecBKPCli;
    VecBKPCli=(Cliente *)malloc(sizeof(Cliente)*CantRegs);
    funciona=LeerClientesBKP(VecBKPCli,CantRegs);
    if(!funciona)
        return false;
    funciona=RecuperarClientes(VecBKPCli,CantRegs);
    if(!funciona)
        return false;
    cout<<"Recuperación de archivo Clientes Completada."<<endl;
    return true;

}





#endif // FUNCIONES_CLIENTES_H_INCLUDED
