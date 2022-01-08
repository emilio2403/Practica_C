#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define IDRPC 5
#define RPC 10

typedef char tIRPC [IDRPC];
typedef int tTvida;

typedef struct
{
    tIRPC idRPC;
    tTvida tiempovida;

} tRPC;

typedef int tNumRPCActivas;
typedef tRPC tArrayRPCs [RPC];

typedef struct
{
    tNumRPCActivas numRPCs;
    tArrayRPCs arrayRPCs;

} tRPCs;

extern bool buscarRPCPorId(int *l, tIRPC nid, const tRPCs RPCs);
extern bool haySitioEnRPCs(const tRPCs RPCs, int *r);
extern void leerRPC(tIRPC nRPC);
extern void altaRPCEnServidor(tRPCs *RPCs);
extern void inicializarRPCs(tRPCs *listaRPCs);
extern void mostrarRPCs(const tRPCs *RPCs);
