/* Convert BCD to decimal */
char BCDtoDecimal (char val)
{
    char res;
    res = (val & 0x0F) + ((val & 0xF0)>>4)*10;
    return res;
}

/* convert the decimal values to BCD using below function */
char Dec2BCD (char val)
{
    char res;
    res = (val/10) << 4;
    res = res | (val % 10);
    return res;
}