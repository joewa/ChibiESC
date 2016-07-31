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
Sheet 6 11
Title "DrMOS power stage"
Date "2016-01-22"
Rev "0.1"
Comp "Jörg Wangemann"
Comment1 "DrMOS power stage"
Comment2 ""
Comment3 "CC-BY-SA 4.0"
Comment4 ""
$EndDescr
Text HLabel 4100 4100 0    60   Input ~ 0
PWM
Text HLabel 4100 4000 0    60   Input ~ 0
DSBL
$Comp
L C Cboot1
U 1 1 55DF8D4F
P 6900 3700
AR Path="/55DB7E47/55DF8D4F" Ref="Cboot1"  Part="1" 
AR Path="/55E59DEF/55DF8D4F" Ref="C?"  Part="1" 
AR Path="/55E6829E/55DF8D4F" Ref="C23"  Part="1" 
AR Path="/55E631D7/55DF8D4F" Ref="C21"  Part="1" 
AR Path="/56B7FDE9/55DF8D4F" Ref="Cboot1"  Part="1" 
AR Path="/56B809CA/55DF8D4F" Ref="Cboot2"  Part="1" 
AR Path="/56B8347B/55DF8D4F" Ref="Cboot3"  Part="1" 
AR Path="/56BC308A/55DF8D4F" Ref="Cboot4"  Part="1" 
AR Path="/56BA2E2B/55DF8D4F" Ref="Cboot5"  Part="1" 
AR Path="/56BA5F82/55DF8D4F" Ref="Cboot6"  Part="1" 
F 0 "Cboot6" V 6647 3700 50  0000 C CNN
F 1 "0.47uF" V 6739 3700 50  0000 C CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 6938 3550 30  0001 C CNN
F 3 "" H 6900 3700 60  0000 C CNN
	1    6900 3700
	0    1    1    0   
$EndComp
$Comp
L C CDrGate1
U 1 1 55DF8D84
P 4950 2900
AR Path="/55DB7E47/55DF8D84" Ref="CDrGate1"  Part="1" 
AR Path="/55E59DEF/55DF8D84" Ref="C?"  Part="1" 
AR Path="/55E6829E/55DF8D84" Ref="C22"  Part="1" 
AR Path="/55E631D7/55DF8D84" Ref="C20"  Part="1" 
AR Path="/56B7FDE9/55DF8D84" Ref="CDrGate1"  Part="1" 
AR Path="/56B809CA/55DF8D84" Ref="CDrGate2"  Part="1" 
AR Path="/56B8347B/55DF8D84" Ref="CDrGate3"  Part="1" 
AR Path="/56BC308A/55DF8D84" Ref="CDrGate4"  Part="1" 
AR Path="/56BA2E2B/55DF8D84" Ref="CDrGate5"  Part="1" 
AR Path="/56BA5F82/55DF8D84" Ref="CDrGate6"  Part="1" 
F 0 "CDrGate6" H 5065 2946 50  0000 L CNN
F 1 "0.47uF" H 5065 2854 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 4988 2750 30  0001 C CNN
F 3 "" H 4950 2900 60  0000 C CNN
F 4 "X7R, >10V" H 4950 2900 60  0001 C CNN "Comment"
	1    4950 2900
	1    0    0    -1  
$EndComp
Text HLabel 7800 4500 2    60   Output ~ 0
SENSV
Text HLabel 8750 2650 2    60   Output ~ 0
SENSC
$Comp
L ACS711 Usens1
U 1 1 56984538
P 7850 3550
AR Path="/55DB7E47/56984538" Ref="Usens1"  Part="1" 
AR Path="/56B7FDE9/56984538" Ref="Usens1"  Part="1" 
AR Path="/56B809CA/56984538" Ref="Usens2"  Part="1" 
AR Path="/56B8347B/56984538" Ref="Usens3"  Part="1" 
AR Path="/56BC308A/56984538" Ref="Usens4"  Part="1" 
AR Path="/56BA2E2B/56984538" Ref="Usens5"  Part="1" 
AR Path="/56BA5F82/56984538" Ref="Usens6"  Part="1" 
F 0 "Usens6" V 7797 2922 60  0000 R CNN
F 1 "ACS711" V 7903 2922 60  0000 R CNN
F 2 "Allegro:QFN-12-1EX_3x3mm_Pitch0.5mm" V 7956 2922 60  0001 R CNN
F 3 "" H 7700 3750 60  0000 C CNN
F 4 "Allegro" V 7850 3550 60  0001 C CNN "Manufacturer"
F 5 "ACS711KEXLT-31AB-T" V 7850 3550 60  0001 C CNN "Part Number"
	1    7850 3550
	0    -1   1    0   
