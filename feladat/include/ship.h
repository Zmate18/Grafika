#ifndef SHIP_H
#define SHIP_H

#include <obj/model.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "texture.h"
#include "utils.h"


typedef struct Ship
{
    GLuint texture_id;
    Model model;
    vec3 pos;
} Ship;

/**
 * Initialize the ship.
*/
void init_ship(Ship* ship);


#endif /*SHIP_H*/