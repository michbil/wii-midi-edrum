// enables serial port functions
//#define USE_SERPORT

// enables the + - up down left right buttons if defined
//#define GHWT

// trigger on either rising or falling edge (never both please)
// these only apply to the 5 pads, buttons and bass pedals are always falling edge
// pull_up_res will enable internal pull-up resistors for the pad pins
// does not effect buttons and bass pedals
//#define trig_on_rise
#define trig_on_fall
#define pull_up_res 

// guarantee the release of a pad before the next hit if defined
//#define GUARANTEE_RELEASE

// minimum pulse time (x = actual pulse time / 0.005)
// keep at 5, raise if you see double hits
#define hit_min_time 4

// hit softness (0 = max, 7 = min, just make it 0)
#define default_hit_softness 0

// simulated degree of thumb stick movement (something under 32)
#define thumbstick_speed 16

#ifndef pindef_h

#define twi_port PORTC
#define twi_ddr DDRC
#define twi_scl_pin 5
#define twi_sda_pin 4

#define dev_detect_port PORTD
#define dev_detect_ddr DDRD
#define dev_detect_pin 3

#define uart_port PORTD
#define uart_rx_pin 0

#define LED_pin 5
#define LED_port PORTB
#define LED_ddr DDRB

#define power_detect_pin 4
#define power_detect_port PORTD
#define power_detect_ddr DDRD
#define power_detect_input PIND

#define adc_port PORTC
#define adc_ddr DDRC

// for the bit numbers, go to
// http://wiibrew.org/wiki/Wiimote/Extension_Controllers

#define drum_port PORTD
#define drum_ddr DDRD
#define drum_in_reg PIND

#define bass_port PORTD
#define bass_ddr DDRD
#define bass_in_reg PIND

#define green_bit 4
#define green_pin 5

#define red_bit 6
#define red_pin 6

#define yellow_bit 5
#define yellow_pin 7

#define blue_bit 3
#define blue_pin 0

#define orange_bit 7
#define orange_pin 4

#define bass_bit 2

#define bass1_pin 2
#define bass2_pin 2

#define plusminus_port PORTA
#define plusminus_ddr DDRA
#define plusminus_in_reg PINA

#define stick_in_reg PINA
#define stick_port PORTA
#define stick_ddr DDRA

#define plus_bit 2
#define plus_pin 6

#define minus_bit 4
#define minus_pin 7

#define up_stick_pin 6
#define down_stick_pin 6
#define left_stick_pin 6
#define right_stick_pin 6

void hit_pcint(unsigned char w);
extern char hits;

#define MIDI

#define pindef_h
#endif

#ifndef macros_h

/* old macros */

// Macros
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit)) // clear bit
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit)) // set bit
#define tog(sfr, bit) (_SFR_BYTE(sfr) ^= _BV(bit)) // toggle bit
#define wdr() __asm__ __volatile__ ("wdr") // watchdog reset
#define nop() __asm__ __volatile__ ("nop") // no operation

#define macros_h
#endif
