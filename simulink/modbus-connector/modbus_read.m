function modbus_read(block)

setup(block);
  
%endfunction

%
function setup(block)

  % Register the number of ports.
  block.NumInputPorts  = 0;
  block.NumOutputPorts = 1;

  % Set up the port properties to be inherited or dynamic.
  block.SetPreCompPortInfoToDefaults;
  
  % Override the output port properties.
  block.OutputPort(1).DatatypeID  = 0; % double
  block.OutputPort(1).Complexity  = 'Real';

  % Register the parameters.
  block.NumDialogPrms     = 3;
  block.DialogPrmsTunable = {'Nontunable','Nontunable','Nontunable'};

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
  
  block.AutoRegRuntimePrms;

 %endfunction

function Start(block)
%Read the input parameters
address = block.DialogPrm(2).Data;%read the ip address
port = block.DialogPrm(3).Data;%read the port typically 502
ModBusTCP = openConnection(address, port); %open the connection
set_param(block.BlockHandle, 'UserData', ModBusTCP);%register variable ModBusTCP
   
%endfunction

function Outputs(block)
%send the value read from the registry to the output port
block.OutputPort(1).Data = block.Dwork(1).Data;
%endfunction

function Update(block)
%At every simulation Step a new read is made
ModBusTCP = get_param(block.BlockHandle, 'UserData');
registry = block.DialogPrm(1).Data;%read the registry
%Prepare message for reading
message = prepareReadingMessage(registry);
response = readFloating(ModBusTCP, message);    

%Send the value read in output
block.Dwork(1).Data = double(response); 
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

    
function message = prepareReadingMessage(registry)
    stationId = 1; %the station id on the slave we are referring to
    transID=uint16(0);
    FunCod =  int16(3); % Function code to read register (3)
    ProtID = int16(0); % 16b Protocol ID (0 for ModBus) 
    Lenght = int16(6); % 16b Remaining bytes (24) 
    UnitID = int16(256*stationId); % Unit ID (1)
    UnitID = bitshift(UnitID,8); 
    UnitIDFunCod = bitor(FunCod,UnitID); 
    % Concatenation of UnitID & FunctionCode 
    % in one uint16 word
    % According to modbus protocol, UnitID and Function code are 8bit data. 
    % In order to maintain the same data tipe in vector "message", I converted 
    % each of them to uint16, and used "bitor" to create a uint16 word when 
    % the MSB is the UnitID and the LSB is the function code
    Address_offset = int16(registry); % 16b Adress of the register
    reg_number = int16(2);%number of register to read
    message = [transID; ProtID; Lenght; UnitIDFunCod; Address_offset;reg_number];
   
function response = readFloating(ModBusTCP, message)
    % Write the message
    fwrite(ModBusTCP, message,'int16');

    % check if the message is received correctly
    while ~ModBusTCP.BytesAvailable
        % wait for the response to be in the buffer
    end
      %response = fread(ModBusTCP,ModBusTCP.BytesAvailable); %get received bytes
    transId = fread(ModBusTCP,1, 'int16');
    protId =  fread(ModBusTCP,1, 'int16');
    len =  fread(ModBusTCP,1, 'int16');
    uidFC = fread(ModBusTCP,1, 'int16');
    bytesToFollow = fread(ModBusTCP,1, 'int8');
    msb = fread(ModBusTCP,1, 'int16');
    lsb = fread(ModBusTCP,1, 'int16');
    float_num = int16([msb lsb]);
    response = typecast(float_num, 'single');
    %disp(['Reading Value:',num2str(response)]);
 
    
    
