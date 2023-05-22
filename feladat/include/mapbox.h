#ifndef MAPBOX_H
#define MAPBOX_H

#include <obj/load.h>
#include <obj/draw.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include "texture.h"

typedef struct Mapbox
{
    GLuint top;
    GLuint front;
    GLuint back;
    GLuint left;
    GLuint right;
} Mapbox;

/**
 * Initialize the box for the map.
 */
void init_mapbox(Mapbox* mapbox);

/**
 * Render the box for the map.
 */
void render_mapbox(const Mapbox* mapbox);


#endif /*MAPBOX_H*/