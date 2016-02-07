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
LIBS:special
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
LIBS:DrChibi-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 6
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
SENSY
$Comp
L R R29
U 1 1 55E2B8A9
P 4500 3100
F 0 "R29" V 4580 3100 50  0000 C CNN
F 1 "R" V 4500 3100 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4430 3100 30  0001 C CNN
F 3 "" H 4500 3100 30  0000 C CNN
	1    4500 3100
	0    1    1    0   
$EndComp
$Comp
L R R30
U 1 1 55E2B8E8
P 4500 3350
F 0 "R30" V 4580 3350 50  0000 C CNN
F 1 "R" V 4500 3350 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 4430 3350 30  0001 C CNN
F 3 "" H 4500 3350 30  0000 C CNN
	1    4500 3350
	0    1    1    0   
$EndComp
$Comp
L R R31
U 1 1 55E2B905
P 4500 3600
F 0 "R31" V 4580 3600 50  0000 C CNN
F 1 "R" V 4500 3600 50  0000 C CNN
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
$Comp
L PAD_SMD P6
U 1 1 56A8F597
P 5400 3050
F 0 "P6" H 5527 3156 60  0000 L CNN
F 1 "PAD_SMD" H 5527 3050 60  0000 L CNN
F 2 "Pads:PAD_SMD_1.2x2.5" H 5527 2944 60  0000 L CNN
F 3 "" H 5400 2900 60  0000 C CNN
	1    5400 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3050 5050 3050
Wire Wire Line
	5050 3050 5050 3350
Connection ~ 5050 3350
Text Notes 5100 2350 0    60   ~ 0
Spannungsteiler nicht vergessen
$EndSCHEMATC
