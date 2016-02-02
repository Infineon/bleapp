// ======================================================================
// robot.v generated from TopDesign.cysch
// 02/01/2016 at 14:00
// This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
// ======================================================================

`define CYDEV_CHIP_FAMILY_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_UNKNOWN 0
`define CYDEV_CHIP_FAMILY_PSOC3 1
`define CYDEV_CHIP_MEMBER_3A 1
`define CYDEV_CHIP_REVISION_3A_PRODUCTION 3
`define CYDEV_CHIP_REVISION_3A_ES3 3
`define CYDEV_CHIP_REVISION_3A_ES2 1
`define CYDEV_CHIP_REVISION_3A_ES1 0
`define CYDEV_CHIP_FAMILY_PSOC4 2
`define CYDEV_CHIP_MEMBER_4G 2
`define CYDEV_CHIP_REVISION_4G_PRODUCTION 17
`define CYDEV_CHIP_REVISION_4G_ES 17
`define CYDEV_CHIP_REVISION_4G_ES2 33
`define CYDEV_CHIP_MEMBER_4U 3
`define CYDEV_CHIP_REVISION_4U_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4E 4
`define CYDEV_CHIP_REVISION_4E_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4N 5
`define CYDEV_CHIP_REVISION_4N_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4D 6
`define CYDEV_CHIP_REVISION_4D_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4J 7
`define CYDEV_CHIP_REVISION_4J_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4K 8
`define CYDEV_CHIP_REVISION_4K_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4H 9
`define CYDEV_CHIP_REVISION_4H_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4A 10
`define CYDEV_CHIP_REVISION_4A_PRODUCTION 17
`define CYDEV_CHIP_REVISION_4A_ES0 17
`define CYDEV_CHIP_MEMBER_4F 11
`define CYDEV_CHIP_REVISION_4F_PRODUCTION 0
`define CYDEV_CHIP_REVISION_4F_PRODUCTION_256K 0
`define CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA 0
`define CYDEV_CHIP_MEMBER_4F 12
`define CYDEV_CHIP_REVISION_4F_PRODUCTION 0
`define CYDEV_CHIP_REVISION_4F_PRODUCTION_256K 0
`define CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA 0
`define CYDEV_CHIP_MEMBER_4M 13
`define CYDEV_CHIP_REVISION_4M_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4L 14
`define CYDEV_CHIP_REVISION_4L_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4I 15
`define CYDEV_CHIP_REVISION_4I_PRODUCTION 0
`define CYDEV_CHIP_MEMBER_4C 16
`define CYDEV_CHIP_REVISION_4C_PRODUCTION 0
`define CYDEV_CHIP_FAMILY_PSOC5 3
`define CYDEV_CHIP_MEMBER_5B 17
`define CYDEV_CHIP_REVISION_5B_PRODUCTION 0
`define CYDEV_CHIP_REVISION_5B_ES0 0
`define CYDEV_CHIP_MEMBER_5A 18
`define CYDEV_CHIP_REVISION_5A_PRODUCTION 1
`define CYDEV_CHIP_REVISION_5A_ES1 1
`define CYDEV_CHIP_REVISION_5A_ES0 0
`define CYDEV_CHIP_FAMILY_USED 2
`define CYDEV_CHIP_MEMBER_USED 11
`define CYDEV_CHIP_REVISION_USED 0
// Component: or_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0\or_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\or_v1_0\or_v1_0.v"
`endif

