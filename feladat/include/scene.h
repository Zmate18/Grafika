#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "ship.h"
#include "apache.h"

#include <obj/model.h>

typedef struct Scene
{
    Material material;
    Ship ship;
    float lightingLevel;
    Apache apache;
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

#endif /* SCENE_H */