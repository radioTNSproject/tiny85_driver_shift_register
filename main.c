#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>
//#include <shift_register_8.h>

#define DATA PB0
#define LATCH PB2
#define CLOCK PB3

unsigned char push8(unsigned char);

int main(void)
{
    DDRB |= (1 << DATA);
    DDRB |= (1 << LATCH);
    DDRB |= (1 << CLOCK);

    uint8_t test =0;
    test++;
    
    unsigned char sample = 15;
    while(1)
    {
        sample = 1;
        for(int i = 0; i <= 7; i++)
        {
            push8(sample);
            sample = sample*2 + 1; //bar
            //sample++; //incremental
            //sample *= 2; //chenillard
            _delay_ms(50);
            
        }
    }
return 0;
}

unsigned char push8(unsigned char bte)
{            
    PORTB &= ~(1 << LATCH); // Let's lock the output

    for(int idx = 0; idx <= 7; idx++)
    {
        PORTB &= ~(1 << CLOCK); // Clock to low state before adding data

        if (bte & 0b00000001)
            PORTB |= (1 << DATA);  // if LSB is equal to 1 let's add it to port B
        else
            PORTB &= ~(1 << DATA);  // otherwise, we put to 0

        PORTB |= (1 << CLOCK);  // Clock set to high, edge will push the bit
        bte >>= 1;              // Shift to next bit in the 8 bit given
    }
    PORTB |= (1 << LATCH);      // When all bits have been sent, release the lock
    return 1;
}