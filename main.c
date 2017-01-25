/* UART communication Test. Send/receive command works. CLOCK used: 16 MHz, Baud Rate: 9600, 8 bits, 1 stop bit, no parity
 * test1.c
 * Works. Data is being captured. Connect GPS module's TX pin to uC's TX pin
 * Issues: 
 * why can't we connect to RX pin? 
 * In Tera Term, we have to disconnect and reconnect to get new data. 
 * Created: 1/16/2017 1:19:23 AM
 * Author : Burair Zaidi
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void UartInit (void);
void receive (void);
void send(char data_transmit);

char read_arr[5] = {'0','0','0','0','0'};
int j = 0, i = 0;
char data_received;

int main(void)
{
	UartInit();
	//DDRB |= 0B00100000; //DDxn bit in DDRB register determines direction. 1 = output, 0 = input
    /* Replace with your application code */
    while (1) 
    {
		receive();
		send(data_received);
		
		/*PORTB |= 0B00100000;
		_delay_ms(200);
		PORTB &= 0B11011111;
		_delay_ms(200);*/
    }
}

void UartInit(void){
	
	PRR &= ~(1<<PRUSART0);			//power enabled
	UBRR0 = 103;					//UBRR0 = (F_CPU/(16*baud)) - 1; //baud:9600
	UCSR0C |= (3<<UCSZ00);			//char size 8 bits, default: no parity, 1 stop bit
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0); //enables USART Receiver
}

void receive(void){
	while ((UCSR0A & (1<<RXC0))==0){}
	
	UDR0 = data_received; //receive
}

void send (char data_transmit) {
	while ((UCSR0A & (1<<UDRE0)==0)) {} //wait for transmitter to be ready
	
	data_transmit = UDR0;		//data register
	}

