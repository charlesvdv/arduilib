#ifndef _REG_TIME_H
#define _REG_TIME_H

unsigned long reg_get_time();
void reg_set_time_interval(int microseconds);
unsigned long reg_increment_time();

#endif
