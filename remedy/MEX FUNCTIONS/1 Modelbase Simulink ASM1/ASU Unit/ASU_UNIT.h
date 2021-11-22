

// Parametros del modelo nº 1
#include "..\ModN1.h"

// CARACTERISTICAS DE LA PLANTA
#define NUMREACTORES				1
#define AS_UNIT						0


#define NUMESTADOSCONTINUOS			(NUMESTADOSMODASM1*NUMREACTORES)
#define NUMESTADOSDISCRETOS			0


// CARACTERISTICAS DEL BLOQUE
// _____________________________________________________________________

#define NUMPUERTOSENTRADA			2
#define IP_INFLUX					0
#define IP_CONSIGNAS				1

#define ANCHURAPUERTO1ENTRADA		(1+NUMESTADOSMODASM1)		// Caudal + concentraciones entrada D            
#define ANCHURAPUERTO2ENTRADA		4							// KLA, QW, TEMP_LM, PAMB


#define NUMPUERTOSSALIDA			2 
#define OP_SENSORES					0
#define OP_OUTFLUX					1

#define ANCHURAPUERTO1SALIDA		NUM_EASENSORES				// Sensores            
#define ANCHURAPUERTO2SALIDA		(1+NUMESTADOSMODASM1)


// _____________________________________________________________________

// PARAMETROS DE LA S-FUNCTION
#define NUMPARAM_SFUNCT		6
#define PARAM_ESTEQ(S)		ssGetSFcnParam(S,0)
#define CINETICS(S)			ssGetSFcnParam(S,1)
#define ARRHEN(S)			ssGetSFcnParam(S,2)
#define ESTEQUIOM(S)		ssGetSFcnParam(S,3)
#define PARAMS_ASU(S)		ssGetSFcnParam(S,4)
#define INICIALES(S)		ssGetSFcnParam(S,5)


// Dimensiones de los Vectores de Parametros
#define DIMPARAMESTEQ		NUMCOEFESTEQ
#define DIMCINETICOS		NUMCOEFCINETICOS
#define DIMARRHENIUS		NUMCOEFCINETICOS
#define NUMFILESTEQ			NUMREACCIONESBIOL
#define NUMCOLESTEQ			NUMESTADOSMODASM1      
#define DIMPARAMS_ASU		4
#define DIMINICIALES		(NUMESTADOSCONTINUOS+NUMESTADOSDISCRETOS)



// _____________________________________________________________________
////////////////////////////////////////////////////////////////////////
// ASIGNACION DE VECTORES DE TRABAJO
////////////////////////////////////////////////////////////////////////
#define NUMRWORKS				6
#define SO_SAT_TL				RWork[0]
#define DELTA					RWork[1]
#define RHO_W					RWork[2]
#define PV_TL					RWork[3]
#define OMEGA					RWork[4]
#define SO_SAT					RWork[5]


// Vectores de TRABAJO
#define NUMPWORKS			9
#define PARAM_ESTEQUIOM		((real_T *)PWork[0])
#define CINETICOS_20		((real_T *)PWork[1])
#define ARRHENIUS			((real_T *)PWork[2])
#define ESTEQU				((real_T *)PWork[3])
#define PARAM_ASU			((real_T *)PWork[4])
#define x0					((real_T *)PWork[5])	// Estados iniciales
#define CINETICOS_T			((real_T *)PWork[6])	// VECTOR DE PARAMETROS CINETICOS A TEMPERATURA T
#define ESTADOSADIC			((real_T **)PWork[7])	//
#define	LOGFILE				((FILE *)PWork[8])		// Archivo para depuración


// Parámetros
#define V_ASU				PARAM_ASU[0]			// m3
#define DE_TANK				PARAM_ASU[1]			// Effective depth in tanks (m)
#define H_TANK				PARAM_ASU[2]			// Effective depth in tanks (m)
#define BETA_FCT			PARAM_ASU[3]


// ESTADOS ADICIONALES DEl SISTEMA (estados adicionales a los del modelo) 
// TODAVÍA SIN DEFINIR
#define NUM_ESTADOSADIC			2
#define EA_SENSORES				ESTADOSADIC[0]
#define EA_NOT_USED				ESTADOSADIC[1]


#define NUM_EASENSORES			9
#define NUM_EA_NOTUSED			8


// Elementos del vector SENSORES
#define Q_in					(EA_SENSORES[0])
#define Q_w						(EA_SENSORES[1])
#define NO3_ASU					(EA_SENSORES[2])
#define NH4_ASU					(EA_SENSORES[3])
#define DO_ASU					(EA_SENSORES[4])
#define MLSS_ASU				(EA_SENSORES[5])
#define KLa_ASU					(EA_SENSORES[6])
#define Temperature				(EA_SENSORES[7])
#define OUR						(EA_SENSORES[8])

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


#define KLA_INP				(*uPtrs1[0]) 
#define QW_INP			    (*uPtrs1[1])
#define TEMP_ML_INP			(*uPtrs1[2])
#define PAMB_INP			(*uPtrs1[3])


// Posicion INICIAL del Vector de ESTADOS de cada elemento
#define POSINIEST(i)	(NUMESTADOSMODASM1*i)

#define SS(i)				xC[POSINIEST(i)]
#define SO(i)				xC[POSINIEST(i) + 1]
#define SI(i)				xC[POSINIEST(i) + 2]
#define SNO(i)				xC[POSINIEST(i) + 3]
#define SNH(i)				xC[POSINIEST(i) + 4]
#define SND(i)				xC[POSINIEST(i) + 5]
#define SALK(i)				xC[POSINIEST(i) + 6]
#define XI(i)				xC[POSINIEST(i) + 7]
#define XS(i)				xC[POSINIEST(i) + 8]
#define XBH(i)				xC[POSINIEST(i) + 9]
#define XBA(i)				xC[POSINIEST(i) + 10]
#define XP(i)				xC[POSINIEST(i) + 11]
#define XND(i)				xC[POSINIEST(i) + 12]
#define XIN(i)				xC[POSINIEST(i) + 13]


// ESTADOS de cada Elemento de la Planta

// REACTOR ANOX
#define SS_ASU			xC[0]
#define SO_ASU			xC[1]
#define SI_ASU			xC[2]
#define SNO_ASU			xC[3]
#define SNH_ASU			xC[4]
#define SND_ASU			xC[5]
#define SALK_ASU		xC[6]
#define XI_ASU			xC[7]
#define XS_ASU			xC[8]
#define XBH_ASU			xC[9]
#define XBA_ASU			xC[10]
#define XP_ASU			xC[11]
#define XND_ASU			xC[12]
#define XIN_ASU			xC[13]

// CONSTS
#define CNST_PAMB_N		101325
#define CNST_GRAVITY	9.8			// Gravity constant (m/s2)


