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
    vec3 tiltPos;
    vec3 tiltSpeed;
    bool forward;
    bool backward;
    bool left;
    bool right;
    bool tiltBlock;
} Apache;

/**
 * Initialize the helicopter.
*/
void init_apache(Apache* apache);

/**
 * Set the helicopter position.
*/
void set_apache_pos(Apache* apache, vec3 newPos);

/**
 * Sets the helicopter speed.
*/
void set_apache_speed(Apache* apache, double speed);

/**
 * Sets the helicopter side speed.
*/
void set_apache_side_speed(Apache* apache, double speed);

/**
 * Sets the helicopter vertical speed.
*/
void set_apache_vertical_speed(Apache* apache, double speed);

/**
 * Sets the rotor rotation.
*/
void rotate_rotor(Apache* apache, double time);

/**
 * Moves the helicopter.
*/
void move_apache(Apache* apache, double time);

/**
 * Sets the top rotor speed.
*/
void set_rotorTop_speed(Apache* apache, double speed);

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

/**
 * Tilt forward the helicopter.
*/
void tilt_apache_forward(Apache* apache, double time, bool tilt);

void set_tilt_pos(Apache* apache, vec3 newPos);

/**
 * Tilt backward the helicopter.
*/
void tilt_apache_backward(Apache* apache, double time, bool tilt);

/**
 * Tilt left the helicopter.
*/
void tilt_apache_left(Apache* apache, double time, bool tilt);

/**
 * Tilt right the helicopter.
*/
void tilt_apache_right(Apache* apache, double time, bool tilt);

/**
 * Sets the helicopter tilting speed.
*/
void set_tilt_speed(Apache* apache, double speed);

/**
 * Sets the helicopter side tilting speed.
*/
void set_side_tilt_speed(Apache* apache, double speed);

#endif /*APACHE_H*/