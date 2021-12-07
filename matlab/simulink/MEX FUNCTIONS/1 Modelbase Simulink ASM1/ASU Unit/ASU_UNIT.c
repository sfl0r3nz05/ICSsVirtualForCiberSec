
#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME ASU_UNIT

#include "simstruc.h"

#include <malloc.h>
#include <math.h>

#include <stdio.h>
#include <stdlib.h>  

#include "ASU_UNIT.h"      //Definiciones del proceso y del modelo.


//***************FUNCION DE CHEQUEO DE PARAMETROS DE ENTRADA DE LA S-FUNCTION****************
#define MDL_CHECK_PARAMETERS
#if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)
static void mdlCheckParameters(SimStruct *S)
{
	int_T i;

   	for (i=0;i<NUMPARAM_SFUNCT;i++)
	{
		real_T *pr;
		int_T el;
		int_T nEls;

		if ( mxIsEmpty(ssGetSFcnParam(S,i)) || mxIsSparse(ssGetSFcnParam(S,i))	
			|| mxIsComplex(ssGetSFcnParam(S,i)) || !mxIsNumeric(ssGetSFcnParam(S,i)) )
		{ ssSetErrorStatus (S,"Error en los Parametros del Bloque"); return; }
		
		pr = mxGetPr(ssGetSFcnParam(S,i));
		nEls = mxGetNumberOfElements(ssGetSFcnParam(S,i));
		for (el=0;el<nEls;el++)
		{ if (!mxIsFinite(pr[el])) { ssSetErrorStatus (S,"Los Parametros del Bloque han de ser finitos"); return; } }
	}

	if (mxGetNumberOfElements(PARAM_ESTEQ(S)) != DIMPARAMESTEQ)
	{ ssSetErrorStatus (S,"Vector de Params erroneo");	return;	}

	if (mxGetNumberOfElements(CINETICS(S)) != DIMCINETICOS)
	{ ssSetErrorStatus (S,"Vector de Cineticos erroneo");	return;	}

	if (mxGetNumberOfElements(ARRHEN(S)) != DIMARRHENIUS)
	{ ssSetErrorStatus (S,"Vector de Arrhenius erroneo");	return;	}

	if (mxGetM(ESTEQUIOM(S)) != NUMFILESTEQ || mxGetN(ESTEQUIOM(S)) != NUMCOLESTEQ)
	{ ssSetErrorStatus (S,"Matriz de Estequiometrias erronea");	return;	}

	if (mxGetNumberOfElements(PARAMS_ASU(S)) != DIMPARAMS_ASU)       
	{ ssSetErrorStatus (S,"Vector de Par�metros erroneo"); return; }
	
	if (mxGetNumberOfElements(INICIALES(S)) != (NUMESTADOSMODASM1*NUMREACTORES))
	{ ssSetErrorStatus (S,"Vector de Estados Iniciales erroneo"); return; }


}
#endif // MDL_CHECK_PARAMETERS



//*******************FUNCION DE INICIALIZACION DEL BLOQUE S-FUNCTION***********************

static void mdlInitializeSizes(SimStruct *S)
{	                              
	void **PWork = ssGetPWork(S);                     //Returns the pointer work vector used by the block 
	
	ssSetNumSFcnParams(S, NUMPARAM_SFUNCT);           // Number of expected parameters  

    #if defined (MATLAB_MEX_FILE)
		if (ssGetNumSFcnParams(S) == ssGetSFcnParamsCount(S)) 
		{
		    mdlCheckParameters(S);                          // Chequear que los par�metros son correctos
			if (ssGetErrorStatus(S) != NULL) {return;}
		}
		else return;	
	#endif	

	// AQU� LA INICIALIZACI�N
	// Lectura de Parametros de la S-Function
	ssSetNumPWork(S, NUMPWORKS);  //Specify the size of a block's pointer work vector
	ssSetNumRWork(S, NUMRWORKS);  //Specify the size of a block's real work vector
	
	ssSetNumContStates(S, NUMESTADOSCONTINUOS);				//Especifica el numero de estados continuos de S-function 
    ssSetNumDiscStates(S, NUMESTADOSDISCRETOS);  


    if (!ssSetNumInputPorts(S, NUMPUERTOSENTRADA)) {return;}
    ssSetInputPortWidth(S, IP_INFLUX, ANCHURAPUERTO1ENTRADA); ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortWidth(S, IP_CONSIGNAS, ANCHURAPUERTO2ENTRADA); ssSetInputPortDirectFeedThrough(S, 1, 1);

    if (!ssSetNumOutputPorts(S, NUMPUERTOSSALIDA)) {return;}
    ssSetOutputPortWidth(S,OP_SENSORES,ANCHURAPUERTO1SALIDA); 
	ssSetOutputPortWidth(S,OP_OUTFLUX,ANCHURAPUERTO2SALIDA);


    // Intervalos de Muestro
	ssSetNumSampleTimes(S, 1);    //Tiene 1 tiempos de muestreo
	ssSetNumModes(S, 0);          //Specify the size of the block's mode vector
    ssSetNumNonsampledZCs(S, 0);  //Specify the number of states for which a block detects 
	                              //zero crossings that occur between sample points
    ssSetOptions(S, 0);

}



