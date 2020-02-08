// -----------------------------------------------------------------------------
// USB Communication Visualizer
// version: 1.1
// date: 01/29/2020
// author: jocos
// -----------------------------------------------------------------------------


#include "m_general.h"
#include "m_usb.h"

#define beta_in     0.643       // 440Hz cutoff = 0.643
                                // 300Hz cutoff = 0.768
#define decay_rate  48          // [Hz] sets rate of light decay
#define reset_rate  120         // [Hz] sets rate of ADC_max decay

// --------------------------------------------------
// declarations
// --------------------------------------------------

// functions
void visualize_serial_init();

// algorithm variables
int ADC_max = 0;
int ADC_filter = 0;
int ADC_aref = 0;
float level = 1;
float level_filt = 1;

// system variables
volatile int n = 0;             // light delay counter, counts at 1.04kHz
volatile int i = 0;             // ADC_max decay counter, counts at 1.04kHz

// --------------------------------------------------
// main
// --------------------------------------------------

int main(void){
    // initialize program
    visualize_serial_init();

    m_green(ON);

    // main loop
    while (true) {
        // ** control level decay
        // sharp rise
        if (level > level_filt) {
            // increment level
            level_filt = level;
            if (level_filt > 13) {level_filt = 13;}
            // reset light delay counter
            n = 0;
        }
        // slow decay
        else if (n > 1040/decay_rate) {
            // decrement level
            if (level_filt > 1) {level_filt = level_filt - 1;}
            // reset light delay counter
            n = 0;
        }

        // ** manipulate lights
        switch ((int)level_filt) {
            case 1:
                clear(PORTB, 0);    // A
                clear(PORTB, 1);    // B
                clear(PORTB, 2);    // C
                clear(PORTB, 3);    // D
                clear(PORTB, 4);    // E
                clear(PORTB, 5);    // F
                clear(PORTB, 6);    // G
                clear(PORTD, 2);    // H
                clear(PORTD, 3);    // I
                clear(PORTD, 4);    // J
                clear(PORTD, 5);    // K
                clear(PORTD, 6);      // L
                // m_usb_tx_string("\n");
                break;
            case 2:
                clear(PORTB, 0);    // A
                clear(PORTB, 1);    // B
                clear(PORTB, 2);    // C
                clear(PORTB, 3);    // D
                clear(PORTB, 4);    // E
                clear(PORTB, 5);    // F
                clear(PORTB, 6);    // G
                clear(PORTD, 2);    // H
                clear(PORTD, 3);    // I
                clear(PORTD, 4);    // J
                clear(PORTD, 5);    // K
                set(PORTD, 6);      // L
                // m_usb_tx_string("0\n");
                break;
            case 3:
                clear(PORTB, 0);    // A
                clear(PORTB, 1);    // B
                clear(PORTB, 2);    // C
                clear(PORTB, 3);    // D
                clear(PORTB, 4);    // E
                clear(PORTB, 5);    // F
                clear(PORTB, 6);    // G
                clear(PORTD, 2);    // H
                clear(PORTD, 3);    // I
                clear(PORTD, 4);    // J
                set(PORTD, 5);      // K
                set(PORTD, 6);      // L
                // m_usb_tx_string("00\n");
                break;
            case 4:
                clear(PORTB, 0);    // A
                clear(PORTB, 1);    // B
                clear(PORTB, 2);    // C
                clear(PORTB, 3);    // D
                clear(PORTB, 4);    // E
                clear(PORTB, 5);    // F
                clear(PORTB, 6);    // G
                clear(PORTD, 2);    // H
                clear(PORTD, 3);    // I
                set(PORTD, 4);      // J
                set(PORTD, 5);      // K
                set(PORTD, 6);      // L
                // m_usb_tx_string("000\n");
                break;
            case 5:
                clear(PORTB, 0);    // A
                clear(PORTB, 1);    // B
                clear(PORTB, 2);    // C
                clear(PORTB, 3);    // D
                clear(PORTB, 4);    // E
                clear(PORTB, 5);    // F
                clear(PORTB, 6);    // G
                clear(PORTD, 2);    // H
                set(PORTD, 3);      // I
                set(PORTD, 4);      // J
                set(PORTD, 5);      // K
                set(PORTD, 6);      // L
                // m_usb_tx_string("0000\n");
                break;
            case 6:
                clear(PORTB, 0);    // A
                clear(PORTB, 1);    // B
                clear(PORTB, 2);    // C
                clear(PORTB, 3);    // D
                clear(PORTB, 4);    // E
                clear(PORTB, 5);    // F
                clear(PORTB, 6);    // G
                set(PORTD, 2);      // H
                set(PORTD, 3);      // I
                set(PORTD, 4);      // J
                set(PORTD, 5);      // K
                set(PORTD, 6);      // L
                // m_usb_tx_string("00000\n");
                break;
            case 7:
                clear(PORTB, 0);    // A
                clear(PORTB, 1);    // B
                clear(PORTB, 2);    // C
                clear(PORTB, 3);    // D
                clear(PORTB, 4);    // E
                clear(PORTB, 5);    // F
                set(PORTB, 6);      // G
                set(PORTD, 2);      // H
                set(PORTD, 3);      // I
                set(PORTD, 4);      // J
                set(PORTD, 5);      // K
                set(PORTD, 6);      // L
                // m_usb_tx_string("000000\n");
                break;
            case 8:
                clear(PORTB, 0);    // A
                clear(PORTB, 1);    // B
                clear(PORTB, 2);    // C
                clear(PORTB, 3);    // D
                clear(PORTB, 4);    // E
                set(PORTB, 5);      // F
                set(PORTB, 6);      // G
                set(PORTD, 2);      // H
                set(PORTD, 3);      // I
                set(PORTD, 4);      // J
                set(PORTD, 5);      // K
                set(PORTD, 6);      // L
                // m_usb_tx_string("0000000\n");
                break;
            case 9:
                clear(PORTB, 0);    // A
                clear(PORTB, 1);    // B
                clear(PORTB, 2);    // C
                clear(PORTB, 3);    // D
                set(PORTB, 4);      // E
                set(PORTB, 5);      // F
                set(PORTB, 6);      // G
                set(PORTD, 2);      // H
                set(PORTD, 3);      // I
                set(PORTD, 4);      // J
                set(PORTD, 5);      // K
                set(PORTD, 6);      // L
                // m_usb_tx_string("00000000\n");
                break;
            case 10:
                clear(PORTB, 0);    // A
                clear(PORTB, 1);    // B
                clear(PORTB, 2);    // C
                set(PORTB, 3);      // D
                set(PORTB, 4);      // E
                set(PORTB, 5);      // F
                set(PORTB, 6);      // G
                set(PORTD, 2);      // H
                set(PORTD, 3);      // I
                set(PORTD, 4);      // J
                set(PORTD, 5);      // K
                set(PORTD, 6);      // L
                // m_usb_tx_string("000000000\n");
                break;
            case 11:
                clear(PORTB, 0);    // A
                clear(PORTB, 1);    // B
                set(PORTB, 2);      // C
                set(PORTB, 3);      // D
                set(PORTB, 4);      // E
                set(PORTB, 5);      // F
                set(PORTB, 6);      // G
                set(PORTD, 2);      // H
                set(PORTD, 3);      // I
                set(PORTD, 4);      // J
                set(PORTD, 5);      // K
                set(PORTD, 6);      // L
                // m_usb_tx_string("0000000000\n");
                break;
            case 12:
                clear(PORTB, 0);    // A
                set(PORTB, 1);      // B
                set(PORTB, 2);      // C
                set(PORTB, 3);      // D
                set(PORTB, 4);      // E
                set(PORTB, 5);      // F
                set(PORTB, 6);      // G
                set(PORTD, 2);      // H
                set(PORTD, 3);      // I
                set(PORTD, 4);      // J
                set(PORTD, 5);      // K
                set(PORTD, 6);      // L
                // m_usb_tx_string("00000000000\n");
                break;
            case 13:
                set(PORTB, 0);      // A
                set(PORTB, 1);      // B
                set(PORTB, 2);      // C
                set(PORTB, 3);      // D
                set(PORTB, 4);      // E
                set(PORTB, 5);      // F
                set(PORTB, 6);      // G
                set(PORTD, 2);      // H
                set(PORTD, 3);      // I
                set(PORTD, 4);      // J
                set(PORTD, 5);      // K
                set(PORTD, 6);      // L
                // m_usb_tx_string("000000000000\n");
                break;
            default:
                m_red(ON);
                break;
        }

    // debugging
    m_usb_tx_int(ADC_filter);
    m_usb_tx_string("\t");
    m_usb_tx_int(ADC_max);
    m_usb_tx_string("\t");
    m_usb_tx_int(level);
    m_usb_tx_string("\t");
    m_usb_tx_int(level_filt*1000);
    m_usb_tx_string("\n");

    }
}

