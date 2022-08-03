#include <18F4550.h>


#device adc=8

#fuses NOMCLR INTRC_IO

#use delay(clock=16000000)
//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
//#use fast_io(B)
#use i2c(master,Fast,sda=PIN_B0,scl=PIN_B1)
//#use I2C(master, I2C1, FAST = 100000)


#include "keyboard.c"
#include "RTC_handler.c"
#include "utils.c"

#define LCD_TYPE 2
#include <LCD4B.c>

//#include <stdio.h>
//#include <string.h>

int8 two_d_keyboard(){
   /*
   Assuming the key pressioned is a number of only one digits
   Return a number formed by two keys pressioned
   */
   int8 two_digits = 0;
   two_digits = 10*keyboard(PIN_A0, PIN_A4); //H0

   output_bit(PIN_E1, 1); //Signal to tell if the two digits was captured or not
   delay_ms(100);
   output_bit(PIN_E1, 0);

   two_digits = two_digits+keyboard(PIN_A0, PIN_A4);//H0+L = HL

   output_bit(PIN_E1, 1); //Signal to tell if the two digits was captured or not
   delay_ms(100);
   output_bit(PIN_E1, 0);

   return two_digits;
}

void set_datetime(){
   /*
   The datetime is provided by the used from keyboard.
   */

   ds1307_write(0, Dec2BCD(two_d_keyboard())); //seconds
   ds1307_write(1, Dec2BCD(two_d_keyboard())); //minute
   ds1307_write(2, Dec2BCD(two_d_keyboard())); //hour
   //ds1307_write(3, Dec2BCD(two_d_keyboard())); //day = day of the week with range start at 1 to 7
   //ds1307_write(4, Dec2BCD(two_d_keyboard())); //date = day of month: 1-31 
   //ds1307_write(5, Dec2BCD(two_d_keyboard())); //month: 1-12
   //ds1307_write(6, Dec2BCD(two_d_keyboard())); //year: 0-99
   ds1307_write(0, 0); //only Jesus knows
}

void main()
{

   int seconds, minutes, hours, days, date, months, year;
   hours = 14;
   minutes = 38;
   seconds = 30;

   setup_oscillator(OSC_16MHZ);                      // Set internal oscillator to 8MHz
   setup_adc_ports(NO_ANALOGS);
   port_b_pullups(TRUE);// Enable PORTB pull-ups:
   /*
    port_b_pullups(TRUE): The pins used in PORTB will be connected to VCC with a resistence between them. So, the default value is 1. 
   */

   set_tris_a(0xf); //00001111: D0, D1, D2, D3 as input ports

   output_b(0);

   /*
   LCD interaction
   */
   lcd_ini();

   while(1){
      
      if (input(PIN_E0)){
         while(input(PIN_E0)); //wait for PIN back to default.

         set_datetime();
      }
      delay_ms(100);

      ds1307_read(&seconds, &minutes, &hours, &days, &date, &months, &year);
      //ds1307_read();

      lcd_pos_xy(0,0);
      printf(lcd_escreve, "\fTIME: %i:%i:%i", BCDtoDecimal(hours), BCDtoDecimal(minutes), BCDtoDecimal(seconds));
   }

}
