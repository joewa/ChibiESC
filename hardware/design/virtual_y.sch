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
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
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
	5050 3800 5050 4350
$Comp
L R RYSGND1
U 1 1 57935AF7
P 5400 4100
F 0 "RYSGND1" V 5193 4100 50  0000 C CNN
F 1 "0R/DNP" V 5284 4100 50  0000 C CNN
F 2 "Resistors_SMD:R_0402" V 5330 4100 50  0001 C CNN
F 3 "" H 5400 4100 50  0000 C CNN
	1    5400 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	5250 4100 5050 4100
Connection ~ 5050 4100
$Comp
L GND #PWR037
U 1 1 57935C8D
P 5850 4150
F 0 "#PWR037" H 5850 3900 50  0001 C CNN
F 1 "GND" H 5855 3977 50  0000 C CNN
F 2 "" H 5850 4150 50  0000 C CNN
F 3 "" H 5850 4150 50  0000 C CNN
	1    5850 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 4100 5850 4100
Wire Wire Line
	5850 4100 5850 4150
Text Notes 6050 4150 0    60   ~ 0
In case RYX are populated with small caps\nfor EMC reasons, put a bridge to RYSGND.
$EndSCHEMATC
