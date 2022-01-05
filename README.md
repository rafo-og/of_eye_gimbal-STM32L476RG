# Eye OF Gimbal - STM32L476RG - Firmware
 
 This repository contains the code which implements the available functionalities in Eye OF Gimbal platform. All the code is in C language using low-level approach to increase the system performance. Although the project is based on the ARM Cortex-M4 STM32L476RG microcontroller, it's easily translated to other microcontrollers with proper hardware-related code modifications.

The platform uses two *"Optical Flow Eyes (OF Eyes)"*, each one composed by an *ADNS-2610* chip. These chips are usually used in PC mouse devices but also they allow to extract the image which they compute internally.

For those who are interested in system details, the following two references are recommended:

- [Master thesis](http://www2.imse-cnm.csic.es/~juanle/Documents/MasterBacherlorTheses/RafaelDeLaRosaVidal_2020.pdf). *Three-dimensional tracking system based on an optical flow sensor array implemented with low resolution image sensors*. Author: **Rafael de la Rosa Vidal**. *University of Seville*. December 2020.

- **R. de la Rosa-Vidal**, J. A. Leñero-Bardallo, J. -M. Guerrero-Rodríguez and Á. Rodríguez-Vázquez, *"A Mobile Platform for Movement Tracking Based on a Fast-Execution-Time Optical-Flow Algorithm"* in IEEE Transactions on Circuits and Systems I: Regular Papers, doi: [10.1109/TCSI.2021.3136656](https://doi.org/10.1109/tcsi.2021.3136656).