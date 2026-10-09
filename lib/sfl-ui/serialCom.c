#include "serialCom.h"

/** CONTENIDO
 * serialCom.c (core)	
 * writeSerialCom/ln, clearScreen, printFormat (vsnprintf), 
 * readUserChar con el eco y la normalización \r→\n, y las secuencias ANSI. 
 * Solo llama a ui_port_*. 
 * No incluye nada del SDK.
 */


void sendUartDataln(const uint8_t* data, size_t len) 
{
    static const uint8_t crlf[2] = { '\r', '\n' };

    sendUartData(data, len);
    sendUartData(crlf, sizeof(crlf));
}

void sendUartData(const uint8_t* data, size_t len)
{
    uart_write_bytes(UART_DEBUG, data, len);
}

void writeSerialCom(const char* data)
{
    print(data);
    //uart_write_bytes(UART_DEBUG, data, strlen(data));

}

void writeSerialComln(const char* data)
{
    writeSerialCom(data);
    writeSerialCom("\n\r");
}

void clearScreen() 
{
    writeSerialCom("\033[2J\033[H");  // Borra pantalla ANSI
}

//Funcion para leer de a un caracter de la CONSOLA

// Función para leer un caracter de la consola o TCP
char readUserChar(void)
{
    uint8_t ch;

    int len = uart_read_bytes(UART_DEBUG, &ch, 1, 0);
    if (len > 0) {
        // Echo del carácter
        uart_write_bytes(UART_DEBUG, (const char *)&ch, 1);

        // Si la terminal envía \r, lo descartamos si viene seguido de \n,
        // lo convierto a \n directamente.
        if (ch == '\r') {
            return '\n'; // Normaliza cualquier Enter (\r o \n) a '\n'
        }

        return (char)ch;
    }

    return '\0';
}

void print(const char* str) 
{
    if(str!=NULL) {
        sendUartData((const uint8_t*)str, strlen(str));
    }
}

void printFormat(const char* format, ...) 
{
    char buffer[128]; // Ajusta el tamaño según tus necesidades
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    print(buffer);
}
/*-------------------------------------------------------------------*/