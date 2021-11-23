

// Parametros del modelo n� 1
#include "../ModN1.h"

// CARACTERISTICAS DE LA PLANTA
#define NUMTANKS					1
#define SETTLER						0


#define NUMESTADOSCONTINUOS			0
#define NUMESTADOSDISCRETOS			0


// CARACTERISTICAS DEL BLOQUE
// _____________________________________________________________________

#define NUMPUERTOSENTRADA			2
#define IP_INFLUX					0
#define IP_CONSIGNAS				1

#define ANCHURAPUERTO1ENTRADA		(1+NUMESTADOSMODASM1)		// Caudal + concentraciones entrada D            
#define ANCHURAPUERTO2ENTRADA		1							// QRECF

#define NUMPUERTOSSALIDA			3 
#define OP_SENSORES					0
#define OP_OUTFLUX_EFF				1
#define OP_OUTFLUX_REC				2

#define ANCHURAPUERTO1SALIDA		NUM_EASENSORES				// Sensores            
#define ANCHURAPUERTO2SALIDA		(1+NUMESTADOSMODASM1)								
#define ANCHURAPUERTO3SALIDA		(1+NUMESTADOSMODASM1)


// _____________________________________________________________________

// PARAMETROS DE LA S-FUNCTION
#define NUMPARAM_SFUNCT		2
#define PARAM_ESTEQ(S)		ssGetSFcnParam(S,0)
#define PARAMS_SETTLER(S)	ssGetSFcnParam(S,1)


// Dimensiones de los Vectores de Parametros
#define DIMPARAMESTEQ			NUMCOEFESTEQ
#define DIMPARAMS_SETTLER		1


// _____________________________________________________________________
////////////////////////////////////////////////////////////////////////
// ASIGNACION DE VECTORES DE TRABAJO
////////////////////////////////////////////////////////////////////////
// Vectores de TRABAJO
#define NUMPWORKS			4
#define PARAM_ESTEQUIOM		PWork[0]
#define PARAM_SETTL			PWork[1]
#define ESTADOSADIC			PWork[2]			//
#define	LOGFILE				PWork[3]		// Archivo para depuraci�n


// Par�metros
#define F_NS				PARAM_SETTL[0]      

// ESTADOS ADICIONALES DEl SISTEMA (estados adicionales a los del modelo) 
// TODAV�A SIN DEFINIR
#define NUM_ESTADOSADIC			2
#define EA_SENSORES				PWork[2][0]
#define EA_NOT_USED				PWork[2][1]

#define NUM_EASENSORES			4
#define NUM_EA_NOTUSED			8

// Elementos del vector SENSORES
#define SST_EFF					(PWork[2][0][0])
#define NH4_EFF					(PWork[2][0][1])
#define NO3_EFF					(PWork[2][0][2])
#define MLSS_RECF				(PWork[2][0][3])

// _____________________________________________________________________

// PUERTOS DE ENTRADAS
#define Q_INF				(*uPtrs0[0])
#define SS_INF				(*uPtrs0[1])
#define SO_INF				(*uPtrs0[2])
#define SI_INF				(*uPtrs0[3])
#define SNO_INF				(*uPtrs0[4])
#define SNH_INF				(*uPtrs0[5])
#define SND_INF				(*uPtrs0[6])
#define SALK_INF			(*uPtrs0[7])
#define XI_INF				(*uPtrs0[8])
#define XS_INF				(*uPtrs0[9])
#define XBH_INF				(*uPtrs0[10])
#define XBA_INF				(*uPtrs0[11])
#define XP_INF				(*uPtrs0[12])
#define XND_INF				(*uPtrs0[13])
#define XIN_INF				(*uPtrs0[14])


#define QRF_INP				(*uPtrs1[0]) 

