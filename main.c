/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program STM32F446RE-05-LCDmsg_8bit
  ******************************************************************************
  * The LCD controller is connected to the Nucleo-F446RE as follows
  *
  * PC0-PC7 for LCD D0-D7, respectively
  * PB5 for LCD R/S
  * PB6 for LCD R/W
  * PB7 for LCD EN
  */

#include "stm32f4xx.h"

#define RS 0X20			/* PB5 mask for register select */
#define RW 0X40			/*PB6 mask for read/write */
#define EN 0X80			/*PB7 mask for enable */

void delayMs(int n);
void LCD_command(unsigned char command);
void LCD_data(char data);
void LCD_init(void);
void PORTS_init(void);

int main(void) {
	/* initialise LCD controller */
	LCD_init();

	while(1) {
        /* write "Start" on LCD */
		LCD_data('S');
		LCD_data('T');
		LCD_data('M');
		LCD_data('3');
		LCD_data('2');
		delayMs(5000); // test from 1000 to 5000

		/* clear LCD display */
		LCD_command(1);
		delayMs(10); // from 500 to 10
	}
}

/* initialise port pins then initiliase LCD controller */
void LCD_init(void) {
	PORTS_init();

	delayMs(30);			/* initialisation sequence */
	LCD_command(0X30);
	delayMs(10);
	LCD_command(0X30);
	delayMs(1);
	LCD_command(0X30);

	LCD_command(0X38);		/* set 8-bit data, 2-line, 5x7 font */
    LCD_command(0X06);		/* move cursor right after each char */
    LCD_command(0X01);		/* clear screen, move cursor to home */
    LCD_command(0X0F);		/* turn on display, cursor blinking */
}

void PORTS_init(void) {
	RCC->AHB1ENR |= 0X06;		/* enable GPIOB/C clock */

    /* PB5 for LCD R/S */
	/* PB6 for LCD R/W */
	/* PB7 for LCD EN */
	GPIOB->MODER &= ~0X0000FC00;		/* clear pin mode */
	GPIOB->MODER |= 0X00005400;			/* set pin output mode */
	GPIOB->BSRR = 0X00C00000;			/* turn off EN and R/W */

    /* PC0-PC7 for LCD D0-D7, respectively. */
	GPIOC->MODER &= ~0X0000FFFF;		/* clear pin mode */
	GPIOC->MODER |= 0X00005555;			/* set pin output mode */

}

void LCD_command(unsigned char command) {
	GPIOB->BSRR = (RS | RW) << 16;		/* RS = 0, R/W = 0 */
	GPIOC->ODR = command;				/* put command on data bus */
	GPIOB->BSRR = EN;					/* pulse E high */
	delayMs(1);
	GPIOB->BSRR = EN << 16;			/* clear E */

	if (command < 4){
		delayMs(2);						/* command 1 and 2 needs up to 1.6 ms */
	}
	else {
		delayMs(1);						/* all others 40 us */
	}
}

void LCD_data(char data) {
	GPIOB->BSRR = RS;				/* RS = 1 */
	GPIOB->BSRR = RW << 16;			/* R/W = 0 */
	GPIOB->BSRR = EN;				/* pulse E high */
	delayMs(1);
	GPIOC->ODR = data;				/* put data on data bus */

	delayMs(0);
	GPIOB->BSRR = EN << 16;			/* clear E */

	delayMs(1);
}

/* delay n milliseconds (8 MHz CPU clock) check with oscilloscope) */
void delayMs(int n) {
	int i;
	for(; n > 0; n--) {
		for(i = 0; i < 1598; i++);
	}
}

