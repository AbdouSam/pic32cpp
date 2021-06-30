#ifndef DEBUG_H
#define DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

int debug_print(const char * fmt, ...);

void debug_init(void);

void debug_putc(char c);


#ifdef __cplusplus
}
#endif

#endif /* DEBUG_H */