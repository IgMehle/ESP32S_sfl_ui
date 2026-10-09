#include "serialCom.h"

/** CONTENIDO
 * serialCom.c (core)	
 * writeSerialCom/ln, clearScreen, printFormat (vsnprintf), 
 * readUserChar con el eco y la normalización \r→\n, y las secuencias ANSI. 
 * Solo llama a ui_port_*. 
 * No incluye nada del SDK.
 */

int initUart(void)
{
    return (int)ui_port_init();
}

void sendUartData(const uint8_t* data, size_t len)
{
    //uart_write_bytes(UART_DEBUG, data, len);
    ui_port_write((const char*)data, len);
}

 // ESCRITURA MULTILINEA
void sendUartDataln(const uint8_t* data, size_t len) 
{
    static const uint8_t crlf[2] = { '\r', '\n' };

    sendUartData(data, len);
    sendUartData(crlf, sizeof(crlf));
}

void ui_print(const char* str) 
{
    if(str!=NULL) {
        sendUartData((const uint8_t*)str, strlen(str));
    }
}

void ui_printFormat(const char* format, ...) 
{
    char buffer[128]; // Ajusta el tamaño según tus necesidades
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    ui_print(buffer);
}

void writeSerialCom(const char* data)
{
    ui_print(data);
}

void writeSerialComln(const char* data)
{
    writeSerialCom(data);
    writeSerialCom("\r\n");
}

void clearScreen() 
{
    writeSerialCom("\033[2J\033[H");  // Borra pantalla ANSI
}

// Función para leer un caracter de la consola
char readUserChar(void)
{
    return ui_port_read_byte();
}
/*-------------------------------------------------------------------*/