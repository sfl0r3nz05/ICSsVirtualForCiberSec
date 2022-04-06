PROGRAM My_Program
  VAR
    Nitrato AT %MD0 : REAL := 1055211.5;
    Amonio AT %MD2 : REAL := 102.0015;
    Temperatura AT %MD4 : REAL := 0.8544;
    OxigenoDisuelto AT %MD6 : REAL := 10504.5;
    Aireacion AT %MD8 : REAL := 100.2;
    CaudalPurga AT %MD10 : REAL := 106.5;
    CaudalRecircInt AT %MD12 : REAL := 57547.5;
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