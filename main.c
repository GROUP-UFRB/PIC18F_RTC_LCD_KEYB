#include <18F4550.h>

#device adc=8

#fuses NOMCLR INTRC_IO

#use delay(clock=16000000)
//#use fast_io(B)
#use i2c(master,Fast,sda=PIN_B0,scl=PIN_B1)
//#use I2C(master, I2C1, FAST = 100000)

#include "keyboard.c"
#include "RTC_handler.c"
#include "utils.c"

int8 two_d_keyboard(){
   /*
   Assuming the key pressioned is a number of only one digits
   Return a number formed by two keys pressioned
   */
   int8 two_digits = 0;
   two_digits = 10*keyboard(); //H0

   output_bit(PIN_D7, 1); //Signal to tell if the two digits was captured or not
   delay_ms(100);
   output_bit(PIN_D7, 0);

   two_digits = two_digits+keyboard();//H0+L = HL

   output_bit(PIN_D7, 1); //Signal to tell if the two digits was captured or not
   delay_ms(100);
   output_bit(PIN_D7, 0);

   return two_d_keyboard
}

void set_datetime(){
   /*
   The datetime is provided by the used from keyboard.
   */

   //Set date time from keyboard
   ds1307_write(0, Dec2BCD(two_d_keyboard())); //seconds
   ds1307_write(1, Dec2BCD(two_d_keyboard())); //minute
   ds1307_write(2, Dec2BCD(two_d_keyboard())); //hour
   ds1307_write(3, Dec2BCD(two_d_keyboard())); //day = day of the week with range start at 1 to 7
   ds1307_write(4, Dec2BCD(two_d_keyboard())); //date = day of month: 1-31 
   ds1307_write(5, Dec2BCD(two_d_keyboard())); //month: 1-12
   ds1307_write(6, Dec2BCD(two_d_keyboard())); //year: 0-99
   ds1307_write(0, 0); //only Jesus knows
}

void main()
{

   setup_oscillator(OSC_16MHZ);                      // Set internal oscillator to 8MHz
   setup_adc_ports(NO_ANALOGS);
   port_b_pullups(TRUE);// Enable PORTB pull-ups:
   /*
    port_b_pullups(TRUE): The pins used in PORTB will be connected to VCC with a resistence between them. So, the default value is 1. 
   */

   set_tris_d(0xf); //00001111: D0, D1, D2, D3 as input ports

   output_b(0);

   while(1){
      //ds1307_read(&second, &minute, &hour, &day, &date, &month, &year);
      //ds1307_read();
      if (input(PIN_D7)){
         while(input(PIN_D7)); //wait for PIN back to default.

         set_datetime();
      }
      delay_ms(100);
   }

}
