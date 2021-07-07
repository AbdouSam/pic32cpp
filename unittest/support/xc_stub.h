#ifndef XC_STUB_H
#define XC_STUB_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Stub for GPIO register to unit test the module
 */
#if (PIC32_PIN_COUNT != 64)

extern volatile uint32_t PORTA;
extern volatile uint32_t TRISA;
extern volatile uint32_t LATA;
extern volatile uint32_t ODCA;
extern volatile uint32_t ANSELA;
extern volatile uint32_t ANSELC;
extern volatile uint32_t ANSELF;

#endif

extern volatile uint32_t PORTB;
extern volatile uint32_t TRISB;
extern volatile uint32_t LATB;
extern volatile uint32_t ODCB;
extern volatile uint32_t ANSELB;
extern volatile uint32_t PORTC;
extern volatile uint32_t TRISC;
extern volatile uint32_t LATC;
extern volatile uint32_t ODCC;
extern volatile uint32_t PORTD;
extern volatile uint32_t TRISD;
extern volatile uint32_t LATD;
extern volatile uint32_t ODCD;
extern volatile uint32_t PORTE;
extern volatile uint32_t TRISE;
extern volatile uint32_t LATE;
extern volatile uint32_t ODCE;
extern volatile uint32_t ANSELE;
extern volatile uint32_t PORTF;
extern volatile uint32_t TRISF;
extern volatile uint32_t LATF;
extern volatile uint32_t ODCF;
extern volatile uint32_t PORTG;
extern volatile uint32_t TRISG;
extern volatile uint32_t LATG;
extern volatile uint32_t ODCG;
extern volatile uint32_t ANSELG;

#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100))

extern volatile uint32_t PORTH;
extern volatile uint32_t TRISH;
extern volatile uint32_t LATH;
extern volatile uint32_t ODCH;
extern volatile uint32_t ANSELH   ;
extern volatile uint32_t ANSELJ   ;
extern volatile uint32_t PORTJ;
extern volatile uint32_t TRISJ;
extern volatile uint32_t LATJ;
extern volatile uint32_t ODCJ;
extern volatile uint32_t ANSELD;

#endif

#if ((PIC32_PIN_COUNT != 64) && (PIC32_PIN_COUNT != 100) && \
  (PIC32_PIN_COUNT != 124))

extern volatile uint32_t PORTK;
extern volatile uint32_t TRISK;
extern volatile uint32_t LATK;
extern volatile uint32_t ODCK;

#endif



extern volatile uint32_t RPD2R;
extern volatile uint32_t RPG8R;
extern volatile uint32_t RPF4R;
extern volatile uint32_t RPD10R;
extern volatile uint32_t RPF1R;
extern volatile uint32_t RPB9R;
extern volatile uint32_t RPB10R;
extern volatile uint32_t RPC14R;
extern volatile uint32_t RPB5R;

#if (PIC32_PIN_COUNT != 64)
extern volatile uint32_t RPC1R;
extern volatile uint32_t RPD14R;
extern volatile uint32_t RPG1R;
extern volatile uint32_t RPA14R;
#endif

#if ((PIC32_PIN_COUNT != 100) && (PIC32_PIN_COUNT != 64))
extern volatile uint32_t RPD6R;
#endif

extern volatile uint32_t RPD3R;
extern volatile uint32_t RPG7R;
extern volatile uint32_t RPF5R;
extern volatile uint32_t RPD11R;
extern volatile uint32_t RPF0R;
extern volatile uint32_t RPB1R;
extern volatile uint32_t RPE5R;
extern volatile uint32_t RPC13R;
extern volatile uint32_t RPB3R;

#if (PIC32_PIN_COUNT != 64)
extern volatile uint32_t RPC4R;
extern volatile uint32_t RPD15R;
extern volatile uint32_t RPG0R;
extern volatile uint32_t RPA15R;
#endif

#if ((PIC32_PIN_COUNT != 100) && (PIC32_PIN_COUNT != 64))
extern volatile uint32_t RPD7R;
#endif

extern volatile uint32_t RPD9R;
extern volatile uint32_t RPG6R;
extern volatile uint32_t RPB8R;
extern volatile uint32_t RPB15R;
extern volatile uint32_t RPD4R;
extern volatile uint32_t RPB0R;
extern volatile uint32_t RPE3R;
extern volatile uint32_t RPB7R;

#if (PIC32_PIN_COUNT != 64)
extern volatile uint32_t RPF12R;
extern volatile uint32_t RPD12R;
extern volatile uint32_t RPF8R;
extern volatile uint32_t RPC3R;
extern volatile uint32_t RPE9R;
#endif

extern volatile uint32_t RPD1R;
extern volatile uint32_t RPG9R;
extern volatile uint32_t RPB14R;
extern volatile uint32_t RPD0R;
extern volatile uint32_t RPB6R;
extern volatile uint32_t RPD5R;
extern volatile uint32_t RPB2R;
extern volatile uint32_t RPF3R;

#if (PIC32_PIN_COUNT != 64)
extern volatile uint32_t RPF13R;
extern volatile uint32_t RPF2R;
extern volatile uint32_t RPC2R;
extern volatile uint32_t RPE8R;
#endif

/* UART */

