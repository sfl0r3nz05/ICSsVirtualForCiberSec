PROGRAM My_Program
  VAR
    CaudalPurga AT %MD0 : DINT := 95145;
    Nitrato AT %IW0 : INT := 130;
    Amonio AT %IW1 : INT := 685;
    OxigenoDisuelto AT %IW2 : INT := 254;
    SolidoSuspendido AT %MD1 : REAL := 3138.87;
    Aireacion AT %IW3 : INT := 3;
    Temperatura AT %IW4 : INT := 15;
    CaudalAire AT %QW0 : INT;
    CaudalRecircInt AT %QW1 : INT;
  END_VAR
  VAR
    Input : BOOL;
    Output : BOOL;
  END_VAR

  Output := Input;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : My_Program;
  END_RESOURCE
END_CONFIGURATION
