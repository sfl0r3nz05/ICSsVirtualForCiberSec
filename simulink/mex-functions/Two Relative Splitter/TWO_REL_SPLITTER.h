

// Parametros del modelo n� 1
#include "../ModN1.h"

// CARACTERISTICAS DEL BLOQUE
// _____________________________________________________________________

#define NUMPUERTOSENTRADA			1
#define IP_INFLUX					0

#define ANCHURAPUERTO1ENTRADA		(1+NUMESTADOSMODASM1)		// Caudal + concentraciones entrada1            


#define NUMPUERTOSSALIDA			2 
#define OP_OUTFLUX1					0
#define OP_OUTFLUX2					1

#define ANCHURAPUERTOS_SALIDA		(1+NUMESTADOSMODASM1)		// Caudal + concentraciones salida            

// PARAMETROS DE LA S-FUNCTION
#define NUMPARAM_SFUNCT			1
#define PARAMS_SPLITTER(S)		ssGetSFcnParam(S,0)

// Dimensiones de los Vectores de Parametros
#define DIMPARAMS_SPLITTER		1

#define NUMPWORKS			1
#define PARAM_SPLT			((real_T *)PWork[0])

// Par�metros
#define FQ_O1				PARAM_SPLT[0]  


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



