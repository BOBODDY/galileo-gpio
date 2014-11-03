/**
 * usergpio.h - Userspace GPIO sysfs functions
 *
 * authors: Nick Mathews, Daniel Lee
 */


#ifndef USERGPIO_H
#define USERGPIO_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


char f_name[64];


/**
 * Write a value to sysfs
 *
 * @param filename, sysfs name
 * @param value, value to write
 * @return Number of bytes written
 */
extern int echo_write(char *filename, char *value);


/**
 * Write a value to sysfs
 *
 * @param filename, sysfs name
 * @param value, value to write
 * @return Number of bytes written
 */
extern void gpio_init(char *gpio);


/**
 * Close the GPIO port
 * @param gpio, GPIO port to close
 */
extern void gpio_close(char *gpio);


/**
 * Set GPIO port direction
 * @param gpio, GPIO port to write to
 * @param dir, I/O direction to set: "in" for input
 *                                   "out" for output
 */
extern void gpio_set_direction(char *gpio, char *dir);


/**
 * Write a high value to a GPIO output port
 * @param gpio, GPIO port to write to
 */
extern void gpio_set_high(char *gpio);


/**
 * Write a low value to a GPIO output port
 * @param gpio, GPIO port to write to
 */
extern void gpio_set_low(char *gpio);


/**
 * Set active signal state for GPIO output signal
 * @param gpio, GPIO port to write to
 * @param value, state to define high/low: "1" default, active-high
 *                                         "0" invert active logic
 */
extern void gpio_set_active_low(char *gpio, char *value);


/**
 * Select signal edge that will poll on the value file return for GPIO input
 * @param gpio, GPIO port to write to
 * @param value, state to poll value: "none"
 *                                    "rising"
 *                                    "falling"
 */
extern void gpio_set_edge(char *gpio, char *value);


/**
 * Read the value of a GPIO output port
 * @param gpio, GPIO port to read from
 */
extern int gpio_get_value(char *gpio);


/**
 * Read the direction of a GPIO output port
 * @param gpio, GPIO port to read from
 * @param dir, buffer to write result to
 */
extern void gpio_get_direction(char *gpio, char *dir);


#endif /* USERGPIO_H */


