PROGRAM My_Program
  VAR
    Nitrato AT %MD0 : REAL := 1055211.5;
    Amonio AT %MD1 : REAL := 102.0051215;
    Temperatura AT %MD2 : REAL := 0.84525144544;
    OxigenoDisuelto AT %MD3 : REAL := 10545504.5;
    CaudalAire AT %MD4 : REAL := 105.5;
    CaudalPurga AT %MD5 : REAL := 106.5;
    CaudalRecircInt AT %MD6 : REAL := 107.3;
  END_VAR
  VAR
    MOVE5_OUT : REAL;
  END_VAR

  MOVE5_OUT := MOVE(Temperatura);
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : My_Program;
  END_RESOURCE
END_CONFIGURATION