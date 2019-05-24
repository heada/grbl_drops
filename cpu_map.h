/*
  cpu_map.h - CPU and pin mapping configuration file
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

/* The cpu_map.h files serve as a central pin mapping selection file for different
   processor types or alternative pin layouts. This version of Grbl officially supports
   only the Arduino Mega328p. */


#ifndef cpu_map_h
#define cpu_map_h


#ifdef CPU_MAP_ATMEGA328P // (Arduino Uno) Officially supported by Grbl.

  // Define serial port pins and interrupt vectors.
  #define SERIAL_RX     USART_RX_vect
  #define SERIAL_UDRE   USART_UDRE_vect

  // Define step pulse output pins. NOTE: All step bit pins must be on the same port.
  #define STEP_DDR        DDRD
  #define STEP_PORT       PORTD
  #define X_STEP_BIT      2  // Uno Digital Pin 2
  #define Y_STEP_BIT      3  // Uno Digital Pin 3
  #define Z_STEP_BIT      4  // Uno Digital Pin 4
  #define STEP_MASK       ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits

  // Define step direction output pins. NOTE: All direction pins must be on the same port.
  #define DIRECTION_DDR     DDRD
  #define DIRECTION_PORT    PORTD
  #define X_DIRECTION_BIT   5  // Uno Digital Pin 5
  #define Y_DIRECTION_BIT   6  // Uno Digital Pin 6
  #define Z_DIRECTION_BIT   7  // Uno Digital Pin 7
  #define DIRECTION_MASK    ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits

  // Define stepper driver enable/disable output pin.
  #define STEPPERS_DISABLE_DDR    DDRB
  #define STEPPERS_DISABLE_PORT   PORTB
  #define STEPPERS_DISABLE_BIT    0  // Uno Digital Pin 8
  #define STEPPERS_DISABLE_MASK   (1<<STEPPERS_DISABLE_BIT)

  // Define homing/hard limit switch input pins and limit interrupt vectors.
  // NOTE: All limit bit pins must be on the same port, but not on a port with other input pins (CONTROL).
  #define LIMIT_DDR        DDRB
  #define LIMIT_PIN        PINB
  #define LIMIT_PORT       PORTB
  #define X_LIMIT_BIT      1  // Uno Digital Pin 9
  #define Y_LIMIT_BIT      2  // Uno Digital Pin 10
  #ifdef VARIABLE_SPINDLE // Z Limit pin and spindle enabled swapped to access hardware PWM on Pin 11.
    #define Z_LIMIT_BIT	   4 // Uno Digital Pin 12
  #else
    #define Z_LIMIT_BIT    3  // Uno Digital Pin 11
  #endif
  #define LIMIT_MASK       ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits
  #define LIMIT_INT        PCIE0  // Pin change interrupt enable pin
  #define LIMIT_INT_vect   PCINT0_vect
  #define LIMIT_PCMSK      PCMSK0 // Pin change interrupt register

  // Define spindle enable and spindle direction output pins.
  #define SPINDLE_ENABLE_DDR    DDRB
  #define SPINDLE_ENABLE_PORT   PORTB
  // Z Limit pin and spindle PWM/enable pin swapped to access hardware PWM on Pin 11.
  #ifdef VARIABLE_SPINDLE
    #ifdef USE_SPINDLE_DIR_AS_ENABLE_PIN
      // If enabled, spindle direction pin now used as spindle enable, while PWM remains on D11.
      #define SPINDLE_ENABLE_BIT    5  // Uno Digital Pin 13 (NOTE: D13 can't be pulled-high input due to LED.)
    #else
      #define SPINDLE_ENABLE_BIT    3  // Uno Digital Pin 11
    #endif
  #else
    #define SPINDLE_ENABLE_BIT    4  // Uno Digital Pin 12
  #endif
  #ifndef USE_SPINDLE_DIR_AS_ENABLE_PIN
    #define SPINDLE_DIRECTION_DDR   DDRB
    #define SPINDLE_DIRECTION_PORT  PORTB
    #define SPINDLE_DIRECTION_BIT   5  // Uno Digital Pin 13 (NOTE: D13 can't be pulled-high input due to LED.)
  #endif

  // Define flood and mist coolant enable output pins.
  #define COOLANT_FLOOD_DDR   DDRC
  #define COOLANT_FLOOD_PORT  PORTC
  #define COOLANT_FLOOD_BIT   3  // Uno Analog Pin 3
  #define COOLANT_MIST_DDR   DDRC
  #define COOLANT_MIST_PORT  PORTC
  #define COOLANT_MIST_BIT   4  // Uno Analog Pin 4

  // Define user-control controls (cycle start, reset, feed hold) input pins.
  // NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
  #define CONTROL_DDR       DDRC
  #define CONTROL_PIN       PINC
  #define CONTROL_PORT      PORTC
  #define CONTROL_RESET_BIT         0  // Uno Analog Pin 0
  #define CONTROL_FEED_HOLD_BIT     1  // Uno Analog Pin 1
  #define CONTROL_CYCLE_START_BIT   2  // Uno Analog Pin 2
  #define CONTROL_SAFETY_DOOR_BIT   1  // Uno Analog Pin 1 NOTE: Safety door is shared with feed hold. Enabled by config define.
  #define CONTROL_INT       PCIE1  // Pin change interrupt enable pin
  #define CONTROL_INT_vect  PCINT1_vect
  #define CONTROL_PCMSK     PCMSK1 // Pin change interrupt register
  #define CONTROL_MASK      ((1<<CONTROL_RESET_BIT)|(1<<CONTROL_FEED_HOLD_BIT)|(1<<CONTROL_CYCLE_START_BIT)|(1<<CONTROL_SAFETY_DOOR_BIT))
  #define CONTROL_INVERT_MASK   CONTROL_MASK // May be re-defined to only invert certain control pins.

  // Define probe switch input pin.
  #define PROBE_DDR       DDRC
  #define PROBE_PIN       PINC
  #define PROBE_PORT      PORTC
  #define PROBE_BIT       5  // Uno Analog Pin 5
  #define PROBE_MASK      (1<<PROBE_BIT)

  // Variable spindle configuration below. Do not change unless you know what you are doing.
  // NOTE: Only used when variable spindle is enabled.
  #define SPINDLE_PWM_MAX_VALUE     255 // Don't change. 328p fast PWM mode fixes top value as 255.
  #ifndef SPINDLE_PWM_MIN_VALUE
    #define SPINDLE_PWM_MIN_VALUE   1   // Must be greater than zero.
  #endif
  #define SPINDLE_PWM_OFF_VALUE     0
  #define SPINDLE_PWM_RANGE         (SPINDLE_PWM_MAX_VALUE-SPINDLE_PWM_MIN_VALUE)
  #define SPINDLE_TCCRA_REGISTER	  TCCR2A
  #define SPINDLE_TCCRB_REGISTER	  TCCR2B
  #define SPINDLE_OCR_REGISTER      OCR2A
  #define SPINDLE_COMB_BIT	        COM2A1


  // Prescaled, 8-bit Fast PWM mode.
  #define SPINDLE_TCCRA_INIT_MASK   ((1<<WGM20) | (1<<WGM21))  // Configures fast PWM mode.
  // #define SPINDLE_TCCRB_INIT_MASK   (1<<CS20)               // Disable prescaler -> 62.5kHz
  // #define SPINDLE_TCCRB_INIT_MASK   (1<<CS21)               // 1/8 prescaler -> 7.8kHz (Used in v0.9)
  // #define SPINDLE_TCCRB_INIT_MASK   ((1<<CS21) | (1<<CS20)) // 1/32 prescaler -> 1.96kHz
  #define SPINDLE_TCCRB_INIT_MASK      (1<<CS22)               // 1/64 prescaler -> 0.98kHz (J-tech laser)

  // NOTE: On the 328p, these must be the same as the SPINDLE_ENABLE settings.
  #define SPINDLE_PWM_DDR	  DDRB
  #define SPINDLE_PWM_PORT  PORTB
  #define SPINDLE_PWM_BIT	  5    // Uno Digital Pin 11

