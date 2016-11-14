
#include "SLIPEncodedSerial.h"
#include "InchieLED.h"

extern "C" {
#include "uart.h"
#include "BlinkLed.h"
}






/*
 CONSTRUCTOR
 */
SLIPEncodedSerial::SLIPEncodedSerial(hardware_uart * u)
{
    rstate = WAITING;
    rxPacketIndex = 0;
    encodedBufIndex = 0;
    decodedBufIndex = 0;
	uart = u;
}

static const uint8_t eot = 0300;
static const uint8_t slipesc = 0333;
static const uint8_t slipescend = 0334;
static const uint8_t slipescesc = 0335;


int SLIPEncodedSerial::sendPacket(const uint8_t *buf, uint32_t len)//, hardware_uart * uart)
{
	uint32_t i;
    encode(buf, len);
    for (i = 0; i<encodedLength; i++){
    	//uart2_send(encodedBuf[i]);
    	uart->tx_buf[uart->tx_buf_head++] = encodedBuf[i];  //TODO:  block here if buffer gets full
    	if (uart->tx_buf_head >= UART_BUFFER_SIZE)
    		uart->tx_buf_head = 0;
    	//uart->tx_it_en(encodedBuf[i]); // turn on uart interrupt to enable sending
    }
    uart->tx_it_en(0); // turn on uart interrupt to enable sending
    return encodedLength;//s.writeBuffer(encodedBuf, encodedLength);
}

int SLIPEncodedSerial::recvPacket(void)//hardware_uart * uart)
{
    while (uart->rx_buf_tail != uart->rx_buf_head) {
        uint8_t tmp8 = uart->rx_buf[uart->rx_buf_tail++];
        uart->rx_buf_tail %= UART_BUFFER_SIZE;

        if (rstate == WAITING) {
            if (tmp8 == eot) rstate = WAITING; // just keep waiting for something afer EOT
            else {
                rxPacketIndex = 0;
                rxPacket[rxPacketIndex++] = tmp8;
                rstate = RECEIVING;
    			//if (tmp8 != '/') LEDON;
            }
        } // waiting
        else if (rstate == RECEIVING){
            // drop it if too long
        	if (rxPacketIndex >= MAX_MSG_SIZE){  //TODO:  does this want to be max_msg_size * 2
                rstate = WAITING;
        	}
        	else if (tmp8 == eot) {
                rstate = WAITING;
                decode(rxPacket, rxPacketIndex);
                return 1;
            }
            else {
                rxPacket[rxPacketIndex++] = tmp8;
                rstate = RECEIVING;
            }
        } //receiving
    } // gettin bytes
    return 0;
}
 
//encode SLIP, put it in the encoded buffer
void SLIPEncodedSerial::encode(uint8_t b){
    if(b == eot){
        encodedBuf[encodedBufIndex++] = slipesc;
        encodedBuf[encodedBufIndex++] = slipescend;
    } else if(b==slipesc) {
        encodedBuf[encodedBufIndex++] = slipesc;
        encodedBuf[encodedBufIndex++] = slipescesc;
   } else {
        encodedBuf[encodedBufIndex++] = b;
    }
    //if (encodedBuf[1] != '/') AUX_LED_BLUE_ON;
}

void SLIPEncodedSerial::encode(const uint8_t *buf, int size) 
{  
    beginPacket();
    while(size--) encode(*buf++); 
    endPacket();
}

// decode SLIP, put it in the decoded buffer
void SLIPEncodedSerial::decode(const uint8_t *buf, int size)
{
    int i;
    decodedBufIndex = 0;
    i = 0;

    while (i < size) {
        if (buf[i] == slipesc) {  // TODO error out here if slipescend or slipescesc doesn't follow slipesc
            i++;
            if (buf[i] == slipescend) decodedBuf[decodedBufIndex++] = eot;
            if (buf[i] == slipescesc) decodedBuf[decodedBufIndex++] = slipesc;
            i++;
        }
        else {
            decodedBuf[decodedBufIndex++] = buf[i];
            i++;
        }
    }
    decodedLength = decodedBufIndex;
}

//SLIP specific method which begins a transmitted packet
void SLIPEncodedSerial::beginPacket() {
    encodedBufIndex = 0;
    encodedBuf[encodedBufIndex++] = eot;
}

//signify the end of the packet with an EOT
void SLIPEncodedSerial::endPacket(){
    encodedBuf[encodedBufIndex++] = eot;
    encodedLength = encodedBufIndex;
}