extern volatile uint32_t U1MODE;
extern volatile uint32_t U2MODE;
extern volatile uint32_t U3MODE;
extern volatile uint32_t U4MODE;
extern volatile uint32_t U5MODE;
extern volatile uint32_t U6MODE;
extern volatile uint32_t U1STA;
extern volatile uint32_t U2STA;
extern volatile uint32_t U3STA;
extern volatile uint32_t U4STA;
extern volatile uint32_t U5STA;
extern volatile uint32_t U6STA;
extern volatile uint32_t U1BRG;
extern volatile uint32_t U2BRG;
extern volatile uint32_t U3BRG;
extern volatile uint32_t U4BRG;
extern volatile uint32_t U5BRG;
extern volatile uint32_t U6BRG;
extern volatile uint32_t U1RXREG;
extern volatile uint32_t U2RXREG;
extern volatile uint32_t U3RXREG;
extern volatile uint32_t U4RXREG;
extern volatile uint32_t U5RXREG;
extern volatile uint32_t U6RXREG;
extern volatile uint32_t U1TXREG;
extern volatile uint32_t U2TXREG;
extern volatile uint32_t U3TXREG;
extern volatile uint32_t U4TXREG;
extern volatile uint32_t U5TXREG;
extern volatile uint32_t U6TXREG;

extern volatile uint32_t U1RXR;
extern volatile uint32_t U2RXR;
extern volatile uint32_t U3RXR;
extern volatile uint32_t U4RXR;
extern volatile uint32_t U5RXR;
extern volatile uint32_t U6RXR;

/* INTERRUPT */

extern volatile uint32_t IFS0;
extern volatile uint32_t IFS1;
extern volatile uint32_t IFS2;
extern volatile uint32_t IFS3;
extern volatile uint32_t IFS4;
extern volatile uint32_t IFS5;
extern volatile uint32_t IFS6;
extern volatile uint32_t IEC0;
extern volatile uint32_t IEC1;
extern volatile uint32_t IEC2;
extern volatile uint32_t IEC3;
extern volatile uint32_t IEC4;
extern volatile uint32_t IEC5;
extern volatile uint32_t IEC6;
extern volatile uint32_t IPC0;
extern volatile uint32_t IPC1;
extern volatile uint32_t IPC2;
extern volatile uint32_t IPC3;
extern volatile uint32_t IPC4;
extern volatile uint32_t IPC5;
extern volatile uint32_t IPC6;
extern volatile uint32_t IPC7;
extern volatile uint32_t IPC8;
extern volatile uint32_t IPC9;
extern volatile uint32_t IPC10;
extern volatile uint32_t IPC11;
extern volatile uint32_t IPC12;
extern volatile uint32_t IPC13;
extern volatile uint32_t IPC14;
extern volatile uint32_t IPC15;
extern volatile uint32_t IPC16;
extern volatile uint32_t IPC17;
extern volatile uint32_t IPC18;
extern volatile uint32_t IPC19;
extern volatile uint32_t IPC20;
extern volatile uint32_t IPC21;
extern volatile uint32_t IPC22;
extern volatile uint32_t IPC23;
extern volatile uint32_t IPC24;
extern volatile uint32_t IPC25;
extern volatile uint32_t IPC26;
extern volatile uint32_t IPC27;
extern volatile uint32_t IPC28;
extern volatile uint32_t IPC29;
extern volatile uint32_t IPC30;
extern volatile uint32_t IPC31;
extern volatile uint32_t IPC32;
extern volatile uint32_t IPC33;
extern volatile uint32_t IPC34;
extern volatile uint32_t IPC35;
extern volatile uint32_t IPC36;
extern volatile uint32_t IPC37;
extern volatile uint32_t IPC38;
extern volatile uint32_t IPC39;
extern volatile uint32_t IPC40;
extern volatile uint32_t IPC41;
extern volatile uint32_t IPC42;
extern volatile uint32_t IPC43;
extern volatile uint32_t IPC44;
extern volatile uint32_t IPC45;
extern volatile uint32_t IPC46;
extern volatile uint32_t IPC47;
extern volatile uint32_t IPC48;
extern volatile uint32_t IPC49;
extern volatile uint32_t IPC50;
extern volatile uint32_t IPC51;
extern volatile uint32_t IPC52;
extern volatile uint32_t IPC53;

extern volatile uint32_t T1CON;
extern volatile uint32_t T2CON;
extern volatile uint32_t T3CON;
extern volatile uint32_t T4CON;
extern volatile uint32_t T5CON;
extern volatile uint32_t T6CON;
extern volatile uint32_t T7CON;
extern volatile uint32_t T8CON;
extern volatile uint32_t T9CON;
extern volatile uint32_t PR1;
extern volatile uint32_t PR2;
extern volatile uint32_t PR3;
extern volatile uint32_t PR4;
extern volatile uint32_t PR5;
extern volatile uint32_t PR6;
extern volatile uint32_t PR7;
extern volatile uint32_t PR8;
extern volatile uint32_t PR9;
extern volatile uint32_t TMR1;
extern volatile uint32_t TMR2;
extern volatile uint32_t TMR3;
extern volatile uint32_t TMR4;
extern volatile uint32_t TMR5;
extern volatile uint32_t TMR6;
extern volatile uint32_t TMR7;
extern volatile uint32_t TMR8;
extern volatile uint32_t TMR9;

typedef struct INTCONbits_t
{
  volatile uint32_t MVEC;
}INTCONbits_t;

extern volatile INTCONbits_t INTCONbits;

#ifdef __cplusplus
}
#endif

#endif //XC_STUB_H