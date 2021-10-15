#include <stdio.h>
#include <stdlib.h>
#pragma config OSC = XT         // Oscillator Selection bits (XT oscillator)
#pragma config OSCS = OFF       // Oscillator System Clock Switch Enable bit (Oscillator system clock switch option is disabled (main oscillator is source))
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
#pragma config BORV = 20        // Brown-out Reset Voltage bits (VBOR set to 2.0V)
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 128      // Watchdog Timer Postscale Select bits (1:128)
#pragma config CCP2MUX = ON     // CCP2 Mux bit (CCP2 input/output is multiplexed with RC1)
#pragma config STVR = ON        // Stack Full/Underflow Reset Enable bit (Stack Full/Underflow will cause RESET)
#pragma config LVP = OFF        // Low Voltage ICSP Enable bit (Low Voltage ICSP disabled)
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000200-001FFFh) not code protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code protected)
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code protected)
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000200-001FFFh) not write protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write protected)
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write protected)
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000200-001FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from Table Reads executed in other blocks)
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from Table Reads executed in other blocks)

#include <xc.h>
#include <math.h>
#define _XTAL_FREQ 4000000
#define EN RE2
#define RS RE0

//..............variables globales y prototipos de funcion.........................................................

unsigned char buffer[40];
unsigned int num = 0,tuputamadre;
unsigned int nombresbaby(void);
unsigned char bin1[5], bin2[5], bin3[5], binc[8], binco[8];
unsigned char bincor[9];
unsigned char t = 0, A = 0, B = 0, S = 0, PB = 0, D = 0;
unsigned char C = 0, E = 0, F = 0, G = 0, R = 0;
double X = 0, Y = 0,Z = 0;
unsigned char bin[] = {0, 1, 1, 1, 1};
void conf_puertos(void);
void ini_LCD(void);
void enable(void);
void dato_LCD(unsigned char dato);
void ins_LCD(unsigned char dato);
void write_LCD(unsigned char tam);

//..............codigo principal................................................................