// Component: cy_constant_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_constant_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_constant_v1_0\cy_constant_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_constant_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_constant_v1_0\cy_constant_v1_0.v"
`endif

// BLE_v2_30(GapConfig=<?xml version="1.0" encoding="utf-16"?>\r\n<CyGapConfiguration xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema">\r\n  <DevAddress>00A050000000</DevAddress>\r\n  <SiliconGeneratedAddress>true</SiliconGeneratedAddress>\r\n  <MtuSize>23</MtuSize>\r\n  <TxPowerLevel>0</TxPowerLevel>\r\n  <TxPowerLevelConnection>0</TxPowerLevelConnection>\r\n  <TxPowerLevelAdvScan>0</TxPowerLevelAdvScan>\r\n  <SecurityConfig>\r\n    <SecurityMode>SECURITY_MODE_1</SecurityMode>\r\n    <SecurityLevel>NO_SECURITY</SecurityLevel>\r\n    <IOCapability>DISPLAY</IOCapability>\r\n    <PairingMethod>JUST_WORKS</PairingMethod>\r\n    <Bonding>BOND</Bonding>\r\n    <EncryptionKeySize>16</EncryptionKeySize>\r\n  </SecurityConfig>\r\n  <AdvertisementConfig>\r\n    <AdvScanMode>FAST_CONNECTION</AdvScanMode>\r\n    <AdvFastScanInterval>\r\n      <Minimum>20</Minimum>\r\n      <Maximum>30</Maximum>\r\n    </AdvFastScanInterval>\r\n    <AdvReducedScanInterval>\r\n      <Minimum>1000</Minimum>\r\n      <Maximum>10240</Maximum>\r\n    </AdvReducedScanInterval>\r\n    <AdvDiscoveryMode>GENERAL</AdvDiscoveryMode>\r\n    <AdvType>CONNECTABLE_UNDIRECTED</AdvType>\r\n    <AdvFilterPolicy>SCAN_REQUEST_ANY_CONNECT_REQUEST_ANY</AdvFilterPolicy>\r\n    <AdvChannelMap>ALL</AdvChannelMap>\r\n    <AdvFastTimeout>0</AdvFastTimeout>\r\n    <AdvReducedTimeout>150</AdvReducedTimeout>\r\n    <EnableReducedAdvertising>false</EnableReducedAdvertising>\r\n    <ConnectionInterval>\r\n      <Minimum>7.5</Minimum>\r\n      <Maximum>50</Maximum>\r\n    </ConnectionInterval>\r\n    <ConnectionSlaveLatency>0</ConnectionSlaveLatency>\r\n    <ConnectionTimeout>10000</ConnectionTimeout>\r\n  </AdvertisementConfig>\r\n  <ScanConfig>\r\n    <ScanFastWindow>30</ScanFastWindow>\r\n    <ScanFastInterval>30</ScanFastInterval>\r\n    <ScanTimeout>30</ScanTimeout>\r\n    <ScanReducedWindow>1125</ScanReducedWindow>\r\n    <ScanReducedInterval>1280</ScanReducedInterval>\r\n    <ScanReducedTimeout>150</ScanReducedTimeout>\r\n    <EnableReducedScan>true</EnableReducedScan>\r\n    <ScanDiscoveryMode>GENERAL</ScanDiscoveryMode>\r\n    <ScanningState>ACTIVE</ScanningState>\r\n    <ScanFilterPolicy>ACCEPT_ALL_ADV_PACKETS</ScanFilterPolicy>\r\n    <DuplicateFiltering>false</DuplicateFiltering>\r\n    <ConnectionInterval>\r\n      <Minimum>7.5</Minimum>\r\n      <Maximum>50</Maximum>\r\n    </ConnectionInterval>\r\n    <ConnectionSlaveLatency>0</ConnectionSlaveLatency>\r\n    <ConnectionTimeout>10000</ConnectionTimeout>\r\n  </ScanConfig>\r\n  <AdvertisementPacket>\r\n    <PacketType>ADVERTISEMENT</PacketType>\r\n    <Items>\r\n      <CyADStructure>\r\n        <ADType>1</ADType>\r\n        <ADData>06</ADData>\r\n      </CyADStructure>\r\n      <CyADStructure>\r\n        <ADType>9</ADType>\r\n        <ADData>52:6F:62:6F:74</ADData>\r\n      </CyADStructure>\r\n      <CyADStructure>\r\n        <ADType>7</ADType>\r\n        <ADData>F0:34:9B:5F:80:00:00:80:00:10:00:00:00:00:00:00</ADData>\r\n      </CyADStructure>\r\n    </Items>\r\n  </AdvertisementPacket>\r\n  <ScanResponsePacket>\r\n    <PacketType>SCAN_RESPONSE</PacketType>\r\n    <Items />\r\n  </ScanResponsePacket>\r\n</CyGapConfiguration>, HalBaudRate=115200, ImportFilePath=, L2capMpsSize=23, L2capMtuSize=23, L2capNumChannels=1, L2capNumPsm=1, Mode=0, ProfileConfig=<?xml version="1.0" encoding="utf-16"?>\r\n<Profile xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema" ID="1" DisplayName="Custom" Name="Custom" Type="org.bluetooth.profile.custom">\r\n  <CyProfileRole ID="2" DisplayName="Server" Name="Server">\r\n    <CyService ID="3" DisplayName="Generic Access" Name="Generic Access" Type="org.bluetooth.service.generic_access" UUID="1800">\r\n      <CyCharacteristic ID="4" DisplayName="Device Name" Name="Device Name" Type="org.bluetooth.characteristic.gap.device_name" UUID="2A00">\r\n        <Field Name="Name">\r\n          <DataFormat>utf8s</DataFormat>\r\n          <ByteLength>5</ByteLength>\r\n          <FillRequirement>C1</FillRequirement>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>Robot</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n          <Property Type="WRITE" Present="false" Mandatory="false" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="5" DisplayName="Appearance" Name="Appearance" Type="org.bluetooth.characteristic.gap.appearance" UUID="2A01">\r\n        <Field Name="Category">\r\n          <DataFormat>16bit</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <FillRequirement>C1</FillRequirement>\r\n          <ValueType>ENUM</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="6" DisplayName="Peripheral Preferred Connection Parameters" Name="Peripheral Preferred Connection Parameters" Type="org.bluetooth.characteristic.gap.peripheral_preferred_connection_parameters" UUID="2A04">\r\n        <Field Name="Minimum Connection Interval">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>6</Minimum>\r\n            <Maximum>3200</Maximum>\r\n          </Range>\r\n          <FillRequirement>C1</FillRequirement>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>0x0006</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Field Name="Maximum Connection Interval">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>6</Minimum>\r\n            <Maximum>3200</Maximum>\r\n          </Range>\r\n          <FillRequirement>C1</FillRequirement>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>0x0028</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Field Name="Slave Latency">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>0</Minimum>\r\n            <Maximum>1000</Maximum>\r\n          </Range>\r\n          <FillRequirement>C1</FillRequirement>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>0</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Field Name="Connection Supervision Timeout Multiplier">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>10</Minimum>\r\n            <Maximum>3200</Maximum>\r\n          </Range>\r\n          <FillRequirement>C1</FillRequirement>\r\n          <ValueType>BASIC</ValueType>\r\n          <GeneralValue>0x03E8</GeneralValue>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <Declaration>Primary</Declaration>\r\n      <IncludedServices />\r\n    </CyService>\r\n    <CyService ID="7" DisplayName="Generic Attribute" Name="Generic Attribute" Type="org.bluetooth.service.generic_attribute" UUID="1801">\r\n      <CyCharacteristic ID="8" DisplayName="Service Changed" Name="Service Changed" Type="org.bluetooth.characteristic.gatt.service_changed" UUID="2A05">\r\n        <CyDescriptor ID="9" DisplayName="Client Characteristic Configuration" Name="Client Characteristic Configuration" Type="org.bluetooth.descriptor.gatt.client_characteristic_configuration" UUID="2902">\r\n          <Field Name="Properties">\r\n            <DataFormat>16bit</DataFormat>\r\n            <ByteLength>2</ByteLength>\r\n            <Range>\r\n              <IsDeclared>true</IsDeclared>\r\n              <Minimum>0</Minimum>\r\n              <Maximum>3</Maximum>\r\n            </Range>\r\n            <ValueType>BITFIELD</ValueType>\r\n            <Bit>\r\n              <Index>0</Index>\r\n              <Size>1</Size>\r\n              <Value>0</Value>\r\n              <Enumerations>\r\n                <Enumeration key="0" value="Notifications disabled" />\r\n                <Enumeration key="1" value="Notifications enabled" />\r\n              </Enumerations>\r\n            </Bit>\r\n            <Bit>\r\n              <Index>1</Index>\r\n              <Size>1</Size>\r\n              <Value>0</Value>\r\n              <Enumerations>\r\n                <Enumeration key="0" value="Indications disabled" />\r\n                <Enumeration key="1" value="Indications enabled" />\r\n              </Enumerations>\r\n            </Bit>\r\n            <ArrayValue />\r\n          </Field>\r\n          <Properties>\r\n            <Property Type="READ" Present="true" Mandatory="true" />\r\n            <Property Type="WRITE" Present="true" Mandatory="true" />\r\n          </Properties>\r\n          <Permission>\r\n            <AccessPermission>READ_WRITE</AccessPermission>\r\n          </Permission>\r\n        </CyDescriptor>\r\n        <Field Name="Start of Affected Attribute Handle Range">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>1</Minimum>\r\n            <Maximum>65535</Maximum>\r\n          </Range>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Field Name="End of Affected Attribute Handle Range">\r\n          <DataFormat>uint16</DataFormat>\r\n          <ByteLength>2</ByteLength>\r\n          <Range>\r\n            <IsDeclared>true</IsDeclared>\r\n            <Minimum>1</Minimum>\r\n            <Maximum>65535</Maximum>\r\n          </Range>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="READ" Present="true" Mandatory="true" />\r\n          <Property Type="INDICATE" Present="true" Mandatory="true" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <Declaration>Primary</Declaration>\r\n      <IncludedServices />\r\n    </CyService>\r\n    <CyService ID="10" DisplayName="MotorService" Name="Custom Service" Type="org.bluetooth.service.custom" UUID="0000000000001000800000805F9B34F0">\r\n      <CyCharacteristic ID="11" DisplayName="SpeedLeft" Name="Custom Characteristic" Type="org.bluetooth.characteristic.custom" UUID="0000000000001000800000805F9B34F1">\r\n        <CyDescriptor ID="14" DisplayName="Characteristic User Description" Name="Characteristic User Description" Type="org.bluetooth.descriptor.gatt.characteristic_user_description" UUID="2901">\r\n          <Field Name="User Description">\r\n            <DataFormat>utf8s</DataFormat>\r\n            <ByteLength>9</ByteLength>\r\n            <ValueType>BASIC</ValueType>\r\n            <GeneralValue>SpeedLeft</GeneralValue>\r\n            <ArrayValue />\r\n          </Field>\r\n          <Properties>\r\n            <Property Type="READ" Present="true" Mandatory="false" />\r\n            <Property Type="WRITE" Present="false" Mandatory="false" />\r\n          </Properties>\r\n          <Permission />\r\n        </CyDescriptor>\r\n        <Field Name="New field">\r\n          <DataFormat>sint8</DataFormat>\r\n          <ByteLength>1</ByteLength>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="BROADCAST" Present="false" Mandatory="false" />\r\n          <Property Type="READ" Present="true" Mandatory="false" />\r\n          <Property Type="WRITE" Present="true" Mandatory="false" />\r\n          <Property Type="WRITE_WITHOUT_RESPONSE" Present="false" Mandatory="false" />\r\n          <Property Type="NOTIFY" Present="false" Mandatory="false" />\r\n          <Property Type="INDICATE" Present="false" Mandatory="false" />\r\n          <Property Type="AUTHENTICATED_SIGNED_WRITES" Present="false" Mandatory="false" />\r\n          <Property Type="RELIABLE_WRITE" Present="false" Mandatory="false" />\r\n          <Property Type="WRITABLE_AUXILIARIES" Present="false" Mandatory="false" />\r\n        </Properties>\r\n        <Permission>\r\n          <AccessPermission>READ_WRITE</AccessPermission>\r\n        </Permission>\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="15" DisplayName="SpeedRight" Name="Custom Characteristic" Type="org.bluetooth.characteristic.custom" UUID="0000000000001000800000805F9B34F2">\r\n        <CyDescriptor ID="17" DisplayName="Characteristic User Description" Name="Characteristic User Description" Type="org.bluetooth.descriptor.gatt.characteristic_user_description" UUID="2901">\r\n          <Field Name="User Description">\r\n            <DataFormat>utf8s</DataFormat>\r\n            <ByteLength>10</ByteLength>\r\n            <ValueType>BASIC</ValueType>\r\n            <GeneralValue>SpeedRight</GeneralValue>\r\n            <ArrayValue />\r\n          </Field>\r\n          <Properties>\r\n            <Property Type="READ" Present="true" Mandatory="false" />\r\n            <Property Type="WRITE" Present="false" Mandatory="false" />\r\n          </Properties>\r\n          <Permission />\r\n        </CyDescriptor>\r\n        <Field Name="New field">\r\n          <DataFormat>sint8</DataFormat>\r\n          <ByteLength>1</ByteLength>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="BROADCAST" Present="false" Mandatory="false" />\r\n          <Property Type="READ" Present="true" Mandatory="false" />\r\n          <Property Type="WRITE" Present="true" Mandatory="false" />\r\n          <Property Type="WRITE_WITHOUT_RESPONSE" Present="false" Mandatory="false" />\r\n          <Property Type="NOTIFY" Present="false" Mandatory="false" />\r\n          <Property Type="INDICATE" Present="false" Mandatory="false" />\r\n          <Property Type="AUTHENTICATED_SIGNED_WRITES" Present="false" Mandatory="false" />\r\n          <Property Type="RELIABLE_WRITE" Present="false" Mandatory="false" />\r\n          <Property Type="WRITABLE_AUXILIARIES" Present="false" Mandatory="false" />\r\n        </Properties>\r\n        <Permission>\r\n          <AccessPermission>READ_WRITE</AccessPermission>\r\n        </Permission>\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="18" DisplayName="TachLeft" Name="Custom Characteristic" Type="org.bluetooth.characteristic.custom" UUID="0000000000001000800000805F9B34F3">\r\n        <CyDescriptor ID="20" DisplayName="TachLeftCCCD" Name="Client Characteristic Configuration" Type="org.bluetooth.descriptor.gatt.client_characteristic_configuration" UUID="2902">\r\n          <Field Name="Properties">\r\n            <DataFormat>16bit</DataFormat>\r\n            <ByteLength>2</ByteLength>\r\n            <Range>\r\n              <IsDeclared>true</IsDeclared>\r\n              <Minimum>0</Minimum>\r\n              <Maximum>3</Maximum>\r\n            </Range>\r\n            <ValueType>BITFIELD</ValueType>\r\n            <Bit>\r\n              <Index>0</Index>\r\n              <Size>1</Size>\r\n              <Value>0</Value>\r\n              <Enumerations>\r\n                <Enumeration key="0" value="Notifications disabled" />\r\n                <Enumeration key="1" value="Notifications enabled" />\r\n              </Enumerations>\r\n            </Bit>\r\n            <Bit>\r\n              <Index>1</Index>\r\n              <Size>1</Size>\r\n              <Value>0</Value>\r\n              <Enumerations>\r\n                <Enumeration key="0" value="Indications disabled" />\r\n                <Enumeration key="1" value="Indications enabled" />\r\n              </Enumerations>\r\n            </Bit>\r\n            <ArrayValue />\r\n          </Field>\r\n          <Properties>\r\n            <Property Type="READ" Present="true" Mandatory="false" />\r\n            <Property Type="WRITE" Present="true" Mandatory="false" />\r\n          </Properties>\r\n          <Permission>\r\n            <AccessPermission>READ_WRITE</AccessPermission>\r\n          </Permission>\r\n        </CyDescriptor>\r\n        <CyDescriptor ID="21" DisplayName="Characteristic User Description" Name="Characteristic User Description" Type="org.bluetooth.descriptor.gatt.characteristic_user_description" UUID="2901">\r\n          <Field Name="User Description">\r\n            <DataFormat>utf8s</DataFormat>\r\n            <ByteLength>8</ByteLength>\r\n            <ValueType>BASIC</ValueType>\r\n            <GeneralValue>TachLeft</GeneralValue>\r\n            <ArrayValue />\r\n          </Field>\r\n          <Properties>\r\n            <Property Type="READ" Present="true" Mandatory="false" />\r\n            <Property Type="WRITE" Present="false" Mandatory="false" />\r\n          </Properties>\r\n          <Permission />\r\n        </CyDescriptor>\r\n        <Field Name="New field">\r\n          <DataFormat>sint32</DataFormat>\r\n          <ByteLength>4</ByteLength>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="BROADCAST" Present="false" Mandatory="false" />\r\n          <Property Type="READ" Present="true" Mandatory="false" />\r\n          <Property Type="WRITE" Present="false" Mandatory="false" />\r\n          <Property Type="WRITE_WITHOUT_RESPONSE" Present="false" Mandatory="false" />\r\n          <Property Type="NOTIFY" Present="true" Mandatory="false" />\r\n          <Property Type="INDICATE" Present="false" Mandatory="false" />\r\n          <Property Type="AUTHENTICATED_SIGNED_WRITES" Present="false" Mandatory="false" />\r\n          <Property Type="RELIABLE_WRITE" Present="false" Mandatory="false" />\r\n          <Property Type="WRITABLE_AUXILIARIES" Present="false" Mandatory="false" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <CyCharacteristic ID="22" DisplayName="TachRight" Name="Custom Characteristic" Type="org.bluetooth.characteristic.custom" UUID="0000000000001000800000805F9B34F4">\r\n        <CyDescriptor ID="24" DisplayName="Characteristic User Description" Name="Characteristic User Description" Type="org.bluetooth.descriptor.gatt.characteristic_user_description" UUID="2901">\r\n          <Field Name="User Description">\r\n            <DataFormat>utf8s</DataFormat>\r\n            <ByteLength>9</ByteLength>\r\n            <ValueType>BASIC</ValueType>\r\n            <GeneralValue>TachRight</GeneralValue>\r\n            <ArrayValue />\r\n          </Field>\r\n          <Properties>\r\n            <Property Type="READ" Present="true" Mandatory="false" />\r\n            <Property Type="WRITE" Present="false" Mandatory="false" />\r\n          </Properties>\r\n          <Permission />\r\n        </CyDescriptor>\r\n        <CyDescriptor ID="25" DisplayName="TachRightCCCD" Name="Client Characteristic Configuration" Type="org.bluetooth.descriptor.gatt.client_characteristic_configuration" UUID="2902">\r\n          <Field Name="Properties">\r\n            <DataFormat>16bit</DataFormat>\r\n            <ByteLength>2</ByteLength>\r\n            <Range>\r\n              <IsDeclared>true</IsDeclared>\r\n              <Minimum>0</Minimum>\r\n              <Maximum>3</Maximum>\r\n            </Range>\r\n            <ValueType>BITFIELD</ValueType>\r\n            <Bit>\r\n              <Index>0</Index>\r\n              <Size>1</Size>\r\n              <Value>0</Value>\r\n              <Enumerations>\r\n                <Enumeration key="0" value="Notifications disabled" />\r\n                <Enumeration key="1" value="Notifications enabled" />\r\n              </Enumerations>\r\n            </Bit>\r\n            <Bit>\r\n              <Index>1</Index>\r\n              <Size>1</Size>\r\n              <Value>0</Value>\r\n              <Enumerations>\r\n                <Enumeration key="0" value="Indications disabled" />\r\n                <Enumeration key="1" value="Indications enabled" />\r\n              </Enumerations>\r\n            </Bit>\r\n            <ArrayValue />\r\n          </Field>\r\n          <Properties>\r\n            <Property Type="READ" Present="true" Mandatory="false" />\r\n            <Property Type="WRITE" Present="true" Mandatory="false" />\r\n          </Properties>\r\n          <Permission>\r\n            <AccessPermission>READ_WRITE</AccessPermission>\r\n          </Permission>\r\n        </CyDescriptor>\r\n        <Field Name="New field">\r\n          <DataFormat>sint32</DataFormat>\r\n          <ByteLength>4</ByteLength>\r\n          <ValueType>BASIC</ValueType>\r\n          <ArrayValue />\r\n        </Field>\r\n        <Properties>\r\n          <Property Type="BROADCAST" Present="false" Mandatory="false" />\r\n          <Property Type="READ" Present="true" Mandatory="false" />\r\n          <Property Type="WRITE" Present="false" Mandatory="false" />\r\n          <Property Type="WRITE_WITHOUT_RESPONSE" Present="false" Mandatory="false" />\r\n          <Property Type="NOTIFY" Present="true" Mandatory="false" />\r\n          <Property Type="INDICATE" Present="false" Mandatory="false" />\r\n          <Property Type="AUTHENTICATED_SIGNED_WRITES" Present="false" Mandatory="false" />\r\n          <Property Type="RELIABLE_WRITE" Present="false" Mandatory="false" />\r\n          <Property Type="WRITABLE_AUXILIARIES" Present="false" Mandatory="false" />\r\n        </Properties>\r\n        <Permission />\r\n      </CyCharacteristic>\r\n      <Declaration>PrimarySingleInstance</Declaration>\r\n      <IncludedServices />\r\n    </CyService>\r\n    <ProfileRoleIndex>0</ProfileRoleIndex>\r\n    <RoleType>SERVER</RoleType>\r\n  </CyProfileRole>\r\n  <GapRole>PERIPHERAL</GapRole>\r\n</Profile>, SharingMode=0, StackMode=3, UseDeepSleep=true, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMPONENT_NAME=BLE_v2_30, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=BLE_v2_30.pdf, CY_FITTER_NAME=BLE, CY_INSTANCE_SHORT_NAME=BLE, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=30, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  3.3 SP1, INSTANCE_NAME=BLE, )
module BLE_v2_30_0 (
    clk);
    output      clk;


          wire  Net_65;
          wire  Net_64;
          wire  Net_37;
          wire  Net_63;
          wire  Net_15;
          wire  Net_14;
          wire  Net_53;
          wire  Net_60;
          wire  Net_55;

    cy_m0s8_ble_v1_0 cy_m0s8_ble (
        .interrupt(Net_15),
        .rf_ext_pa_en(Net_63));


	cy_isr_v1_0
		#(.int_type(2'b10))
		bless_isr
		 (.int_signal(Net_15));



	cy_clock_v1_0
		#(.id("afa7bbf3-6978-4358-bd11-cc538e9879ce/5ae6fa4d-f41a-4a35-8821-7ce70389cb0c"),
		  .source_clock_id("9A908CA6-5BB3-4db0-B098-959E5D90882B"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(0))
		LFCLK
		 (.clock_out(Net_53));



    assign clk = Net_53 | Net_55;

    assign Net_55 = 1'h0;



endmodule

// Component: cy_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`endif

