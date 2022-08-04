int8 keyboard(int L0, int C0){
    /*
    L0: Start address of pins to map the lines of keyboard. The next 3 address must be free.
    C0: Start address of pins to map the columns of keyboard. The next 2 must be free. 
    Suggestion: Keyboard connected on PORTA of PIC18F4450.
    This function hundles the keyboard interaction.
    */

    //searching for the button pressioned
    int8 i, j;

    int8 value[4][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,9},
        {11,0,12} //11 = *, 12 = #
    };

    output_bit(C0, 0);
    output_bit(C0+1, 0);
    output_bit(C0+2, 0);

    while (1) { //Keep running this while none of the key of keyboard is not pressioned

        for(i = 0; i < 4; i = i+1){ //for each line of the keyboard matrix
            
            //set line i.
            for(j = 0; j < 3; j = j+1){ //for each column of the keyboard matrix, at line i
                
                output_bit(C0+j,1); //turn the column C0 + j to high state.
                
                if (input(L0+i)){ //return only if the cell at line i and column j is high 
                    output_bit(C0+j,0);
                    
                    while (input(L0) | input(L0+1) | input(L0+2) | input(L0+3)); //wait user stop pressing the key to avoid repeated keys captured
                    return value[i][j]; //get the value
                }
                output_bit(C0+j,0);
                
            }
            
        }
    }

}
