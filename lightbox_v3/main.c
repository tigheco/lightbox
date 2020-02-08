// -----------------------------------------------------------------------------
// USB Communication Visualizer
// version: 1.0
// date: 02/07/2014
// author: jocos
// -----------------------------------------------------------------------------


#include "m_general.h"
#include "m_usb.h"

#define beta 0.99

// --------------------------------------------------
// declarations
// --------------------------------------------------

// functions
void visualize_serial_init();

// variables
int max_ADC = 0;
int ADC_filter = 0;
char level = 0;

// --------------------------------------------------
// main
// --------------------------------------------------
int main(void){
    
    visualize_serial_init();
    
    m_green(ON);

    while (true) {
        
        // ** determine incoming volume level
        // low pass filter incoming ADC
        ADC_filter = (float)beta*ADC_filter + (1.0-beta)*ADC;
        
        if (ADC_filter > max_ADC) {max_ADC = ADC_filter;}
        
        if (ADC_filter > max_ADC*3/4) {level = 4;}
        else if (ADC_filter > max_ADC*2/4) {level = 3;}
        else if (ADC_filter > max_ADC*1/4) {level = 2;}
        else {level = 1;}
        
        // ** manipulate lights
        switch (level) {
            case 1:
                clear(PORTF, 4);
                clear(PORTF, 5);
                clear(PORTF, 6);
                //m_usb_tx_string("\n");
                break;
            case 2:
                set(PORTF, 4);
                clear(PORTF, 5);
                clear(PORTF, 6);
                //m_usb_tx_string("000\n");
                break;
            case 3:
                set(PORTF, 4);
                set(PORTF, 5);
                clear(PORTF, 6);
                //m_usb_tx_string("000000\n");
                break;
            case 4:
                set(PORTF, 4);
                set(PORTF, 5);
                set(PORTF, 6);
                //m_usb_tx_string("000000000\n");
                break;
            default:
                break;
        }
        
    }
    
}

// --------------------------------------------------
// visualize_serial_init
// --------------------------------------------------
void visualize_serial_init(){
    
    // ** system clock
    // set system clock to 16MHz
    m_clockdivide(0);
    
    // ** subsystem initialization
    m_disableJTAG();    // enable use of F pins
    m_usb_init();       // initialize USB communications
    
    // ** GPIO initialization
    set(DDRF, 4); clear(PORTF, 4);  // low
    set(DDRF, 5); clear(PORTF, 5);  // middle
    set(DDRF, 6); clear(PORTF, 6);  // high
    
    // ** ADC initialization
    // disable ADC subsystem
    clear(ADCSRA, ADEN);
    // set voltage reference to Vcc
    clear(ADMUX, REFS1);
    set(ADMUX, REFS0);
    // set prescaler to /128
    // clocking at 125kHz
    set(ADCSRA, ADPS2);
    set(ADCSRA, ADPS1);
    set(ADCSRA, ADPS0);
    // disable F0's digital input
    set(DIDR0, ADC0D);
    // enable freerunning mode
    set(ADCSRA, ADATE);
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