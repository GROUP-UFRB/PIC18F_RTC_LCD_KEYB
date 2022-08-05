/*4 bits LCD writer and reader.

unknow outhor. The outhor of the original library is unknow.
This library have some changes of the oringal found on internet.
*/

#define EN PIN_E1
#define RS PIN_E2
#define D4 PIN_D4
#define D5 PIN_D5
#define D6 PIN_D6
#define D7 PIN_D7

void lcd_cmd(byte cmd)
{
OUTPUT_BIT(D4,BIT_TEST(cmd,0));
OUTPUT_BIT(D5,BIT_TEST(cmd,1));
OUTPUT_BIT(D6,BIT_TEST(cmd,2));
OUTPUT_BIT(D7,BIT_TEST(cmd,3));
    
OUTPUT_HIGH(EN);
delay_us(50);
OUTPUT_LOW(EN);
}

void lcd_envia_byte(boolean endereco,byte dado)
{
 OUTPUT_LOW(RS);
 OUTPUT_BIT(RS,endereco);
 delay_us(100);
 //delay_ms(1);
 OUTPUT_LOW(EN);
 lcd_cmd(dado>>4);
 lcd_cmd(dado&0x0f);
}

void lcd_pos_xy(byte x, byte y)
{
 byte endereco;
 if (y!=1)
         endereco = 0xC0;
 else
         endereco = 0x80;
 endereco += x-1;         
 lcd_envia_byte(0,endereco);
 }
 
void lcd_escreve(char c)
{
 switch(c)
 {
  case '\f' : lcd_envia_byte(0,1);
              delay_ms(3);
              break;
  case '\n' : 
  case '\r' : lcd_pos_xy(1,2);
              break;
  case '\b' : lcd_envia_byte(0,0x10);
              break;
  default    : lcd_envia_byte(1,c);
              break;
 }
}  

void lcd_ini()
{
 byte conta;
 
 OUTPUT_LOW(RS);
 //OUTPUT_LOW(WR);
 OUTPUT_LOW(EN);
 OUTPUT_LOW(D4);
 OUTPUT_LOW(D5);
 OUTPUT_LOW(D6);
 OUTPUT_LOW(D7);
 
 delay_ms(15);
 
 for (conta=1;conta<=3;conta++)
      {
      lcd_cmd(0x03);
      delay_ms(5);
      }
      
 lcd_cmd(0x02);          //Escreve comando para interface de 4 vias de dados
 
 lcd_envia_byte(0,0x28); //Escreve comando informando LCD de 2 linhas (5X7) em 4bits
 lcd_envia_byte(0,0x0C); //Escreve comando para ligar o display **COM cursor piscante
 
 delay_ms(3);
 
 lcd_envia_byte(0,0x01); //Escreve comando para limpar a mem�ria do LCD
 lcd_envia_byte(0,0x06); //Escreve comando para incrementar automaticamente � direita
 delay_ms(10);
 } 
 


