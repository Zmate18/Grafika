#include "scene.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene *scene)
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

    scene->lightingLevel = 1.8f;
    set_lighting(scene->lightingLevel);

    glFogf(GL_FOG_DENSITY, 0.25f);
}

void set_lighting(float lightingLevel)
{
    float ambient_light[] = {lightingLevel, lightingLevel, lightingLevel, 1.0f};
    float diffuse_light[] = {lightingLevel, lightingLevel, lightingLevel, 1.0f};
    float specular_light[] = {lightingLevel, lightingLevel, lightingLevel, 1.0f};
    float position[] = {0.0f, 10.0f, 10.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material *material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue};

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue};

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void update_scene(Scene *scene)
{
    if (scene->apache.pos.z < 0)
    {
        scene->apache.pos.z += 0.09;
    }
}

void render_scene(const Scene *scene)
{
    set_material(&(scene->material));

    // ship
    glBindTexture(GL_TEXTURE_2D, scene->ship.texture_id);
    glPushMatrix();
    glRotatef(90.0, 1.0, 0.0, 0.0);
    draw_model(&(scene->ship.model));
    glPopMatrix();

    // helicopter
    glBindTexture(GL_TEXTURE_2D, scene->apache.texture_id);
    glPushMatrix();
    glTranslatef(scene->apache.pos.x, scene->apache.pos.y, scene->apache.pos.z);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glRotatef(scene->apache.tilt.x, 1.0, 0.0, 0.0);
    glRotatef(scene->apache.tilt.y, 0.0, 1.0, 0.0);
    glRotatef(scene->apache.tilt.z, 0.0, 0.0, 1.0);
    glVertex3f(scene->apache.pos.x, scene->apache.pos.y, scene->apache.pos.z);
    draw_model(&(scene->apache.model));
    glPopMatrix();

    // top rotor
    glPushMatrix();
    glTranslatef(scene->apache.pos.x, scene->apache.pos.y, scene->apache.pos.z);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glRotatef(scene->apache.tilt.x, 1.0, 0.0, 0.0);
    glRotatef(scene->apache.tilt.y, 0.0, 1.0, 0.0);
    glRotatef(scene->apache.tilt.z, 0.0, 0.0, 1.0);
    glRotatef(scene->apache.rotor.rotation.y, 0.0, 1.0, 0.0);
    glVertex3f(scene->apache.pos.x, scene->apache.pos.y, scene->apache.pos.z);
    draw_model(&(scene->apache.rotor.rotorTop));
    glPopMatrix();

    if (scene->apache.tilt.x >= 0.0 && scene->apache.tilt.x <= 0.25)
    {
        glPushMatrix();
        glTranslatef(scene->apache.pos.x + 0.15, scene->apache.pos.y + 4.07, scene->apache.pos.z + 3.125);
        glVertex3f(scene->apache.pos.x, scene->apache.pos.y, scene->apache.pos.z + 10.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        glRotatef(scene->apache.rotor.rotation.x, 1.0, 0.0, 0.0);
        draw_model(&(scene->apache.rotor.rotorBack));
        glPopMatrix();
    }
    else if (scene->apache.tilt.x > 0.0)
    {
        glPushMatrix();
        glTranslatef(scene->apache.pos.x + 0.15, scene->apache.pos.y + 1.95, scene->apache.pos.z + 4.75);
        glVertex3f(scene->apache.pos.x, scene->apache.pos.y, scene->apache.pos.z + 10.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        glRotatef(scene->apache.rotor.rotation.x, 1.0, 0.0, 0.0);
        draw_model(&(scene->apache.rotor.rotorBack));
        glPopMatrix();
    }
    else
    {
        glPushMatrix();
        glTranslatef(scene->apache.pos.x + 0.15, scene->apache.pos.y + 5.1, scene->apache.pos.z + 0.7);
        glVertex3f(scene->apache.pos.x, scene->apache.pos.y, scene->apache.pos.z + 10.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        glRotatef(scene->apache.rotor.rotation.x, 1.0, 0.0, 0.0);
        draw_model(&(scene->apache.rotor.rotorBack));
        glPopMatrix();
    }
    // back rotor
}