$EndComp
$Comp
L DrMOS_SiC632A UDrmos1
U 1 1 56A19C85
P 5850 4000
AR Path="/55DB7E47/56A19C85" Ref="UDrmos1"  Part="1" 
AR Path="/56B7FDE9/56A19C85" Ref="UDrmos1"  Part="1" 
AR Path="/56B809CA/56A19C85" Ref="UDrmos2"  Part="1" 
AR Path="/56B8347B/56A19C85" Ref="UDrmos3"  Part="1" 
AR Path="/56BC308A/56A19C85" Ref="UDrmos4"  Part="1" 
AR Path="/56BA2E2B/56A19C85" Ref="UDrmos5"  Part="1" 
AR Path="/56BA5F82/56A19C85" Ref="UDrmos6"  Part="1" 
F 0 "UDrmos6" H 5650 5071 50  0000 C CNN
F 1 "DrMOS_SiC632A" H 5650 4979 50  0000 C CNN
F 2 "DrMOS:MLP55-31L" H 5650 4887 50  0000 C CNN
F 3 "" H 5850 3800 50  0000 C CNN
F 4 "Vishay" H 5850 4000 60  0001 C CNN "Manufacturer"
F 5 "SiC632CD-T1-GE3" H 5850 4000 60  0001 C CNN "Part Number"
	1    5850 4000
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR014
U 1 1 56A2AE4F
P 5750 5050
AR Path="/55DB7E47/56A2AE4F" Ref="#PWR014"  Part="1" 
AR Path="/56B7FDE9/56A2AE4F" Ref="#PWR54"  Part="1" 
AR Path="/56B809CA/56A2AE4F" Ref="#PWR039"  Part="1" 
AR Path="/56B8347B/56A2AE4F" Ref="#PWR052"  Part="1" 
AR Path="/56BC308A/56A2AE4F" Ref="#PWR065"  Part="1" 
AR Path="/56BA2E2B/56A2AE4F" Ref="#PWR078"  Part="1" 
AR Path="/56BA5F82/56A2AE4F" Ref="#PWR091"  Part="1" 
F 0 "#PWR091" H 5750 4850 50  0001 C CNN
F 1 "GNDPWR" H 5750 4900 50  0000 C CNN
F 2 "" H 5750 5000 50  0000 C CNN
F 3 "" H 5750 5000 50  0000 C CNN
	1    5750 5050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 56A2B769
P 5200 5000
AR Path="/55DB7E47/56A2B769" Ref="#PWR015"  Part="1" 
AR Path="/56B7FDE9/56A2B769" Ref="#PWR51"  Part="1" 
AR Path="/56B809CA/56A2B769" Ref="#PWR040"  Part="1" 
AR Path="/56B8347B/56A2B769" Ref="#PWR053"  Part="1" 
AR Path="/56BC308A/56A2B769" Ref="#PWR066"  Part="1" 
AR Path="/56BA2E2B/56A2B769" Ref="#PWR079"  Part="1" 
AR Path="/56BA5F82/56A2B769" Ref="#PWR092"  Part="1" 
F 0 "#PWR092" H 5200 4750 50  0001 C CNN
F 1 "GND" H 5208 4826 50  0000 C CNN
F 2 "" H 5200 5000 50  0000 C CNN
F 3 "" H 5200 5000 50  0000 C CNN
	1    5200 5000
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR016
U 1 1 56A2BBEE
P 4950 3200
AR Path="/55DB7E47/56A2BBEE" Ref="#PWR016"  Part="1" 
AR Path="/56B7FDE9/56A2BBEE" Ref="#PWR50"  Part="1" 
AR Path="/56B809CA/56A2BBEE" Ref="#PWR041"  Part="1" 
AR Path="/56B8347B/56A2BBEE" Ref="#PWR054"  Part="1" 
AR Path="/56BC308A/56A2BBEE" Ref="#PWR067"  Part="1" 
AR Path="/56BA2E2B/56A2BBEE" Ref="#PWR080"  Part="1" 
AR Path="/56BA5F82/56A2BBEE" Ref="#PWR093"  Part="1" 
F 0 "#PWR093" H 4950 3000 50  0001 C CNN
F 1 "GNDPWR" H 4957 3275 50  0000 C CNN
F 2 "" H 4950 3150 50  0000 C CNN
F 3 "" H 4950 3150 50  0000 C CNN
	1    4950 3200
	1    0    0    -1  
