function modbus_write(block)
%modbus_server is  a MATLAB S-Function
%    
%This function will be used to write Modbus Messages to the IP/port/resigtry given in input
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
  block.OutputPort(1).DatatypeID  = 1; % single
  block.OutputPort(1).Complexity  = 'Real';

  % Register the parameters.
  block.NumDialogPrms     = 3;
  block.DialogPrmsTunable = {'Nontunable','Nontunable','Nontunable'};
  
  % Set up the continuous states.
  %block.NumContStates = 1;

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
  block.Dwork(1).DatatypeID      = 1;      % single
  block.Dwork(1).Complexity      = 'Real'; % real
  block.Dwork(1).UsedAsDiscState = true;
  
  block.AutoRegRuntimePrms;

  %endfunction


function Start(block)

%read the input parameters
address = block.DialogPrm(2).Data;
port = block.DialogPrm(3).Data;

ModBusTCP = openConnection(address, port);
%set the variable to hold connection information
set_param(block.BlockHandle, 'UserData', ModBusTCP);
   
%endfunction

function Outputs(block)
%send the value written to the registry to the output port (for checking)
block.OutputPort(1).Data = block.Dwork(1).Data;
%endfunction

function Update(block)
%At every simulation step a new write is made
ModBusTCP = get_param(block.BlockHandle, 'UserData');
registry = block.DialogPrm(1).Data;
value =single(block.InputPort(1).Data); %value is a double converted to single precision

message = prepareWritingMessage(value, registry);%prepare the message to be send over the network
result = writeModBus(ModBusTCP, message);%send the message over TCP
block.Dwork(1).Data = value;
  
%endfunction

%customized functions
function ModBusTCP = openConnection(ipaddress, port)
    ModBusTCP=tcpip(ipaddress, port); %Create the tcpip obeject
    set(ModBusTCP, 'InputBufferSize', 512); %assign the buffer
    ModBusTCP.ByteOrder='bigEndian'; %specify the order in which bytes are transmitted
    try 
        if ~strcmp(ModBusTCP.Status,'open') 
            fopen(ModBusTCP);
            disp(['TCP/IP connection opened with host:', ipaddress]); 
        end
    catch fault % display error if the channel is not opened.
        if ~strcmp(ModBusTCP.Status,'open') % check if the channel is really closed
            disp(fault);
            disp(['Error: Can''t establish TCP/IP connection with: ',ipaddress,':',num2str(port)] ); 
            disp('You can check the following:');
            disp('- If the cable is plugged in correctly ');
            disp('- Whether the Yaskawa controller is turned on.');
            disp('- Your firewall settings');
        end
    end

    
function message = prepareWritingMessage(value, registry )
    %the message has to be in the following int8 form:
    %0000  0000    000c     00      10      0001 0002 04           d636 603d 
    %tr_id prot_id len(=17) unit_id fc(=16) addr reg# byteToFollow lsb   msb  
    
    transID=int8(0);%8 bits transaction identifier
    ProtID=int8(0);%8 bits protocol id
    Lenght =int8(17); % 8bits Remaining bytes 
    UnitID = int8(0); % Unit ID (1)
    FunCod = int8(16); % Function code to write register 
	%Function code 16= write multipple registry 
	%Function code 6 = write single registry
    Address_offset =int8(registry); % 16b Adress of the register
    reg_number = int8(2);%number of register to read
    byteToFollow = int8(4);%bytes that will follow 
    data = typecast(value, 'int8');% 4x8bit data: the order of each 2 bytes has to be reversed
    message = [int8(0); transID;int8(0);ProtID; int8(0);Lenght; UnitID; FunCod; int8(0); Address_offset;int8(0);reg_number;byteToFollow; data(2); data(1); data(4); data(3)];
   
    %disp(['Writing Value:',num2str(value)]);


function result = writeModBus(ModBusTCP, message)
    % Write the message
    fwrite(ModBusTCP, message,'int8');

    % check if the message is received correctly
    while ~ModBusTCP.BytesAvailable
        % wait for the response to be in the buffer
    end
    result = fread(ModBusTCP,ModBusTCP.BytesAvailable); %get received bytes
  
    %% check the function code and display error
    if result(8) >= 128 % function code error
        % There is an error on the communication the function code is byte 8
        % in the received message. PLC adds some numbers (e.g. 128) to the function code to say
        % an error occured. The next field (9) contains the error code.
        err = result(9);
        disp(['Communication error. The controller responds with error code: ', num2str(err)]);
    end