// TCPWM_P4_v2_0(Clock_CheckTolerance=true, Clock_desired_freq=12, Clock_desired_freq_unit=6, Clock_divisor=1, Clock_FractDividerDenominator=0, Clock_FractDividerNumerator=0, Clock_FractDividerUsed=false, Clock_is_direct=false, Clock_is_divider=false, Clock_is_freq=true, Clock_minus_tolerance=5, Clock_ph_align_clock_id=, Clock_ph_align_clock_name=, Clock_plus_tolerance=5, Clock_source_clock_id=, Clock_source_clock_name=, PinVisibility_index=false, PinVisibility_kill=false, PinVisibility_phiA=false, PinVisibility_phiB=false, PinVisibility_switch=false, PWMCompare=50, PWMCompareBuf=65535, PWMCompareSwap=0, PWMCountMode=3, PWMCountPresent=false, PWMDeadTimeCycle=0, PWMInterruptMask=1, PWMKillEvent=0, PWMLinenSignal=0, PWMLineSignal=0, PWMMode=4, PWMPeriod=100, PWMPeriodBuf=65535, PWMPeriodSwap=0, PWMPrescaler=0, PWMReloadMode=0, PWMReloadPresent=false, PWMRunMode=0, PWMSetAlign=0, PWMStartMode=0, PWMStartPresent=false, PWMStopEvent=0, PWMStopMode=0, PWMStopPresent=false, PWMSwitchMode=0, PWMSwitchPresent=false, QuadEncodingModes=0, QuadIndexMode=0, QuadIndexPresent=false, QuadInterruptMask=1, QuadPhiAMode=3, QuadPhiBMode=3, QuadStopMode=0, QuadStopPresent=false, TCCaptureMode=0, TCCapturePresent=false, TCCompare=65535, TCCompareBuf=65535, TCCompareSwap=0, TCCompCapMode=2, TCCountingModes=0, TCCountMode=3, TCCountPresent=false, TCInterruptMask=1, TCPeriod=65535, TCPrescaler=0, TCPWMCapturePresent=false, TCPWMConfig=7, TCPWMCountPresent=false, TCPWMReloadPresent=false, TCPWMStartPresent=false, TCPWMStopPresent=false, TCReloadMode=0, TCReloadPresent=false, TCRunMode=0, TCStartMode=0, TCStartPresent=false, TCStopMode=0, TCStopPresent=false, TermMode_capture=0, TermMode_cc=0, TermMode_clock=0, TermMode_count=0, TermMode_interrupt=0, TermMode_line=0, TermMode_line_n=0, TermMode_ov=0, TermMode_reload=0, TermMode_start=0, TermMode_stop=0, TermMode_un=0, TermModeStates=, TermVisibility_capture=false, TermVisibility_cc=true, TermVisibility_clock=true, TermVisibility_count=false, TermVisibility_interrupt=true, TermVisibility_line=true, TermVisibility_line_n=true, TermVisibility_ov=true, TermVisibility_reload=false, TermVisibility_start=false, TermVisibility_stop=false, TermVisibility_un=true, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMPONENT_NAME=TCPWM_P4_v2_0, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=PWMLEFT, CY_INSTANCE_SHORT_NAME=PWMLEFT, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=0, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  3.3 SP1, INSTANCE_NAME=PWMLEFT, )
module TCPWM_P4_v2_0_1 (
    stop,
    count,
    reload,
    start,
    capture,
    interrupt,
    ov,
    un,
    cc,
    clock,
    line,
    line_n);
    input       stop;
    input       count;
    input       reload;
    input       start;
    input       capture;
    output      interrupt;
    output      ov;
    output      un;
    output      cc;
    input       clock;
    output      line;
    output      line_n;


          wire  Net_64;
          wire  Net_63;
          wire  Net_85;
          wire  Net_62;
          wire  Net_110;
          wire  Net_95;
          wire  Net_106;
          wire  Net_104;
          wire  Net_109;
          wire  Net_98;
          wire  Net_108;
          wire  Net_101;
          wire  Net_66;
          wire  Net_81;
          wire  Net_75;
          wire  Net_69;
          wire  Net_82;
          wire  Net_72;

    cy_m0s8_tcpwm_v1_0 cy_m0s8_tcpwm_1 (
        .capture(Net_75),
        .underflow(un),
        .overflow(ov),
        .line_out_compl(line_n),
        .line_out(line),
        .compare_match(cc),
        .interrupt(interrupt),
        .count(Net_69),
        .reload(Net_66),
        .stop(Net_82),
        .start(Net_72),
        .clock(Net_81));

	// VMux_reload (cy_virtualmux_v1_0)
	assign Net_66 = reload;

	// VMux_count (cy_virtualmux_v1_0)
	assign Net_69 = count;

	// VMux_start (cy_virtualmux_v1_0)
	assign Net_72 = start;

	// VMux_capture (cy_virtualmux_v1_0)
	assign Net_75 = capture;

	// VMux_stop (cy_virtualmux_v1_0)
	assign Net_82 = stop;

	// VMux_clock (cy_virtualmux_v1_0)
	assign Net_81 = clock;