#endif

#ifdef CPU_MAP_ATMEGA2560_RAMPS_1_4 // (Arduino Mega 2560)+Ramps1.4 Working Arsi

// Serial port pins
#define SERIAL_RX USART0_RX_vect
#define SERIAL_UDRE USART0_UDRE_vect

// Increase Buffers to make use of extra SRAM
//#define RX_BUFFER_SIZE		256
//#define TX_BUFFER_SIZE		128
//#define BLOCK_BUFFER_SIZE	36
//#define LINE_BUFFER_SIZE	100

// Define step pulse output pins. Changed for Ramps
#define STEP_DDR      DDRA
#define STEP_PORT     PORTA
#define STEP_PIN      PINA
#define X_STEP_BIT        2 // Not realy used
#define Y_STEP_BIT        4 // Not realy used
#define Z_STEP_BIT        3 // Not realy used
#define STEP_MASK ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits

// Define step direction output pins. Changed for Ramps
#define DIRECTION_DDR      DDRA
#define DIRECTION_PORT     PORTA
#define DIRECTION_PIN      PINA
#define X_DIRECTION_BIT   5 // Not realy used
#define Y_DIRECTION_BIT   7 // Not realy used
#define Z_DIRECTION_BIT   6 // Not realy used
#define DIRECTION_MASK ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits

