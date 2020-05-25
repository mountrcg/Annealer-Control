/*
 * Annealer-Control.h
 * 
 * Header file for annealer project. Breaks out defines, etc.
 * 
 */

#ifndef _ANNEALER_CONTROL_H
#define _ANNEALER_CONTROL_H

#include <Chrono.h>
#include <EEPROM.h>
#include <SerLCD.h> // SerLCD from SparkFun - http://librarymanager/All#SparkFun_SerLCD
#include <Wire.h>

#include <ctype.h> 


/*
 *  PIN CONFIGURATION
 */
#define  THERM1_PIN      A0
#define  CURRENT_PIN     A1
#define  VOLTAGE_PIN     A2
#define  OPTO_PIN        A5
#define  INDUCTOR_PIN    4
#define  SOLENOID_PIN    5
#define  START_PIN       6   
#define  STOP_PIN        7   
#define  INDUCTOR_LED    8
#define  SOLENOID_LED    9
#define  ENCODER_A_PIN   10
#define  ENCODER_B_PIN   11
#define  ENCODER_BUTTON  12



/*
 * CONSTANTS
 */
// System Constants
#ifdef _AP3_VARIANT_H_
#define RESOLUTION_MAX  16384 // Artemis boards have a 14-bit ADC resolution (make sure to turn it on!!!)
#define VREF            2.0
#else
#define RESOLUTION_MAX  1024 // 10-bit ADC seems to be the lowest common denominator
#define VREF            5.0  // YMMV - basic Arduino board is 5v, but some are 3.3V
#endif

// Thermistor Values
#define THERM_NOMINAL       10000   //Resistance at nominal temperature
#define THERM_NOM_TEMP      25      //Nominal temperature in DegC
#define THERM_BETA          3950    //Beta coefficient for thermistor
#define THERM_RESISTOR      10000   //Value of resistor in series with thermistor
#define THERM_SMOOTH_RATIO  0.35    // What percentage of the running average is the latest reading - used to smooth analog input

#ifdef _AP3_VARIANT_H_
#define INT_TEMP_SMOOTH_RATIO 0.35
#endif

// Power sensor values
#define AMPS_SMOOTH_RATIO   0.50
#define VOLTS_SMOOTH_RATIO  0.50

#ifdef _AP3_VARIANT_H_
#define VOLTS_PER_RESOLUTION  0.0029296875 // 48v over 14-bit resolution - 48 divided by 16384
#else
#define VOLTS_PER_RESOLUTION  0.046875  // 48v over 10-bit resolution - 48 divided by 1024
#endif

// EEPROM addresses - int is 2 bytes, so make sure these are even numbers!
#define ANNEAL_ADDR   0
#define DELAY_ADDR    2
#define CASEDROP_ADDR 4
#define EE_FAILSAFE_ADDR  100
#define EE_FAILSAFE_VALUE 43  // bump in v0.4

// Control constants
#define CASE_DROP_DELAY_DEFAULT   50      // hundredths of seconds
#define ANNEAL_TIME_DEFAULT       10      // hundredths of seconds - for the timer formats
#define DELAY_DEFAULT             50      // hundredths of seconds - for the timer formats
#define LCD_STARTUP_INTERVAL      1000    // milliseconds - let the screen fire up and come online before we hit it
#define LCD_UPDATE_INTERVAL       500     // milliseconds
#define ANNEAL_LCD_TIMER_INTERVAL 250     // milliseconds
#define ANNEAL_POWER_INTERVAL     100     // millseconds
#define DEBOUNCE_MICROS           100000  // MICROseconds

// LCD contstants
#define LCD_SETPOINT_LABEL  0,0
#define LCD_SETPOINT        4,0
#define LCD_TIMER_LABEL     9,0
#define LCD_TIMER           15,0
#define LCD_CURRENT_LABEL   0,1
#define LCD_CURRENT         4,1
#define LCD_VOLTAGE_LABEL   9,1
#define LCD_VOLTAGE         15,1
#define LCD_THERM1_LABEL    0,2
#define LCD_THERM1          5,2
#define LCD_2NDTEMP_LABEL   9,2
#define LCD_2NDTEMP         16,2
#define LCD_STATE_LABEL     0,3
#define LCD_STATE           7,3


#define ANALOG_INTERVAL       1000
#define LCDSTARTUP_INTERVAL   1000


enum AnnealState
{
  WAIT_BUTTON,
  WAIT_CASE,
  START_ANNEAL,
  ANNEAL_TIMER,
  DROP_CASE,
  DROP_CASE_TIMER,
  DELAY
};

extern AnnealState annealState;


#endif // _ANNEALER_CONTROL_H