endmodule

// TCPWM_P4_v2_0(Clock_CheckTolerance=true, Clock_desired_freq=12, Clock_desired_freq_unit=6, Clock_divisor=1, Clock_FractDividerDenominator=0, Clock_FractDividerNumerator=0, Clock_FractDividerUsed=false, Clock_is_direct=false, Clock_is_divider=false, Clock_is_freq=true, Clock_minus_tolerance=5, Clock_ph_align_clock_id=, Clock_ph_align_clock_name=, Clock_plus_tolerance=5, Clock_source_clock_id=, Clock_source_clock_name=, PinVisibility_index=false, PinVisibility_kill=false, PinVisibility_phiA=false, PinVisibility_phiB=false, PinVisibility_switch=false, PWMCompare=50, PWMCompareBuf=65535, PWMCompareSwap=0, PWMCountMode=3, PWMCountPresent=false, PWMDeadTimeCycle=0, PWMInterruptMask=1, PWMKillEvent=0, PWMLinenSignal=0, PWMLineSignal=0, PWMMode=4, PWMPeriod=100, PWMPeriodBuf=65535, PWMPeriodSwap=0, PWMPrescaler=0, PWMReloadMode=0, PWMReloadPresent=false, PWMRunMode=0, PWMSetAlign=0, PWMStartMode=0, PWMStartPresent=false, PWMStopEvent=0, PWMStopMode=0, PWMStopPresent=false, PWMSwitchMode=0, PWMSwitchPresent=false, QuadEncodingModes=0, QuadIndexMode=0, QuadIndexPresent=false, QuadInterruptMask=1, QuadPhiAMode=3, QuadPhiBMode=3, QuadStopMode=0, QuadStopPresent=false, TCCaptureMode=0, TCCapturePresent=false, TCCompare=65535, TCCompareBuf=65535, TCCompareSwap=0, TCCompCapMode=2, TCCountingModes=0, TCCountMode=3, TCCountPresent=false, TCInterruptMask=1, TCPeriod=65535, TCPrescaler=0, TCPWMCapturePresent=false, TCPWMConfig=7, TCPWMCountPresent=false, TCPWMReloadPresent=false, TCPWMStartPresent=false, TCPWMStopPresent=false, TCReloadMode=0, TCReloadPresent=false, TCRunMode=0, TCStartMode=0, TCStartPresent=false, TCStopMode=0, TCStopPresent=false, TermMode_capture=0, TermMode_cc=0, TermMode_clock=0, TermMode_count=0, TermMode_interrupt=0, TermMode_line=0, TermMode_line_n=0, TermMode_ov=0, TermMode_reload=0, TermMode_start=0, TermMode_stop=0, TermMode_un=0, TermModeStates=, TermVisibility_capture=false, TermVisibility_cc=true, TermVisibility_clock=true, TermVisibility_count=false, TermVisibility_interrupt=true, TermVisibility_line=true, TermVisibility_line_n=true, TermVisibility_ov=true, TermVisibility_reload=false, TermVisibility_start=false, TermVisibility_stop=false, TermVisibility_un=true, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMPONENT_NAME=TCPWM_P4_v2_0, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=PWMRIGHT, CY_INSTANCE_SHORT_NAME=PWMRIGHT, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=0, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  3.3 SP1, INSTANCE_NAME=PWMRIGHT, )
module TCPWM_P4_v2_0_2 (
    stop,
    count,
    reload,
    start,
    capture,
    interrupt,
    ov,
    un,
    cc,
    clock,
    line,
    line_n);
    input       stop;
    input       count;
    input       reload;
    input       start;
    input       capture;
    output      interrupt;
    output      ov;
    output      un;
    output      cc;
    input       clock;
    output      line;
    output      line_n;


          wire  Net_64;
          wire  Net_63;
          wire  Net_85;
          wire  Net_62;
          wire  Net_110;
          wire  Net_95;
          wire  Net_106;
          wire  Net_104;
          wire  Net_109;
          wire  Net_98;
          wire  Net_108;
          wire  Net_101;
          wire  Net_66;
          wire  Net_81;
          wire  Net_75;
          wire  Net_69;
          wire  Net_82;
          wire  Net_72;

    cy_m0s8_tcpwm_v1_0 cy_m0s8_tcpwm_1 (
        .capture(Net_75),
        .underflow(un),
        .overflow(ov),
        .line_out_compl(line_n),
        .line_out(line),
        .compare_match(cc),
        .interrupt(interrupt),
        .count(Net_69),
        .reload(Net_66),
        .stop(Net_82),
        .start(Net_72),
        .clock(Net_81));

	// VMux_reload (cy_virtualmux_v1_0)
	assign Net_66 = reload;

	// VMux_count (cy_virtualmux_v1_0)
	assign Net_69 = count;

	// VMux_start (cy_virtualmux_v1_0)
	assign Net_72 = start;

	// VMux_capture (cy_virtualmux_v1_0)
	assign Net_75 = capture;

	// VMux_stop (cy_virtualmux_v1_0)
	assign Net_82 = stop;

	// VMux_clock (cy_virtualmux_v1_0)
	assign Net_81 = clock;



endmodule