// Define stepper driver enable/disable output pin. Changed for Ramps
#define STEPPERS_DISABLE_DDR   DDRB
#define STEPPERS_DISABLE_PORT  PORTB
#define STEPPERS_DISABLE_BIT   7 // Not realy used
#define STEPPERS_DISABLE_MASK (1<<STEPPERS_DISABLE_BIT)

// NOTE: All limit bit pins must be on the same port
#define LIMIT_DDR       DDRB
#define LIMIT_PORT      PORTB
#define LIMIT_PIN       PINB
#define X_LIMIT_BIT     0 // Ramps PB3 ( MISO/PCINT3 ) Digital pin 50 (MISO) ->Ramps AUX-3 pin 3
#define Y_LIMIT_BIT     1 // Ramps PB2 ( MOSI/PCINT2 ) Digital pin 51 (MOSI) ->Ramps AUX-3 pin 4
#define Z_LIMIT_BIT     2 // Ramps PB1 ( SCK/PCINT1 ) Digital pin 52 (SCK) -> Ramps AUX-3 pin 5
#define LIMIT_INT       PCIE0  // Pin change interrupt enable pin
#define LIMIT_INT_vect  PCINT0_vect 
#define LIMIT_PCMSK     PCMSK0 // Pin change interrupt register
#define LIMIT_MASK ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits

// Define spindle enable and spindle direction output pins.
#define SPINDLE_ENABLE_DDR   DDRH
#define SPINDLE_ENABLE_PORT  PORTH
#define SPINDLE_ENABLE_BIT   3 // MEGA2560 Digital Pin 6
#define SPINDLE_DIRECTION_DDR   DDRG
#define SPINDLE_DIRECTION_PORT  PORTG
#define SPINDLE_DIRECTION_BIT   PG5 // MEGA2560 Digital Pin 5

// Define flood and mist coolant enable output pins.
// NOTE: Uno analog pins 4 and 5 are reserved for an i2c interface, and may be installed at
// a later date if flash and memory space allows.
#define COOLANT_FLOOD_DDR   DDRH
#define COOLANT_FLOOD_PORT  PORTH
#define COOLANT_FLOOD_BIT   5 // MEGA2560 Digital Pin 8
#ifdef ENABLE_M7 // Mist coolant disabled by default. See config.h to enable/disable.
#define COOLANT_MIST_DDR   DDRH
#define COOLANT_MIST_PORT  PORTH
#define COOLANT_MIST_BIT   6 // MEGA2560 Digital Pin 9
#endif  

