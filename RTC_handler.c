/*
This module provide some functions to handle the Real Time Clock componet.
Requirements: keyboard.c, utils.c

*/

/*
Part of this code was found on: http://ccspicc.blogspot.com/2016/09/pic18f4550-ds1307-rtcc-alarm-buttons.html
*/

void ds1307_write(unsigned int8 address, data_){
   /*
   Procedure to writing time and date:
      1.Initiate a START condition
      2. Transmit the RTC address 0xD0, with LSB 0 for write mode.
      3. Transmit the address of the register to write (for example 0x00, for write to second register). This transfer sets register pointer inside the DS1307 RTC.
      4. Set the value to the address, setted on step 3. It will increment the address automatically.
      5. Finish the communication with a STOP condition.
   Reference: https://openlabpro.com/guide/interfacing-rtc-ds1307-with-pic18f4550/
   */

   i2c_start();                                   // Start I2C
   i2c_write(0xD0);                               // DS1307 address
   i2c_write(address);                            // Send register address
   i2c_write(data_);                              // Write data to the selected register
   i2c_stop();                                    // Stop I2C
}

void ds1307_read(int *second, int *minute, int *hour, int *day, int* date, int *month, int* year){
   i2c_start();
   i2c_write(0xD0);                             /* slave address with write mode */
   i2c_write(0x00);                                // Start I2C
   i2c_stop();
   i2c_start();
   i2c_write(0xD1);                              // Initialize data read
   *second =i2c_read(1);                          // Read seconds from register 0
   *minute =i2c_read(1);                          // Read minuts from register 1
   *hour = i2c_read(1);                           // Read hour from register 2
   *day = i2c_read(1);                            // Read day from register 3
   *date = i2c_read(1);                           // Read date from register 4
   *month = i2c_read(1);                          // Read month from register 5
   *year = i2c_read(0);                           // Read year from register 6
   i2c_stop();                                   // Stop I2C
}


