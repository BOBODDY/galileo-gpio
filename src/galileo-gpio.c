/**
 * usergpio.c - Userspace GPIO sysfs functions
 *
 * authors: Nick Mathews, Daniel Lee
 */

#include "usergpio.h"

static int debug_mode = 0;

int echo_write(char *filename, char *value)
{
    int fd = open(filename, O_WRONLY);
    if (fd == -1)
        printf("\topen: %s\n", strerror(errno));
    int n = strlen(value);
    int n_wrote = write(fd, value, n);

    /* DEBUGGING PRINT */
    if(debug_mode) {
    	printf("wrote %d/%d of %s to %s\n", n_wrote, strlen(value), value, filename);
    }

    if (n_wrote == -1)
        printf("\twrite: %s\n", strerror(errno));
    close(fd);
    return n_wrote;
}

void gpio_init(char *gpio)
{ echo_write("/sys/class/gpio/export", gpio); }

void gpio_close(char *gpio)
{ echo_write("/sys/class/gpio/unexport", gpio); }

void gpio_set_direction(char *gpio, char *dir)
{
    sprintf(f_name, "/sys/class/gpio/gpio%s/direction", gpio);
    echo_write(f_name, dir);
}

void gpio_set_high(char *gpio)
{
    sprintf(f_name, "/sys/class/gpio/gpio%s/value", gpio);
    echo_write(f_name, "1");
}

void gpio_set_low(char *gpio)
{
    sprintf(f_name, "/sys/class/gpio/gpio%s/value", gpio);
    echo_write(f_name, "0");
}

void gpio_set_active_low(char *gpio, char *value)
{
    sprintf(f_name, "/sys/class/gpio/gpio%s/active_low", gpio);
    echo_write(f_name, value);
}

void gpio_set_edge(char *gpio, char *value)
{
    sprintf(f_name, "/sys/class/gpio/gpio%s/edge", gpio);
    echo_write(f_name, value);
}

int gpio_get_value(char *gpio)
{
    sprintf(f_name, "/sys/class/gpio/gpio%s/value", gpio);
    int fd = open(f_name, O_RDWR);
    if (fd == -1)
        return -1;
    char buffer[8];
    read(fd, buffer, strlen(buffer));
    close(fd);
    return atoi(buffer);
}

void gpio_get_direction(char *gpio, char* dir)
{
    sprintf(f_name, "/sys/class/gpio/gpio%s/direction", gpio);
    int fd = open(f_name, O_RDWR);
    if (fd == -1)
        printf("\tgpio_get_direction: %s\n", strerror(errno));
    read(fd, dir, strlen(dir));
    close(fd);
}

void debug_on()
{
    debug_mode = 1;
}

void debug_off()
{
    debug_mode = 0;
}
