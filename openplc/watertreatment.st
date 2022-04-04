PROGRAM My_Program
  VAR
    CaudalPurga AT %MD0 : DINT;
    Nitrato AT %MW201 : INT;
    Amonio AT %MW205 : INT;
    OxigenoDisuelto AT %MW206 : INT;
    Aireacion AT %MW208 : INT;
    Temperatura AT %MW209 : INT;
    CaudalAire AT %MW210 : INT;
    CaudalRecircInt AT %QW1 : INT;
  END_VAR
  VAR
    Input : BOOL;
    Output : BOOL;
    MOVE5_OUT : INT;
    MOVE3_OUT : INT;
  END_VAR

  MOVE5_OUT := MOVE(Temperatura);
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : My_Program;
  END_RESOURCE
END_CONFIGURATION
