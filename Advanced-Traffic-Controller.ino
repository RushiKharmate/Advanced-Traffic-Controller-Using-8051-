#include <reg51.h>

sbit RED0 = P0^0;
sbit GREEN0 = P0^1;
sbit YELLOW0 = P0^2;
sbit RED1 = P0^3;
sbit GREEN1 = P0^4;
sbit YELLOW1 = P0^5;
sbit RED2 = P1^0;
sbit GREEN2 = P1^1;
sbit YELLOW2 = P1^2;
sbit RED3 = P2^0;
sbit GREEN3 = P2^1;
sbit YELLOW3 = P2^2;
sbit IR_SENSOR = P3^2;  
sbit rs = P2^5;
sbit rw = P2^6;
sbit e = P2^7;
sfr LCD_DATA = 0xB0;

void sdelay(unsigned int time) {
    unsigned int j, k;
    for (k = 0; k < time; k++) {
        for (j = 0; j < 1275; j++);
    }
}

void lcd_data(unsigned char dataa) {
    LCD_DATA = dataa;
    rs = 1;
    rw = 0;
    e = 1;
    sdelay(2);
    e = 0;
}

void lcd_cmd(unsigned char command) {
    LCD_DATA = command;
    rs = 0;
    rw = 0;
    e = 1;
    sdelay(2);
    e = 0;
}

void lcd_init() {
    lcd_cmd(0X38);  
    sdelay(2);
    lcd_cmd(0X0C);  
    sdelay(2);
    lcd_cmd(0x80); 
    sdelay(2);
}

void display(unsigned char *s) {
    lcd_init();
    while (*s) {
        lcd_data(*s);
        s++;
        if (*s == '\0') break; 
        if (*s == '\n') {
            lcd_cmd(0xC0); 
            s++;
        }
    }
}

void delay(unsigned int time_ms) {
    unsigned int i;
    for (i = 0; i < time_ms; i++) {
        TMOD = 0X01;
        TH0 = 0XFF;
        TL0 = 0XF5;
        TR0 = 1;
        while (TF0 == 0);
        TF0 = 0;
        TR0 = 0;
    }
}

void lcd_clr() {
    lcd_cmd(0X01);  
}

void main() {
    RED0 = 0;
    RED1 = 0;
    RED2 = 0;
    RED3 = 0;
    
    while (1) {
        if (IR_SENSOR == 0) {
            // Heavy traffic detected
            
            RED0 = 1;
            GREEN0 = 0;
            display("Road 1 is On - Heavy traffic");
            delay(65000);
            GREEN0 = 1;
            lcd_clr();
            YELLOW0 = 0;
            display("Please wait");
            delay(20000);
            YELLOW0 = 1;
            RED0 = 0;
            
            RED1 = 1;
            GREEN1 = 0;
            display("Road 2 is On - Heavy traffic");
            delay(65000);
            GREEN1 = 1;
            lcd_clr();
            YELLOW1 = 0;
            display("Please wait");
            delay(20000);
            YELLOW1 = 1;
            RED1 = 0;
            
            RED2 = 1;
            GREEN2 = 0;
            display("Road 3 is On - Heavy traffic");
            delay(65000);
            GREEN2 = 1;
            lcd_clr();
            YELLOW2 = 0;
            display("Please wait");
            delay(20000);
            YELLOW2 = 1;
            RED2 = 0;
            
            RED3 = 1;
            GREEN3 = 0;
            display("Road 4 is On - Heavy traffic");
            delay(65000);
            GREEN3 = 1;
            lcd_clr();
            YELLOW3 = 0;
            display("Please wait");
            delay(20000);
            YELLOW3 = 1;
            RED3 = 0;
        } else {
            // Normal traffic flow
        
            RED0 = 1;
            GREEN0 = 0;
            display("Road 1 is On - Normal traffic");
            delay(65000);
            GREEN0 = 1;
            lcd_clr();
            YELLOW0 = 0;
            display("Please wait");
            delay(20000);
            YELLOW0 = 1;
            RED0 = 0;
            
            RED1 = 1;
            GREEN1 = 0;
            display("Road 2 is On - Normal traffic");
            delay(65000);
            GREEN1 = 1;
            lcd_clr();
            YELLOW1 = 0;
            display("Please wait");
            delay(20000);
            YELLOW1 = 1;
            RED1 = 0;
            
            RED2 = 1;
            GREEN2 = 0;
            display("Road 3 is On - Normal traffic");
            delay(65000);
            GREEN2 = 1;
            lcd_clr();
            YELLOW2 = 0;
            display("Please wait");
            delay(20000);
            YELLOW2 = 1;
            RED2 = 0;
            
            RED3 = 1;
            GREEN3 = 0;
            display("Road 4 is On - Normal traffic");
            delay(65000);
            GREEN3 = 1;
            lcd_clr();
            YELLOW3 = 0;
            display("Please wait");
            delay(20000);
            YELLOW3 = 1;
            RED3 = 0;
        }
    }
}