int main() {

    //.........................conf perifericos.................................................
    conf_puertos();
    ini_LCD(); //inicializa la LCD

    ins_LCD(130);

    write_LCD(sprintf(buffer, "Dj Fumaratto"));

    ins_LCD(196);

    write_LCD(sprintf(buffer, "Presents"));

    __delay_ms(700);
    ins_LCD(1);
    //.........................bucle.............................................................
    while (1) {
        PB = PORTB;
        A = PB >> 4;
        B = PB & 0x0F;
        S = PORTA & 0x0F;
        switch (S) {
            case 0:
                ins_LCD(1);
                write_LCD(sprintf(buffer, "%i  + %i", A, B));
                D = A + B;
                ins_LCD(192);
                write_LCD(sprintf(buffer, "Resultado: %i", D));
                __delay_ms(100);
                break;
            case 1:
                if (A >= B) {
                    ins_LCD(1);
                    write_LCD(sprintf(buffer, "%i", A));
                    ins_LCD(131);
                    write_LCD(sprintf(buffer, "- %i", B));
                    D = A - B;
                    ins_LCD(192);
                    write_LCD(sprintf(buffer, "Resultado:  %i", D));
                    __delay_ms(100);
                }
                if (B > A) {
                    ins_LCD(1);
                    write_LCD(sprintf(buffer, "%i", A));
                    ins_LCD(131);
                    write_LCD(sprintf(buffer, "- %i", B));
                    D = B - A;
                    ins_LCD(192);
                    write_LCD(sprintf(buffer, "Resultado: -%i", D));
                    __delay_ms(100);
                }
                break;
            case 2:
                ins_LCD(1);
                write_LCD(sprintf(buffer, "%i", A));
                ins_LCD(131);
                write_LCD(sprintf(buffer, "* %i", B));
                D = A*B;
                ins_LCD(192);
                write_LCD(sprintf(buffer, "Resultado: %i", D));
                __delay_ms(100);
                break;
            case 3:
                ins_LCD(1);
                if (A >= B) {
                    ins_LCD(1);
                    write_LCD(sprintf(buffer, "%i", A));
                    ins_LCD(131);
                    write_LCD(sprintf(buffer, "/ %i", B));
                    num = A / B;
                    ins_LCD(192);
                    write_LCD(sprintf(buffer, "Resultado: %i", num));
                    __delay_ms(100);
                } else {
                    ins_LCD(192);
                    write_LCD(sprintf(buffer, "Resultado: </3"));
                    __delay_ms(100);
                }
                break;

            case 4: // AND
                for (t = 4; t > 0; t--) {
                    bin1[t] = A % 2;
                    A = A / 2;
                }
                ins_LCD(128);
                write_LCD(sprintf(buffer, "A=%i%i%i%i", bin1[1], bin1[2], bin1[3], bin1[4]));
                for (t = 4; t > 0; t--) {
                    bin2[t] = B % 2;
                    B = B / 2;
                }
                ins_LCD(135);
                write_LCD(sprintf(buffer, "B=%i%i%i%i", bin2[1], bin2[2], bin2[3], bin2[4]));
                for (t = 1; t < 5; t++) {
                    bin3[t] = bin1[t] & bin2[t];
                }
                ins_LCD(192);
                write_LCD(sprintf(buffer, "R AND : %d%d%d%d", bin3[1], bin3[2], bin3[3], bin3[4]));
                __delay_ms(100);
                break;

            case 5: // OR
                for (t = 4; t > 0; t--) {
                    bin1[t] = A % 2;
                    A = A / 2;
                }
                ins_LCD(128);
                write_LCD(sprintf(buffer, "A=%i%i%i%i", bin1[1], bin1[2], bin1[3], bin1[4]));
                for (t = 4; t > 0; t--) {
                    bin2[t] = B % 2;
                    B = B / 2;
                }
                ins_LCD(135);
                write_LCD(sprintf(buffer, "B=%i%i%i%i", bin2[1], bin2[2], bin2[3], bin2[4]));
                for (t = 1; t < 5; t++) {
                    bin3[t] = bin1[t] | bin2[t];
                }
                ins_LCD(192);
                write_LCD(sprintf(buffer, "R OR  : %d%d%d%d", bin3[1], bin3[2], bin3[3], bin3[4]));
                __delay_ms(100);
                break;

            case 6:     //  XOR
                for (t = 4; t > 0; t--) {
                    bin1[t] = A % 2;
                    A = A / 2;
                }
                ins_LCD(128);
                write_LCD(sprintf(buffer, "A=%i%i%i%i", bin1[1], bin1[2], bin1[3], bin1[4]));
                for (t = 4; t > 0; t--) {
                    bin2[t] = B % 2;
                    B = B / 2;
                }
                ins_LCD(135);
                write_LCD(sprintf(buffer, "B=%i%i%i%i", bin2[1], bin2[2], bin2[3], bin2[4]));
                for (t = 1; t < 5; t++) {
                    bin3[t] = bin1[t]^bin2[t];
                }
                ins_LCD(192);
                write_LCD(sprintf(buffer, "R XOR : %d%d%d%d", bin3[1], bin3[2], bin3[3], bin3[4]));
                __delay_ms(100);
                break;

            case 7: //  NAND
                for (t = 4; t > 0; t--) {
                    bin1[t] = A % 2;
                    A = A / 2;
                }
                ins_LCD(128);
                write_LCD(sprintf(buffer, "A=%i%i%i%i", bin1[1], bin1[2], bin1[3], bin1[4]));
                for (t = 4; t > 0; t--) {
                    bin2[t] = B % 2;
                    B = B / 2;
                }
                ins_LCD(135);
                write_LCD(sprintf(buffer, "B=%i%i%i%i", bin2[1], bin2[2], bin2[3], bin2[4]));
                for (t = 1; t < 5; t++) {
                    bin3[t] = bin[t]&~(bin1[t] & bin2[t]);
                }
                ins_LCD(192);
                write_LCD(sprintf(buffer, "R NAND: %d%d%d%d", bin3[1], bin3[2], bin3[3], bin3[4]));
                __delay_ms(100);
                break;

            case 8: //  NOR
                ins_LCD(1);
                for (t = 4; t > 0; t--) {
                    bin1[t] = A % 2;
                    A = A / 2;
                }
                ins_LCD(128);
                write_LCD(sprintf(buffer, "A=%i%i%i%i", bin1[1], bin1[2], bin1[3], bin1[4]));
                for (t = 4; t > 0; t--) {
                    bin2[t] = B % 2;
                    B = B / 2;
                }
                ins_LCD(135);
                write_LCD(sprintf(buffer, "B=%i%i%i%i", bin2[1], bin2[2], bin2[3], bin2[4]));
                for (t = 1; t < 5; t++) {
                    bin3[t] = bin[t]&~(bin1[t] | bin2[t]);
                }
                ins_LCD(192);
                write_LCD(sprintf(buffer, "R NOR : %d%d%d%d", bin3[1], bin3[2], bin3[3], bin3[4]));
                __delay_ms(100);
                break;

            case 9: //  XNOR
                for (t = 4; t > 0; t--) {
                    bin1[t] = A % 2;
                    A = A / 2;
                }
                ins_LCD(128);
                write_LCD(sprintf(buffer, "A=%i%i%i%i", bin1[1], bin1[2], bin1[3], bin1[4]));
                for (t = 4; t > 0; t--) {
                    bin2[t] = B % 2;
                    B = B / 2;
                }
                ins_LCD(135);
                write_LCD(sprintf(buffer, "B=%i%i%i%i", bin2[1], bin2[2], bin2[3], bin2[4]));
                for (t = 1; t < 5; t++) {
                    bin3[t] = bin[t]&~(bin1[t]^bin2[t]);
                }
                ins_LCD(192);
                write_LCD(sprintf(buffer, "R XNOR: %d%d%d%d", bin3[1], bin3[2], bin3[3], bin3[4]));
                __delay_ms(100);
                break;

            case 10: // Corrimiento PuertoB>>7
                for (t = 8; t > 0; t--) {
                    binc[t] = PB % 2;
                    PB = PB / 2;
                }
                ins_LCD(128);
                write_LCD(sprintf(buffer, "Num: %i%i%i%i%i%i%i%i", binc[1], binc[2], binc[3], binc[4], binc[5], binc[6], binc[7], binc[8]));
                PB = PORTB;
                F = PB >> 7;
                G = PB << 1;
                C = F + G;
                for (t = 8; t > 0; t--) {
                    binco[t] = C % 2;
                    C = C / 2;
                }
                ins_LCD(192);
                write_LCD(sprintf(buffer, "Res: %i%i%i%i%i%i%i%i", binco[1], binco[2], binco[3], binco[4], binco[5], binco[6], binco[7], binco[8]));
                __delay_ms(100);
                break;

            case 11: // Corrimiento PuertoB<<4
                for (t = 8; t > 0; t--) {
                    binc[t] = PB % 2;
                    PB = PB / 2;
                }
                ins_LCD(128);
                write_LCD(sprintf(buffer, "Num: %i%i%i%i%i%i%i%i", binc[1], binc[2], binc[3], binc[4], binc[5], binc[6], binc[7], binc[8]));
                PB = PORTB;
                F = PB << 4;
                G = PB >> 4;
                C = F + G;
                for (t = 8; t > 0; t--) {
                    binco[t] = C % 2;
                    C = C / 2;
                }
                ins_LCD(192);
                write_LCD(sprintf(buffer, "Res: %i%i%i%i%i%i%i%i", binco[1], binco[2], binco[3], binco[4], binco[5], binco[6], binco[7], binco[8]));
                __delay_ms(100);
                break;

            case 12:
                ins_LCD(1);
                ins_LCD(128);
                write_LCD(sprintf(buffer,"%i Potencia %i",A,B));
                num=pow(A,B);
                ins_LCD(192);
                write_LCD(sprintf(buffer,"Rta: %i",num));
                __delay_ms(100);
                break;

            case 13:
                ins_LCD(1);
                ins_LCD(128);
                write_LCD(sprintf(buffer,"%i Raiz de %i",B,A));
                Y=1/B;
                X=pow(A,Y);
                ins_LCD(192);
                write_LCD(sprintf(buffer,"Rta: %.2f",X));
                __delay_ms(100);
                break;

            case 14: // Corrimiento A<<B Sin perder Dato
                ins_LCD(1);
                for (t = 4; t > 0; t--) {
                    bin1[t] = A % 2;
                    A = A / 2;
                }
                ins_LCD(128);
                write_LCD(sprintf(buffer, "Num:%i%i%i%i", bin1[1], bin1[2], bin1[3], bin1[4]));
                ins_LCD(137);
                write_LCD(sprintf(buffer, "B=%i", B));
                PB=PORTB;
                A = PB >> 4;
                if (B < 9) {
                    C = A << B;
                    D = 8 - B;
                    E = A >> D;
                    F = E | C;
                   
                    for (t = 8; t > 0; t--) {
                        bincor[t] = F % 2;
                        F = F / 2;
                    }
                    ins_LCD(192);
                    write_LCD(sprintf(buffer, "Res: %d%d%d%d%d%d%d%d", bincor[1], bincor[2], bincor[3], bincor[4], bincor[5], bincor[6], bincor[7], bincor[8]));
                }
                else if(B > 8){
                    C = A << B;
                    D = B - 8;
                    E = A << D;
                    F = 8 - D;
                    G = A >> F;
                    R = G | E;
                    
                    for (t = 8; t > 0; t--) {
                        bincor[t] = R % 2;
                        R = R / 2;
                    }
                    ins_LCD(192);
                    write_LCD(sprintf(buffer, "Res: %d%d%d%d%d%d%d%d", bincor[1], bincor[2], bincor[3], bincor[4], bincor[5], bincor[6], bincor[7], bincor[8]));
                
                }
                __delay_ms(100);
                break;

            case 15:
                nombresbaby();
                break;


        }
    }
}
//......................funciones............................................................

