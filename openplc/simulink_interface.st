FUNCTION_BLOCK Simulink_Conversion
  VAR_INPUT
    int_part : UINT;
    factor : INT;
    dec_part: UINT;
  END_VAR
  VAR
    int_real : REAL;
    factor_real : REAL;
    dec_real : REAL;
  END_VAR
  VAR_OUTPUT
    real_out: REAL;
  END_VAR

  (*Calculate decimal part*)
  dec_real := UINT_TO_REAL(dec_part);
  dec_real := dec_real / 10000.0;
  
  (*Calculate real number*)
  int_real := UINT_TO_REAL(int_part);
  factor_real := INT_TO_REAL(factor);
  real_out := (int_real * factor_real) + dec_real;

END_FUNCTION_BLOCK





PROGRAM My_Program
  VAR
    Temperatura_int AT %IW0 : UINT := 1;
    Temperatura_factor AT %IW1 : INT := 1;
    Temperatura_dec AT %IW2 : UINT := 57;
    OxigenoDisuelto_int AT %IW3 : UINT := 4;
    OxigenoDisuelto_factor AT %IW4 : INT := 1;
    OxigenoDisuelto_dec AT %IW5 : UINT := 57;
    Amonio_int AT %IW6 : UINT := 2;
    Amonio_factor AT %IW7 : INT := 1;
    Amonio_dec AT %IW8 : UINT := 57;
    Nitrato_int AT %IW9 : UINT := 1;
    Nitrato_factor AT %IW10 : INT := 1;
    Nitrato_dec AT %IW11 : UINT := 57;
    Aireacion AT %QW0 : UINT := 100;
    CaudalPurga AT %QW1 : UINT := 106;
    CaudalRecInr AT %QW2 : UINT := 5000;
    Temperatura_real AT %MD0 : REAL;
    OxigenoDisuelto_real AT %MD3 : REAL;
    Amonio_real AT %MD1 : REAL;
    Nitrato_real AT %MD2 : REAL;
  END_VAR
  VAR
    MOVE5_OUT : INT;
    Simulink_Conversion0: Simulink_Conversion;
    Simulink_Conversion1: Simulink_Conversion;
    Simulink_Conversion2: Simulink_Conversion;
    Simulink_Conversion3: Simulink_Conversion;
  END_VAR

  Simulink_Conversion0(int_part := Temperatura_int, factor := Temperatura_factor, dec_part:= Temperatura_dec);
  Temperatura_real := Simulink_Conversion0.real_out;
  Simulink_Conversion1(int_part := Amonio_int, factor := Amonio_factor, dec_part:= Amonio_dec);
  Amonio_real := Simulink_Conversion1.real_out;
  Simulink_Conversion2(int_part := Nitrato_int, factor := Nitrato_factor, dec_part:= Nitrato_dec);
  Nitrato_real := Simulink_Conversion2.real_out;
  Simulink_Conversion3(int_part := OxigenoDisuelto_int, factor := OxigenoDisuelto_factor, dec_part:= OxigenoDisuelto_dec);
  OxigenoDisuelto_real := Simulink_Conversion3.real_out;
  
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : My_Program;
  END_RESOURCE
END_CONFIGURATION
