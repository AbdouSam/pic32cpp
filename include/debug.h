#ifndef DEBUG_H
#define DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

void debug_init(void);

void debug_putc(char c);

int debug_print(const char * fmt, ...);


#ifdef __cplusplus
}
#endif

#endif /* DEBUG_H */