$EndComp
$Comp
L C CDrLogic1
U 1 1 56A2CDC4
P 4300 3400
AR Path="/55DB7E47/56A2CDC4" Ref="CDrLogic1"  Part="1" 
AR Path="/56B7FDE9/56A2CDC4" Ref="CDrLogic1"  Part="1" 
AR Path="/56B809CA/56A2CDC4" Ref="CDrLogic2"  Part="1" 
AR Path="/56B8347B/56A2CDC4" Ref="CDrLogic3"  Part="1" 
AR Path="/56BC308A/56A2CDC4" Ref="CDrLogic4"  Part="1" 
AR Path="/56BA2E2B/56A2CDC4" Ref="CDrLogic5"  Part="1" 
AR Path="/56BA5F82/56A2CDC4" Ref="CDrLogic6"  Part="1" 
F 0 "CDrLogic6" H 4415 3446 50  0000 L CNN
F 1 "2.2uF" H 4415 3354 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 4338 3250 30  0001 C CNN
F 3 "" H 4300 3400 60  0000 C CNN
F 4 "Kemet" H 4300 3400 60  0001 C CNN "Manufacturer"
F 5 "C0603C225K8RACTU" H 4300 3400 60  0001 C CNN "Part Number"
F 6 "X7R, >10V" H 4300 3400 60  0001 C CNN "Comment"
	1    4300 3400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR017
U 1 1 56A2CDEC
P 4300 3550
AR Path="/55DB7E47/56A2CDEC" Ref="#PWR017"  Part="1" 
AR Path="/56B7FDE9/56A2CDEC" Ref="#PWR49"  Part="1" 
AR Path="/56B809CA/56A2CDEC" Ref="#PWR042"  Part="1" 
AR Path="/56B8347B/56A2CDEC" Ref="#PWR055"  Part="1" 
AR Path="/56BC308A/56A2CDEC" Ref="#PWR068"  Part="1" 
AR Path="/56BA2E2B/56A2CDEC" Ref="#PWR081"  Part="1" 
AR Path="/56BA5F82/56A2CDEC" Ref="#PWR094"  Part="1" 
F 0 "#PWR094" H 4300 3300 50  0001 C CNN
F 1 "GND" H 4308 3376 50  0000 C CNN
F 2 "" H 4300 3550 50  0000 C CNN
F 3 "" H 4300 3550 50  0000 C CNN
	1    4300 3550
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR018
U 1 1 56A2CF9B
P 4300 2650
AR Path="/55DB7E47/56A2CF9B" Ref="#PWR018"  Part="1" 
AR Path="/56B7FDE9/56A2CF9B" Ref="#PWR48"  Part="1" 
AR Path="/56B809CA/56A2CF9B" Ref="#PWR043"  Part="1" 
AR Path="/56B8347B/56A2CF9B" Ref="#PWR056"  Part="1" 
AR Path="/56BC308A/56A2CF9B" Ref="#PWR069"  Part="1" 
AR Path="/56BA2E2B/56A2CF9B" Ref="#PWR082"  Part="1" 
AR Path="/56BA5F82/56A2CF9B" Ref="#PWR095"  Part="1" 
F 0 "#PWR095" H 4300 2500 50  0001 C CNN
F 1 "+5V" H 4318 2824 50  0000 C CNN
F 2 "" H 4300 2650 50  0000 C CNN
F 3 "" H 4300 2650 50  0000 C CNN
	1    4300 2650
	1    0    0    -1  
$EndComp
$Comp
L R RDrLogic1
U 1 1 56A2D0BC
P 4300 2900
AR Path="/55DB7E47/56A2D0BC" Ref="RDrLogic1"  Part="1" 
AR Path="/56B7FDE9/56A2D0BC" Ref="RDrLogic1"  Part="1" 
AR Path="/56B809CA/56A2D0BC" Ref="RDrLogic2"  Part="1" 
AR Path="/56B8347B/56A2D0BC" Ref="RDrLogic3"  Part="1" 
AR Path="/56BC308A/56A2D0BC" Ref="RDrLogic4"  Part="1" 
AR Path="/56BA2E2B/56A2D0BC" Ref="RDrLogic5"  Part="1" 
AR Path="/56BA5F82/56A2D0BC" Ref="RDrLogic6"  Part="1" 
F 0 "RDrLogic6" H 4370 2946 50  0000 L CNN
F 1 "R" H 4370 2854 50  0000 L CNN
F 2 "Resistors_SMD:R_0603" V 4230 2900 50  0001 C CNN
F 3 "" H 4300 2900 50  0000 C CNN
	1    4300 2900
	1    0    0    -1  
$EndComp
Text HLabel 4100 4200 0    60   BiDi ~ 0
THWn
$Comp
L GND #PWR019
U 1 1 56A2EFF6
P 8550 3050
AR Path="/55DB7E47/56A2EFF6" Ref="#PWR019"  Part="1" 
AR Path="/56B7FDE9/56A2EFF6" Ref="#PWR58"  Part="1" 
AR Path="/56B809CA/56A2EFF6" Ref="#PWR044"  Part="1" 
AR Path="/56B8347B/56A2EFF6" Ref="#PWR057"  Part="1" 
AR Path="/56BC308A/56A2EFF6" Ref="#PWR070"  Part="1" 
AR Path="/56BA2E2B/56A2EFF6" Ref="#PWR083"  Part="1" 
AR Path="/56BA5F82/56A2EFF6" Ref="#PWR096"  Part="1" 
F 0 "#PWR096" H 8550 2800 50  0001 C CNN
F 1 "GND" H 8558 2876 50  0000 C CNN
F 2 "" H 8550 3050 50  0000 C CNN
F 3 "" H 8550 3050 50  0000 C CNN
	1    8550 3050
	1    0    0    -1  
