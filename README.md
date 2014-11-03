galileo-gpio
============

Library for using GPIO functions on an Intel Galileo board

I adapted the code presented in this site:
https://projects.drogon.net/raspberry-pi/gpio-examples/lcd-interface/
It was written for a Raspberry Pi and uses Arduino libraries (digitalWrite(), pinMode()). I switched those to use my own GPIO library, which acts as a wrapper for writing to sysfs. 

Usage:
Include the userlcd header.
Basic process for writing text:
    setup()
    lcdPosition(0, 1)
    lcdPuts("your_text_here")
    clean_up()

Possible changes/TODO:
1. Add option for 4-bit mode so not as many wires are necessary
2. Port to other languages
3. Allow easier configuration for pin numbers. Parameters to allow a custom setup.
4. Mapping between pin numbers on the board to the GPIO numbers.
5. Auto-wrapping text longer than 16 characters