//
// Created by Marc on 17/01/2024.
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


// Code (for code doors)
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

// Doors to open
typedef struct {
    int upDownStairs;
    Point position;
    struct Stairs * linkStairs;
    Size size;
} Stairs;

// ------------------------------------------------- //

// Doors to open
typedef struct {
    Point position;
    Size size;
} Chest;

// ------------------------------------------------- //

typedef enum {
    BUTTON,
    ELECTRIC_METER,
    CODE,
    LIFT,
    DOOR,
    STAIRS,
    CHEST
} InteractiveType;

// Interactive things
typedef struct {
    InteractiveType type;
    union {
        InGameButton button;
        ElectricMeter electricMeter;
        Code code;
        Lift lift;
        Doors door;
        Stairs stairs;
        Chest chest;
    } part;
} InteractivePart;

// ------------------------------------------------- //

// Chain list to store interactive part in game.
typedef struct {
    InteractivePart interactivePart;
    struct InteractiveList * next;
} InteractiveList;

#endif //INTERACTIVESSTRUCT_H