$EndComp
Text HLabel 7850 2500 2    60   BiDi ~ 0
FAULTC
$Comp
L R Rhsens1
U 1 1 56A2FD69
P 7450 4300
AR Path="/55DB7E47/56A2FD69" Ref="Rhsens1"  Part="1" 
AR Path="/56B7FDE9/56A2FD69" Ref="Rhsens1"  Part="1" 
AR Path="/56B809CA/56A2FD69" Ref="Rhsens2"  Part="1" 
AR Path="/56B8347B/56A2FD69" Ref="Rhsens3"  Part="1" 
AR Path="/56BC308A/56A2FD69" Ref="Rhsens4"  Part="1" 
AR Path="/56BA2E2B/56A2FD69" Ref="Rhsens5"  Part="1" 
AR Path="/56BA5F82/56A2FD69" Ref="Rhsens6"  Part="1" 
F 0 "Rhsens6" H 7520 4346 50  0000 L CNN
F 1 "10k" H 7520 4254 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" V 7380 4300 50  0001 C CNN
F 3 "" H 7450 4300 50  0000 C CNN
	1    7450 4300
	1    0    0    -1  
$EndComp
$Comp
L R Rlsens1
U 1 1 56A2FEAC
P 7450 4700
AR Path="/55DB7E47/56A2FEAC" Ref="Rlsens1"  Part="1" 
AR Path="/56B7FDE9/56A2FEAC" Ref="Rlsens1"  Part="1" 
AR Path="/56B809CA/56A2FEAC" Ref="Rlsens2"  Part="1" 
AR Path="/56B8347B/56A2FEAC" Ref="Rlsens3"  Part="1" 
AR Path="/56BC308A/56A2FEAC" Ref="Rlsens4"  Part="1" 
AR Path="/56BA2E2B/56A2FEAC" Ref="Rlsens5"  Part="1" 
AR Path="/56BA5F82/56A2FEAC" Ref="Rlsens6"  Part="1" 
F 0 "Rlsens6" H 7520 4746 50  0000 L CNN
F 1 "2k2" H 7520 4654 50  0000 L CNN
F 2 "Resistors_SMD:R_0402" V 7380 4700 50  0001 C CNN
F 3 "" H 7450 4700 50  0000 C CNN
	1    7450 4700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 56A30067
P 7450 4950
AR Path="/55DB7E47/56A30067" Ref="#PWR020"  Part="1" 
AR Path="/56B7FDE9/56A30067" Ref="#PWR57"  Part="1" 
AR Path="/56B809CA/56A30067" Ref="#PWR045"  Part="1" 
AR Path="/56B8347B/56A30067" Ref="#PWR058"  Part="1" 
AR Path="/56BC308A/56A30067" Ref="#PWR071"  Part="1" 
AR Path="/56BA2E2B/56A30067" Ref="#PWR084"  Part="1" 
AR Path="/56BA5F82/56A30067" Ref="#PWR097"  Part="1" 
F 0 "#PWR097" H 7450 4700 50  0001 C CNN
F 1 "GND" H 7458 4776 50  0000 C CNN
F 2 "" H 7450 4950 50  0000 C CNN
F 3 "" H 7450 4950 50  0000 C CNN
	1    7450 4950
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR021
U 1 1 56A31D68
P 6050 3000
AR Path="/55DB7E47/56A31D68" Ref="#PWR021"  Part="1" 
AR Path="/56B7FDE9/56A31D68" Ref="#PWR55"  Part="1" 
AR Path="/56B809CA/56A31D68" Ref="#PWR046"  Part="1" 
AR Path="/56B8347B/56A31D68" Ref="#PWR059"  Part="1" 
AR Path="/56BC308A/56A31D68" Ref="#PWR072"  Part="1" 
AR Path="/56BA2E2B/56A31D68" Ref="#PWR085"  Part="1" 
AR Path="/56BA5F82/56A31D68" Ref="#PWR098"  Part="1" 
F 0 "#PWR098" H 6050 2850 50  0001 C CNN
F 1 "+24V" H 6068 3174 50  0000 C CNN
F 2 "" H 6050 3000 50  0000 C CNN
F 3 "" H 6050 3000 50  0000 C CNN
	1    6050 3000
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR022
U 1 1 56A32138
P 7350 2650
AR Path="/55DB7E47/56A32138" Ref="#PWR022"  Part="1" 
AR Path="/56B7FDE9/56A32138" Ref="#PWR56"  Part="1" 
AR Path="/56B809CA/56A32138" Ref="#PWR047"  Part="1" 
AR Path="/56B8347B/56A32138" Ref="#PWR060"  Part="1" 
AR Path="/56BC308A/56A32138" Ref="#PWR073"  Part="1" 
AR Path="/56BA2E2B/56A32138" Ref="#PWR086"  Part="1" 
AR Path="/56BA5F82/56A32138" Ref="#PWR099"  Part="1" 
F 0 "#PWR099" H 7350 2500 50  0001 C CNN
F 1 "+3.3V" H 7368 2824 50  0000 C CNN
F 2 "" H 7350 2650 50  0000 C CNN
F 3 "" H 7350 2650 50  0000 C CNN
	1    7350 2650
	1    0    0    -1  