// --------------------------------------------------
// interrupts
// --------------------------------------------------

// when new ADC conversion ready
// smooth signal input
ISR(ADC_vect){
    // pull ADC measurement
    ADC_aref = ADC;

    // low pass filter
    // dt = ~20/125000
    ADC_filter = (float)beta_in*ADC_filter + (1.0-beta_in)*ADC_aref;

    // start next conversion
    set(ADCSRA, ADSC);
}

// when Timer 1 reaches OCR1A
// implement ADC_max decay
// determine raw level
ISR(TIMER1_COMPA_vect){
    // increment light decay counter
    n++;

    // reduce ADC_max
    if (reset_rate != 0) {
        // increment counter
        i++;

        // decrease ADC_max by 1 at reset_rate
        if (i > 1040/ reset_rate) {
            if (ADC_max > 13) {ADC_max += -1;}
            i = 0;
        }
    }

    // adjust ADC_max to reflect filtered signal values
    if (ADC_aref > ADC_max) {ADC_max = ADC_aref;}

    // determine new raw level
    if      (ADC_filter > ADC_max*12/13) {level = 13;}
    else if (ADC_filter > ADC_max*11/13) {level = 12;}
    else if (ADC_filter > ADC_max*10/13) {level = 11;}
    else if (ADC_filter > ADC_max*9/13)  {level = 10;}
    else if (ADC_filter > ADC_max*8/13)  {level = 9;}
    else if (ADC_filter > ADC_max*7/13)  {level = 8;}
    else if (ADC_filter > ADC_max*6/13)  {level = 7;}
    else if (ADC_filter > ADC_max*5/13)  {level = 6;}
    else if (ADC_filter > ADC_max*4/13)  {level = 5;}
    else if (ADC_filter > ADC_max*3/13)  {level = 4;}
    else if (ADC_filter > ADC_max*2/13)  {level = 3;}
    else if (ADC_filter > ADC_max*1/13)  {level = 2;}
    else                                 {level = 1;}
}

