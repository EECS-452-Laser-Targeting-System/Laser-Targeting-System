/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include <DynamixelShield.h>

#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)
  #include <SoftwareSerial.h>
  SoftwareSerial soft_serial(7, 8); // DYNAMIXELShield UART RX/TX
  #define DEBUG_SERIAL soft_serial
#elif defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAM_ZERO)
  #define DEBUG_SERIAL SerialUSB    
#else
  #define DEBUG_SERIAL Serial
#endif

const uint8_t servoy = 1;
const uint8_t servox = 2;
const float DXL_PROTOCOL_VERSION = 2.0;

DynamixelShield dxl;

//This namespace is required to use Control table item names
using namespace ControlTableItem;

void setup() {
  // put your setup code here, to run once:
  
  // For Uno, Nano, Mini, and Mega, use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);

  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(1000000);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  // Get DYNAMIXEL information
  dxl.ping(servox);
  dxl.ping(servoy);

  // Turn off torque when configuring items in EEPROM area
  dxl.torqueOff(servox);
  dxl.setOperatingMode(servox, OP_POSITION);
  dxl.torqueOn(servox);
  dxl.torqueOff(servoy);
  dxl.setOperatingMode(servoy, OP_POSITION);
  dxl.torqueOn(servoy);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // Please refer to e-Manual(http://emanual.robotis.com/docs/en/parts/interface/dynamixel_shield/) for available range of value. 
  // Set Goal Position in RAW value
  dxl.setGoalPosition(servox, 256);
  delay(1000);
  dxl.setGoalPosition(servoy, 515);
  // Print present position in raw value
  // DEBUG_SERIAL.print("Present Position(raw) : ");
  // DEBUG_SERIAL.println(dxl.getPresentPosition(DXL_ID));
  delay(1000);

  // Set Goal Position in DEGREE value
  dxl.setGoalPosition(servox, 464);
  delay(1000);
  dxl.setGoalPosition(servoy, 820);
  // Print present position in degree value
  // DEBUG_SERIAL.print("Present Position(degree) : ");
  // DEBUG_SERIAL.println(dxl.getPresentPosition(DXL_ID, UNIT_DEGREE));
  delay(1000);
}
