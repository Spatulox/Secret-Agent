//
// Created by M78st on 17/01/2024.
//

#ifndef INTERACTIVESSTRUCT_H
#define INTERACTIVESSTRUCT_H

#include "./structPlayer.h"

// ------------------------------------------------- //
//         Part which you can interact with          //

// In game button to activate or desactivate things like lift / electricity / etc...
typedef struct {
    int active;
    Point position;
    int * activeThing;
} InGameButton;


// Electric Meter (compteur electrique)
typedef struct {
    int active;
    Point position;
    int * activeThing;
} ElectricMeter;


// Electric Meter (compteur electrique)
typedef struct {
    int active;
    Point position;
    int code;
    int * activeThing;
} Code;


// ------------------------------------------------- //
//                    Moving parts                   //

// In Game lift ( do we keep it ?? )
typedef struct {
    int active;
    Point position;
} Lift;

// ------------------------------------------------- //

// Doors to open
typedef struct {
    int active;
    Point position;
} Doors;

// ------------------------------------------------- //

// Interactive things
typedef union {
    InGameButton button;
    ElectricMeter electricMeter;
    Lift lift;
    Doors door;
} InteractivePart;

// ------------------------------------------------- //

// Chain list to store interactive part in game.
typedef struct {
    InteractivePart interactivePart;
    int * next
} InteractiveList;

#endif //INTERACTIVESSTRUCT_H
