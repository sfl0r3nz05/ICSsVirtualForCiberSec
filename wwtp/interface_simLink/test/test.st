
PROGRAM My_Program
  VAR
    Temperatura_int AT %IW0 : INT := 9999;
    OxigenoDisuelto_int AT %IW1 : INT := 4;
    Amonio_int AT %IW2 : INT := 2;
    Nitrato_int AT %IW3 : INT := 1;
    Aireacion AT %QW0 : INT := 100;
    CaudalPurga AT %QW1 : INT := 106;
    CaudalRecInr AT %QW2 : INT := 5000;
  END_VAR
  VAR
    MOVE5_OUT : INT;
  END_VAR
    MOVE5_OUT := MOVE(Temperatura_int);

  
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : My_Program;
  END_RESOURCE
END_CONFIGURATION
