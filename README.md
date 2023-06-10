# STM32F446RE
Low level programming of development board Nucleo STM32F446RE.

*** THIS IS A LEARNING PROJECT *** HANDLE WITH CAUTION ***

This repo contains C programs for several ST Microelectronics Nucleo boards. They are mostly based on books and tutorials. Therefore, they retain the copyrights.
Modifications are done to either correct errors or adapt to available hardware at the time of creation.

LCDmsg1:
I did not have the LCD display used in the demonstration, so I used one provided with an Arduino kit. However, for simplicity it is controlled
using a header file I did not want to use, as it defeats the learning purpose of this exercise.
Therefore, I found and read the documentation from the display's manufacturer. 
It was clear that This diplay needs additional power supply to turn it on and control its contrast. In addition, D0-D7 are in reverse order.
However, the mayor change to the code was the the 1602A requires an overlap between the ENABLE signal and the DATA to be written, while the authors
of the tutorial worked with a display that required to pull E low before writing any data.
This microproject has told me to overcome novel problems, find solutions on my own and translate hardware documentation into working C code.