$EndComp
Text Notes 8700 2900 0    60   ~ 0
VIOUT muss mit min 15kOhm und max 1nF nach GND
$Comp
L R Rcfilt1
U 1 1 56A3225A
P 8350 2800
AR Path="/55DB7E47/56A3225A" Ref="Rcfilt1"  Part="1" 
AR Path="/56B7FDE9/56A3225A" Ref="Rcfilt1"  Part="1" 
AR Path="/56B809CA/56A3225A" Ref="Rcfilt2"  Part="1" 
AR Path="/56B8347B/56A3225A" Ref="Rcfilt3"  Part="1" 
AR Path="/56BC308A/56A3225A" Ref="Rcfilt4"  Part="1" 
AR Path="/56BA2E2B/56A3225A" Ref="Rcfilt5"  Part="1" 
AR Path="/56BA5F82/56A3225A" Ref="Rcfilt6"  Part="1" 
F 0 "Rcfilt6" H 8420 2846 50  0000 L CNN
F 1 "20k" H 8420 2754 50  0000 L CNN
F 2 "Resistors_SMD:R_0402" V 8280 2800 50  0001 C CNN
F 3 "" H 8350 2800 50  0000 C CNN
	1    8350 2800
	1    0    0    -1  
$EndComp
$Comp
L C Ccfilt1
U 1 1 56A3233B
P 8050 2800
AR Path="/55DB7E47/56A3233B" Ref="Ccfilt1"  Part="1" 
AR Path="/56B7FDE9/56A3233B" Ref="Ccfilt1"  Part="1" 
AR Path="/56B809CA/56A3233B" Ref="Ccfilt2"  Part="1" 
AR Path="/56B8347B/56A3233B" Ref="Ccfilt3"  Part="1" 
AR Path="/56BC308A/56A3233B" Ref="Ccfilt4"  Part="1" 
AR Path="/56BA2E2B/56A3233B" Ref="Ccfilt5"  Part="1" 
AR Path="/56BA5F82/56A3233B" Ref="Ccfilt6"  Part="1" 
F 0 "Ccfilt6" H 8165 2846 50  0000 L CNN
F 1 "0.5n" H 8165 2754 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 8088 2650 50  0001 C CNN
F 3 "" H 8050 2800 50  0000 C CNN
	1    8050 2800
	1    0    0    -1  
$EndComp
Text HLabel 4100 3900 0    60   Input ~ 0
ZCD_EN
$Comp
L +24V #PWR023
U 1 1 56A69AD2
P 5750 950
AR Path="/55DB7E47/56A69AD2" Ref="#PWR023"  Part="1" 
AR Path="/56B7FDE9/56A69AD2" Ref="#PWR52"  Part="1" 
AR Path="/56B809CA/56A69AD2" Ref="#PWR048"  Part="1" 
AR Path="/56B8347B/56A69AD2" Ref="#PWR061"  Part="1" 
AR Path="/56BC308A/56A69AD2" Ref="#PWR074"  Part="1" 
AR Path="/56BA2E2B/56A69AD2" Ref="#PWR087"  Part="1" 
AR Path="/56BA5F82/56A69AD2" Ref="#PWR0100"  Part="1" 
F 0 "#PWR0100" H 5750 800 50  0001 C CNN
F 1 "+24V" H 5768 1124 50  0000 C CNN
F 2 "" H 5750 950 50  0000 C CNN
F 3 "" H 5750 950 50  0000 C CNN
	1    5750 950 
	1    0    0    -1  