// Define user-control pinouts (cycle start, reset, feed hold) input pins.
// NOTE: All pinouts pins must be on the same port and not on a port with other input pins (limits).
#define PINOUT_DDR       DDRK
#define PINOUT_PIN       PINK
#define PINOUT_PORT      PORTK
#define PIN_RESET        0  // MEGA2560 Analog Pin 8
#define PIN_FEED_HOLD    1  // MEGA2560 Analog Pin 9
#define PIN_CYCLE_START  2  // MEGA2560 Analog Pin 10
#define PINOUT_INT       PCIE2  // Pin change interrupt enable pin
#define PINOUT_INT_vect  PCINT2_vect
#define PINOUT_PCMSK     PCMSK2 // Pin change interrupt register
#define PINOUT_MASK ((1<<PIN_RESET)|(1<<PIN_FEED_HOLD)|(1<<PIN_CYCLE_START))

// Define probe switch input pin.
#define PROBE_DDR       DDRK
#define PROBE_PIN       PINK
#define PROBE_PORT      PORTK
#define PROBE_BIT       3  // MEGA2560 Analog Pin 11
#define PROBE_MASK      (1<<PROBE_BIT)

// Define ServoPort output pins (only ONE defined)
//#define SERVO_ESC_DDR   DDRB
//#define SERVO_ESC_PORT  PORTB
//#define SERVO_ESC_PIN   PINB
//#define SERVO_ESC_OUTPUT_PIN 5




// Start of PWM & Stepper Enabled Spindle
#ifdef VARIABLE_SPINDLE
// Advanced Configuration Below You should not need to touch these variables
// Set Timer up to use TIMER2B which is attached to Digital Pin 9
/*
#define TCCRA_REGISTER		TCCR2A
#define TCCRB_REGISTER		TCCR2B
#define OCR_REGISTER		OCR2B

#define COMB_BIT			COM2B1
#define WAVE0_REGISTER		WGM20
#define WAVE1_REGISTER		WGM21
#define WAVE2_REGISTER		WGM22
#define WAVE3_REGISTER		WGM23

#define SPINDLE_PWM_DDR		DDRH
#define SPINDLE_PWM_PORT    PORTH
#define SPINDLE_PWM_BIT		6 // MEGA2560 Digital Pin 9
*/
#define TCCRA_REGISTER		TCCR4A
#define TCCRB_REGISTER		TCCR4B
#define OCR_REGISTER		OCR4A

#define COMB_BIT			COM4A1
#define WAVE0_REGISTER		WGM20
#define WAVE1_REGISTER		WGM21
#define WAVE2_REGISTER		WGM22
#define WAVE3_REGISTER		WGM23

#define SPINDLE_PWM_DDR		DDRH
#define SPINDLE_PWM_PORT    PORTH
#define SPINDLE_PWM_BIT		PH3 // MEGA2560 Digital Pin 9






#endif // End of VARIABLE_SPINDLE

  // Variable spindle configuration below. Do not change unless you know what you are doing.
  // NOTE: Only used when variable spindle is enabled.
#define SPINDLE_PWM_MAX_VALUE     255 // Don't change. 328p fast PWM mode fixes top value as 255.
#ifndef SPINDLE_PWM_MIN_VALUE
#define SPINDLE_PWM_MIN_VALUE   1   // Must be greater than zero.
#endif
#define SPINDLE_PWM_OFF_VALUE     0
#define SPINDLE_PWM_RANGE         (SPINDLE_PWM_MAX_VALUE-SPINDLE_PWM_MIN_VALUE)
#define SPINDLE_TCCRA_REGISTER	  TCCR4A
#define SPINDLE_TCCRB_REGISTER	  TCCR4B
#define SPINDLE_OCR_REGISTER      OCR4A
#define SPINDLE_COMB_BIT	        COM4A1
#define SPINDLE_TIMER_MATCH 		ICR4

  // Prescaled, 8-bit Fast PWM mode.
