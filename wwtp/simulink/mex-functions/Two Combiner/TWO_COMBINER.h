

// Parametros del modelo n� 1
#include "../ModN1.h"

// CARACTERISTICAS DEL BLOQUE
// _____________________________________________________________________

#define NUMPUERTOSENTRADA			2
#define IP_INFLUX1					0
#define IP_INFLUX2					1

#define ANCHURAPUERTO1ENTRADA		(1+NUMESTADOSMODASM1)		// Caudal + concentraciones entrada1            
#define ANCHURAPUERTO2ENTRADA		(1+NUMESTADOSMODASM1)		// Caudal + concentraciones entrada2


#define NUMPUERTOSSALIDA			1 
#define OP_OUTFLUX					0

#define ANCHURAPUERTO1SALIDA		(1+NUMESTADOSMODASM1)		// Caudal + concentraciones salida            


// _____________________________________________________________________


// PUERTOS DE ENTRADAS
#define Q_IN1					(*uPtrs0[0])
#define SS_IN1				(*uPtrs0[1])
#define SO_IN1				(*uPtrs0[2])
#define SI_IN1				(*uPtrs0[3])
#define SNO_IN1				(*uPtrs0[4])
#define SNH_IN1				(*uPtrs0[5])
#define SND_IN1				(*uPtrs0[6])
#define SALK_IN1			(*uPtrs0[7])
#define XI_IN1				(*uPtrs0[8])
#define XS_IN1				(*uPtrs0[9])
#define XBH_IN1				(*uPtrs0[10])
#define XBA_IN1				(*uPtrs0[11])
#define XP_IN1				(*uPtrs0[12])
#define XND_IN1				(*uPtrs0[13])
#define XIN_IN1				(*uPtrs0[14])


#define Q_IN2					(*uPtrs1[0])
#define SS_IN2				(*uPtrs1[1])
#define SO_IN2				(*uPtrs1[2])
#define SI_IN2				(*uPtrs1[3])
#define SNO_IN2				(*uPtrs1[4])
#define SNH_IN2				(*uPtrs1[5])
#define SND_IN2				(*uPtrs1[6])
#define SALK_IN2			(*uPtrs1[7])
#define XI_IN2				(*uPtrs1[8])
#define XS_IN2				(*uPtrs1[9])
#define XBH_IN2				(*uPtrs1[10])
#define XBA_IN2				(*uPtrs1[11])
#define XP_IN2				(*uPtrs1[12])
#define XND_IN2				(*uPtrs1[13])
#define XIN_IN2				(*uPtrs1[14])