$EndComp
$Comp
L C CDrHV1
U 1 1 56A69B0E
P 5750 1200
AR Path="/55DB7E47/56A69B0E" Ref="CDrHV1"  Part="1" 
AR Path="/56B7FDE9/56A69B0E" Ref="CDrHV1"  Part="1" 
AR Path="/56B809CA/56A69B0E" Ref="CDrHV2"  Part="1" 
AR Path="/56B8347B/56A69B0E" Ref="CDrHV3"  Part="1" 
AR Path="/56BC308A/56A69B0E" Ref="CDrHV4"  Part="1" 
AR Path="/56BA2E2B/56A69B0E" Ref="CDrHV5"  Part="1" 
AR Path="/56BA5F82/56A69B0E" Ref="CDrHV6"  Part="1" 
F 0 "CDrHV6" H 5865 1246 50  0000 L CNN
F 1 "10u" H 5865 1154 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 5788 1050 50  0001 C CNN
F 3 "" H 5750 1200 50  0000 C CNN
	1    5750 1200
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR024
U 1 1 56A69BA7
P 5750 1500
AR Path="/55DB7E47/56A69BA7" Ref="#PWR024"  Part="1" 
AR Path="/56B7FDE9/56A69BA7" Ref="#PWR53"  Part="1" 
AR Path="/56B809CA/56A69BA7" Ref="#PWR049"  Part="1" 
AR Path="/56B8347B/56A69BA7" Ref="#PWR062"  Part="1" 
AR Path="/56BC308A/56A69BA7" Ref="#PWR075"  Part="1" 
AR Path="/56BA2E2B/56A69BA7" Ref="#PWR088"  Part="1" 
AR Path="/56BA5F82/56A69BA7" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 5750 1300 50  0001 C CNN
F 1 "GNDPWR" H 5757 1575 50  0000 C CNN
F 2 "" H 5750 1450 50  0000 C CNN
F 3 "" H 5750 1450 50  0000 C CNN
	1    5750 1500
	1    0    0    -1  
$EndComp
Text Notes 6250 3250 0    60   ~ 0
Rboot can be used to\nslow down high side\nFET. (1-5ohm)
Text Notes 8300 5250 0    60   ~ 0
SENSV = Rlsens / (Rlsens+Rhsens)\nMust be below 4V to protect the input pin of STM32F4.\nIs 3.8V for Rl=2k2 and Rh=10k\n\nNote:\nRlsens is placed close to the controller and\nRhsens at the pad. Having load at the wire would make\nit less susceptible to noise.\n\nPad PVSens is for alternate motor voltage sensing\nthan the actual phase
Text Label 5750 4950 0    60   ~ 0
PWRGND
Text Label 5000 4950 0    60   ~ 0
GND
$Comp
L C CDrHVs1
U 1 1 56AF6D20
P 5200 1200
AR Path="/55DB7E47/56AF6D20" Ref="CDrHVs1"  Part="1" 
AR Path="/56B7FDE9/56AF6D20" Ref="CDrHVs1"  Part="1" 
AR Path="/56B809CA/56AF6D20" Ref="CDrHVs2"  Part="1" 
AR Path="/56B8347B/56AF6D20" Ref="CDrHVs3"  Part="1" 
AR Path="/56BC308A/56AF6D20" Ref="CDrHVs4"  Part="1" 
AR Path="/56BA2E2B/56AF6D20" Ref="CDrHVs5"  Part="1" 
AR Path="/56BA5F82/56AF6D20" Ref="CDrHVs6"  Part="1" 
F 0 "CDrHVs6" H 5315 1246 50  0000 L CNN
F 1 "0.47u" H 5315 1154 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 5315 1108 50  0001 L CNN
F 3 "" H 5200 1200 50  0000 C CNN
	1    5200 1200
	1    0    0    -1  
$EndComp
$Comp
L PAD_SMD PMotor1
U 1 1 56B30AD6
P 9050 4000
AR Path="/55DB7E47/56B30AD6" Ref="PMotor1"  Part="1" 
AR Path="/56B7FDE9/56B30AD6" Ref="PMotor1"  Part="1" 
AR Path="/56B809CA/56B30AD6" Ref="PMotor2"  Part="1" 
AR Path="/56B8347B/56B30AD6" Ref="PMotor3"  Part="1" 
AR Path="/56BC308A/56B30AD6" Ref="PMotor4"  Part="1" 
AR Path="/56BA2E2B/56B30AD6" Ref="PMotor5"  Part="1" 
AR Path="/56BA5F82/56B30AD6" Ref="PMotor6"  Part="1" 
F 0 "PMotor6" H 9177 4106 60  0000 L CNN
F 1 "PAD_SMD" H 9177 4000 60  0000 L CNN
F 2 "CRF1:1PAD_4x5mm" H 9177 3894 60  0000 L CNN
F 3 "" H 9050 3850 60  0000 C CNN
	1    9050 4000
	1    0    0    -1  
