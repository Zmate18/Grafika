#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{

    init_ship(&(scene->ship));

    init_apache(&(scene->apache));
 

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 0.0;

    scene->lightingLevel=1.8f;
    set_lighting(scene->lightingLevel);

    glFogf(GL_FOG_DENSITY, 0.25f);
}

void set_lighting(float lightingLevel)
{
    float ambient_light[] = { lightingLevel, lightingLevel, lightingLevel, 1.0f };
    float diffuse_light[] = { lightingLevel, lightingLevel, lightingLevel, 1.0f };
    float specular_light[] = { lightingLevel, lightingLevel, lightingLevel, 1.0f };
    float position[] = { 0.0f, 10.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene* scene)
{
}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    
    glBindTexture(GL_TEXTURE_2D, scene->ship.texture_id);
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    draw_model(&(scene->ship.model));
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, scene->apache.texture_id);
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    draw_model(&(scene->apache.model));
    draw_model(&(scene->apache.rotor.rotorTop));
    draw_model(&(scene->apache.rotor.rotorBack));
    glPopMatrix();


}