void conf_puertos(void) {

    TRISB = 0xFF;
    LATB = 0;
    PORTB = 0;

    TRISA = 0xFF;
    LATA = 0;
    PORTA = 0;
    ADCON1 = 0x06;

    TRISD = 0x00; // puerto D de salida
    LATD = 0; // limpia puerto D
    PORTD = 0; // limpia puerto D

    TRISE = 0x00; // puerto E de salida
    LATE = 0x00; // Limpia puerto 
    PORTE = 0x00; // Limpia puerto
    ADCON1 = 0x06; //Puerto E digital
}

//...................ini_LCD....................................

void ini_LCD(void) {
    __delay_ms(20); // delay 20 ms
    PORTD = 0x30; // VALOR DE INICIALIZACION
    enable();

    __delay_ms(5); // delay 5 ms
    PORTD = 0x30; // VALOR DE INICIALIZACION
    enable();

    __delay_ms(1); // delay 1 ms
    PORTD = 0x30; // VALOR DE INICIALIZACION
    enable();

    PORTD = 0b00111000; // Function set 8 bits - 2 lineas - 5*8
    enable();

    PORTD = 0b00001000; // display off
    enable();

    PORTD = 0b00000001; // display clear
    enable();

    PORTD = 0b00000110; // entry mode set - incrementa la posicion del cursor
    enable();

    PORTD = 0b00001110; // display on/off control - LCD on - cursor on - blink off
    enable();


}

