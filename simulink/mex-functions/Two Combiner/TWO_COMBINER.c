
#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME	TWO_COMBINER

#include "simstruc.h"

#include "TWO_COMBINER.h"      //Definiciones del proceso y del modelo.


//***************FUNCION DE CHEQUEO DE PARAMETROS DE ENTRADA DE LA S-FUNCTION****************
#define MDL_CHECK_PARAMETERS
#if defined(MDL_CHECK_PARAMETERS) && defined(MATLAB_MEX_FILE)
static void mdlCheckParameters(SimStruct *S)
{

}
#endif // MDL_CHECK_PARAMETERS



//*******************FUNCION DE INICIALIZACION DEL BLOQUE S-FUNCTION***********************

static void mdlInitializeSizes(SimStruct *S)
{	                              

    if (!ssSetNumInputPorts(S, NUMPUERTOSENTRADA)) {return;}
    ssSetInputPortWidth(S, IP_INFLUX1, ANCHURAPUERTO1ENTRADA); ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortWidth(S, IP_INFLUX2, ANCHURAPUERTO2ENTRADA); ssSetInputPortDirectFeedThrough(S, 1, 1);

    if (!ssSetNumOutputPorts(S, NUMPUERTOSSALIDA)) {return;}
    ssSetOutputPortWidth(S,OP_OUTFLUX,ANCHURAPUERTO1SALIDA); 
	
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
	InputRealPtrsType uPtrs0 = ssGetInputPortRealSignalPtrs(S,0); /* Influx (kg/d) */            
	InputRealPtrsType uPtrs1 = ssGetInputPortRealSignalPtrs(S,1); /* Consignas */

	// SENSORES
	//========================CALCULO DEL CAUDAL DE ENTRADA=================


	//	SALIDA de SENSORES
	y = ssGetOutputPortRealSignal(S,OP_OUTFLUX);
	y[0] = Q_IN1 + Q_IN2;

	for (i=1;i<ANCHURAPUERTO1SALIDA ;i++) { y[i] = (Q_IN1*(*uPtrs0[i]) + Q_IN2*(*uPtrs1[i]))/(Q_IN1 + Q_IN2) ;}

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


