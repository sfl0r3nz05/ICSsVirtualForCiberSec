function updateBlockParameter(block)
%This function writes the value in input in the parameter identified by
%paramete-name.
%
% The setup method is used to setup the basic attributes of the
% S-function such as ports, parameters, etc. Do not add any other
% calls to the main body of the function.  
%   
setup(block);
  
%endfunction

%
function setup(block)

  % Register the number of ports.
  block.NumInputPorts  = 1;
  block.NumOutputPorts = 1;

  % Set up the port properties to be inherited or dynamic.
  block.SetPreCompPortInfoToDefaults;
  
    % Override the input port properties.
  block.InputPort(1).DatatypeID  = 0;  % double
  block.InputPort(1).Complexity  = 'Real';

  
  % Override the output port properties.
  block.OutputPort(1).DatatypeID  = 0; % double
  block.OutputPort(1).Complexity  = 'Real';

  % Register the parameters.
  block.NumDialogPrms     = 2;
  block.DialogPrmsTunable = {'Tunable','Tunable'};

  % Register the sample times.
  %  [0 offset]            : Continuous sample time
  %  [positive_num offset] : Discrete sample time
  %
  %  [-1, 0]               : Inherited sample time
  %  [-2, 0]               : Variable sample time
  block.SampleTimes = [-1 0];

  % Specify if Accelerator should use TLC or call back to the 
  % MATLAB file
  block.SetAccelRunOnTLC(false);
  
   
  % -----------------------------------------------------------------
  % Register the methods called during update diagram/compilation.
  % -----------------------------------------------------------------
  
  % SetInputPortDimensions:
  block.RegBlockMethod('SetInputPortDimensions', @SetInpPortDims);
  
  % SetInputPortDatatype:
  block.RegBlockMethod('SetInputPortDataType', @SetInpPortDataType);
  
  % SetOutputPortDimensions:
  block.RegBlockMethod('SetOutputPortDimensions', @SetOutPortDims);
  
  % SetOutputPortDatatype:
  block.RegBlockMethod('SetOutputPortDataType', @SetOutPortDataType);
  
  % PostPropagationSetup:
  block.RegBlockMethod('PostPropagationSetup', @DoPostPropSetup);

  % -----------------------------------------------------------------
  % Register methods called at run-time
  % -----------------------------------------------------------------
  
   
  % ProcessParameters  
  block.RegBlockMethod('ProcessParameters', @ProcessPrms);

   
  % InitializeConditions:
  %block.RegBlockMethod('InitializeConditions', @InitializeConditions);
  
  % Start:
  block.RegBlockMethod('Start', @Start);

  % Outputs:
  block.RegBlockMethod('Outputs', @Outputs);
   
  % Update:
  block.RegBlockMethod('Update', @Update);

function ProcessPrms(block)

  block.AutoUpdateRuntimePrms;
 
%endfunction

function SetInpPortDims(block, idx, di)
  
  block.InputPort(idx).Dimensions = di;
  block.OutputPort(1).Dimensions  = di;
  
function SetInpPortDataType(block, idx, dt)
  
  block.InputPort(idx).DataTypeID = dt;
  block.OutputPort(1).DataTypeID  = dt;

%endfunction  

function SetOutPortDims(block, idx, di)
  
  block.OutputPort(idx).Dimensions = di;
  block.InputPort(1).Dimensions    = di;

%endfunction

  
function SetOutPortDataType(block, idx, dt)

  block.OutputPort(idx).DataTypeID  = dt;
  block.InputPort(1).DataTypeID     = dt;

%endfunction  

    
function DoPostPropSetup(block)
  block.NumDworks = 1;
  

  block.Dwork(1).Name            = 'result';
  block.Dwork(1).Dimensions      = 1;
  block.Dwork(1).DatatypeID      = 0;      % double
  block.Dwork(1).Complexity      = 'Real'; % real
  block.Dwork(1).UsedAsDiscState = true;
  
 % block.AutoRegRuntimePrms;

 %endfunction

function Start(block)
%Read the input parameters   

%endfunction

function Outputs(block)
%send the value got as input to the output port
block.OutputPort(1).Data = block.Dwork(1).Data;
%endfunction

function Update(block)
block_id= block.DialogPrm(1).Data;%read the name of the simulink block passed as argument
param_name= block.DialogPrm(2).Data;%read the name of the parameter we want to change 
%At every simulation Step the value of the block parameter is chenged if necessary
input_value =single(block.InputPort(1).Data);

set_param(block_id, param_name, num2str(input_value));

disp(['New Parameter Value:',num2str(input_value)]);

%Send the value read in output
block.Dwork(1).Data = double(input_value); 
%endfunction

%customized functions


    
