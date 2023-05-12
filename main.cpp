#include "mbed.h"

#define BUF_SIZE 64
 
// input ports
DigitalIn         in_BUSY     (PA_9);    
InterruptIn       irq_BUSY    (PA_9);    
DigitalIn         in_D_OUT    (PA_10);    
InterruptIn       irq_D_OUT   (PA_10);
DigitalIn         in_SEL_2    (PB_6); 
DigitalIn         in_SEL_1    (PB_1);
DigitalIn         in_D_IN     (PA_1); 
DigitalIn         in_X_OUT    (PA_0);     
InterruptIn       irq_X_OUT   (PA_0);
// output ports  
DigitalOut        out_SEL_2   (PA_8); 
DigitalOut        out_SEL_1   (PA_11);   
DigitalOut        out_ACK     (PB_7);  
DigitalOut        out_D_OUT   (PA_12); 
DigitalOut        out_D_IN    (PB_0);     

// others
DigitalOut        infoLed     (LED1);

// Note - bouncing could trigger multiple events
InterruptIn       user_BTN    (PB_4);

RawSerial         pc(USBTX, USBRX);
//InterruptIn     btn(USER_BUTTON);
Timer           mainTime;

volatile int bufPosition;
volatile char buffer[BUF_SIZE];
volatile int timediff;

void onCharReceived()
{
    char c = pc.getc();
    // echo
    pc.putc(c);
    // save it to a ring buffer
    buffer[ ((bufPosition++)%BUF_SIZE) ] = c;

    if (c == 'k'){
        out_ACK = 1;
        wait(0.5);
        out_ACK = 0;
    } else {    
        infoLed = !infoLed;
        out_D_OUT = infoLed; 
        out_D_IN  = infoLed;      
        out_SEL_1 = infoLed;    
        out_SEL_2 = infoLed; 
        wait_us(500);
    }

}

void btnRaised() 
{
    user_BTN.rise(NULL); // debouncing
    wait_us(500);

    infoLed = !infoLed;
    out_D_OUT = infoLed; 
    out_D_IN  = infoLed;      
    out_SEL_1 = infoLed;    
    out_SEL_2 = infoLed; 
    
    user_BTN.rise(callback(btnRaised));

};

void in_D_OUT_Fall()
{
    pc.printf ("%d in_D_OUT Fall: ", mainTime.read_us());
    char c = (     in_SEL_1 
                + (in_SEL_2 <<1) + 
                + (in_D_OUT <<2) 
                + (in_D_IN  <<3) );
    pc.printf (" %2x\n", c);
}
 
void in_D_OUT_Rise()
{
    pc.printf ("%d in_D_OUT Rise: ", mainTime.read_us());
    char c = (     in_SEL_1 
                + (in_SEL_2 <<1) + 
                + (in_D_OUT <<2) 
                + (in_D_IN  <<3) );
    pc.printf (" %2x\n", c);
}

void in_BUSY_Fall()
{
    pc.printf ("%d in_BUSY Fall: ", mainTime.read_us());
    char c = (     in_SEL_1 
                + (in_SEL_2 <<1) + 
                + (in_D_OUT <<2) 
                + (in_D_IN  <<3) );
    pc.printf (" %2x\n", c);
}
 
void in_BUSY_Rise()
{
    pc.printf ("%d in_BUSY Rise: ", mainTime.read_us());
    char c = (     in_SEL_1 
                + (in_SEL_2 <<1) + 
                + (in_D_OUT <<2) 
                + (in_D_IN  <<3) );
    pc.printf (" %2x\n", c);
}
 
int main()
{
    pc.baud ( 9600 );

    uint8_t i = 20;
    while (i--) { infoLed =! infoLed; wait_ms(20); }
    pc.printf ( "test init\n" );

    mainTime.reset();
    mainTime.start();

    // reset outputs
    out_ACK = 0;
    // out_D_OUT = 0;
    out_D_IN  = 0;     
    out_SEL_2 = 0;     
    out_SEL_1 = 0;

    // default inputs: pull-down
    in_BUSY.mode(PullDown);
    in_X_OUT.mode(PullDown);
    in_D_OUT.mode( PullDown );
    in_D_IN.mode ( PullDown );
    in_SEL_2.mode( PullDown );
    in_SEL_1.mode( PullDown );  

    // input pin triggers
    irq_D_OUT.rise(&in_D_OUT_Rise);
    irq_D_OUT.fall(&in_D_OUT_Fall);
    irq_BUSY.rise(&in_BUSY_Rise);
    irq_BUSY.fall(&in_BUSY_Fall);
    
    pc.attach(&onCharReceived);
    
    user_BTN.rise(callback(btnRaised));

    infoLed = 0;
    out_ACK = 0;
    out_SEL_1 = 0;
    out_SEL_2 = 0;
    out_D_OUT = 0;
    out_D_IN  = 0;

    while (true)
    {   
        wait (2);
        infoLed = !infoLed;
        wait (0.05);
        infoLed = !infoLed;
    }
}