//...................enable....................................

void enable(void) {
    EN = 1; // enable en alto
    __delay_ms(1);
    EN = 0; // enable en bajo
}

//...................dato....................................

void dato_LCD(unsigned char dato) {
    RS = 1; //RS en 1 (envia dato)
    PORTD = dato; //dato a publicar 
    enable();
    __delay_ms(2); //tiempo de ejecucion
}

//...................instruccion..................................

void ins_LCD(unsigned char dato) {
    RS = 0; //RS en 0 (envia instruccion)
    PORTD = dato; //dato a publicar 
    enable();
    __delay_ms(2); //tiempo de ejecucion
}

void write_LCD(unsigned char tam) {

    unsigned char i;

    for (i = 0; i < tam; i++) {
        dato_LCD(buffer[i]);
    }
}
unsigned int nombresbaby(void) {
    ins_LCD(132);
    write_LCD(sprintf(buffer, " "));
    ins_LCD(197);
    write_LCD(sprintf(buffer, " "));
    ins_LCD(128);
    write_LCD(sprintf(buffer, "J"));
    ins_LCD(204);
    write_LCD(sprintf(buffer, "O"));
    ins_LCD(199);
    write_LCD(sprintf(buffer, "A"));
    __delay_ms(300);

    ins_LCD(130);
    write_LCD(sprintf(buffer, "A"));
    ins_LCD(202);
    write_LCD(sprintf(buffer, "A"));
    ins_LCD(198);
    write_LCD(sprintf(buffer, "S"));
    __delay_ms(300);

    ins_LCD(129);
    write_LCD(sprintf(buffer, "U"));
    ins_LCD(203);
    write_LCD(sprintf(buffer, "D"));
    ins_LCD(200);
    write_LCD(sprintf(buffer, "L"));
    __delay_ms(300);

    ins_LCD(131);
    write_LCD(sprintf(buffer, "N"));
    ins_LCD(201);
    write_LCD(sprintf(buffer, "G"));
    __delay_ms(300);

    ins_LCD(133);
    write_LCD(sprintf(buffer, "S"));
    ins_LCD(140);
    write_LCD(sprintf(buffer, "L"));
    ins_LCD(194);
    write_LCD(sprintf(buffer, "V"));
    __delay_ms(300);

    ins_LCD(134);
    write_LCD(sprintf(buffer, "A"));
    ins_LCD(139);
    write_LCD(sprintf(buffer, "A"));
    ins_LCD(193);
    write_LCD(sprintf(buffer, "E"));
    __delay_ms(300);

    ins_LCD(135);
    write_LCD(sprintf(buffer, "N"));
    ins_LCD(138);
    write_LCD(sprintf(buffer, "V"));
    ins_LCD(195);
    write_LCD(sprintf(buffer, "I"));
    __delay_ms(300);

    ins_LCD(136);
    write_LCD(sprintf(buffer, "DO"));
    ins_LCD(192);
    write_LCD(sprintf(buffer, "K"));
    ins_LCD(196);
    write_LCD(sprintf(buffer, "N"));
    __delay_ms(300);
    return 0;
}
