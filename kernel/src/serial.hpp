#ifndef OS_SERIAL_HPP
#define OS_SERIAL_HPP

int init_serial(void);
int serial_received(void);
char read_serial(void);
int is_transmit_empty(void);
void write_serial(char c);
void write_serial_line(char *str);

#endif
