#include "xc_stub.h"
#include "pic32_config.h"

/**
 * Stub for GPIO register to unit test the module
 */

#if (PIC32_PIN_COUNT != 64)

volatile uint32_t PORTA = 0;
volatile uint32_t TRISA = 0;
volatile uint32_t LATA = 0;
volatile uint32_t ANSELA = 0;
volatile uint32_t ANSELC = 0;
volatile uint32_t ANSELF = 0;

#endif

volatile uint32_t PORTB = 0;
volatile uint32_t TRISB = 0;
volatile uint32_t LATB = 0;
volatile uint32_t ANSELB = 0;
volatile uint32_t PORTC = 0;
volatile uint32_t TRISC = 0;
volatile uint32_t LATC = 0;
volatile uint32_t PORTD = 0;
volatile uint32_t TRISD = 0;
volatile uint32_t LATD = 0;
volatile uint32_t PORTE = 0;
volatile uint32_t TRISE = 0;
volatile uint32_t LATE = 0;
volatile uint32_t ANSELE = 0;
volatile uint32_t PORTF = 0;
volatile uint32_t TRISF = 0;
volatile uint32_t LATF = 0;
volatile uint32_t PORTG = 0;
volatile uint32_t TRISG = 0;
volatile uint32_t LATG = 0;
volatile uint32_t ANSELG = 0;

#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100))

volatile uint32_t PORTH = 0;
volatile uint32_t TRISH = 0;
volatile uint32_t LATH = 0;
volatile uint32_t ANSELH    = 0;
volatile uint32_t ANSELJ    = 0;
volatile uint32_t PORTJ = 0;
volatile uint32_t TRISJ = 0;
volatile uint32_t LATJ = 0;
volatile uint32_t ANSELD = 0;

#endif

#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100) && \
  (PIC32_PIN_COUNT != 124))

volatile uint32_t PORTK = 0;
volatile uint32_t TRISK = 0;
volatile uint32_t LATK = 0;

#endif


volatile uint32_t RPD2R = 0;
volatile uint32_t RPG8R = 0;
volatile uint32_t RPF4R = 0;
volatile uint32_t RPD10R = 0;
volatile uint32_t RPF1R = 0;
volatile uint32_t RPB9R = 0;
volatile uint32_t RPB10R = 0;
volatile uint32_t RPC14R = 0;
volatile uint32_t RPB5R = 0;

#if (PIC32_PIN_COUNT != 64)
volatile uint32_t RPC1R = 0;
volatile uint32_t RPD14R = 0;
volatile uint32_t RPG1R = 0;
volatile uint32_t RPA14R = 0;
#endif

#if ((PIC32_PIN_COUNT != 100) && (PIC32_PIN_COUNT != 64))
volatile uint32_t RPD6R = 0;
#endif

volatile uint32_t RPD3R = 0;
volatile uint32_t RPG7R = 0;
volatile uint32_t RPF5R = 0;
volatile uint32_t RPD11R = 0;
volatile uint32_t RPF0R = 0;
volatile uint32_t RPB1R = 0;
volatile uint32_t RPE5R = 0;
volatile uint32_t RPC13R = 0;
volatile uint32_t RPB3R = 0;

#if (PIC32_PIN_COUNT != 64)
volatile uint32_t RPC4R = 0;
volatile uint32_t RPD15R = 0;
volatile uint32_t RPG0R = 0;
volatile uint32_t RPA15R = 0;
#endif

#if ((PIC32_PIN_COUNT != 100) && (PIC32_PIN_COUNT != 64))
volatile uint32_t RPD7R = 0;
#endif

volatile uint32_t RPD9R = 0;
volatile uint32_t RPG6R = 0;
volatile uint32_t RPB8R = 0;
volatile uint32_t RPB15R = 0;
volatile uint32_t RPD4R = 0;
volatile uint32_t RPB0R = 0;
volatile uint32_t RPE3R = 0;
volatile uint32_t RPB7R = 0;

#if (PIC32_PIN_COUNT != 64)
volatile uint32_t RPF12R = 0;
volatile uint32_t RPD12R = 0;
volatile uint32_t RPF8R = 0;
volatile uint32_t RPC3R = 0;
volatile uint32_t RPE9R = 0;
#endif

volatile uint32_t RPD1R = 0;
volatile uint32_t RPG9R = 0;
volatile uint32_t RPB14R = 0;
volatile uint32_t RPD0R = 0;
volatile uint32_t RPB6R = 0;
volatile uint32_t RPD5R = 0;
volatile uint32_t RPB2R = 0;
volatile uint32_t RPF3R = 0;

#if (PIC32_PIN_COUNT != 64)
volatile uint32_t RPF13R = 0;
volatile uint32_t RPF2R = 0;
volatile uint32_t RPC2R = 0;
volatile uint32_t RPE8R = 0;
#endif

