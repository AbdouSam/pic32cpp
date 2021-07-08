#ifndef INCLUDED_PIC32_CONFIG_H
#define INCLUDED_PIC32_CONFIG_H

/*64, 100, 124, 144 */
#define PIC32_PIN_COUNT             144

/* TIMERS */

#define TIMER_2_ENABLED             (1)
#define TIMER_3_ENABLED             (0)
#define TIMER_4_ENABLED             (0)
#define TIMER_5_ENABLED             (0)
#define TIMER_6_ENABLED             (0)
#define TIMER_7_ENABLED             (0)
#define TIMER_8_ENABLED             (0)
#define TIMER_9_ENABLED             (0)

#define TIMER1_INT_PRIO  7
#define TIMER2_INT_PRIO  4
#define TIMER3_INT_PRIO  4
#define TIMER4_INT_PRIO  4
#define TIMER5_INT_PRIO  4
#define TIMER6_INT_PRIO  4
#define TIMER7_INT_PRIO  4
#define TIMER8_INT_PRIO  4
#define TIMER9_INT_PRIO  4

#define TIMER_1_FREQ (1000) /* Hz */

/* UART */

#define PIC32_UART_1_ENABLED        (0)
#define PIC32_UART_2_ENABLED        (0)
#define PIC32_UART_3_ENABLED        (0)
#define PIC32_UART_4_ENABLED        (0)
#define PIC32_UART_5_ENABLED        (0)
#define PIC32_UART_6_ENABLED        (0)

/* These priorities sets the Shadow-set registers */
#define UART1_INT_PRIO  1
#define UART2_INT_PRIO  1
#define UART3_INT_PRIO  1
#define UART4_INT_PRIO  5
#define UART5_INT_PRIO  1
#define UART6_INT_PRIO  1

/* Pin mapping (from Datasheet) */

#define PIC32_UART_4_RX_PIN         pinB14
#define PIC32_UART_4_TX_PIN         pinF12

#define UART_ATTACHED_TO_DBG        PIC32_UART_4
#define CONFIG_DEBUG_RS485_PIN      (pinA10)
#define UART_DEBUG_BAUDRATE         (115200)

#endif /* INCLUDED_PIC32_CONFIG_H */