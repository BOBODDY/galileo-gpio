/**
 * userlcd.c - Userspace LCD functions
 *
 * author: Nick Mathews
 */
 
#include "userlcd.h"
#include "usergpio.h"

static int data_pins[11] = {D0, D1, D2, D3, D4, D5, D6, D7, RS, E};

void delay(int milliseconds)
{
  long time_to_delay = milliseconds * 1000000;
  struct timespec delay_o = {0, time_to_delay}; // uses nanoseconds, I need microseconds
  nanosleep(&delay_o, NULL);
}

char *itoa(int val)
{
  char *buf = malloc(sizeof(char) * 4);
  sprintf(buf, "%d", val);
  return buf;
}

void dataByte(uint8_t data)
{
  uint8_t i;

  for (i=0; i<8; ++i)
  {
    if ((data & 1) == 1)
    {
      gpio_set_high(itoa(data_pins[i]));
    }
    else
    {
      gpio_set_low(itoa(data_pins[i]));
    }
    data >>= 1;
  }
}

void putCommand(uint8_t command)
{
  gpio_set_low(itoa(RS)); gpio_set_high(itoa(E));
  dataByte(command);      delay(1);   //sleep 1ms
  gpio_set_low(itoa(E));  delay(1);   //sleep 1ms
}

void lcdPosition(int x, int y)
{
  uint8_t l2 = LCD_DGRAM;

  if (y == 1)
  {
    l2 |= 0x40;
  }

  l2 += x;
  putCommand(l2);
}

void lcdPutchar(uint8_t data)
{
  gpio_set_high(itoa(RS)); gpio_set_high(itoa(E));

  dataByte(data);         delay(1);   // sleep 1ms
  gpio_set_low(itoa(E));  delay(1);   // sleep 1ms
}

void lcdPuts(char *string)
{
  while (*string)
  {
    lcdPutchar(*string++);
  }
}

void setup()
{
  uint8_t i;

  for (i=0; i<8; ++i)
  {
    gpio_init(itoa(data_pins[i]));
    gpio_set_direction(itoa(data_pins[i]), "out");
    gpio_set_low(itoa(data_pins[i]));
  }

  gpio_init(itoa(RS));
  gpio_set_direction(itoa(RS), "out");
  gpio_set_low(itoa(RS));

  gpio_init(itoa(E));
  gpio_set_direction(itoa(E), "out");
  gpio_set_high(itoa(E)); delay(35);                          //sleep 35ms

  putCommand(LCD_FUNC | LCD_FUNC_DL | LCD_FUNC_N); delay(5);  //sleep 5ms
  putCommand(LCD_FUNC | LCD_FUNC_DL | LCD_FUNC_N); delay(5);  //sleep 5ms
  putCommand(LCD_FUNC | LCD_FUNC_DL | LCD_FUNC_N); delay(5);  //sleep 5ms

  putCommand(LCD_ON_OFF | LCD_ON_OFF_D); delay(2);            //sleep 2ms
  putCommand(LCD_ENTRY | LCD_ENTRY_ID);  delay(2);            //sleep 2ms
  putCommand(LCD_CDSHIFT | LCD_CDSHIFT_RL); delay(2);         //sleep 2ms
  putCommand(LCD_CLEAR); delay(2);                            //sleep 5ms
}

void clean_up()
{
  uint8_t i;
  for (i=0; i<11; ++i)
  {
    gpio_close(itoa(data_pins[i]));
  }
}