//*******************FUNCION DE INICIALIZACION DEL TIEMPO DE MUESTREO***********************

static void mdlInitializeSampleTimes(SimStruct *S)
{
    	
	ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);

    //ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    //ssSetSampleTime(S, 1, PERIODO); 
}



//******************************FUNCION DE INICIALIZACION************************************

#define MDL_INITIALIZE_CONDITIONS                    /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)
static void mdlInitializeConditions(SimStruct *S)
{	
	int_T i;
	void **PWork = ssGetPWork(S);                     //Returns the pointer work vector used by the block 
	
	real_T *xC = ssGetContStates(S);                  //to get the real_T continuous state vector
	real_T *xD = ssGetRealDiscStates(S);              //to get the real_T discrete state vector
	
	for (i=0;i<NUMPARAM_SFUNCT;i++) { PWork[i] = mxGetPr(ssGetSFcnParam(S,i)); }

	for (i=0;i<NUMESTADOSCONTINUOS;i++)	{xC[i] = x0[i];}  //Se carga en el vector "xC" los valores iniciales                                                        

	CINETICOS_T = (real_T *)malloc(sizeof(real_T)*(NUMCOEFCINETICOS));

	// Asignar Memoria para Estados Adicionales
	ESTADOSADIC = (real_T **)malloc(sizeof(real_T *)*(NUM_ESTADOSADIC));

	EA_SENSORES = (real_T *)malloc(sizeof(real_T)*(NUM_EASENSORES));
	EA_NOT_USED = (real_T *)malloc(sizeof(real_T)*(NUM_EA_NOTUSED));

	
}

#endif /* MDL_INITIALIZE_CONDITIONS */



//*************************************FUNCION DE START******************************************


#define MDL_START                          /* Change to #undef to remove function */
#if defined(MDL_START) 
static void mdlStart(SimStruct *S)
{

}
#endif /*  MDL_START */


/****************************FUNCION DE GENERACION DE SALIDAS****************************
/* Function: mdlOutputs
    In this function, you compute the outputs of your S-function
    block. Generally outputs are placed in the output vector, ssGetY(S). */

static void mdlOutputs(SimStruct *S, int_T tid)
{
	int i;
	real_T *y;	// Puntero a los puertos de salida	
	real_T *xC = ssGetContStates(S);
	void **PWork = ssGetPWork(S);
	real_T *RWork = ssGetRWork(S);
	InputRealPtrsType uPtrs0 = ssGetInputPortRealSignalPtrs(S,0); /* Influx (kg/d) */            
	InputRealPtrsType uPtrs1 = ssGetInputPortRealSignalPtrs(S,1); /* Consignas */
	void CalcularEstadosAlgebraicos(SimStruct *);

	CalcularEstadosAlgebraicos(S);

	// SENSORES
	//========================CALCULO DEL CAUDAL DE ENTRADA=================
	Q_in = Q_INF;
	Q_w = QW_INP;
	NO3_ASU = SNO_ASU;
	NH4_ASU = SNH_ASU;
	DO_ASU = SO_ASU;
	KLa_ASU = KLA_INP;
	
	//	SALIDA de SENSORES
	y = ssGetOutputPortRealSignal(S,OP_SENSORES);
	for (i=0;i<ANCHURAPUERTO1SALIDA ;i++) { y[i] = EA_SENSORES[i];}
	
	// OUTPUT FLUX
	y = ssGetOutputPortRealSignal(S,OP_OUTFLUX);
	y[0] = Q_INF - QW_INP;
	for (i=0;i<NUMESTADOSMODASM1;i++) { y[i+1] = xC[POSINIEST(AS_UNIT)+i];}
}



/************************FUNCION DE ACTUALIZACION DE ESTADOS=====================

#define MDL_UPDATE                    /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
static void mdlUpdate(SimStruct *S, int_T tid)
{


}
#endif /* MDL_UPDATE */


//**********************FUNCION QUE CALCULA LAS DERIVADAS********************