// --------------------------------------------------
// visualize_serial_init
// --------------------------------------------------
void visualize_serial_init(){

    // ** system clock
    // set system clock to 16MHz
    m_clockdivide(0);

    // ** subsystem initialization
    m_disableJTAG();        // enable use of F pins
    m_usb_init();           // initialize USB communications

    // ** GPIO initialization
    set(DDRB, 0); set(PORTB, 0);    // A
    set(DDRB, 1); set(PORTB, 1);    // B
    set(DDRB, 2); set(PORTB, 2);    // C
    set(DDRB, 3); set(PORTB, 3);    // D
    set(DDRB, 4); set(PORTB, 4);    // E
    set(DDRB, 5); set(PORTB, 5);    // F
    set(DDRB, 6); set(PORTB, 6);    // G
    set(DDRD, 2); set(PORTD, 2);    // H
    set(DDRD, 3); set(PORTD, 3);    // I
    set(DDRD, 4); set(PORTD, 4);    // J
    set(DDRD, 5); set(PORTD, 5);    // K
    set(DDRD, 6); set(PORTD, 6);    // L

    // ** Timer 1 initialization **
    // set prescaler to /1024 (15625Hz counter)
    set(TCCR1B, CS12);
    clear(TCCR1B, CS11);
    set(TCCR1B, CS10);
    // set timer to mode 4
    // count UP to OCR1A, then reset to 0x0000
    clear(TCCR1B, WGM13);
    set(TCCR1B, WGM12);
    clear(TCCR1A, WGM11);
    clear(TCCR1A, WGM10);
    // disable pin change
    clear(TCCR1A, COM1B1);
    clear(TCCR1A, COM1B0);
    // enable interrupt at OCR1A
    set(TIMSK1, OCIE1A);
    // set OCR1A to 15 (1.04kHz reset)
    OCR1A = 15;

    // ** ADC initialization
    // disable ADC subsystem
    clear(ADCSRA, ADEN);
    // set voltage reference to Vcc
    clear(ADMUX, REFS1);
    set (ADMUX, REFS0);
    // set prescaler to /128
    // clocking at 125kHz
    set(ADCSRA, ADPS2);
    set(ADCSRA, ADPS1);
    set(ADCSRA, ADPS0);
    // disable F0's digital input
    set(DIDR0, ADC0D);
    // enable interrupt each conversion
    set(ADCSRA, ADIE);
    // set input channel to F0
    clear(ADCSRB, MUX5);
    clear(ADMUX, MUX2);
    clear(ADMUX, MUX1);
    clear(ADMUX, MUX0);
    // begin conversion
    set(ADCSRA, ADEN);
    set(ADCSRA, ADSC);

    // ** enable global interrupts
    sei();
}