#ifndef ROTOR_H
#define ROTOR_H

#include <obj/model.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "texture.h"
#include "utils.h"
#include <stdbool.h>

typedef struct Rotor
{
    GLuint texture_id;
    Model rotorTop;
    Model rotorBack;
    vec3 pos;
    vec3 rotation;
    vec3 rotationSpeed;
    bool active;
} Rotor;


#endif /*ROTOR_H*/