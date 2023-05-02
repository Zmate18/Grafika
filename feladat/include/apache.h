#ifndef APACHE_H
#define APACHE_H

#include <obj/model.h>
#include <obj/load.h>
#include <obj/draw.h>
#include "texture.h"
#include "utils.h"
#include "rotor.h"
#include "camera.h"
#include <stdbool.h>


typedef struct Apache
{
    GLuint texture_id;
    Model model;
    Rotor rotor;
    vec3 pos;
    vec3 speed;
    vec3 tilt;
    vec3 tiltSpeed;
    bool forward;
    bool backward;
} Apache;

/**
 * Initialize the Apache.
*/
void init_apache(Apache* apache);

/**
 * Set the Apache position.
*/
void set_apache_pos(Apache* apache, vec3 newPos);

/**
 * Sets the apache speed.
*/
void set_apache_speed(Apache* apache, double speed);

/**
 * Sets the apache side speed.
*/
void set_apache_side_speed(Apache* apache, double speed);

/**
 * Sets the apache vertical speed.
*/
void set_apache_vertical_speed(Apache* apache, double speed);

/**
 * Sets the top rotor speed.
*/
void set_rotorTop_speed(Apache* apache, double speed);

/**
 * Sets the rotor rotation.
*/
void rotate_rotor(Apache* apache, double time);

/**
 * Moves the apache helicopter.
*/
void move_apache(Apache* apache, double time);

/**
 * Sets the back rotor speed.
*/
void set_rotorBack_speed(Apache* apache, double speed);

void tilt_apache_forward(Apache* apache, double time, bool tilt);

void tilt_apache_backward(Apache* apache, double time, bool tilt);

void set_tilt_speed(Apache* apache, double speed);


#endif /*APACHE_H*/