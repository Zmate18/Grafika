#ifndef APACHE_H
#define APACHE_H

#include <obj/model.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "texture.h"
#include "utils.h"
#include "rotor.h"

typedef struct Apache
{
    GLuint texture_id;
    Model model;
    Rotor rotor;
    vec3 pos;
} Apache;

/**
 * Initialize the Apache.
*/
void init_apache(Apache* apache);

/**
 * Set the Apache position.
*/
void set_apache_pos(Apache* apache, vec3 newPos);



#endif /*APACHE_H*/