int8 keyboard(){
    /*  
    Keyboard connected on PORTD of PIC18F4450.
    This function hundles the keyboard interaction.
    */

    //searching for the button pressioned

    int8 value[4][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,9},
        {11,0,12} //11 = *, 12 = #
    };

    /*
    PIN_D0  31768
    PIN_D1  31769
    PIN_D2  31770
    PIN_D3  31771
    PIN_D4  31772
    PIN_D5  31773
    PIN_D6  31774
    PIN_D7  31775
    */
    int8 v = -1;
    int8 i, j;

    while (1) { //Keep running this while none of the key of keyboard is not pressioned

        for(i = 0; i < 4; i = i+1){ //for each line of the keyboard matrix
            
            //set line i. D0 = 31768
            //output_bit(48+i,1);
            for(j = 0; j < 3; j = j+1){ //for each column of the keyboard matrix, at line i
                
                output_bit(PIN_D4+j,1); //turn the column PIN_D4 + j to high state.
                
                if (input(PIN_D0+i)){ //return only if the cell at line i and column j is high 
                    output_bit(PIN_D4+j,0);
                    
                    while (input(PIN_D0) | input(PIN_D1) | input(PIN_D2) | input(PIN_D3)); //wait user stop pressing the key to avoid repeated keys captured
                    return value[i][j]; //get the value
                }
                output_bit(PIN_D4+j,0);
                
            }
            
            output_bit(PIN_D0+i,0);
        }
    }

    
    return v;
}
