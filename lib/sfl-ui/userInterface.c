

#include <ctype.h>
#include <string.h>
#include "userInterface.h"
#include "menuTree.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#define MAX_DATA_BUFFER 30



static MenuNode *menu = NULL;
char data_buffer[MAX_DATA_BUFFER] ; //Variable para almacenar los datos recibidos
unsigned char buffer_index = 0; //脥ndice para el buffer de datos
bool aceptandoDatos=false;
bool updateScreen=false;
static int lastMenuId = -1;

void printDataValues(void);
void printDataNames(void);
void moveCursor(int row, int col);


void procesarDatos(const char* data, unsigned char length) ;
static void onEnterNode(MenuNode* n);
static void onUpdateNode(MenuNode* n);
static bool nodeRequiresInput(int id);




bool userInterfaceInit(){

    initUart();
    clearScreen();//Borra mensajes del ESP32 al iniciar el programa
    menu=menuInit();
    if(menu){
        ESP_LOGI("userInterface", "Menu inicializado");
    }else{
        ESP_LOGI("userInterface", "Menu no inicializado");
    }


}


void userInterfaceUpdate() {
    if (menu == NULL) return;

    char charReceived = readUserChar();
    if(charReceived== GO_BACK){ // ESCAPE
        menuUpdate(charReceived, &menu);
        
        clearScreen();
        printNode(menu);
        onEnterNode(menu);
        lastMenuId = menu->id;
        
        //Si el nodo es nuevo y requiere datos, preparo el buffer para recibirlos
        //Si no es nuevo pero aun asi requiere datos(porque ya se enviaron datos previamente
        //y se quiere seguir enviando datos) tambien preparo el buffer
        aceptandoDatos = nodeRequiresInput(menu->id);

        
        return ;
    }
  

    if (charReceived == '\n') {
        if (aceptandoDatos) {
            // Terminamos de recibir datos
            data_buffer[buffer_index] = '\0';  // Terminador nulo
            procesarDatos(data_buffer,buffer_index);
            memset(data_buffer, 0, sizeof(data_buffer));
            buffer_index = 0;
            aceptandoDatos = false;
        } 
        return;
    }

   if (!aceptandoDatos) {

        
        menuUpdate(charReceived, &menu);

        if (lastMenuId != menu->id) {
            clearScreen();
            printNode(menu);
            onEnterNode(menu);
            lastMenuId = menu->id;
        }
        //Si el nodo es nuevo y requiere datos, preparo el buffer para recibirlos
        //Si no es nuevo pero aun asi requiere datos(porque ya se enviaron datos previamente
        //y se quiere seguir enviando datos) tambien preparo el buffer
        aceptandoDatos = nodeRequiresInput(menu->id);

    } else {
        // Captura de caracteres
        if(buffer_index < MAX_DATA_BUFFER - 1) {
            // Aceptamos solo n煤meros,caracteres , coma y espacios
            if (isdigit(charReceived) || isalpha(charReceived) || charReceived == ',' || isspace(charReceived)) {
                data_buffer[buffer_index++] = charReceived;
            } 
        }
    }




    // 馃敼 Ejecutar siempre la l贸gica de actualizaci贸n peri贸dica
    onUpdateNode(menu);

    return;
}








void procesarDatos(const char* data, unsigned char length) {
    if (data == NULL || menu == NULL || length <= 0) { 
        return;
    }


/*
    if(menu->id == xx){
    
        //Accion a ejecutar al recibir datos en el nodo con id xx
        return;
    }
}
*/

    if(menu->id == 21){
    

        //Accion a ejecutar al recibir datos en el nodo con id xx
        return;
    }







}


static void onEnterNode(MenuNode* n) {
    if (!n) return;

    if (nodeRequiresInput(n->id)) {
        aceptandoDatos = false;
        memset(data_buffer, 0, sizeof(data_buffer));
        buffer_index = 0;
        //sendUartDataln("Nodo requiere entrada. Presiona 'ENTER' para comenzar.");

    } 

    // Acciones inmediatas (sin pedir datos) y automaticas en elupdate
    switch (n->id) {

        case 21: print();
                   
        /*
        casexx:  // Acci贸n inmediata para el nodo con id xx
            break;
        */


        default:
            break;
    }

    // Nodos que requieren datos: activar captura y mostrar prompt
    if (nodeRequiresInput(n->id)) {
        aceptandoDatos = true;
        memset(data_buffer, 0, sizeof(data_buffer));
        buffer_index = 0;

        switch (n->id) {
            //case xx:  ESP_LOGI("userInterface", "Ingrese SSID y presione 'ENTER' para confirmar"); break;
            default: break;
        }
    }
}

//Ejecuto acciones peri贸dicas al estar en ciertos nodos
static void onUpdateNode(MenuNode* n) {
    if (!n) return;

    switch (n->id) {
        /*
        case xx :
            // Acci贸n peri贸dica para el nodo con id xx
            break;
        */


        default:
            // Otros men煤s no se refrescan constantemente
            break;
    }
}

static bool nodeRequiresInput(int id) {
    switch (id) {

        //case XX:  // Cambiar SSID
        return true;
      
        default:
            return false;
    }
}



void moveCursor(int row, int col) {
    char buffer[10];
    snprintf(buffer, sizeof(buffer), "\033[%d;%dH", row, col);
    writeSerialCom(buffer);

}