#define MDL_DERIVATIVES                /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
static void mdlDerivatives(SimStruct *S)
{
	int i;
	real_T *xC = ssGetContStates(S), *dX = ssGetdX(S);
	void **PWork = ssGetPWork(S);
	real_T *RWork = ssGetRWork(S);
	InputRealPtrsType uPtrs1 = ssGetInputPortRealSignalPtrs(S,1);

	void CalcularEstadosAlgebraicos(SimStruct *);
	void CalcularDerivFisicas(real_T *, SimStruct *);
	void CalcConversionTerm(real_T *, real_T *, SimStruct *);


	CalcularEstadosAlgebraicos(S);


	//==================================CALCULO DERIVADA BIOLOGICA======================
	for (i=0;i<NUMESTADOSCONTINUOS;i++){dX[i]=0;} 
	
	CalcularDerivFisicas(dX,S); 
	CalcConversionTerm(&dX[POSINIEST(AS_UNIT)], &xC[POSINIEST(AS_UNIT)], S); 

	//SO_Sat = 14.65 - 0.41 * TEMP_INP + 0.00799 * pow(TEMP_INP,2)  - 0.0000778 * pow(TEMP_INP,3);
		
	
	RHO_W = 999.842594 + 6.793052E-2*TEMP_ML_INP - 9.095290E-3*pow(TEMP_ML_INP,2)+ 1.001685E-4*pow(TEMP_ML_INP,3) 
				- 1.120083E-6*pow(TEMP_ML_INP,4) + 6.536332E-9*pow(TEMP_ML_INP,5);
	
	PV_TL = CNST_PAMB_N*exp(11.8571 - (3840.70/(273.15 + TEMP_ML_INP)) - (216961/pow(273.15 + TEMP_ML_INP,2)));
	
	DELTA = (CNST_PAMB_N - PV_TL + RHO_W*CNST_GRAVITY*DE_TANK*H_TANK)/(CNST_PAMB_N - PV_TL);	

	OMEGA = (PAMB_INP - PV_TL + RHO_W*CNST_GRAVITY*DE_TANK*H_TANK)/(CNST_PAMB_N - PV_TL + RHO_W*CNST_GRAVITY*DE_TANK*H_TANK);
	
	SO_SAT_TL = exp(-139.344110+(1.575701E5/(273.15+TEMP_ML_INP))-(6.642308E7/pow(273.15+TEMP_ML_INP,2)) + (1.2438E10/pow(273.15+TEMP_ML_INP,3))
						- (8.621949E11/pow(273.15+TEMP_ML_INP,4)));

	SO_SAT = OMEGA*BETA_FCT*DELTA*SO_SAT_TL;
	
	dX[POSINIEST(AS_UNIT)+EST_SO] += KLA_INP*(SO_SAT - SO_ASU);  
	
}
#endif /* MDL_DERIVATIVES */


/************************************FUNCION QUE TERMINA EL PROCESO*************************/

static void mdlTerminate(SimStruct *S)
{  
	int i;
	void **PWork = ssGetPWork(S); 

	if (CINETICOS_T != NULL) {free(CINETICOS_T);}

	// Memoria para estados adicionales
	for (i=0;i<NUM_ESTADOSADIC;i++) 
		if (ESTADOSADIC[i] != NULL) {free(ESTADOSADIC[i]);}
	
	if (ESTADOSADIC != NULL) {free(ESTADOSADIC);}
	if (LOGFILE != NULL) {fclose (LOGFILE);}	// Cierra el FICHERO
}


#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif


// ==============Funcion que calcula las derivadas=================== 
void CalcularDerivFisicas(real_T *dX, SimStruct *S) // Difusiones y attachment-detachment
{
	int idcEstado;
	real_T	*xC = ssGetContStates(S);
	void **PWork = ssGetPWork(S);
	InputRealPtrsType uPtrs0 = ssGetInputPortRealSignalPtrs(S,0);
	InputRealPtrsType uPtrs1 = ssGetInputPortRealSignalPtrs(S,1);

	// ssGetSampleTime(S, 0);
	
	/////////////////// BULK

	// Hidr�ulica Entrada-salida tanque
	for (idcEstado=0;idcEstado<NUMESTADOSMODASM1;idcEstado++)
	{ dX[POSINIEST(AS_UNIT)+idcEstado] =  (Q_INF*(*uPtrs0[idcEstado+1] - xC[POSINIEST(AS_UNIT)+idcEstado]))/V_ASU;}
	
}