$EndComp
NoConn ~ 5500 4800
NoConn ~ 5550 4800
$Comp
L C Csens1
U 1 1 56B897AB
P 6850 2050
AR Path="/55DB7E47/56B897AB" Ref="Csens1"  Part="1" 
AR Path="/56B809CA/56B897AB" Ref="Csens2"  Part="1" 
AR Path="/56B8347B/56B897AB" Ref="Csens3"  Part="1" 
AR Path="/56BC308A/56B897AB" Ref="Csens4"  Part="1" 
AR Path="/56BA2E2B/56B897AB" Ref="Csens5"  Part="1" 
AR Path="/56BA5F82/56B897AB" Ref="Csens6"  Part="1" 
F 0 "Csens6" H 6965 2142 50  0000 L CNN
F 1 "0.47u" H 6965 2050 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603" H 6965 1958 50  0000 L CNN
F 3 "" H 6850 2050 50  0000 C CNN
F 4 "X7R, >10V" H 6850 2050 60  0001 C CNN "Comment"
	1    6850 2050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 56B89931
P 6850 2200
AR Path="/55DB7E47/56B89931" Ref="#PWR025"  Part="1" 
AR Path="/56B809CA/56B89931" Ref="#PWR050"  Part="1" 
AR Path="/56B8347B/56B89931" Ref="#PWR063"  Part="1" 
AR Path="/56BC308A/56B89931" Ref="#PWR076"  Part="1" 
AR Path="/56BA2E2B/56B89931" Ref="#PWR089"  Part="1" 
AR Path="/56BA5F82/56B89931" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H 6850 1950 50  0001 C CNN
F 1 "GND" H 6858 2026 50  0000 C CNN
F 2 "" H 6850 2200 50  0000 C CNN
F 3 "" H 6850 2200 50  0000 C CNN
	1    6850 2200
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR026
U 1 1 56B89961
P 6850 1900
AR Path="/55DB7E47/56B89961" Ref="#PWR026"  Part="1" 
AR Path="/56B809CA/56B89961" Ref="#PWR051"  Part="1" 
AR Path="/56B8347B/56B89961" Ref="#PWR064"  Part="1" 
AR Path="/56BC308A/56B89961" Ref="#PWR077"  Part="1" 
AR Path="/56BA2E2B/56B89961" Ref="#PWR090"  Part="1" 
AR Path="/56BA5F82/56B89961" Ref="#PWR0103"  Part="1" 
F 0 "#PWR0103" H 6850 1750 50  0001 C CNN
F 1 "+3.3V" H 6868 2074 50  0000 C CNN
F 2 "" H 6850 1900 50  0000 C CNN
F 3 "" H 6850 1900 50  0000 C CNN
	1    6850 1900
	1    0    0    -1  
$EndComp
Text Notes 7450 1900 0    60   ~ 0
Csens is the bypass capacitor for ACS711
$Comp
L C CDrHV1back1
U 1 1 578D654C
P 6300 1200
AR Path="/55DB7E47/578D654C" Ref="CDrHV1back1"  Part="1" 
AR Path="/56B809CA/578D654C" Ref="CDrHV1back2"  Part="1" 
AR Path="/56B8347B/578D654C" Ref="CDrHV1back3"  Part="1" 
AR Path="/56BC308A/578D654C" Ref="CDrHV1back4"  Part="1" 
AR Path="/56BA2E2B/578D654C" Ref="CDrHV1back5"  Part="1" 
AR Path="/56BA5F82/578D654C" Ref="CDrHV1back6"  Part="1" 
F 0 "CDrHV1back6" H 6415 1246 50  0000 L CNN
F 1 "4.7u" H 6415 1155 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206" H 6338 1050 50  0001 C CNN
F 3 "" H 6300 1200 50  0000 C CNN
	1    6300 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 4800 6050 4800
Connection ~ 5850 4800
Connection ~ 5900 4800
Connection ~ 5950 4800
Connection ~ 6000 4800
Wire Wire Line
	5750 5050 5750 4800
Wire Wire Line
	5200 5000 5200 4800
Wire Wire Line
	5200 4800 5300 4800
Wire Wire Line
	4950 3200 4950 3050
Wire Wire Line
	4300 2750 5300 2750
Wire Wire Line
	5300 2750 5300 3200
Wire Wire Line
	4300 2650 4300 2750
Connection ~ 4950 2750
Wire Wire Line
	4300 3050 4300 3250
Wire Wire Line
	4100 4000 4650 4000
Wire Wire Line
	4100 4100 4650 4100
Wire Wire Line
	4100 4200 4650 4200
Wire Wire Line
	6650 3700 6750 3700
Wire Wire Line
	7050 3700 7050 3850
Wire Wire Line
	7050 3850 6650 3850
Wire Wire Line
	7350 3150 7350 2650
Wire Wire Line
	8350 2950 8350 3150
