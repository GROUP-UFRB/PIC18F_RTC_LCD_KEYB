#include <18F4550.h>


#device adc=8

#fuses NOMCLR INTRC_IO

#use delay(clock=16000000)
#use i2c(master,Fast,sda=PIN_B0,scl=PIN_B1)


#include "keyboard.c"
#include "RTC_handler.c"
#include "utils.c"

#define LCD_TYPE 2
#include <LCD4B.c>

//#include <stdio.h>
//#include <string.h>

int8 two_d_keyboard(){
   /*
   Return decimal value
   */
   int8 two_digits = 0;
   /*
   Assuming the key pressioned is a number of only one digits
   Return a number formed by two keys pressioned
   */

   two_digits = 10*keyboard(PIN_A0, PIN_A4); //H0

   lcd_pos_xy(0,0);
   printf(lcd_escreve, "\f %i", two_digits);

   two_digits = two_digits+keyboard(PIN_A0, PIN_A4);//H0+L = HL

   lcd_pos_xy(0,0);
   printf(lcd_escreve, "\f %i", two_digits);

   return two_digits;
}

void set_datetime(){
   /*
   The datetime is provided by the used from keyboard.
   */
   //ds1307_write(0, Dec2BCD(two_d_keyboard())); //Seconds
   lcd_pos_xy(0,0);
   printf(lcd_escreve, "\f Write Minutes");
   delay_ms(100);

   ds1307_write(1, Dec2BCD(two_d_keyboard())); //Minutes

   lcd_pos_xy(0,0);
   printf(lcd_escreve, "\f Write Hours");
   delay_ms(100);

   ds1307_write(2, Dec2BCD(two_d_keyboard())); //Hours
   //ds1307_write(3, Dec2BCD(two_d_keyboard())); //day = day of the week with range start at 1 to 7
   //ds1307_write(4, Dec2BCD(two_d_keyboard())); //date = day of month: 1-31 
   //ds1307_write(5, Dec2BCD(two_d_keyboard())); //month: 1-12
   //ds1307_write(6, Dec2BCD(two_d_keyboard())); //year: 0-99
   ds1307_write(0, 0);
}

void set_alarm_BCD(int8 *minutes, int8 *hours) {
   lcd_pos_xy(0,0);
   printf(lcd_escreve, "\f Set Alarm");
   delay_ms(500);

   lcd_pos_xy(0,0);
   printf(lcd_escreve, "\f Write minutes");
   *minutes = Dec2BCD(two_d_keyboard());
   *hours = Dec2BCD(two_d_keyboard());
}

void main()
{
   int8 minutes_a, hours_a;
   
   int8 seconds, minutes, hours, days, date, months, year;
   hours = 14;
   minutes = 38;
   seconds = 30;

   minutes_a = Dec2BCD(54);
   hours_a = Dec2BCD(15);

   setup_oscillator(OSC_16MHZ);                      // Set internal oscillator to 16MHz
   setup_adc_ports(NO_ANALOGS);
   port_b_pullups(TRUE);// Enable PORTB pull-ups:
   /*
    port_b_pullups(TRUE): The pins used in PORTB will be connected to VCC with a resistence between them. So, the default value is 1. 
   */

   set_tris_a(0xf); //00001111: D0, D1, D2, D3 as input ports
   output_b(0);
   
   lcd_ini();

   set_tris_c(0x0);//set C0 as output
   output_bit(PIN_C0, 0); //alarm pin
   while(1){

      /*User interaction hundler */
      if (input(PIN_E0)){
         while(input(PIN_E0)); //wait for PIN back to default.

         set_datetime();
      }else if (input(PIN_E1)) {
         while(input(PIN_E1));

         set_alarm_BCD(minutes_a, hours_a);
      }

      delay_ms(100);
      ds1307_read(&seconds, &minutes, &hours, &days, &date, &months, &year);//get date and time
      //ds1307_read();

      if (minutes == minutes_a && hours == hours_a){//alarm
         output_toggle(PIN_C0); // toggle while the minutes and hours is equals
      }

      lcd_pos_xy(0,0);
      printf(lcd_escreve, "\fTIME: %i:%i:%i", BCDtoDecimal(hours), BCDtoDecimal(minutes), BCDtoDecimal(seconds)); //write current time
   }

}
