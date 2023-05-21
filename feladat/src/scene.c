#include "scene.h"
#include <GL/gl.h>
#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene *scene)
{
    scene->water_texture = load_texture("assets/textures/water.png");
    scene->water_pos.x = 0.0;
    scene->water_pos.y = 0.0;
    scene->water_pos.z = 0.0;

    scene->water_speed.x = 0.6;
    scene->water_speed.y = 0.6;
    scene->water_speed.z = 0.0;

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

    // fog settings
    scene->fogColor[0] = 0.5f;
    scene->fogColor[1] = 0.5f;
    scene->fogColor[2] = 0.5f;
    scene->fogColor[3] = 1.0f;
    glEnable(GL_FOG);
    glFogf(GL_FOG_DENSITY, 0.0f);
    glFogfv(GL_FOG_COLOR, scene->fogColor);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    scene->helpShow = false;
    scene->help_texture = load_texture("assets/textures/help.jpg");

    scene->exit = false;
    scene->restart = false;
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
    if (scene->apache.pos.z < 0 && check_apache_boundaries(scene))
    {
        scene->apache.pos.z += 0.09;
    }

    if (scene->apache.pos.z >= 0.0 && scene->apache.pos.z <= 1.0 && check_apache_boundaries(scene))
    {
        scene->apache.tiltBlock = true;
    }
    else
    {
        scene->apache.tiltBlock = false;
    }

    if (scene->apache.pos.z <= -2.5 && !check_apache_boundaries(scene))
    {
        int button_id;
        button_id = showEndGameDialog();
        if (button_id == 0)
        {
            scene->exit = true;
        }
        else
        {
            scene->restart = true;
        }
        
    }
    
}

bool check_apache_boundaries(Scene *scene)
{
    if (scene->apache.pos.x >= 5.47)
    {
        return false;
    }

    if (scene->apache.pos.x <= -5.83)
    {
        return false;
    }

    if (scene->apache.pos.y <= -27.68)
    {
        return false;
    }

    if (scene->apache.pos.y >= 25)
    {
        return false;
    }
    return true;
}

void help(GLuint texture)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void render_scene(const Scene *scene)
{
    set_material(&(scene->material));

    // water side
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(scene->water_pos.x, 0.0, 0.0);
    render_water_side(scene);
    glPopMatrix();
    glEnable(GL_LIGHTING);

    // water
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(0.0, scene->water_pos.y, 0.0);
    render_water_(scene);
    glPopMatrix();
    glEnable(GL_LIGHTING);

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
    glRotatef(scene->apache.tilt.z, 0.0, 0.0, 1.0);
    glVertex3f(scene->apache.pos.x, scene->apache.pos.y, scene->apache.pos.z);
    draw_model(&(scene->apache.model));
    glPopMatrix();

    // rotor top
    glPushMatrix();
    glTranslatef(scene->apache.pos.x, scene->apache.pos.y, scene->apache.pos.z);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glRotatef(scene->apache.tilt.x, 1.0, 0.0, 0.0);
    glRotatef(scene->apache.tilt.z, 0.0, 0.0, 1.0);
    glRotatef(scene->apache.rotor.rotation.y, 0.0, 1.0, 0.0);
    glVertex3f(scene->apache.pos.x, scene->apache.pos.y, scene->apache.pos.z);
    draw_model(&(scene->apache.rotor.rotorTop));
    glPopMatrix();

    // rotor back
    glPushMatrix();
    glTranslatef(scene->apache.pos.x, scene->apache.pos.y, scene->apache.pos.z);
    glRotatef(scene->apache.tilt.x, 1.0, 0.0, 0.0);
    glRotatef(scene->apache.tilt.z, 0.0, -1.0, 0.0);
    glTranslatef(0.3, 4.07, 3.125);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glRotatef(scene->apache.rotor.rotation.x, 1.0, 0.0, 0.0);
    glVertex3f(scene->apache.pos.x, scene->apache.pos.y, scene->apache.pos.z);
    draw_model(&(scene->apache.rotor.rotorBack));
    glPopMatrix();

    // F1 help
    if (scene->helpShow)
    {
        help(scene->help_texture);
    }
}

void render_water_side(const Scene *scene)
{
    glBindTexture(GL_TEXTURE_2D, scene->water_texture);
    glBegin(GL_QUADS);
    glPushMatrix();
    for (int i = -50; i < 50; i++)
    {
        for (int j = -30; j <= 30; j++)
        {
            glTexCoord2f(0, 1);
            glVertex3f(j, i, 0);

            glTexCoord2f(1, 1);
            glVertex3f(j + 1, i, 0);

            glTexCoord2f(1, 0);
            glVertex3f(j + 1, i + 1, 0);

            glTexCoord2f(0, 0);
            glVertex3f(j, i + 1, 0);
        }
    }
    glPopMatrix();
    glEnd();
}

void render_water_(const Scene *scene)
{
    glBindTexture(GL_TEXTURE_2D, scene->water_texture);
    glBegin(GL_QUADS);
    glPushMatrix();
    for (int i = -50; i < 50; i++)
    {
        for (int j = -30; j <= 30; j++)
        {
            glTexCoord2f(0, 1);
            glVertex3f(j, i, 0);

            glTexCoord2f(1, 1);
            glVertex3f(j + 1, i, 0);

            glTexCoord2f(1, 0);
            glVertex3f(j + 1, i + 1, 0);

            glTexCoord2f(0, 0);
            glVertex3f(j, i + 1, 0);
        }
    }
    glPopMatrix();
    glEnd();
}

int showEndGameDialog()
{
    const SDL_MessageBoxButtonData buttons[] = {
        {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "Exit"},
        {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Restart"},
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        {{255, 0, 0},
         {0, 255, 0},
         {255, 255, 0},
         {0, 0, 255},
         {255, 0, 255}}};

    const SDL_MessageBoxData messageBoxData = {
        SDL_MESSAGEBOX_INFORMATION,
        NULL,
        "Drowned",
        "You flew the helicopter into the ocean!",
        SDL_arraysize(buttons),
        buttons,
        &colorScheme};

    int buttonid;
    SDL_ShowMessageBox(&messageBoxData, &buttonid);

    return buttonid;
}