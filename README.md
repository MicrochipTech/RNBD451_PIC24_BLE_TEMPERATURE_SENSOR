# RNBD451 WITH PIC24FJ64GU205 AS BLE TEMPERATURE SENSOR

<img src="docs/IoT-Made-Easy-Logo.png" width=100>


> "IoT Made Easy!" 

Devices: **| RNBD451 | PIC24FJ64GU205 |**<br>
Features: **| BLE |**


## ⚠ Disclaimer

<p><span style="color:red"><b>
THE SOFTWARE ARE PROVIDED "AS IS" AND GIVE A PATH FOR SELF-SUPPORT AND SELF-MAINTENANCE. This repository contains example code intended to help accelerate client product development. </br>

For additional Microchip repos, see: <a href="https://github.com/Microchip-MPLAB-Harmony" target="_blank">https://github.com/Microchip-MPLAB-Harmony</a>

Checkout the <a href="https://microchipsupport.force.com/s/" target="_blank">Technical support portal</a> to access our knowledge base, community forums or submit support ticket requests.
</span></p></b>

## Contents

1. [Introduction](#step1)
1. [Bill of materials](#step2)
1. [Hardware Setup](#step3)
1. [Software Setup](#step4)
1. [Harmony MCC Configuration](#step5)
1. [Board Programming](#step6)
1. [Run the demo](#step7)

## 1. Introduction<a name="step1">

### Getting started with adding RNBD451 to PIC24FJ64GU205

This application shows how to use the RNBD451 along with the PIC24FJ64GU205 to develop a BLE temperature sensor application with TEMP&HUM 13 CLICK. The PIC24FJ64GU205 Curiosity Nano Development Board sends RN instructions to establish the Temperature sensor application, which can be monitored in the Microchip Bluetooth Data application.

![](docs/app.png)

## 2. Bill of materials<a name="step2">

| TOOLS | QUANTITY |
| :- | :- |
| [PIC24FJ64GU205 CURIOSITY NANO DEVELOPMENT BOARD](https://www.microchip.com/en-us/development-tool/ev10k72a) | 1 |
| [CURIOSITY NANO BASE FOR CLICK BOARDS](https://www.microchip.com/en-us/development-tool/ac164162) | 1 |
| [RNBD451 Add-on Board](https://www.microchip.com/en-us/development-tool/ev25f14a) | 1 |
| [TEMP&HUM 13 CLICK](https://www.mikroe.com/temphum-13-click) | 1 |

## 3. Hardware Setup<a name="step3">

- Connect the TEMP&HUM 13 CLICK Board to the Mikro Bus 1, RNBD451 Add-on Board to the Mikro Bus 2 and connect the PIC24FJ64GU205 CURIOSITY NANO DEVELOPMENT BOARD as shown below.

![](docs/hardware.png)

## 4. Software Setup<a name="step4">

- [MPLAB X IDE ](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide#tabs)

    - Version: 6.10
	- XC16 Compiler: v2.00
	- MPLAB® Code Configurator: v5.4.1
	- mcc_core_version: v5.6.1
	- content_manager_version: v4.3.1
	- PIC24F-GP-GU_DFP: v1.1.227
	  
- Any Serial Terminal application like [TERA TERM](https://download.cnet.com/Tera-Term/3000-2094_4-75766675.html) terminal application

- [MPLAB X IPE v6.10](https://microchipdeveloper.com/ipe:installation)

- [Microchip Bluetooth Data (MBD) iOS/Android app](https://play.google.com/store/apps/details?id=com.microchip.bluetooth.data&hl=en_IN&gl=US).


## 5. Harmony MCC Configuration<a name="step5">

### Implementing the RNBD451 with PIC24FJ64GU205.

| Tip | New users of MPLAB Code Configurator are recommended to go through the [overview](https://onlinedocs.microchip.com/pr/GUID-1F7007B8-9A46-4D03-AEED-650357BA760D-en-US-6/index.html?GUID-AFAB9227-B10C-4FAE-9785-98474664B50A) |
| :- | :- |

**Step 1** - Connect the PIC24FJ64GU205 CURIOSITY NANO DEVELOPMENT BOARD to the device/system using a micro-USB cable.

- Follow the steps for creating new project for PIC24FJ64GU205.

![](docs/np1.png)

![](docs/np2.png)

![](docs/np3.png)

![](docs/np4.png)

**Step 2** - Open the MPLAB Code Configurator and follow the steps as shown below.

- Choose MCC Classic while opening the MCC Code Configurator.

![](docs/project_resources.png)

**Step 3** - In Device Resources, go to Libraries->Foundation Services->I2CSIMPLE and add the I2CSIMPLE component to configure.

![](docs/I2CSIMPLE.png)

**Step 4** - In Project Resources, select the 16 bit I2CMASTER component from Foundation Services and configure.

![](docs/16bitI2CMASTER.png)

**Step 5** - In Project Resources, select the I2C1 component from Peripherals and configure.

![](docs/I2C1.png)

**Step 6** - In Device Resources, go to Libraries->Foundation Services->DELAY and add the DELAY component to configure.

![](docs/delay.png)

**Step 7** - In Device Resources, go to Libraries->Foundation Services->UART and add the UART component to configure.

![](docs/uart.png)

**Step 8** - In Project Resources, select the UART1 component from Peripherals and configure.

![](docs/UART1.png)

**Step 9** - In Project Resources, select the UART2 component from Peripherals and configure.

![](docs/UART2.png)

**Step 10** - In Project Resources, select the Pin Module component from Systems and configure.

- Refer the PIN Manager : Grid View and configure.

![](docs/gridview.png)

- Refer the pin module and configure.

![](docs/pinmodule.png)

**Step 11** - [Generate](https://onlinedocs.microchip.com/pr/GUID-A5330D3A-9F51-4A26-B71D-8503A493DF9C-en-US-1/index.html?GUID-9C28F407-4879-4174-9963-2CF34161398E) the code.

**Step 12** - Change the following Code as mentioned below.

- From the unzipped folder of this repository copy the folder "app_tempHum13" and "rnbd" from drivers to the folder firmware/your_project.x under your MPLAB application project and add the Header (app_temphum13.h, rnbd.h, rnbd_interface.h) and Source file (app_temphum13.c, rnbd.c, rnbd_interface.c).

![](docs/DRIVERS.png)

- In the project explorer, Right click on folder Header Files and add a sub folder "app_tempHum13" and "rnbd" by selecting “Add Existing Items from Folders…”

![](docs/header_add.png)

- Click on “Add Folder…” button.

![](docs/header_add2.png)

- Select the "app_tempHum13" and "rnbd" folder and select “Files of Types” as Header Files then click on “Add” button to add the selected folder.

![](docs/header_add4.png)
 
- The header files gets added to your project.

![](docs/header_add5.png)

- In the project explorer, Right click on folder Source Files and add a sub folder "app_tempHum13" and "rnbd" by selecting “Add Existing Items from Folders…”.

![](docs/source_add.png)

- Click on “Add Folder…” button

![](docs/source_add2.png)

- Select the "app_tempHum13" and "rnbd" folder and select “Files of Types” as Source Files then click on “Add” button to add the selected folder.

![](docs/source_add4.png)

- The source files gets added to your project.

![](docs/source_add5.png)

- Copy the file [main.c](https://github.com/MicrochipTech/RNBD451_BLE_TEMPERATURE_SENSOR/blob/main/firmware/PIC24_RNBD451_TH.X/main.c) and replace it.
		
	- In this file the RNBD_TempHum_example() function initializes the RNBD451 Module and sends the temperature value to the MBD App.

**Step 13** - Clean and build the project. To run the project, select "Make and program device" button.
	
**Step 14** - The Application Serial logs can be viewed in [TERA TERM](https://download.cnet.com/Tera-Term/3000-2094_4-75766675.html) COM PORT.

- Baud Rate: 9600 

![](docs/TERATERM.png)
	
## 6. Board Programming<a name="step6">

## Programming hex file:

### Program the precompiled hex file using MPLAB X IPE

- The Precompiled hex file is given in the hex folder.

Follow the steps provided in the link to [program the precompiled hex file](https://microchipdeveloper.com/ipe:programming-device) using MPLABX IPE to program the pre-compiled hex image. 


### Build and program the application using MPLAB X IDE

The application folder can be found by navigating to the following path: 

- "firmware/PIC24_RNBD451_TH.X"

Follow the steps provided in the link to [Build and program the application](https://github.com/Microchip-MPLAB-Harmony/wireless_apps_pic32cxbz2_wbz45/tree/master/apps/ble/advanced_applications/ble_sensor#build-and-program-the-application-guid-3d55fb8a-5995-439d-bcd6-deae7e8e78ad-section).

## 7. Run the demo<a name="step7">

- After programming the board, the expected application behavior is shown in the below [video](https://github.com/MicrochipTech/RNBD451_BLE_TEMPERATURE_SENSOR/blob/main/docs/demo.gif).

![Alt Text](docs/demo.gif)	