// TCPWM_P4_v2_0(Clock_CheckTolerance=true, Clock_desired_freq=12, Clock_desired_freq_unit=6, Clock_divisor=1, Clock_FractDividerDenominator=0, Clock_FractDividerNumerator=0, Clock_FractDividerUsed=false, Clock_is_direct=false, Clock_is_divider=false, Clock_is_freq=true, Clock_minus_tolerance=5, Clock_ph_align_clock_id=, Clock_ph_align_clock_name=, Clock_plus_tolerance=5, Clock_source_clock_id=, Clock_source_clock_name=, PinVisibility_index=false, PinVisibility_kill=false, PinVisibility_phiA=true, PinVisibility_phiB=true, PinVisibility_switch=false, PWMCompare=65535, PWMCompareBuf=65535, PWMCompareSwap=0, PWMCountMode=3, PWMCountPresent=false, PWMDeadTimeCycle=0, PWMInterruptMask=1, PWMKillEvent=0, PWMLinenSignal=0, PWMLineSignal=0, PWMMode=4, PWMPeriod=65535, PWMPeriodBuf=65535, PWMPeriodSwap=0, PWMPrescaler=0, PWMReloadMode=0, PWMReloadPresent=false, PWMRunMode=0, PWMSetAlign=0, PWMStartMode=0, PWMStartPresent=false, PWMStopEvent=0, PWMStopMode=0, PWMStopPresent=false, PWMSwitchMode=0, PWMSwitchPresent=false, QuadEncodingModes=0, QuadIndexMode=0, QuadIndexPresent=false, QuadInterruptMask=0, QuadPhiAMode=3, QuadPhiBMode=3, QuadStopMode=0, QuadStopPresent=false, TCCaptureMode=0, TCCapturePresent=false, TCCompare=65535, TCCompareBuf=65535, TCCompareSwap=0, TCCompCapMode=2, TCCountingModes=0, TCCountMode=3, TCCountPresent=false, TCInterruptMask=1, TCPeriod=65535, TCPrescaler=0, TCPWMCapturePresent=false, TCPWMConfig=3, TCPWMCountPresent=false, TCPWMReloadPresent=false, TCPWMStartPresent=false, TCPWMStopPresent=false, TCReloadMode=0, TCReloadPresent=false, TCRunMode=0, TCStartMode=0, TCStartPresent=false, TCStopMode=0, TCStopPresent=false, TermMode_capture=0, TermMode_cc=0, TermMode_clock=0, TermMode_count=0, TermMode_interrupt=0, TermMode_line=0, TermMode_line_n=0, TermMode_ov=0, TermMode_reload=0, TermMode_start=0, TermMode_stop=0, TermMode_un=0, TermModeStates=, TermVisibility_capture=false, TermVisibility_cc=true, TermVisibility_clock=true, TermVisibility_count=true, TermVisibility_interrupt=true, TermVisibility_line=false, TermVisibility_line_n=false, TermVisibility_ov=false, TermVisibility_reload=false, TermVisibility_start=true, TermVisibility_stop=false, TermVisibility_un=false, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMPONENT_NAME=TCPWM_P4_v2_0, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=QDLEFT, CY_INSTANCE_SHORT_NAME=QDLEFT, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=0, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  3.3 SP1, INSTANCE_NAME=QDLEFT, )
module TCPWM_P4_v2_0_3 (
    stop,
    count,
    reload,
    start,
    capture,
    interrupt,
    ov,
    un,
    cc,
    clock,
    line,
    line_n);
    input       stop;
    input       count;
    input       reload;
    input       start;
    input       capture;
    output      interrupt;
    output      ov;
    output      un;
    output      cc;
    input       clock;
    output      line;
    output      line_n;


          wire  Net_64;
          wire  Net_63;
          wire  Net_85;
          wire  Net_62;
          wire  Net_110;
          wire  Net_95;
          wire  Net_106;
          wire  Net_104;
          wire  Net_109;
          wire  Net_98;
          wire  Net_108;
          wire  Net_101;
          wire  Net_66;
          wire  Net_81;
          wire  Net_75;
          wire  Net_69;
          wire  Net_82;
          wire  Net_72;

    cy_m0s8_tcpwm_v1_0 cy_m0s8_tcpwm_1 (
        .capture(Net_75),
        .underflow(un),
        .overflow(ov),
        .line_out_compl(line_n),
        .line_out(line),
        .compare_match(cc),
        .interrupt(interrupt),
        .count(Net_69),
        .reload(Net_66),
        .stop(Net_82),
        .start(Net_72),
        .clock(Net_81));

	// VMux_reload (cy_virtualmux_v1_0)
	assign Net_66 = reload;

	// VMux_count (cy_virtualmux_v1_0)
	assign Net_69 = count;

	// VMux_start (cy_virtualmux_v1_0)
	assign Net_72 = start;

	// VMux_capture (cy_virtualmux_v1_0)
	assign Net_75 = capture;

	// VMux_stop (cy_virtualmux_v1_0)
	assign Net_82 = stop;

	// VMux_clock (cy_virtualmux_v1_0)
	assign Net_81 = clock;



endmodule

// TCPWM_P4_v2_0(Clock_CheckTolerance=true, Clock_desired_freq=12, Clock_desired_freq_unit=6, Clock_divisor=1, Clock_FractDividerDenominator=0, Clock_FractDividerNumerator=0, Clock_FractDividerUsed=false, Clock_is_direct=false, Clock_is_divider=false, Clock_is_freq=true, Clock_minus_tolerance=5, Clock_ph_align_clock_id=, Clock_ph_align_clock_name=, Clock_plus_tolerance=5, Clock_source_clock_id=, Clock_source_clock_name=, PinVisibility_index=false, PinVisibility_kill=false, PinVisibility_phiA=true, PinVisibility_phiB=true, PinVisibility_switch=false, PWMCompare=65535, PWMCompareBuf=65535, PWMCompareSwap=0, PWMCountMode=3, PWMCountPresent=false, PWMDeadTimeCycle=0, PWMInterruptMask=1, PWMKillEvent=0, PWMLinenSignal=0, PWMLineSignal=0, PWMMode=4, PWMPeriod=65535, PWMPeriodBuf=65535, PWMPeriodSwap=0, PWMPrescaler=0, PWMReloadMode=0, PWMReloadPresent=false, PWMRunMode=0, PWMSetAlign=0, PWMStartMode=0, PWMStartPresent=false, PWMStopEvent=0, PWMStopMode=0, PWMStopPresent=false, PWMSwitchMode=0, PWMSwitchPresent=false, QuadEncodingModes=0, QuadIndexMode=0, QuadIndexPresent=false, QuadInterruptMask=0, QuadPhiAMode=3, QuadPhiBMode=3, QuadStopMode=0, QuadStopPresent=false, TCCaptureMode=0, TCCapturePresent=false, TCCompare=65535, TCCompareBuf=65535, TCCompareSwap=0, TCCompCapMode=2, TCCountingModes=0, TCCountMode=3, TCCountPresent=false, TCInterruptMask=1, TCPeriod=65535, TCPrescaler=0, TCPWMCapturePresent=false, TCPWMConfig=3, TCPWMCountPresent=false, TCPWMReloadPresent=false, TCPWMStartPresent=false, TCPWMStopPresent=false, TCReloadMode=0, TCReloadPresent=false, TCRunMode=0, TCStartMode=0, TCStartPresent=false, TCStopMode=0, TCStopPresent=false, TermMode_capture=0, TermMode_cc=0, TermMode_clock=0, TermMode_count=0, TermMode_interrupt=0, TermMode_line=0, TermMode_line_n=0, TermMode_ov=0, TermMode_reload=0, TermMode_start=0, TermMode_stop=0, TermMode_un=0, TermModeStates=, TermVisibility_capture=false, TermVisibility_cc=true, TermVisibility_clock=true, TermVisibility_count=true, TermVisibility_interrupt=true, TermVisibility_line=false, TermVisibility_line_n=false, TermVisibility_ov=false, TermVisibility_reload=false, TermVisibility_start=true, TermVisibility_stop=false, TermVisibility_un=false, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMPONENT_NAME=TCPWM_P4_v2_0, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=QDRIGHT, CY_INSTANCE_SHORT_NAME=QDRIGHT, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=0, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  3.3 SP1, INSTANCE_NAME=QDRIGHT, )
module TCPWM_P4_v2_0_4 (
    stop,
    count,
    reload,
    start,
    capture,
    interrupt,
    ov,
    un,
    cc,
    clock,
    line,
    line_n);
    input       stop;
    input       count;
    input       reload;
    input       start;
    input       capture;
    output      interrupt;
    output      ov;
    output      un;
    output      cc;
    input       clock;
    output      line;
    output      line_n;


          wire  Net_64;
          wire  Net_63;
          wire  Net_85;
          wire  Net_62;
          wire  Net_110;
          wire  Net_95;
          wire  Net_106;
          wire  Net_104;
          wire  Net_109;
          wire  Net_98;
          wire  Net_108;
          wire  Net_101;
          wire  Net_66;
          wire  Net_81;
          wire  Net_75;
          wire  Net_69;
          wire  Net_82;
          wire  Net_72;

    cy_m0s8_tcpwm_v1_0 cy_m0s8_tcpwm_1 (
        .capture(Net_75),
        .underflow(un),
        .overflow(ov),
        .line_out_compl(line_n),
        .line_out(line),
        .compare_match(cc),
        .interrupt(interrupt),
        .count(Net_69),
        .reload(Net_66),
        .stop(Net_82),
        .start(Net_72),
        .clock(Net_81));

	// VMux_reload (cy_virtualmux_v1_0)
	assign Net_66 = reload;

	// VMux_count (cy_virtualmux_v1_0)
	assign Net_69 = count;

	// VMux_start (cy_virtualmux_v1_0)
	assign Net_72 = start;

	// VMux_capture (cy_virtualmux_v1_0)
	assign Net_75 = capture;

	// VMux_stop (cy_virtualmux_v1_0)
	assign Net_82 = stop;

	// VMux_clock (cy_virtualmux_v1_0)
	assign Net_81 = clock;



endmodule

// Component: B_PWM_v3_30
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v3_30"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v3_30\B_PWM_v3_30.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v3_30"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v3_30\B_PWM_v3_30.v"
`endif

// Component: ZeroTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`endif