//#define SPINDLE_TCCRA_INIT_MASK   ((1<<WGM40) | (1<<WGM41))  // Configures fast PWM mode.(OLD)
#define SPINDLE_TCCRA_INIT_MASK   ((1<<COM4A1) | (1<<WGM41))  // Configures fast PWM mode.
// #define SPINDLE_TCCRB_INIT_MASK   (1<<CS20)               // Disable prescaler -> 62.5kHz
// #define SPINDLE_TCCRB_INIT_MASK   (1<<CS21)               // 1/8 prescaler -> 7.8kHz (Used in v0.9)
// #define SPINDLE_TCCRB_INIT_MASK   ((1<<CS21) | (1<<CS20)) // 1/32 prescaler -> 1.96kHz
#define SPINDLE_TCCRB_INIT_MASK      (1<<CS42)               // 1/265 prescaler Arduino Mega	(OLD)1/64 prescaler -> 0.98kHz (J-tech laser)
 


  // Define user-control controls (cycle start, reset, feed hold) input pins.
  // NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
#define CONTROL_DDR       DDRC
#define CONTROL_PIN       PINC
#define CONTROL_PORT      PORTC
#define CONTROL_RESET_BIT         0  // Uno Analog Pin 0
#define CONTROL_FEED_HOLD_BIT     1  // Uno Analog Pin 1
#define CONTROL_CYCLE_START_BIT   2  // Uno Analog Pin 2
#define CONTROL_SAFETY_DOOR_BIT   1  // Uno Analog Pin 1 NOTE: Safety door is shared with feed hold. Enabled by config define.
#define CONTROL_INT       PCIE1  // Pin change interrupt enable pin
#define CONTROL_INT_vect  PCINT1_vect
#define CONTROL_PCMSK     PCMSK1 // Pin change interrupt register
#define CONTROL_MASK      ((1<<CONTROL_RESET_BIT)|(1<<CONTROL_FEED_HOLD_BIT)|(1<<CONTROL_CYCLE_START_BIT)|(1<<CONTROL_SAFETY_DOOR_BIT))
#define CONTROL_INVERT_MASK   CONTROL_MASK // May be re-defined to only invert certain control pins.



// MOD GRBL for Cyclone

#define PROBE_PIN 18 // Z endstop
#define ZLIM_PIN 18
#define XLIM_PIN 2
#define YLIM_PIN 14

//#define X_STEP_PIN         54 //PF0 ( ADC0 )
//#define X_DIR_PIN          55 //PF1 ( ADC1 )
//#define X_ENABLE_PIN       38 //PD7 ( T0 )

//#define Y_STEP_PIN         60 //PF6 ( ADC6 )
//#define Y_DIR_PIN          61 //PF7 ( ADC7 )
//#define Y_ENABLE_PIN       56 //PF2 ( ADC2 )

//#define Z_STEP_PIN         46 //PL3 ( OC5A )
//#define Z_DIR_PIN          48 //PL1 ( ICP5 )
//#define Z_ENABLE_PIN       62 //PK0 ( ADC8/PCINT16 )

#define X_STEP_PIN         54 //PF0 ( ADC0 )
#define X_DIR_PIN          55 //PF1 ( ADC1 )
#define X_ENABLE_PIN       38 //PD7 ( T0 )

#define Z_STEP_PIN         60 //PF6 ( ADC6 )
#define Z_DIR_PIN          61 //PF7 ( ADC7 )
#define Z_ENABLE_PIN       56 //PF2 ( ADC2 )

#define Y_STEP_PIN         46 //PL3 ( OC5A )
#define Y_DIR_PIN          48 //PL1 ( ICP5 )
#define Y_ENABLE_PIN       62 //PK0 ( ADC8/PCINT16 )

#define SPINDLE_ENABLE_PIN 10
#define SPINDLE_DIRECTION_PIN 9
#define COOLANT_FLOOD_PIN 8

#endif
/*
#ifdef CPU_MAP_CUSTOM_PROC
  // For a custom pin map or different processor, copy and edit one of the available cpu
  // map files and modify it to your needs. Make sure the defined name is also changed in
  // the config.h file.
#endif
*/

#endif
