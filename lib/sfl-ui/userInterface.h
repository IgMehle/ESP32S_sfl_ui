/* --------------------------------------------------------------------------------------------
* Para agregar un nuevo comando 
* 1) Agregar titulo y un id uncio en menuInit() en menuTree.cpp y asignar el nodo con add_child()
*
* 2) Para agregar una accion que se ejecute un unica vez agregar un case con el id correspondiente 
*    en onEnterNode() en userInterface.cpp
*
*
* 3A) Si el nodo requiere entrada de datos agregar un case en onEnterNode() el mensaje que
*    se quiere mostrar al entrar al nodo.
*
* 3B) Si el nodo requiere entrada de datos agregar un case en nodeRequiresInput()
*
* 4) Si es necesario actualizar datos periodicamente mientras se esta en un nodo agregar el case 
*    en onUpdateNode()
*
* 5) El filtrado y procesamiento de los datos ingresados por el usuario se ejectuara en procesarDatos()
*    agregar un if(menu->id==xx) para el id correspondiente y procesar los datos recibidos en "data"
* ----------------------------------------------------------------------------------------------- */
#pragma once

#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <ctype.h>
#include <string.h>
#include "menuTree.h"
#include "serialCom.h"

// FREERTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define MAX_DATA_BUFFER 30

void printDataValues(void);
void printDataNames(void);
void moveCursor(int row, int col);

void procesarDatos(const char* data, unsigned char length) ;
static void onEnterNode(MenuNode* n);
static void onUpdateNode(MenuNode* n);
static bool nodeRequiresInput(int id);

bool userInterfaceInit(void);
void userInterfaceUpdate(void);

/* -----------------------------------------------------------------------
* Pasos a seguir para crear un menu
*
* - Agregar el nodo en menuTree.cpp con un id nuevo
* - Agregar if menu id==xx en onEnterNode para mostrar mensaje al entrar
* - Agregar if menu id==xx en nodeRequiresInput si el nodo requiere datos
* ---------------------------------------------------------------------- */

#endif // USERINTERFACE_H