// PWM_v3_30(CaptureMode=0, Clock_CheckTolerance=true, Clock_desired_freq=12, Clock_desired_freq_unit=6, Clock_divisor=1, Clock_FractDividerDenominator=0, Clock_FractDividerNumerator=0, Clock_FractDividerUsed=false, Clock_is_direct=false, Clock_is_divider=false, Clock_is_freq=true, Clock_minus_tolerance=5, Clock_ph_align_clock_id=, Clock_ph_align_clock_name=, Clock_plus_tolerance=5, Clock_source_clock_id=, Clock_source_clock_name=, Compare1_16=false, Compare1_8=true, Compare2_16=false, Compare2_8=false, CompareStatusEdgeSense=true, CompareType1=1, CompareType1Software=0, CompareType2=1, CompareType2Software=0, CompareValue1=100, CompareValue2=63, CONTROL3=0, ControlReg=true, CtlModeReplacementString=SyncCtl, CyGetRegReplacementString=CY_GET_REG8, CySetRegReplacementString=CY_SET_REG8, DeadBand=0, DeadBand2_4=0, DeadBand256=0, DeadBandUsed=0, DeadTime=1, DitherOffset=0, EnableMode=0, FF16=false, FF8=false, FixedFunction=false, FixedFunctionUsed=0, InterruptOnCMP1=false, InterruptOnCMP2=false, InterruptOnKill=false, InterruptOnTC=false, IntOnCMP1=0, IntOnCMP2=0, IntOnKill=0, IntOnTC=0, KillMode=0, KillModeMinTime=0, MinimumKillTime=1, OneCompare=true, Period=199, PWMMode=0, PWMModeCenterAligned=0, RegDefReplacementString=reg8, RegSizeReplacementString=uint8, Resolution=8, RstStatusReplacementString=sSTSReg_rstSts, RunMode=0, Status=true, TermMode_capture=0, TermMode_clock=0, TermMode_cmp_sel=0, TermMode_enable=0, TermMode_interrupt=0, TermMode_kill=0, TermMode_ph1=0, TermMode_ph2=0, TermMode_pwm=0, TermMode_pwm1=0, TermMode_pwm2=0, TermMode_reset=0, TermMode_tc=0, TermMode_trigger=0, TermVisibility_capture=false, TermVisibility_clock=true, TermVisibility_cmp_sel=false, TermVisibility_enable=false, TermVisibility_interrupt=true, TermVisibility_kill=false, TermVisibility_ph1=false, TermVisibility_ph2=false, TermVisibility_pwm=true, TermVisibility_pwm1=false, TermVisibility_pwm2=false, TermVisibility_reset=true, TermVisibility_tc=true, TermVisibility_trigger=false, TriggerMode=0, UDB16=false, UDB8=true, UseControl=true, UseInterrupt=true, UseStatus=true, VerilogSectionReplacementString=sP8, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMPONENT_NAME=PWM_v3_30, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=tachPwm, CY_INSTANCE_SHORT_NAME=tachPwm, CY_MAJOR_VERSION=3, CY_MINOR_VERSION=30, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  3.3 SP1, INSTANCE_NAME=tachPwm, )
module PWM_v3_30_5 (
    pwm2,
    tc,
    clock,
    reset,
    pwm1,
    interrupt,
    capture,
    kill,
    enable,
    trigger,
    cmp_sel,
    pwm,
    ph1,
    ph2);
    output      pwm2;
    output      tc;
    input       clock;
    input       reset;
    output      pwm1;
    output      interrupt;
    input       capture;
    input       kill;
    input       enable;
    input       trigger;
    input       cmp_sel;
    output      pwm;
    output      ph1;
    output      ph2;

    parameter Resolution = 8;

          wire  Net_227;
          wire  Net_226;
          wire  Net_225;
          wire  Net_224;
          wire  Net_223;
          wire  Net_222;
          wire  Net_139;
          wire  Net_138;
          wire  Net_135;
          wire  Net_178;
          wire  Net_181;
          wire  Net_179;
          wire  Net_180;
          wire  Net_183;
          wire  Net_186;
          wire  Net_68;
          wire  Net_125;

    B_PWM_v3_30 PWMUDB (
        .reset(Net_186),
        .clock(Net_68),
        .tc(tc),
        .pwm1(pwm1),
        .pwm2(pwm2),
        .interrupt(interrupt),
        .kill(Net_179),
        .capture(Net_180),
        .enable(Net_181),
        .cmp_sel(Net_183),
        .trigger(Net_178),
        .pwm(pwm),
        .ph1(ph1),
        .ph2(ph2));
    defparam PWMUDB.CaptureMode = 0;
    defparam PWMUDB.CompareStatusEdgeSense = 1;
    defparam PWMUDB.CompareType1 = 1;
    defparam PWMUDB.CompareType2 = 1;
    defparam PWMUDB.DeadBand = 0;
    defparam PWMUDB.DitherOffset = 0;
    defparam PWMUDB.EnableMode = 0;
    defparam PWMUDB.KillMode = 0;
    defparam PWMUDB.PWMMode = 0;
    defparam PWMUDB.Resolution = 8;
    defparam PWMUDB.RunMode = 0;
    defparam PWMUDB.TriggerMode = 0;
    defparam PWMUDB.UseStatus = 1;

	// VMux_clock (cy_virtualmux_v1_0)
	assign Net_68 = clock;


    assign Net_139 = Net_125 | Net_138;

    ZeroTerminal ZeroTerminal_7 (
        .z(Net_138));

	// VMux_capture (cy_virtualmux_v1_0)
	assign Net_179 = kill;

	// VMux_capture_1 (cy_virtualmux_v1_0)
	assign Net_183 = cmp_sel;

	// VMux_capture_2 (cy_virtualmux_v1_0)
	assign Net_180 = capture;

	// VMux_capture_3 (cy_virtualmux_v1_0)
	assign Net_181 = enable;

	// VMux_capture_4 (cy_virtualmux_v1_0)
	assign Net_178 = trigger;

	// VMux_capture_5 (cy_virtualmux_v1_0)
	assign Net_186 = reset;



endmodule

// PWM_v3_30(CaptureMode=0, Clock_CheckTolerance=true, Clock_desired_freq=12, Clock_desired_freq_unit=6, Clock_divisor=1, Clock_FractDividerDenominator=0, Clock_FractDividerNumerator=0, Clock_FractDividerUsed=false, Clock_is_direct=false, Clock_is_divider=false, Clock_is_freq=true, Clock_minus_tolerance=5, Clock_ph_align_clock_id=, Clock_ph_align_clock_name=, Clock_plus_tolerance=5, Clock_source_clock_id=, Clock_source_clock_name=, Compare1_16=false, Compare1_8=true, Compare2_16=false, Compare2_8=false, CompareStatusEdgeSense=true, CompareType1=1, CompareType1Software=0, CompareType2=1, CompareType2Software=0, CompareValue1=127, CompareValue2=63, CONTROL3=0, ControlReg=true, CtlModeReplacementString=SyncCtl, CyGetRegReplacementString=CY_GET_REG8, CySetRegReplacementString=CY_SET_REG8, DeadBand=0, DeadBand2_4=0, DeadBand256=0, DeadBandUsed=0, DeadTime=1, DitherOffset=0, EnableMode=0, FF16=false, FF8=false, FixedFunction=false, FixedFunctionUsed=0, InterruptOnCMP1=false, InterruptOnCMP2=false, InterruptOnKill=false, InterruptOnTC=false, IntOnCMP1=0, IntOnCMP2=0, IntOnKill=0, IntOnTC=0, KillMode=0, KillModeMinTime=0, MinimumKillTime=1, OneCompare=true, Period=255, PWMMode=0, PWMModeCenterAligned=0, RegDefReplacementString=reg8, RegSizeReplacementString=uint8, Resolution=8, RstStatusReplacementString=sSTSReg_rstSts, RunMode=0, Status=true, TermMode_capture=0, TermMode_clock=0, TermMode_cmp_sel=0, TermMode_enable=0, TermMode_interrupt=0, TermMode_kill=0, TermMode_ph1=0, TermMode_ph2=0, TermMode_pwm=0, TermMode_pwm1=0, TermMode_pwm2=0, TermMode_reset=0, TermMode_tc=0, TermMode_trigger=0, TermVisibility_capture=false, TermVisibility_clock=true, TermVisibility_cmp_sel=false, TermVisibility_enable=false, TermVisibility_interrupt=true, TermVisibility_kill=false, TermVisibility_ph1=false, TermVisibility_ph2=false, TermVisibility_pwm=true, TermVisibility_pwm1=false, TermVisibility_pwm2=false, TermVisibility_reset=true, TermVisibility_tc=true, TermVisibility_trigger=false, TriggerMode=0, UDB16=false, UDB8=true, UseControl=true, UseInterrupt=true, UseStatus=true, VerilogSectionReplacementString=sP8, CY_API_CALLBACK_HEADER_INCLUDE=#include "cyapicallbacks.h", CY_COMPONENT_NAME=PWM_v3_30, CY_CONTROL_FILE=<:default:>, CY_DATASHEET_FILE=<:default:>, CY_FITTER_NAME=ledpwm, CY_INSTANCE_SHORT_NAME=ledpwm, CY_MAJOR_VERSION=3, CY_MINOR_VERSION=30, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=PSoC Creator  3.3 SP1, INSTANCE_NAME=ledpwm, )
module PWM_v3_30_6 (
    pwm2,
    tc,
    clock,
    reset,
    pwm1,
    interrupt,
    capture,
    kill,
    enable,
    trigger,
    cmp_sel,
    pwm,
    ph1,
    ph2);
    output      pwm2;
    output      tc;
    input       clock;
    input       reset;
    output      pwm1;
    output      interrupt;
    input       capture;
    input       kill;
    input       enable;
    input       trigger;
    input       cmp_sel;
    output      pwm;
    output      ph1;
    output      ph2;

    parameter Resolution = 8;

          wire  Net_227;
          wire  Net_226;
          wire  Net_225;
          wire  Net_224;
          wire  Net_223;
          wire  Net_222;
          wire  Net_139;
          wire  Net_138;
          wire  Net_135;
          wire  Net_178;
          wire  Net_181;
          wire  Net_179;
          wire  Net_180;
          wire  Net_183;
          wire  Net_186;
          wire  Net_68;
          wire  Net_125;

    B_PWM_v3_30 PWMUDB (
        .reset(Net_186),
        .clock(Net_68),
        .tc(tc),
        .pwm1(pwm1),
        .pwm2(pwm2),
        .interrupt(interrupt),
        .kill(Net_179),
        .capture(Net_180),
        .enable(Net_181),
        .cmp_sel(Net_183),
        .trigger(Net_178),
        .pwm(pwm),
        .ph1(ph1),
        .ph2(ph2));
    defparam PWMUDB.CaptureMode = 0;
    defparam PWMUDB.CompareStatusEdgeSense = 1;
    defparam PWMUDB.CompareType1 = 1;
    defparam PWMUDB.CompareType2 = 1;
    defparam PWMUDB.DeadBand = 0;
    defparam PWMUDB.DitherOffset = 0;
    defparam PWMUDB.EnableMode = 0;
    defparam PWMUDB.KillMode = 0;
    defparam PWMUDB.PWMMode = 0;
    defparam PWMUDB.Resolution = 8;
    defparam PWMUDB.RunMode = 0;
    defparam PWMUDB.TriggerMode = 0;
    defparam PWMUDB.UseStatus = 1;

	// VMux_clock (cy_virtualmux_v1_0)
	assign Net_68 = clock;


    assign Net_139 = Net_125 | Net_138;

    ZeroTerminal ZeroTerminal_7 (
        .z(Net_138));

	// VMux_capture (cy_virtualmux_v1_0)
	assign Net_179 = kill;

	// VMux_capture_1 (cy_virtualmux_v1_0)
	assign Net_183 = cmp_sel;

	// VMux_capture_2 (cy_virtualmux_v1_0)
	assign Net_180 = capture;

	// VMux_capture_3 (cy_virtualmux_v1_0)
	assign Net_181 = enable;

	// VMux_capture_4 (cy_virtualmux_v1_0)
	assign Net_178 = trigger;

	// VMux_capture_5 (cy_virtualmux_v1_0)
	assign Net_186 = reset;



