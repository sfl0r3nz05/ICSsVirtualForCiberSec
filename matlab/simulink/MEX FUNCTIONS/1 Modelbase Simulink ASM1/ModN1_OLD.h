// Parámetros del Modelo Nº 1

// El Modelo Nº1 tiene 13 estados y 8 reacciones
#define NUMESTADOSMODASM1		14
#define NUMREACCIONESBIOL		9
#define NUMESTADOSDISUELT		7
#define NUMESTADOSPARTIC		7
#define NUMCOEFESTEQ			8
#define NUMCOEFCINETICOS		15

// ESTEQUIOMETRICOS
#define yH				PARAM_ESTEQUIOM[0]
#define yA				PARAM_ESTEQUIOM[1]
#define fP				PARAM_ESTEQUIOM[2]
#define iXB				PARAM_ESTEQUIOM[3]
#define iXP				PARAM_ESTEQUIOM[4]
#define iVSS_XB			PARAM_ESTEQUIOM[5]
#define iVSS_XI			PARAM_ESTEQUIOM[6]
#define iVSS_XS			PARAM_ESTEQUIOM[7]

// CINETICOS
#define muH				CINETICOS_T[0]
#define nuG				CINETICOS_T[1]
#define bH				CINETICOS_T[2]
#define kS				CINETICOS_T[3]
#define kA				CINETICOS_T[4]
#define	kNHG			CINETICOS_T[5]

#define kH				CINETICOS_T[6]
#define nuH				CINETICOS_T[7]
#define kOH				CINETICOS_T[8]
#define kNO				CINETICOS_T[9]
#define kX				CINETICOS_T[10]

#define muA				CINETICOS_T[11]
#define	bA				CINETICOS_T[12]
#define kOA				CINETICOS_T[13]
#define kNH				CINETICOS_T[14]

#define Arrh_muH		ARRHENIUS[0]
#define Arrh_nuG		ARRHENIUS[1]
#define Arrh_bH			ARRHENIUS[2]
#define Arrh_kS			ARRHENIUS[3]
#define Arrh_kA			ARRHENIUS[4]
#define	Arrh_kNHG		ARRHENIUS[5]

#define Arrh_kH			ARRHENIUS[6]
#define Arrh_nuH		ARRHENIUS[7]
#define Arrh_kOH		ARRHENIUS[8]
#define Arrh_kNO		ARRHENIUS[9]
#define Arrh_kX			ARRHENIUS[10]

#define Arrh_muA		ARRHENIUS[11]
#define	Arrh_bA			ARRHENIUS[12]
#define Arrh_kOA		ARRHENIUS[13]
#define Arrh_kNH		ARRHENIUS[14]


// ESTADOS DEL MODELO Nº1
#define EST_SS			0
#define EST_SO			1
#define EST_SI			2
#define EST_SNO			3
#define EST_SNH			4
#define EST_SND			5
#define EST_SALK		6

#define EST_XI			7
#define EST_XS			8
#define EST_XBH			9
#define EST_XBA			10
#define EST_XP			11
#define EST_XND			12
#define EST_XIN			13


// Reacciones BIOLOGICAS
#define CRECIM_AEROB_XBH	0
#define CRECIM_ANOX_XBH		1	
#define CRECIM_AEROB_XBA	2
#define LISIS_XBH			3
#define LISIS_XBA			4
#define AMONIFICACION		5
#define HIDROLISIS_XS		6
#define HIDROLISIS_XND		7
#define AERACION			8



// A lo mejor lo elimino ...

//Matriz de ESTEQUIOMETRIA
#define ESTEQ_SS_R1			ESTEQU[0]
#define ESTEQ_SS_R2			ESTEQU[1]
#define ESTEQ_SS_R7			ESTEQU[6]

#define ESTEQ_SO_R1			ESTEQU[9]
#define ESTEQ_SO_R3			ESTEQU[11]
#define ESTEQ_SO_R9			ESTEQU[17]

#define ESTEQ_SNO_R2		ESTEQU[28]
#define ESTEQ_SNO_R3		ESTEQU[29]

#define ESTEQ_SNH_R1		ESTEQU[36]
#define ESTEQ_SNH_R2		ESTEQU[37]
#define ESTEQ_SNH_R3		ESTEQU[38]
#define ESTEQ_SNH_R6		ESTEQU[41]

#define ESTEQ_SND_R6		ESTEQU[50]
#define ESTEQ_SND_R8		ESTEQU[52]

#define ESTEQ_SALK_R1		ESTEQU[54]
#define ESTEQ_SALK_R2		ESTEQU[55]
#define ESTEQ_SALK_R3		ESTEQU[56]
#define ESTEQ_SALK_R6		ESTEQU[59]

#define ESTEQ_XS_R4			ESTEQU[75]
#define ESTEQ_XS_R5			ESTEQU[76]
#define ESTEQ_XS_R7			ESTEQU[78]

#define ESTEQ_XBH_R1		ESTEQU[81]
#define ESTEQ_XBH_R2		ESTEQU[82]
#define ESTEQ_XBH_R4		ESTEQU[84]

#define ESTEQ_XBA_R3		ESTEQU[92]
#define ESTEQ_XBA_R5		ESTEQU[94]

#define ESTEQ_XP_R4			ESTEQU[102]
#define ESTEQ_XP_R5			ESTEQU[103]

#define ESTEQ_XND_R4		ESTEQU[111]
#define ESTEQ_XND_R5		ESTEQU[112]
#define ESTEQ_XND_R8		ESTEQU[115]

