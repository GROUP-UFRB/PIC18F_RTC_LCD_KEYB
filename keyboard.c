
int8 keypad_scanner()  
{      
    int D0_, D1_, D2_, D3_;
    
    delay_ms(15);
    output_low(PIN_B0);
    
    D0_ = input(PIN_D0);
    D1_ = input(PIN_D1);
    D2_ = input(PIN_D2);
    D3_ = input(PIN_D3);
    
    if ( D3_ == 0 ) { delay_ms(100); while( input(PIN_D3) == 0 ); return 1; }
    else if ( D2_ == 0 ) {delay_ms(100); while( input(PIN_D2) == 0 ); return 4; }
    else if ( D1_ == 0 ) {delay_ms(100); while( input(PIN_D1) == 0 ); return 7; }
    else if ( D0_ == 0 ) {delay_ms(100); while( input(PIN_D0) == 0 ); return 11; } //*
    
    output_high(PIN_B0);
    delay_ms(15);
    output_low(PIN_B1);
    
    D0_ = input(PIN_D0);
    D1_ = input(PIN_D1);
    D2_ = input(PIN_D2);
    D3_ = input(PIN_D3);
    
    if ( D3_ == 0 ) {delay_ms(100); while( input(PIN_D3) == 0 ); return 2; }
    else if ( D2_ == 0 ) {delay_ms(100); while( input(PIN_D2) == 0 ); return 5; }
    else if ( D1_ == 0 ) {delay_ms(100); while( input(PIN_D1) == 0 ); return 8; }
    else if ( D0_ == 0 ) {delay_ms(100); while( input(PIN_D0) == 0 ); return 0; }
    
    output_high(PIN_B1);
    delay_ms(15);
    output_low(PIN_B2);
    
    D0_ = input(PIN_D0);
    D1_ = input(PIN_D1);
    D2_ = input(PIN_D2);
    D3_ = input(PIN_D3);
    
    if ( D3_ == 0 ) {delay_ms(100); while( input(PIN_D3) == 0 ); return 3; }
    else if ( D2_ == 0 ) {delay_ms(100); while( input(PIN_D2) == 0 ); return 6; }
    else if ( D1_ == 0 ) {delay_ms(100); while( input(PIN_D1) == 0 ); return 9; }
    else if ( D0_ == 0 ) {delay_ms(100); while( input(PIN_D0) == 0 ); return 12; } //#
    
    output_high(PIN_B2);
        
    return -1;                   
}

int8 switch_press_scan()                       // Get key from user
{
    int8 key = -1;              // Assume no key pressed
    while(key==-1){ // Wait untill a key is pressed
        key = keypad_scanner();   // Scan the keys again and again
    }
    return key;                  //when key pressed then return its value
}