/* UART */
volatile uint32_t U1MODE = 0;
volatile uint32_t U2MODE = 0;
volatile uint32_t U3MODE = 0;
volatile uint32_t U4MODE = 0;
volatile uint32_t U5MODE = 0;
volatile uint32_t U6MODE = 0;
volatile uint32_t U1STA = 0;
volatile uint32_t U2STA = 0;
volatile uint32_t U3STA = 0;
volatile uint32_t U4STA = 0;
volatile uint32_t U5STA = 0;
volatile uint32_t U6STA = 0;
volatile uint32_t U1BRG = 0;
volatile uint32_t U2BRG = 0;
volatile uint32_t U3BRG = 0;
volatile uint32_t U4BRG = 0;
volatile uint32_t U5BRG = 0;
volatile uint32_t U6BRG = 0;
volatile uint32_t U1RXREG = 0;
volatile uint32_t U2RXREG = 0;
volatile uint32_t U3RXREG = 0;
volatile uint32_t U4RXREG = 0;
volatile uint32_t U5RXREG = 0;
volatile uint32_t U6RXREG = 0;
volatile uint32_t U1TXREG = 0;
volatile uint32_t U2TXREG = 0;
volatile uint32_t U3TXREG = 0;
volatile uint32_t U4TXREG = 0;
volatile uint32_t U5TXREG = 0;
volatile uint32_t U6TXREG = 0;

volatile uint32_t U1RXR = 0;
volatile uint32_t U2RXR = 0;
volatile uint32_t U3RXR = 0;
volatile uint32_t U4RXR = 0;
volatile uint32_t U5RXR = 0;
volatile uint32_t U6RXR = 0;

/* Interrupts  */

volatile uint32_t IFS0 = 0;
volatile uint32_t IFS1 = 0;
volatile uint32_t IFS2 = 0;
volatile uint32_t IFS3 = 0;
volatile uint32_t IFS4 = 0;
volatile uint32_t IFS5 = 0;
volatile uint32_t IFS6 = 0;
volatile uint32_t IEC0 = 0;
volatile uint32_t IEC1 = 0;
volatile uint32_t IEC2 = 0;
volatile uint32_t IEC3 = 0;
volatile uint32_t IEC4 = 0;
volatile uint32_t IEC5 = 0;
volatile uint32_t IEC6 = 0;
volatile uint32_t IPC0 = 0;
volatile uint32_t IPC1 = 0;
volatile uint32_t IPC2 = 0;
volatile uint32_t IPC3 = 0;
volatile uint32_t IPC4 = 0;
volatile uint32_t IPC5 = 0;
volatile uint32_t IPC6 = 0;
volatile uint32_t IPC7 = 0;
volatile uint32_t IPC8 = 0;
volatile uint32_t IPC9 = 0;
volatile uint32_t IPC10 = 0;
volatile uint32_t IPC11 = 0;
volatile uint32_t IPC12 = 0;
volatile uint32_t IPC13 = 0;
volatile uint32_t IPC14 = 0;
volatile uint32_t IPC15 = 0;
volatile uint32_t IPC16 = 0;
volatile uint32_t IPC17 = 0;
volatile uint32_t IPC18 = 0;
volatile uint32_t IPC19 = 0;
volatile uint32_t IPC20 = 0;
volatile uint32_t IPC21 = 0;
volatile uint32_t IPC22 = 0;
volatile uint32_t IPC23 = 0;
volatile uint32_t IPC24 = 0;
volatile uint32_t IPC25 = 0;
volatile uint32_t IPC26 = 0;
volatile uint32_t IPC27 = 0;
volatile uint32_t IPC28 = 0;
volatile uint32_t IPC29 = 0;
volatile uint32_t IPC30 = 0;
volatile uint32_t IPC31 = 0;
volatile uint32_t IPC32 = 0;
volatile uint32_t IPC33 = 0;
volatile uint32_t IPC34 = 0;
volatile uint32_t IPC35 = 0;
volatile uint32_t IPC36 = 0;
volatile uint32_t IPC37 = 0;
volatile uint32_t IPC38 = 0;
volatile uint32_t IPC39 = 0;
volatile uint32_t IPC40 = 0;
volatile uint32_t IPC41 = 0;
volatile uint32_t IPC42 = 0;
volatile uint32_t IPC43 = 0;
volatile uint32_t IPC44 = 0;
volatile uint32_t IPC45 = 0;
volatile uint32_t IPC46 = 0;
volatile uint32_t IPC47 = 0;
volatile uint32_t IPC48 = 0;
volatile uint32_t IPC49 = 0;
volatile uint32_t IPC50 = 0;
volatile uint32_t IPC51 = 0;
volatile uint32_t IPC52 = 0;
volatile uint32_t IPC53 = 0;


volatile uint32_t T1CON = 0;
volatile uint32_t T2CON = 0;
volatile uint32_t T3CON = 0;
volatile uint32_t T4CON = 0;
volatile uint32_t T5CON = 0;
volatile uint32_t T6CON = 0;
volatile uint32_t T7CON = 0;
volatile uint32_t T8CON = 0;
volatile uint32_t T9CON = 0;
volatile uint32_t PR1 = 0;
volatile uint32_t PR2 = 0;
volatile uint32_t PR3 = 0;
volatile uint32_t PR4 = 0;
volatile uint32_t PR5 = 0;
volatile uint32_t PR6 = 0;
volatile uint32_t PR7 = 0;
volatile uint32_t PR8 = 0;
volatile uint32_t PR9 = 0;
volatile uint32_t TMR1 = 0;
volatile uint32_t TMR2 = 0;
volatile uint32_t TMR3 = 0;
volatile uint32_t TMR4 = 0;
volatile uint32_t TMR5 = 0;
volatile uint32_t TMR6 = 0;
volatile uint32_t TMR7 = 0;
volatile uint32_t TMR8 = 0;
volatile uint32_t TMR9 = 0;

volatile INTCONbits_t INTCONbits;