endmodule

// Component: not_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\not_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\not_v1_0\not_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\not_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\3.3\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\not_v1_0\not_v1_0.v"
`endif

// top
module top ;

          wire  Net_1562;
          wire  Net_938;
          wire  Net_2561;
          wire  Net_2737;
          wire  Net_2736;
          wire  Net_2735;
          wire  Net_2734;
          wire  Net_2733;
          wire  Net_2732;
          wire  Net_2731;
          wire  Net_2730;
          wire  Net_2729;
          wire  Net_2728;
          wire  Net_2727;
          wire  Net_578;
          wire  Net_2726;
          wire  Net_2725;
          wire  Net_2724;
          wire  Net_2723;
          wire  Net_2722;
          wire  Net_2721;
          wire  Net_2720;
          wire  Net_2719;
          wire  Net_802;
          wire  Net_2718;
          wire  Net_2717;
          wire  Net_2716;
          wire  Net_537;
          wire  Net_175;
          wire  Net_174;
          wire  Net_173;
          wire  Net_172;
          wire  Net_171;
          wire  Net_170;
          wire  Net_169;
          wire  Net_168;
          wire  Net_167;
          wire  Net_166;
          wire  Net_165;
          wire  Net_135;
          wire  Net_134;
          wire  Net_133;
          wire  Net_132;
          wire  Net_131;
          wire  Net_130;
          wire  Net_129;
          wire  Net_128;
          wire  Net_127;
          wire  Net_126;
          wire  Net_125;
          wire  Net_1985;
          wire  Net_254;
          wire  Net_1984;
          wire  Net_1983;
          wire  Net_1982;
          wire  Net_1981;
          wire  Net_1980;
          wire  Net_1979;
          wire  Net_1978;
          wire  Net_1977;
          wire  Net_1976;
          wire  Net_1953;
          wire  Net_214;
          wire  Net_1952;
          wire  Net_1951;
          wire  Net_1950;
          wire  Net_1949;
          wire  Net_1948;
          wire  Net_1947;
          wire  Net_1946;
          wire  Net_1945;
          wire  Net_1944;
          wire  Net_2199;
          wire  Net_256;
          wire  Net_935;
          wire  Net_676;
          wire  Net_6;

    BLE_v2_30_0 BLE (
        .clk(Net_2199));

	wire [0:0] tmpOE__Control_net;
	wire [0:0] tmpFB_0__Control_net;
	wire [0:0] tmpIO_0__Control_net;
	electrical [0:0] tmpSIOVREF__Control_net;

	cy_psoc3_pins_v1_10
		#(.id("8d318d8b-cf7b-4b6b-b02c-ab1c5c49d0ba"),
		  .drive_mode(3'b010),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b10),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b00),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		Control
		 (.oe(tmpOE__Control_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__Control_net[0:0]}),
		  .io({tmpIO_0__Control_net[0:0]}),
		  .siovref(tmpSIOVREF__Control_net),
		  .interrupt({Net_6}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__Control_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


	cy_isr_v1_0
		#(.int_type(2'b10))
		swint
		 (.int_signal(Net_6));


    TCPWM_P4_v2_0_1 PWMLEFT (
        .stop(1'b0),
        .reload(1'b0),
        .start(1'b0),
        .count(1'b1),
        .capture(1'b0),
        .interrupt(Net_1949),
        .ov(Net_1950),
        .un(Net_1951),
        .cc(Net_1952),
        .line(Net_214),
        .line_n(Net_1953),
        .clock(Net_256));

    TCPWM_P4_v2_0_2 PWMRIGHT (
        .stop(1'b0),
        .reload(1'b0),
        .start(1'b0),
        .count(1'b1),
        .capture(1'b0),
        .interrupt(Net_1981),
        .ov(Net_1982),
        .un(Net_1983),
        .cc(Net_1984),
        .line(Net_254),
        .line_n(Net_1985),
        .clock(Net_256));

    TCPWM_P4_v2_0_3 QDLEFT (
        .stop(1'b0),
        .reload(1'b0),
        .start(Net_127),
        .count(Net_128),
        .capture(1'b0),
        .interrupt(Net_130),
        .ov(Net_131),
        .un(Net_132),
        .cc(Net_133),
        .line(Net_134),
        .line_n(Net_135),
        .clock(Net_256));

    TCPWM_P4_v2_0_4 QDRIGHT (
        .stop(1'b0),
        .reload(1'b0),
        .start(Net_167),
        .count(Net_168),
        .capture(1'b0),
        .interrupt(Net_170),
        .ov(Net_171),
        .un(Net_172),
        .cc(Net_173),
        .line(Net_174),
        .line_n(Net_175),
        .clock(Net_256));

    PWM_v3_30_5 tachPwm (
        .reset(Net_537),
        .clock(Net_676),
        .tc(Net_2716),
        .pwm1(Net_2717),
        .pwm2(Net_2718),
        .interrupt(Net_802),
        .capture(1'b0),
        .kill(1'b1),
        .enable(1'b1),
        .trigger(1'b0),
        .cmp_sel(1'b0),
        .pwm(Net_2724),
        .ph1(Net_2725),
        .ph2(Net_2726));
    defparam tachPwm.Resolution = 8;

    PWM_v3_30_6 ledpwm (
        .reset(Net_578),
        .clock(Net_676),
        .tc(Net_2727),
        .pwm1(Net_2728),
        .pwm2(Net_2729),
        .interrupt(Net_2730),
        .capture(1'b0),
        .kill(1'b1),
        .enable(1'b1),
        .trigger(1'b0),
        .cmp_sel(1'b0),
        .pwm(Net_935),
        .ph1(Net_2736),
        .ph2(Net_2737));
    defparam ledpwm.Resolution = 8;

    assign Net_537 = 1'h0;

    assign Net_578 = 1'h0;


	cy_clock_v1_0
		#(.id("1d897849-ebab-4b98-9969-0e25401e3ded"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("938086303939.963"),
		  .is_direct(0),
		  .is_digital(0))
		Clock_1
		 (.clock_out(Net_676));



	cy_isr_v1_0
		#(.int_type(2'b10))
		tachTimer
		 (.int_signal(Net_802));



    assign Net_938 = ~Net_935;

	wire [0:0] tmpOE__red_net;
	wire [0:0] tmpFB_0__red_net;
	wire [0:0] tmpIO_0__red_net;
	wire [0:0] tmpINTERRUPT_0__red_net;
	electrical [0:0] tmpSIOVREF__red_net;

	cy_psoc3_pins_v1_10
		#(.id("e851a3b9-efb8-48be-bbb8-b303b216c393"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		red
		 (.oe(tmpOE__red_net),
		  .y({Net_938}),
		  .fb({tmpFB_0__red_net[0:0]}),
		  .io({tmpIO_0__red_net[0:0]}),
		  .siovref(tmpSIOVREF__red_net),
		  .interrupt({tmpINTERRUPT_0__red_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__red_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__M1_net;
	wire [0:0] tmpFB_0__M1_net;
	wire [0:0] tmpIO_0__M1_net;
	wire [0:0] tmpINTERRUPT_0__M1_net;
	electrical [0:0] tmpSIOVREF__M1_net;

	cy_psoc3_pins_v1_10
		#(.id("69c0e94d-9618-4464-81eb-8f27fa6fb145"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		M1
		 (.oe(tmpOE__M1_net),
		  .y({Net_214}),
		  .fb({tmpFB_0__M1_net[0:0]}),
		  .io({tmpIO_0__M1_net[0:0]}),
		  .siovref(tmpSIOVREF__M1_net),
		  .interrupt({tmpINTERRUPT_0__M1_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__M1_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__M2_net;
	wire [0:0] tmpFB_0__M2_net;
	wire [0:0] tmpIO_0__M2_net;
	wire [0:0] tmpINTERRUPT_0__M2_net;
	electrical [0:0] tmpSIOVREF__M2_net;

	cy_psoc3_pins_v1_10
		#(.id("1e71cf50-5465-42b0-a389-a42675f37e72"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b1),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		M2
		 (.oe(tmpOE__M2_net),
		  .y({Net_254}),
		  .fb({tmpFB_0__M2_net[0:0]}),
		  .io({tmpIO_0__M2_net[0:0]}),
		  .siovref(tmpSIOVREF__M2_net),
		  .interrupt({tmpINTERRUPT_0__M2_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__M2_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__POWERLEFT_net;
	wire [0:0] tmpFB_0__POWERLEFT_net;
	wire [0:0] tmpIO_0__POWERLEFT_net;
	wire [0:0] tmpINTERRUPT_0__POWERLEFT_net;
	electrical [0:0] tmpSIOVREF__POWERLEFT_net;

	cy_psoc3_pins_v1_10
		#(.id("55a880ec-bc79-4cc6-8b44-8f5229c06363"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		POWERLEFT
		 (.oe(tmpOE__POWERLEFT_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__POWERLEFT_net[0:0]}),
		  .io({tmpIO_0__POWERLEFT_net[0:0]}),
		  .siovref(tmpSIOVREF__POWERLEFT_net),
		  .interrupt({tmpINTERRUPT_0__POWERLEFT_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__POWERLEFT_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__GNDLEFT_net;
	wire [0:0] tmpFB_0__GNDLEFT_net;
	wire [0:0] tmpIO_0__GNDLEFT_net;
	wire [0:0] tmpINTERRUPT_0__GNDLEFT_net;
	electrical [0:0] tmpSIOVREF__GNDLEFT_net;

	cy_psoc3_pins_v1_10
		#(.id("a01436ef-01ae-47ac-9d59-0be48e815850"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		GNDLEFT
		 (.oe(tmpOE__GNDLEFT_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__GNDLEFT_net[0:0]}),
		  .io({tmpIO_0__GNDLEFT_net[0:0]}),
		  .siovref(tmpSIOVREF__GNDLEFT_net),
		  .interrupt({tmpINTERRUPT_0__GNDLEFT_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__GNDLEFT_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__DIRLEFT_net;
	wire [0:0] tmpFB_0__DIRLEFT_net;
	wire [0:0] tmpIO_0__DIRLEFT_net;
	wire [0:0] tmpINTERRUPT_0__DIRLEFT_net;
	electrical [0:0] tmpSIOVREF__DIRLEFT_net;

	cy_psoc3_pins_v1_10
		#(.id("8df0419c-3fc9-4ace-b4b6-ebbc1bae81d7"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		DIRLEFT
		 (.oe(tmpOE__DIRLEFT_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__DIRLEFT_net[0:0]}),
		  .io({tmpIO_0__DIRLEFT_net[0:0]}),
		  .siovref(tmpSIOVREF__DIRLEFT_net),
		  .interrupt({tmpINTERRUPT_0__DIRLEFT_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__DIRLEFT_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__POWERRIGHT_net;
	wire [0:0] tmpFB_0__POWERRIGHT_net;
	wire [0:0] tmpIO_0__POWERRIGHT_net;
	wire [0:0] tmpINTERRUPT_0__POWERRIGHT_net;
	electrical [0:0] tmpSIOVREF__POWERRIGHT_net;

	cy_psoc3_pins_v1_10
		#(.id("2b6d5c2b-7b96-48fe-8662-e2e401f11629"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		POWERRIGHT
		 (.oe(tmpOE__POWERRIGHT_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__POWERRIGHT_net[0:0]}),
		  .io({tmpIO_0__POWERRIGHT_net[0:0]}),
		  .siovref(tmpSIOVREF__POWERRIGHT_net),
		  .interrupt({tmpINTERRUPT_0__POWERRIGHT_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__POWERRIGHT_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__GNDRIGHT_net;
	wire [0:0] tmpFB_0__GNDRIGHT_net;
	wire [0:0] tmpIO_0__GNDRIGHT_net;
	wire [0:0] tmpINTERRUPT_0__GNDRIGHT_net;
	electrical [0:0] tmpSIOVREF__GNDRIGHT_net;

	cy_psoc3_pins_v1_10
		#(.id("cce97e0f-9a79-4532-bee5-e266205dea28"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		GNDRIGHT
		 (.oe(tmpOE__GNDRIGHT_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__GNDRIGHT_net[0:0]}),
		  .io({tmpIO_0__GNDRIGHT_net[0:0]}),
		  .siovref(tmpSIOVREF__GNDRIGHT_net),
		  .interrupt({tmpINTERRUPT_0__GNDRIGHT_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__GNDRIGHT_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__DIRRIGHT_net;
	wire [0:0] tmpFB_0__DIRRIGHT_net;
	wire [0:0] tmpIO_0__DIRRIGHT_net;
	wire [0:0] tmpINTERRUPT_0__DIRRIGHT_net;
	electrical [0:0] tmpSIOVREF__DIRRIGHT_net;

	cy_psoc3_pins_v1_10
		#(.id("99109c82-8912-46f7-a3cb-2fe7420c7d79"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b10),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		DIRRIGHT
		 (.oe(tmpOE__DIRRIGHT_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__DIRRIGHT_net[0:0]}),
		  .io({tmpIO_0__DIRRIGHT_net[0:0]}),
		  .siovref(tmpSIOVREF__DIRRIGHT_net),
		  .interrupt({tmpINTERRUPT_0__DIRRIGHT_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__DIRRIGHT_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};


	cy_clock_v1_0
		#(.id("5e11703b-a341-4dae-8104-aa1d463baa98"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("50000000000"),
		  .is_direct(0),
		  .is_digital(0))
		Clock_2
		 (.clock_out(Net_256));


	wire [0:0] tmpOE__qd1a_net;
	wire [0:0] tmpIO_0__qd1a_net;
	wire [0:0] tmpINTERRUPT_0__qd1a_net;
	electrical [0:0] tmpSIOVREF__qd1a_net;

	cy_psoc3_pins_v1_10
		#(.id("0d0e6b28-f095-447c-bf68-a2b37a371b40"),
		  .drive_mode(3'b001),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b00),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		qd1a
		 (.oe(tmpOE__qd1a_net),
		  .y({1'b0}),
		  .fb({Net_128}),
		  .io({tmpIO_0__qd1a_net[0:0]}),
		  .siovref(tmpSIOVREF__qd1a_net),
		  .interrupt({tmpINTERRUPT_0__qd1a_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__qd1a_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__qd1b_net;
	wire [0:0] tmpIO_0__qd1b_net;
	wire [0:0] tmpINTERRUPT_0__qd1b_net;
	electrical [0:0] tmpSIOVREF__qd1b_net;

	cy_psoc3_pins_v1_10
		#(.id("b9c8f005-8f97-442a-bdfc-9b90a32b17e4"),
		  .drive_mode(3'b001),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b00),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		qd1b
		 (.oe(tmpOE__qd1b_net),
		  .y({1'b0}),
		  .fb({Net_127}),
		  .io({tmpIO_0__qd1b_net[0:0]}),
		  .siovref(tmpSIOVREF__qd1b_net),
		  .interrupt({tmpINTERRUPT_0__qd1b_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__qd1b_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__qd2a_net;
	wire [0:0] tmpIO_0__qd2a_net;
	wire [0:0] tmpINTERRUPT_0__qd2a_net;
	electrical [0:0] tmpSIOVREF__qd2a_net;

	cy_psoc3_pins_v1_10
		#(.id("b0231df0-3baa-496d-81f5-d5755b2991ee"),
		  .drive_mode(3'b001),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b00),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		qd2a
		 (.oe(tmpOE__qd2a_net),
		  .y({1'b0}),
		  .fb({Net_168}),
		  .io({tmpIO_0__qd2a_net[0:0]}),
		  .siovref(tmpSIOVREF__qd2a_net),
		  .interrupt({tmpINTERRUPT_0__qd2a_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__qd2a_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__qd2b_net;
	wire [0:0] tmpIO_0__qd2b_net;
	wire [0:0] tmpINTERRUPT_0__qd2b_net;
	electrical [0:0] tmpSIOVREF__qd2b_net;

	cy_psoc3_pins_v1_10
		#(.id("4cece307-5f30-463e-8247-14929e0e276f"),
		  .drive_mode(3'b001),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_clk_en(0),
		  .input_sync(1'b1),
		  .input_sync_mode(1'b0),
		  .intr_mode(2'b00),
		  .invert_in_clock(0),
		  .invert_in_clock_en(0),
		  .invert_in_reset(0),
		  .invert_out_clock(0),
		  .invert_out_clock_en(0),
		  .invert_out_reset(0),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .oe_reset(0),
		  .oe_sync(1'b0),
		  .output_clk_en(0),
		  .output_clock_mode(1'b0),
		  .output_conn(1'b0),
		  .output_mode(1'b0),
		  .output_reset(0),
		  .output_sync(1'b0),
		  .pa_in_clock(-1),
		  .pa_in_clock_en(-1),
		  .pa_in_reset(-1),
		  .pa_out_clock(-1),
		  .pa_out_clock_en(-1),
		  .pa_out_reset(-1),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b1),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .use_annotation(1'b0),
		  .vtrip(2'b00),
		  .width(1),
		  .ovt_hyst_trim(1'b0),
		  .ovt_needed(1'b0),
		  .ovt_slew_control(2'b00),
		  .input_buffer_sel(2'b00))
		qd2b
		 (.oe(tmpOE__qd2b_net),
		  .y({1'b0}),
		  .fb({Net_167}),
		  .io({tmpIO_0__qd2b_net[0:0]}),
		  .siovref(tmpSIOVREF__qd2b_net),
		  .interrupt({tmpINTERRUPT_0__qd2b_net[0:0]}),
		  .in_clock({1'b0}),
		  .in_clock_en({1'b1}),
		  .in_reset({1'b0}),
		  .out_clock({1'b0}),
		  .out_clock_en({1'b1}),
		  .out_reset({1'b0}));

	assign tmpOE__qd2b_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};



endmodule

