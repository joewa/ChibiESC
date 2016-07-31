EESchema Schematic File Version 2
LIBS:BLDC_4-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:crf_1
LIBS:pkl_sensor
LIBS:pkl_drmos
LIBS:pkl_misc
LIBS:pkl_regulator
LIBS:DrChibi-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 11
Title ""
Date ""
Rev "0.1"
Comp "Jörg Wangemann"
Comment1 ""
Comment2 ""
Comment3 "CC-BY-SA 4.0"
Comment4 ""
$EndDescr
Text HLabel 4000 3100 0    60   Input ~ 0
SENS1
Text HLabel 4000 3350 0    60   Input ~ 0
SENS2
Text HLabel 4000 3600 0    60   Input ~ 0
SENS3
Text HLabel 5200 3350 2    60   Output ~ 0
SENSY1
$Comp
L R RY1
U 1 1 55E2B8A9
P 4500 3100
AR Path="/55DFCB16/55E2B8A9" Ref="RY1"  Part="1" 
AR Path="/56BBABF4/55E2B8A9" Ref="RY4"  Part="1" 
F 0 "RY1" V 4292 3100 50  0000 C CNN
F 1 "R/DNP" V 4384 3100 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4430 3100 30  0001 C CNN
F 3 "" H 4500 3100 30  0000 C CNN
	1    4500 3100
	0    1    1    0   
$EndComp
$Comp
L R RY2
U 1 1 55E2B8E8
P 4500 3350
AR Path="/55DFCB16/55E2B8E8" Ref="RY2"  Part="1" 
AR Path="/56BBABF4/55E2B8E8" Ref="RY5"  Part="1" 
F 0 "RY2" V 4580 3350 50  0000 C CNN
F 1 "R/DNP" V 4500 3350 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4430 3350 30  0001 C CNN
F 3 "" H 4500 3350 30  0000 C CNN
	1    4500 3350
	0    1    1    0   
$EndComp
$Comp
L R RY3
U 1 1 55E2B905
P 4500 3600
AR Path="/55DFCB16/55E2B905" Ref="RY3"  Part="1" 
AR Path="/56BBABF4/55E2B905" Ref="RY6"  Part="1" 
F 0 "RY3" V 4580 3600 50  0000 C CNN
F 1 "R/DNP" V 4500 3600 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4430 3600 30  0001 C CNN
F 3 "" H 4500 3600 30  0000 C CNN
	1    4500 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	4000 3100 4350 3100
Wire Wire Line
	4000 3350 4350 3350
Wire Wire Line
	4000 3600 4350 3600
Wire Wire Line
	4650 3100 4800 3100
Wire Wire Line
	4800 3100 4800 3600
Wire Wire Line
	4650 3350 5200 3350
Connection ~ 4800 3350
Wire Wire Line
	4800 3600 4650 3600
Connection ~ 5050 3350
$Comp
L R RY4
U 1 1 56CBA2E3
P 4500 4050
F 0 "RY4" V 4292 4050 50  0000 C CNN
F 1 "R/DNP" V 4384 4050 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4430 4050 50  0001 C CNN
F 3 "" H 4500 4050 50  0000 C CNN
	1    4500 4050
	0    1    1    0   
$EndComp
$Comp
L R RY5
U 1 1 56CBA350
P 4500 4350
F 0 "RY5" V 4292 4350 50  0000 C CNN
F 1 "R/DNP" V 4384 4350 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4430 4350 50  0001 C CNN
F 3 "" H 4500 4350 50  0000 C CNN
	1    4500 4350
	0    1    1    0   
$EndComp
$Comp
L R RY6
U 1 1 56CBA38A
P 4500 4650
F 0 "RY6" V 4292 4650 50  0000 C CNN
F 1 "R/DNP" V 4384 4650 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4430 4650 50  0001 C CNN
F 3 "" H 4500 4650 50  0000 C CNN
	1    4500 4650
	0    1    1    0   
$EndComp
Text HLabel 4000 4050 0    60   Input ~ 0
SENS4
Text HLabel 4000 4350 0    60   Input ~ 0
SENS5
Text HLabel 4000 4650 0    60   Input ~ 0
SENS6
$Comp
L R RYS1
U 1 1 56CBA751
P 5050 3650
F 0 "RYS1" H 5120 3696 50  0000 L CNN
F 1 "0R/DNP" H 5120 3604 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4980 3650 50  0001 C CNN
F 3 "" H 5050 3650 50  0000 C CNN
	1    5050 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 4050 4350 4050
Wire Wire Line
	4000 4350 4350 4350
Wire Wire Line
	4000 4650 4350 4650
Wire Wire Line
	4650 4050 4800 4050
Wire Wire Line
	4800 4050 4800 4650
