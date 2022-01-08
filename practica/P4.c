//Realizado por Emilio López Novillo.
//Fecha de finalización de la práctica 04/01/2020 hora 18:38.


#include "RPC.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#define MAXS 100
#define MAXID 6
#define IDRPC 5
#define RPC 10

typedef char tIdServidor [MAXID];

typedef struct
{
    tRPCs rpcs;
    tIdServidor idservidor;

} tServidor;

typedef struct
{
    bool ocupado;
    tServidor servidor;
} tCelda;

typedef tCelda tServidores [MAXS];

int menu(void);
void altaServidor(tServidores servidores);
bool haySitioEnServidores(const tServidores servidores, int *p);
void inicializarServidores(tServidores servidores);
void listarServidores(const tServidores servidores);
bool buscarServidorPorId(const tServidores servidores, int *pos, const tIdServidor nserv);
void leerCadena(tIdServidor nserv);
void mostrarSistema(const tServidores servidores);
void darDeBajaServidor(tServidores servidores);
void incluirRPCs(tServidores servidores);
bool leerServidores(tServidores servidores, char *nFichero);
bool grabarServidores(tServidores servidores, char *nFichero);


int main (int argc, char *argv[])
{
    int caso;
    tServidores s;

    inicializarServidores(s);
    leerServidores(s, argv[1]);

    do
    {
        caso=menu();

        switch(caso)
        {
        case 1:
            altaServidor(s);
            break;
        case 2:
            incluirRPCs(s);
            break;
        case 3:
            mostrarSistema(s);
            break;
        case 4:
            darDeBajaServidor(s);
            break;
        case 5:
            break;
        default:
            printf("\nNo es una opcion correcta. Por favor introduzca un numero entre el 1 y el 5.\n");
        }
    }
    while(caso!=5);

    if(grabarServidores(s,argv[1]))
        fprintf(stdout,"\nError al guardar los datos en el fichero.\n");
    else
        fprintf(stdout,"\nDatos correctamente guardados en el fichero.\n");

    return 0;
}
int menu (void)
{
    int opmenu;

    printf("\n\n");
    printf("*******************OPCIONES*******************\n");
    printf("* 1. Dar de alta un servidor en el sistema   *\n");
    printf("* 2. Incluir una RPC en un servidor          *\n");
    printf("* 3. Mostrar el estado del sistema           *\n");
    printf("* 4. Borrar un servidor del sistema          *\n");
    printf("* 5. Salir                                   *\n");
    printf("**********************************************\n");
    fprintf(stdout,"Elija opcion: ");
    fflush(stdout);
    fflush(stdin);
    fscanf(stdin,"%d", &opmenu);
    fflush(stdin);

    return opmenu;
}
void altaServidor(tServidores servidores)
{
    int numenc;
    int posic;
    int posic2;
    tIdServidor nservidores;

    if(haySitioEnServidores(servidores, &posic)==false)
    {
        posic2=posic;
        leerCadena(nservidores);
        if(buscarServidorPorId(servidores, &numenc, nservidores)==false)
        {
            fprintf(stdout,"\nEste servidor se a agregado correctamente.\n");
            strcpy(servidores[posic2].servidor.idservidor,nservidores);
            servidores[posic2].ocupado=true;
            inicializarRPCs(&(servidores[posic2].servidor.rpcs));
        }
        else
        {
            printf("Este servidor esta ya dado en alta en la posicion %d.\n", numenc+1);
        }
    }
    else
        printf("No hay sitio en los servidores");

    listarServidores(servidores);
}
bool buscarServidorPorId(const tServidores servidores, int *pos, const tIdServidor nserv)
{
    bool encontrado=false;

    for(int i=0; i<MAXS; i++)
    {
        if(servidores[i].ocupado==true&&strcmp(nserv,servidores[i].servidor.idservidor)==0)
        {
            encontrado=true;
            *pos=i;
        }
    }

    return encontrado;
}
bool haySitioEnServidores(const tServidores servidores, int *p)
{
    bool sitio=true;
    int y=0;

    do
    {
        if(servidores[y].ocupado==false)
        {
            sitio=false;
            *p=y;
        }
        y++;
    }
    while(y<MAXS&&sitio==true);

    return sitio;
}
void listarServidores(const tServidores servidores)
{
    fprintf(stdout,"\nServidores actuales:");
    for(int w=0; w<MAXS; w++)
    {
        if(servidores[w].ocupado==true)
        {
            printf("\n");
            fputs(servidores[w].servidor.idservidor,stdout);
        }

    }
    fprintf(stdout,"\n");
}
void inicializarServidores(tServidores servidores)
{
    for(int u=0; u<MAXS; u++)
    {
        servidores[u].ocupado=false;
    }
}
void leerCadena(tIdServidor nserv)
{
    do
    {
        printf("\nEscriba el nombre del servidor: ");
        fflush(stdout);
        fflush(stdin);
        gets(nserv);
        fflush(stdin);

        if(nserv[strlen(nserv)-1]=='\n')
            nserv[strlen(nserv)-1]='\0';
        if(strlen(nserv)>MAXID)
            fprintf(stdout,"Has superado el numero maximo de caracteres.");
    }
    while(strlen(nserv)>MAXID);

}
void mostrarSistema(const tServidores servidores)
{
    for(int h=0; h<MAXS; h++)
    {
        if(servidores[h].ocupado==true)
        {
            fprintf(stdout,"\nId del servidor: ");
            fputs(servidores[h].servidor.idservidor,stdout);
            mostrarRPCs(&(servidores[h].servidor.rpcs));

        }
    }

    if(servidores[0].ocupado==false&&servidores[1].ocupado==false&&servidores[2].ocupado==false)
        fprintf(stdout,"\nNo hay servidores dados de alta.\n");
}
void darDeBajaServidor(tServidores servidores)
{
    tIdServidor exservidor;
    int loc;
    fprintf(stdout,"Introduzca el nombre del servidor que quiere dar de baja: ");
    leerCadena(exservidor);

    if(buscarServidorPorId(servidores, &loc, exservidor)==true)
    {
        servidores[loc].ocupado=false;
        fprintf(stdout, "El servidor ha sido dado de baja correctamente");
    }
    else
        fprintf(stdout,"No hay ningun servidor con esa ID.");
    fprintf(stdout,"\n");
    listarServidores(servidores);
}
void incluirRPCs(tServidores servidores)
{
    tIdServidor nservidor;
    int lug1;
    int lug2;
    fprintf(stdout,"En que servidor desea agregar una RPC: ");
    leerCadena(nservidor);
    if(buscarServidorPorId(servidores, &lug1, nservidor)==true)
    {
        altaRPCEnServidor(&(servidores[lug1].servidor.rpcs));
    }
    else
    {
        if(haySitioEnServidores(servidores, &lug2)==false)
        {
            fprintf(stdout,"\nEste servidor se a agregado correctamente.\n");
            strcpy(servidores[lug2].servidor.idservidor,nservidor);
            servidores[lug2].ocupado=true;
            inicializarRPCs(&(servidores[lug2].servidor.rpcs));
            altaRPCEnServidor(&(servidores[lug2].servidor.rpcs));
        }
        else
            fprintf(stdout,"No se pueden agregar mas servidores.");
    }
    fprintf(stdout,"\n");
    listarServidores(servidores);
}
bool leerServidores(tServidores servidores, char *nFichero)
{
    FILE *pf; ;
    int i =0;
    bool error = false;
    pf = fopen (nFichero, "rb");
    fread(&(servidores[i].servidor),sizeof(tCelda),1,pf);
    if (pf!= NULL) {
        while(!feof(pf)&&!ferror(pf)){
            servidores[i].ocupado= true;
            i++;
            fread(&(servidores[i].servidor),sizeof(tCelda),1,pf);
        }
        if (ferror(pf)) {
            error= true;
            fprintf(stdout,"\nSe ha producido un error con el fichero.");
        }
        else
            fprintf(stdout,"\nFichero ejecutado correctamente.");
        fclose (pf);
    }else{
        fprintf(stdout,"\nEl fichero no se ha abierto correctamente.");
        error= true;
    }
    return error;
}
bool grabarServidores(tServidores servidores, char *nFichero)
{
    FILE *pf; ;
    bool error=false;
    int q=0;

    pf = fopen(nFichero,"wt");

    if(pf!=NULL)
    {
        while(q<MAXS&&!ferror(pf))
        {
            if(servidores[q].ocupado==true)
            {
                fwrite(&(servidores[q].servidor),sizeof(tCelda),1,pf);
            }
            q++;
        }
        if(ferror(pf))
        {
            error=true;
            fprintf(stdout,"\nSe ha producido un error en el fichero.");
        }
        else
        fclose(pf);
    }
    else
    {
        error=true;
        fprintf(stdout,"\nHay un error en la apertura del fichero");
    }

    return error;
}
