

// Parametros del modelo n� 1
#include "../ModN1.h"

// CARACTERISTICAS DEL BLOQUE
// _____________________________________________________________________

#define NUMPUERTOSENTRADA			2
#define IP_INFLUX					0
#define IP_QOUT2					1

#define ANCHURAPUERTO1ENTRADA		(1+NUMESTADOSMODASM1)		// Caudal + concentraciones entrada1            
#define ANCHURAPUERTO2ENTRADA		1							// Q2            


#define NUMPUERTOSSALIDA			2 
#define OP_OUTFLUX1					0
#define OP_OUTFLUX2					1

#define ANCHURAPUERTOS_SALIDA		(1+NUMESTADOSMODASM1)		// Caudal + concentraciones salida            


// _____________________________________________________________________

// PUERTOS DE ENTRADAS
#define Q_IN				(*uPtrs0[0])
#define SS_IN				(*uPtrs0[1])
#define SO_IN				(*uPtrs0[2])
#define SI_IN				(*uPtrs0[3])
#define SNO_IN				(*uPtrs0[4])
#define SNH_IN				(*uPtrs0[5])
#define SND_IN				(*uPtrs0[6])
#define SALK_IN				(*uPtrs0[7])
#define XI_IN				(*uPtrs0[8])
#define XS_IN				(*uPtrs0[9])
#define XBH_IN				(*uPtrs0[10])
#define XBA_IN				(*uPtrs0[11])
#define XP_IN				(*uPtrs0[12])
#define XND_IN				(*uPtrs0[13])
#define XIN_IN				(*uPtrs0[14])


#define Q_O2				(*uPtrs1[0])  


