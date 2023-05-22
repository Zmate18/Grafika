#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "ship.h"
#include "apache.h"
#include "mapbox.h"
#include <obj/model.h>
#include "utils.h"
#include <obj/load.h>
#include <obj/draw.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>

typedef struct Scene
{
    Material material;
    Ship ship;
    float lightingLevel;
    Apache apache;
    bool helpShow;
    GLuint water_texture;
    GLuint help_texture;
    GLfloat fogColor[4];
    vec3 water_pos;
    vec3 water_speed;
    bool exit;
    bool restart;
    Mapbox mapbox;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(float lightingLevel);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Show help.
 */
void help(GLuint texture);

void render_water_side(const Scene* scene);

void render_waterTop(const Scene* scene);

bool check_apache_boundaries(Scene* scene);

int waterDialog();

#endif /* SCENE_H */
