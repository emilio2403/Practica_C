#include "RPC.h"

bool buscarRPCPorId(int *l, tIRPC nid, const tRPCs RPCs)
{
    bool rpc=false;

    for(int h=0; h<RPCs.numRPCs; h++)
    {
        if(strcmp(nid,RPCs.arrayRPCs[h].idRPC)==0)
        {
            *l=h;
            rpc=true;
        }
    }

    return rpc;
}
bool haySitioEnRPCs(const tRPCs RPCs, int *r)
{
    bool esp=true;

    if(RPCs.numRPCs!=4)
    {
        *r=RPCs.numRPCs;
        esp=false;
    }
    return esp;
}
void leerRPC(tIRPC nRPC)
{
    do
    {
        fprintf(stdout,"\nId de la RPC: ");
        fflush(stdout);
        fflush(stdin);
        gets(nRPC);
        fflush(stdin);

        if(nRPC[strlen(nRPC)-1]=='\n')
            nRPC[strlen(nRPC)-1]='\0';
        if(strlen(nRPC)>IDRPC)
            fprintf(stdout,"Has superado el numero maximo de caracteres.");
    }
    while(strlen(nRPC)>IDRPC);

}
void altaRPCEnServidor(tRPCs *RPCs)
{
    tIRPC id;
    tTvida tvida;
    int posRPC;
    int lugRPC;
    if(RPCs->numRPCs!=4)
    {
        leerRPC(id);
        if(buscarRPCPorId(&posRPC, id, *RPCs)==false&&haySitioEnRPCs(*RPCs,&lugRPC)==false)
        {
            fprintf(stdout,"Introduzca el tiempo de vida de la RPC: ");
            fflush(stdout);
            fflush(stdin);
            fscanf(stdin,"%d", &tvida);
            RPCs->arrayRPCs[lugRPC].tiempovida=tvida;
            strcpy(RPCs->arrayRPCs[lugRPC].idRPC,id);
            RPCs->numRPCs++;
            fprintf(stdout,"RPC dada de alta correctamente.");
        }
        else
            fprintf(stdout,"Esa RPC ya existe.");
    }
    else
        fprintf(stdout,"No hay sitio para mas RPCs.");

}
void inicializarRPCs(tRPCs *listaRPCs)
{
    listaRPCs->numRPCs=0;
}
void mostrarRPCs(const tRPCs *RPCs)
{
    if(RPCs->numRPCs==0)
        fprintf(stdout,"\nNo hay RPCs en este servidor.");
    else
    {
        for(int p=0; p<RPCs->numRPCs; p++)
        {
            fprintf(stdout,"\n-RPC: ");
            fputs(RPCs->arrayRPCs[p].idRPC,stdout);
            fprintf(stdout,"  --> Tiempo de vida: %d segundos.\n", RPCs->arrayRPCs[p].tiempovida);
        }

    }

}
