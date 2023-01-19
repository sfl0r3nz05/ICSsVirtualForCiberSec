
#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME  TWO_REL_SPLITTER

#include "simstruc.h"

#include "TWO_REL_SPLITTER.h"      //Definiciones del proceso y del modelo.


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

	if (mxGetNumberOfElements(PARAMS_SPLITTER(S)) != DIMPARAMS_SPLITTER)
	{ ssSetErrorStatus (S,"Vector de Params erroneo");	return;	}

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
		    mdlCheckParameters(S);                          // Chequear que los parámetros son correctos
			if (ssGetErrorStatus(S) != NULL) {return;}
		}
		else return;	
	#endif	

	// AQUÍ LA INICIALIZACIÓN
	// Lectura de Parametros de la S-Function
	ssSetNumPWork(S, NUMPWORKS);  //Specify the size of a block's pointer work vector 

    if (!ssSetNumInputPorts(S, NUMPUERTOSENTRADA)) {return;}
    ssSetInputPortWidth(S, IP_INFLUX, ANCHURAPUERTO1ENTRADA); ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S, NUMPUERTOSSALIDA)) {return;}
    ssSetOutputPortWidth(S,OP_OUTFLUX1,ANCHURAPUERTOS_SALIDA);
	ssSetOutputPortWidth(S,OP_OUTFLUX2,ANCHURAPUERTOS_SALIDA);
	
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
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
}



//******************************FUNCION DE INICIALIZACION************************************

#define MDL_INITIALIZE_CONDITIONS                    /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)
static void mdlInitializeConditions(SimStruct *S)
{	
	int_T i;
	void **PWork = ssGetPWork(S);                     //Returns the pointer work vector used by the block 
	
	for (i=0;i<NUMPARAM_SFUNCT;i++) { PWork[i] = mxGetPr(ssGetSFcnParam(S,i)); }

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
	real_T *y1, *y2, dbl_FQ;	// Puntero a los puertos de salida	
	InputRealPtrsType uPtrs0 = ssGetInputPortRealSignalPtrs(S,0); 
	void **PWork = ssGetPWork(S);                     //Returns the pointer work vector used by the block 

	if (FQ_O1 > 1) {dbl_FQ = 1;}
	else if (FQ_O1 <0) {dbl_FQ = 0;}
	else {dbl_FQ  = FQ_O1;}
	
	y1 = ssGetOutputPortRealSignal(S,OP_OUTFLUX1);
	y2 = ssGetOutputPortRealSignal(S,OP_OUTFLUX2);

	y1[0] = Q_IN*dbl_FQ;
	y2[0] = Q_IN*(1-dbl_FQ);
	
	for (i=1;i<ANCHURAPUERTOS_SALIDA;i++) { y1[i] = y2[i] = *uPtrs0[i];}

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

}
#endif /* MDL_DERIVATIVES */


/************************************FUNCION QUE TERMINA EL PROCESO*************************/

static void mdlTerminate(SimStruct *S)
{  

}


#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif


