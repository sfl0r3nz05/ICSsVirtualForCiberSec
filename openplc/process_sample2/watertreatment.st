PROGRAM My_Program
  VAR
    CaudalPurga AT %MD0 : DINT := 95145;
    PINitrato AT %MW201 : INT := 100;
    PINitratoR AT %MW202 : INT := 130;
    SCNitrato AT %MW203 : INT := 125;
    SCNitratoR AT %MW204 : INT := 120;
    Amonio AT %MW205 : INT := 685;
    OxigenoDisuelto AT %MW206 : INT := 254;
    Aireacion AT %MW208 : INT := 3;
    Temperatura AT %MW209 : INT := 15;
    CaudalAire AT %MW210 : INT;
    CaudalRecircInt AT %QW1 : INT;
  END_VAR
  VAR
    Input : BOOL;
    Output : BOOL;
    MOVE5_OUT : INT;
    MOVE3_OUT : INT;
    MOVE1_OUT : INT;
  END_VAR

  MOVE5_OUT := MOVE(PINitrato);
  PINitratoR := MOVE5_OUT;
  MOVE3_OUT := MOVE(SCNitratoR);
  PINitrato := MOVE3_OUT;
  MOVE1_OUT := MOVE(SCNitrato);
  SCNitratoR := MOVE1_OUT;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : My_Program;
  END_RESOURCE
END_CONFIGURATION