void CalcConversionTerm(real_T *dX, real_T *xC, SimStruct *S)
{	
	void **PWork = ssGetPWork(S);

	double EstXS, EstXBH, EstXBA;
	double Rho1,Rho2,Rho3,Rho4,Rho5,Rho6,Rho7,Rho8, Rho9;
	double MonodSS, MonodSNH, SubMonodXS, MonodXS, SwitzeSOhet;
	double SwitchSOhet, SwitchSOaut, SwitchSNHhet, SwitchSNHaut, SwitchSNOhet;
	
	// __________________________________________________________________________	
	// MONOD Y SWITCHING FUNCTIONS
	MonodSS=xC[EST_SS]/(kS+xC[EST_SS]);
	MonodSNH=xC[EST_SNH]/(kNH+xC[EST_SNH]);
	EstXS=xC[EST_XS]; EstXBH=xC[EST_XBH]; EstXBA=xC[EST_XBA];
	
	if(EstXS==0.0 || EstXBH==0.0) { MonodXS=0.0; }
	else { SubMonodXS=EstXS/EstXBH; MonodXS=SubMonodXS/(kX+SubMonodXS); }

	SwitzeSOhet=kOH/(kOH+xC[EST_SO]);
	SwitchSOhet=xC[EST_SO]/(kOH+xC[EST_SO]);
	SwitchSOaut=xC[EST_SO]/(kOA+xC[EST_SO]);

	SwitchSNHhet=xC[EST_SNH]/(kNHG+xC[EST_SNH]);
	SwitchSNHaut=xC[EST_SNH]/(kNH+xC[EST_SNH]);
	SwitchSNOhet=xC[EST_SNO]/(kNO+xC[EST_SNO]);

	// __________________________________________________________________________	
	// CINETICAS
	
	Rho1 = muH*MonodSS*SwitchSOhet*SwitchSNHhet*EstXBH;
	Rho2= muH*nuG*MonodSS*SwitzeSOhet*SwitchSNOhet*SwitchSNHhet*EstXBH;
	//Rho2 = muH*nuG*MonodSS*SwitzeSOhet*SwitchSNOhet*EstXBH;
	Rho3 = muA*SwitchSNHaut*SwitchSOaut*EstXBA;
	Rho4 = bH*EstXBH;
	Rho5 = bA*EstXBA;
	Rho6 = kA*xC[EST_SND]*EstXBH;
	Rho7 = kH*MonodXS*(SwitchSOhet+nuH*SwitzeSOhet*SwitchSNOhet)*EstXBH;
	Rho8 = Rho7*xC[EST_XND]/EstXS;
	Rho9 = 0; 

	OUR = - (ESTEQ_SO_R1*Rho1+ESTEQ_SO_R3*Rho3 + ESTEQ_SO_R9*Rho9);

	dX[EST_SS]+=ESTEQ_SS_R1*(Rho1+Rho2)+Rho7;
	dX[EST_SO] -= OUR;
	dX[EST_SNO]+=ESTEQ_SNO_R2*Rho2+ESTEQ_SNO_R3*Rho3;
	dX[EST_SNH]+=ESTEQ_SNH_R1*(Rho1+Rho2)+ESTEQ_SNH_R3*Rho3+ESTEQ_SNH_R6*Rho6;
	dX[EST_SND]+=Rho8-Rho6;
	dX[EST_SALK]+=ESTEQ_SALK_R1*Rho1+ESTEQ_SALK_R2*Rho2+ESTEQ_SALK_R3*Rho3+ESTEQ_SALK_R6*Rho6;

	dX[EST_XS]+=ESTEQ_XS_R4*(Rho4+Rho5)-Rho7;
	dX[EST_XBH]+=Rho1+Rho2-Rho4;
	dX[EST_XBA]+=Rho3-Rho5;
	dX[EST_XP]+=ESTEQ_XP_R4*(Rho4+Rho5);
	dX[EST_XND]+=ESTEQ_XND_R4*(Rho4+Rho5)-Rho8;

}


void CalcularEstadosAlgebraicos(SimStruct *S)
{
	int i;
	real_T *xC = ssGetContStates(S);
	void **PWork = ssGetPWork(S);
	InputRealPtrsType uPtrs0 = ssGetInputPortRealSignalPtrs(S,0); /* Influx (kg/d) */            
	InputRealPtrsType uPtrs1 = ssGetInputPortRealSignalPtrs(S,1); /* Consignas */

	MLSS_ASU = iVSS_XB*(XBH_ASU+XBA_ASU) + iVSS_XI*(XI_ASU + XP_ASU) + iVSS_XS*XS_ASU + XIN_ASU;

	// Temperatura, pH y KLa
	Temperature = TEMP_ML_INP;
	
	// Actualizaci�n de los coeficientes cin�ticos
	for (i=0;i<NUMCOEFCINETICOS;i++) {CINETICOS_T[i] = CINETICOS_20[i]*pow(ARRHENIUS[i], Temperature - 20.);}

}