
#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME SETTLING_POINT

#include "simstruc.h"

#include <malloc.h>
#include <math.h>

#include <stdio.h>
#include <stdlib.h>  

#include "SETTLING_POINT.h"      //Definiciones del proceso y del modelo.


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

	if (mxGetNumberOfElements(PARAMS_SETTLER(S)) != DIMPARAMS_SETTLER)       
	{ ssSetErrorStatus (S,"Vector de Par�metros erroneo"); return; }
	
}
#endif // MDL_CHECK_PARAMETERS



//*******************FUNCION DE INICIALIZACION DEL BLOQUE S-FUNCTION***********************

static void mdlInitializeSizes(SimStruct *S)
{	                              							
	
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

	ssSetNumContStates(S, NUMESTADOSCONTINUOS);				//Especifica el numero de estados continuos de S-function 
    ssSetNumDiscStates(S, NUMESTADOSDISCRETOS);  


    if (!ssSetNumInputPorts(S, NUMPUERTOSENTRADA)) {return;}
    ssSetInputPortWidth(S, IP_INFLUX, ANCHURAPUERTO1ENTRADA); ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortWidth(S, IP_CONSIGNAS, ANCHURAPUERTO2ENTRADA); ssSetInputPortDirectFeedThrough(S, 1, 1);

    if (!ssSetNumOutputPorts(S, NUMPUERTOSSALIDA)) {return;}
    ssSetOutputPortWidth(S,OP_SENSORES,ANCHURAPUERTO1SALIDA); 
	ssSetOutputPortWidth(S,OP_OUTFLUX_EFF,ANCHURAPUERTO2SALIDA);
	ssSetOutputPortWidth(S,OP_OUTFLUX_REC,ANCHURAPUERTO3SALIDA);


    // Intervalos de Muestro
	ssSetNumSampleTimes(S, 1);    //Tiene 1 tiempos de muestreo
	ssSetNumModes(S, 0);          //Specify the size of the block's mode vector
    ssSetNumNonsampledZCs(S, 0);  //Specify the number of states for which a block detects 
	                              //zero crossings that occur between sample points
	
	ssSetOptions(S, SS_OPTION_CALL_TERMINATE_ON_EXIT);

}



//*******************FUNCION DE INICIALIZACION DEL TIEMPO DE MUESTREO***********************

static void mdlInitializeSampleTimes(SimStruct *S)
{   	
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
}



//******************************FUNCION DE INICIALIZACION************************************

#define MDL_INITIALIZE_CONDITIONS                    /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)
static void mdlInitializeConditions(SimStruct *S)
{		
	void **PWork = ssGetPWork(S);
	real_T** Sensores;
	int i;

	for (i=0;i<NUMPARAM_SFUNCT;i++) { PWork[i] = mxGetPr(ssGetSFcnParam(S,i)); }

	// Asignar Memoria para Estados Adicionales
	PWork[2] = (real_T *)malloc(sizeof(real_T)*(NUM_SENSORES));

}

#endif /* MDL_INITIALIZE_CONDITIONS */



//*************************************FUNCION DE START******************************************


#undef MDL_START                          /* Change to #undef to remove function */
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
	void **PWork = ssGetPWork(S);
	InputRealPtrsType uPtrs0 = ssGetInputPortRealSignalPtrs(S,0); /* Influx (kg/d) */            
	InputRealPtrsType uPtrs1 = ssGetInputPortRealSignalPtrs(S,1); /* Consignas */
	real_T dblQRFreal;
	real_T* Sensores;

	Sensores = ((real_T *)PWork[2]);

	if (Q_INF < QRF_INP) {dblQRFreal = Q_INF;}
	else {dblQRFreal = QRF_INP;}

	SST_EFF = F_NS*(iVSS_XB * (XBH_INF + XBA_INF) + iVSS_XI * (XI_INF + XP_INF) + iVSS_XS * XS_INF + XIN_INF);
	NH4_EFF = *uPtrs0[EST_SNH+1];
	NO3_EFF = *uPtrs0[EST_SNO+1];


	y = ssGetOutputPortRealSignal(S,OP_OUTFLUX_EFF);
	y[0] = Q_INF - dblQRFreal;
	for (i=0;i<NUMESTADOSDISUELT;i++){y[i+1] = *uPtrs0[i+1];}
	for (i=NUMESTADOSDISUELT;i<NUMESTADOSMODASM1;i++){y[i+1] = F_NS*(*uPtrs0[i+1]);}

	y = ssGetOutputPortRealSignal(S,OP_OUTFLUX_REC);
	y[0] = dblQRFreal;
	for (i=0;i<NUMESTADOSDISUELT;i++){y[i+1] = *uPtrs0[i+1];}
	for (i=NUMESTADOSDISUELT;i<NUMESTADOSMODASM1;i++)
	{
		if (dblQRFreal == 0) {y[i+1] = 0.;}
		else { y[i+1] = (Q_INF*(1-F_NS) + dblQRFreal*F_NS )*(*uPtrs0[i+1])/dblQRFreal;}
	}
	
	MLSS_RECF = iVSS_XB*(y[EST_XBH+1] + y[EST_XBA+1]) + iVSS_XI*(y[EST_XI+1] + y[EST_XP+1]) + iVSS_XS*y[EST_XS+1] + y[EST_XIN+1];


	//	SALIDA de SENSORES
	y = ssGetOutputPortRealSignal(S,OP_SENSORES);
	for (i=0;i<ANCHURAPUERTO1SALIDA ;i++) { y[i] = Sensores[i];}
	
}



//************************FUNCION DE ACTUALIZACION DE ESTADOS=====================

#undef MDL_UPDATE                    /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
static void mdlUpdate(SimStruct *S, int_T tid)
{


}
#endif /* MDL_UPDATE */


//**********************FUNCION QUE CALCULA LAS DERIVADAS********************

#undef MDL_DERIVATIVES                /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
static void mdlDerivatives(SimStruct *S)
{


}
#endif /* MDL_DERIVATIVES */


/************************************FUNCION QUE TERMINA EL PROCESO*************************/

static void mdlTerminate(SimStruct *S)
{  
	int i;
	void **PWork = ssGetPWork(S);
	real_T* Sensores;

	Sensores = (real_T*)PWork[2];

	// Memoria para estados adicionales
	if (PWork != NULL)
	{
		if (Sensores != NULL) {free(Sensores);}
	}

}


#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif

