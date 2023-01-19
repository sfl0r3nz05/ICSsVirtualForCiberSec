clear all;

iniASM1model;

% Influente
Inf_Const(1) = 0;               % t
Inf_Const(2) = 19029;           % Qinf
Inf_Const(3) = 69.0432;         % SS
Inf_Const(4) = 0;               % S0
Inf_Const(5) = 34.5216;         % SI
Inf_Const(6) = 0.;              % SNO
Inf_Const(7) = 36.0;            % SNH
Inf_Const(8) = 2.071296;        % SND
Inf_Const(9) = 200;             % SALK
Inf_Const(10) = 47.75232;       % XI
Inf_Const(11) = 200.93056;      % XS
Inf_Const(12) = 47.75232;       % XH
Inf_Const(13) = 0;              % XA
Inf_Const(14) = 0;              % XP
Inf_Const(15) = 6.8175616;      % XND
Inf_Const(16) = 40.8;           % XIN

% Dos metanol
Inf_DosMet(1) = 0;               % t
Inf_DosMet(2) = 19.029;          % Q meth
Inf_DosMet(3) = 45000;           % SS
Inf_DosMet(4) = 0;               % S0
Inf_DosMet(5) = 0;               % SI
Inf_DosMet(6) = 0.;              % SNO
Inf_DosMet(7) = 0;               % SNH
Inf_DosMet(8) = 0;               % SND
Inf_DosMet(9) = 0;               % SALK
Inf_DosMet(10) = 0;              % XI
Inf_DosMet(11) = 0;              % XS
Inf_DosMet(12) = 0;              % XH
Inf_DosMet(13) = 0;              % XA
Inf_DosMet(14) = 0;              % XP
Inf_DosMet(15) = 0;              % XND
Inf_DosMet(16) = 0;              % XIN


% TANQUE_D
% Configuración de Planta
Param_ASU_D(1) = 6343;          %VASU
Param_ASU_D(2) = 0.325;           %DE_TANK
Param_ASU_D(3) = 4;               %H_TANK
Param_ASU_D(4) = 0.95;            %BETA_FACTOR

% Iniciales
x0_D(1) = 1;
x0_D(2) = 2;
x0_D(3) = 30;
x0_D(4) = 0.9;
x0_D(5) = 5;
x0_D(6) = 1;
x0_D(7) = 200;
x0_D(8) = 1000;
x0_D(9) = 40;
x0_D(10) = 2000;
x0_D(11) = 100;
x0_D(12) = 700;
x0_D(13) = 5;
x0_D(14) = 900;


% Variables de operacion D
VarManip_D(1)= 3;                         %KLA
VarManip_D(2)= 0*Inf_Const(2);            %QW 
VarManip_D(3)= 15;                        %TEMP
VarManip_D(4)= 101000;                    %PAMB


% TANQUE_N
% Configuración de Planta
Param_ASU_N(1) = 9514.5;                  % VASU
Param_ASU_N(2) = 0.325;                 % DE_TANK
Param_ASU_N(3) = 4;                     % H_TANK
Param_ASU_N(4) = 0.95;                  % BETA_FACTOR

% Iniciales
x0_N(1) = 1;
x0_N(2) = 2;
x0_N(3) = 30;
x0_N(4) = 0.9;
x0_N(5) = 5;
x0_N(6) = 1;
x0_N(7) = 200;
x0_N(8) = 1000;
x0_N(9) = 40;
x0_N(10) = 2000;
x0_N(11) = 100;
x0_N(12) = 700;
x0_N(13) = 5;
x0_N(14) = 900;


% Variables de operacion N
VarManip_N(1)= 15;                           % TEMP
VarManip_N(2)= 101000;                       % PAMB

iniSETTLING_POINT;