Wire Wire Line
	4650 4350 5200 4350
Wire Wire Line
	4800 4650 4650 4650
Connection ~ 4800 4350
Text HLabel 5200 4350 2    60   Output ~ 0
SENSY2
Connection ~ 5050 4350
Text Notes 5500 3700 0    60   ~ 0
Do not populate for\ntwo-motor mode.
Wire Wire Line
	5050 3500 5050 3350
Wire Wire Line
	5050 3800 5050 5650
$Comp
L R RYSGND1
U 1 1 57935AF7
P 4650 5850
F 0 "RYSGND1" V 4443 5850 50  0000 C CNN
F 1 "0R/DNP" V 4534 5850 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 4580 5850 50  0001 C CNN
F 3 "" H 4650 5850 50  0000 C CNN
	1    4650 5850
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR037
U 1 1 57935C8D
P 4650 6250
F 0 "#PWR037" H 4650 6000 50  0001 C CNN
F 1 "GND" H 4655 6077 50  0000 C CNN
F 2 "" H 4650 6250 50  0000 C CNN
F 3 "" H 4650 6250 50  0000 C CNN
	1    4650 6250
	1    0    0    -1  
$EndComp
Text Notes 6950 4200 0    60   ~ 0
In case RYX are populated with small caps\nfor EMC reasons, put a bridge to RYSGND.
$Comp
L PAD_SMD PHFAC1
U 1 1 579D159A
P 6250 5650
F 0 "PHFAC1" H 6378 5703 60  0000 L CNN
F 1 "PAD_SMD" H 6378 5597 60  0000 L CNN
F 2 "Pads:PAD_SMD_1.2x2.5" H 6250 5400 60  0001 C CNN
F 3 "" H 6250 5500 60  0000 C CNN
	1    6250 5650
	1    0    0    -1  
$EndComp
$Comp
L R RHFAC1
U 1 1 579D1630
P 5350 5650
F 0 "RHFAC1" V 5143 5650 50  0000 C CNN
F 1 "R" V 5234 5650 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 5280 5650 50  0001 C CNN
F 3 "" H 5350 5650 50  0000 C CNN
	1    5350 5650
	0    1    1    0   
$EndComp
$Comp
L +3.3V #PWR038
U 1 1 579D18A3
P 4650 5100
F 0 "#PWR038" H 4650 4950 50  0001 C CNN
F 1 "+3.3V" H 4665 5273 50  0000 C CNN
F 2 "" H 4650 5100 50  0000 C CNN
F 3 "" H 4650 5100 50  0000 C CNN
	1    4650 5100
	1    0    0    -1  
$EndComp
$Comp
L C CHFAC1
U 1 1 579D1951
P 5800 5650
F 0 "CHFAC1" V 5548 5650 50  0000 C CNN
F 1 "C" V 5639 5650 50  0000 C CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 5838 5500 50  0001 C CNN
F 3 "" H 5800 5650 50  0000 C CNN
	1    5800 5650
	0    1    1    0   
$EndComp
$Comp
L R RYOFFS1
U 1 1 579D1B7A
P 4650 5350
F 0 "RYOFFS1" H 4720 5396 50  0000 L CNN
F 1 "R" H 4720 5305 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4580 5350 50  0001 C CNN
F 3 "" H 4650 5350 50  0000 C CNN
	1    4650 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 6000 4650 6250
Connection ~ 4650 6200
Wire Wire Line
	4650 5500 4650 5700
Wire Wire Line
	4500 5650 5200 5650
Connection ~ 4650 5650
Connection ~ 5050 5650
Wire Wire Line
	5500 5650 5650 5650
Wire Wire Line
	5950 5650 6050 5650
Text Notes 6900 5100 0    60   ~ 0
PHFAC - High Frequency AC sensing on SENSY2\n- voltage divider RYSGND/(RYOFFS+RYSGND) sets the offset for SENSY2\n- the gain is set by RHFAC/(RHFAC+RYOFFS||RYSGND)\n- DZLIM limits the ADC input to 3.3V
$Comp
L D_Schottky_x2_Serial_AKC Dclamp1
U 1 1 579D5C9B
P 4300 5650
F 0 "Dclamp1" V 4346 5730 50  0000 L CNN
F 1 "D_Schottky_x2_Serial_AKC__BAT754S" V 4255 5730 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 4300 5650 50  0001 C CNN
F 3 "" H 4300 5650 50  0000 C CNN
	1    4300 5650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4650 5200 4650 5100
Wire Wire Line
	4300 5950 4300 6200
Wire Wire Line
	4300 6200 4650 6200
Wire Wire Line
	4300 5350 4300 5150
Wire Wire Line
	4300 5150 4650 5150
Connection ~ 4650 5150
$EndSCHEMATC