Connection ~ 8350 3050
Wire Wire Line
	6650 4000 7550 4000
Wire Wire Line
	7550 4000 7550 3950
Connection ~ 7450 4000
Wire Wire Line
	6650 4000 6650 4500
Connection ~ 6650 4050
Connection ~ 6650 4100
Connection ~ 6650 4150
Connection ~ 6650 4200
Connection ~ 6650 4250
Connection ~ 6650 4300
Connection ~ 6650 4350
Connection ~ 6650 4400
Connection ~ 6650 4450
Wire Wire Line
	7450 4950 7450 4850
Wire Wire Line
	7450 4550 7450 4450
Wire Wire Line
	7800 4500 7450 4500
Connection ~ 7450 4500
Wire Wire Line
	8150 4000 8850 4000
Wire Wire Line
	8250 3950 8250 4150
Wire Wire Line
	8150 3950 8150 4000
Connection ~ 8250 4000
Wire Wire Line
	6050 3200 6050 3000
Wire Wire Line
	5850 3200 6050 3200
Connection ~ 6000 3200
Connection ~ 5950 3200
Connection ~ 5900 3200
Wire Wire Line
	7750 3150 7750 2650
Wire Wire Line
	7750 2650 8750 2650
Connection ~ 8050 2650
Connection ~ 8350 2650
Wire Wire Line
	7550 3150 7550 2500
Wire Wire Line
	7550 2500 7850 2500
Wire Wire Line
	4650 3800 4650 3250
Wire Wire Line
	4650 3250 4300 3250
Wire Wire Line
	4100 3900 4650 3900
Wire Wire Line
	5750 1500 5750 1350
Wire Wire Line
	5750 1050 5750 950 
Wire Wire Line
	5200 1050 5200 1000
Wire Wire Line
	5200 1000 7050 1000
Connection ~ 5750 1000
Wire Wire Line
	5200 1350 5200 1400
Wire Wire Line
	5200 1400 7050 1400
Connection ~ 5750 1400
Wire Wire Line
	8050 3050 8550 3050
Wire Wire Line
	8050 2950 8050 3050
Wire Wire Line
	7450 3950 7450 4000
Wire Wire Line
	8250 4150 7450 4150
Wire Wire Line
	8250 3150 8250 3100
Wire Wire Line
	8250 3100 7350 3100
Connection ~ 7350 3100
Wire Wire Line
	8150 3150 8150 3100
Connection ~ 8150 3100
Wire Wire Line
	6300 1000 6300 1050
Wire Wire Line
	6300 1400 6300 1350
$Comp
L C CDrHV2back1
U 1 1 578D76CB
P 7050 1200
AR Path="/55DB7E47/578D76CB" Ref="CDrHV2back1"  Part="1" 
AR Path="/56B809CA/578D76CB" Ref="CDrHV2back2"  Part="1" 
AR Path="/56B8347B/578D76CB" Ref="CDrHV2back3"  Part="1" 
AR Path="/56BC308A/578D76CB" Ref="CDrHV2back4"  Part="1" 
AR Path="/56BA2E2B/578D76CB" Ref="CDrHV2back5"  Part="1" 
AR Path="/56BA5F82/578D76CB" Ref="CDrHV2back6"  Part="1" 
F 0 "CDrHV2back6" H 7165 1246 50  0000 L CNN
F 1 "4.7u" H 7165 1155 50  0000 L CNN
F 2 "Capacitors_SMD:C_1206_HandSoldering" H 7088 1050 50  0001 C CNN
F 3 "" H 7050 1200 50  0000 C CNN
	1    7050 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 1000 7050 1050
Connection ~ 6300 1000
Wire Wire Line
	7050 1400 7050 1350
Connection ~ 6300 1400
$Comp
L PAD_SMD PVSens1
U 1 1 57981B05
P 7250 4150
AR Path="/55DB7E47/57981B05" Ref="PVSens1"  Part="1" 
AR Path="/56B809CA/57981B05" Ref="PVSens2"  Part="1" 
AR Path="/56B8347B/57981B05" Ref="PVSens3"  Part="1" 
AR Path="/56BC308A/57981B05" Ref="PVSens4"  Part="1" 
AR Path="/56BA2E2B/57981B05" Ref="PVSens5"  Part="1" 
AR Path="/56BA5F82/57981B05" Ref="PVSens6"  Part="1" 
F 0 "PVSens6" H 7378 4203 60  0000 L CNN
F 1 "PAD_SMD" H 7378 4097 60  0000 L CNN
F 2 "Pads:PAD_SMD_1x1" H 7250 3900 60  0001 C CNN
F 3 "" H 7250 4000 60  0000 C CNN
	1    7250 4150
	-1   0    0    -1  
$EndComp
$EndSCHEMATC
