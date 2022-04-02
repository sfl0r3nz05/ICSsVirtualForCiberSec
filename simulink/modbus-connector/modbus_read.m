function modbus_read(block)
setup(block);
function Start(block)
address = block.DialogPrm(2).Data;
port = block.DialogPrm(3).Data;
ModBusTCP = openConnection(address, port);
set_param(block.BlockHandle, 'UserData', ModBusTCP);
function Outputs(block)
block.OutputPort(1).Data = block.Dwork(1).Data;
function Update(block)
ModBusTCP = get_param(block.BlockHandle, 'UserData');
registry = block.DialogPrm(1).Data;
message = prepareReadingMessage(registry);
response = readFloating(ModBusTCP, message);
block.Dwork(1).Data = double(response);

function setup(block)
  block.NumInputPorts  = 0;
  block.NumOutputPorts = 1;
  block.SetPreCompPortInfoToDefaults;
  block.OutputPort(1).DatatypeID  = 0; % double
  block.OutputPort(1).Complexity  = 'Real';
  block.NumDialogPrms     = 3;
  block.DialogPrmsTunable = {'Nontunable','Nontunable','Nontunable'};
  block.SampleTimes = [-1 0];
  block.SetAccelRunOnTLC(false);
  block.RegBlockMethod('SetInputPortDimensions', @SetInpPortDims);
  block.RegBlockMethod('SetInputPortDataType', @SetInpPortDataType);
  block.RegBlockMethod('SetOutputPortDimensions', @SetOutPortDims);
  block.RegBlockMethod('SetOutputPortDataType', @SetOutPortDataType);
  block.RegBlockMethod('PostPropagationSetup', @DoPostPropSetup);
  block.RegBlockMethod('ProcessParameters', @ProcessPrms);
  %block.RegBlockMethod('InitializeConditions', @InitializeConditions);
  block.RegBlockMethod('Start', @Start);
  block.RegBlockMethod('Outputs', @Outputs);
  block.RegBlockMethod('Update', @Update);

function ProcessPrms(block)
  block.AutoUpdateRuntimePrms;

function SetInpPortDims(block, idx, di)
  block.InputPort(idx).Dimensions = di;
  block.OutputPort(1).Dimensions  = di;
  
function SetInpPortDataType(block, idx, dt)
  block.InputPort(idx).DataTypeID = dt;
  block.OutputPort(1).DataTypeID  = dt;

function SetOutPortDims(block, idx, di)  
  block.OutputPort(idx).Dimensions = di;
  block.InputPort(1).Dimensions    = di;

function SetOutPortDataType(block, idx, dt)
  block.OutputPort(idx).DataTypeID  = dt;
  block.InputPort(1).DataTypeID     = dt;
    
function DoPostPropSetup(block)
  block.NumDworks = 1;
  block.Dwork(1).Name            = 'result';
  block.Dwork(1).Dimensions      = 1;
  block.Dwork(1).DatatypeID      = 0;      % double
  block.Dwork(1).Complexity      = 'Real'; % real
  block.Dwork(1).UsedAsDiscState = true;
  block.AutoRegRuntimePrms;

function ModBusTCP = openConnection(ipaddress, port)
    ModBusTCP=modbus('tcpip', ipaddress, port);
    ModBusTCP.ByteOrder='big-endian';
    
function message = prepareReadingMessage(registry)
    stationId = 1; %the station id on the slave we are referring to
    transID= uint16(0);
    FunCod =  int16(3);
    ProtID = int16(0);
    Lenght = int16(6);
    UnitID = int16(256*stationId);
    UnitID = bitshift(UnitID,8); 
    UnitIDFunCod = bitor(FunCod,UnitID);
    Address_offset = int16(registry);
    reg_number = int16(2);
    message = [transID; ProtID; Lenght; UnitIDFunCod; Address_offset; reg_number];
   
function response = readFloating(ModBusTCP, message)
  response = read(ModBusTCP, 'holdingregs', 1234)
    
