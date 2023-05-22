#include "scene.h"
#include "mapbox.h"

#include <obj/load.h>
#include <obj/draw.h>
#include <SDL2/SDL.h>

void init_mapbox(Mapbox* mapbox)
{
    mapbox->top = load_texture("assets/textures/top.jpg");
    mapbox->front = load_texture("assets/textures/front.jpg");
    mapbox->back = load_texture("assets/textures/back.jpg");
    mapbox->left = load_texture("assets/textures/left.jpg");
    mapbox->right = load_texture("assets/textures/right.jpg");
}

void render_mapbox(const Mapbox* mapbox)
{
    glDepthFunc(GL_LESS);

    // top
    glBindTexture(GL_TEXTURE_2D, mapbox->top);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-50.0f, 50.0f, 60.0f);

    glTexCoord2f(0, 1);
    glVertex3f(50.0f, 50.0f, 60.0f);

    glTexCoord2f(1, 1);
    glVertex3f(50.0f, -50.0f, 60.0f);

    glTexCoord2f(1, 0);
    glVertex3f(-50.0f, -50.0f, 60.0f);
    glEnd();

    // front
    glBindTexture(GL_TEXTURE_2D, mapbox->front);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(50.0f, 50.0f, -40.0f);

    glTexCoord2f(0, 0);
    glVertex3f(50.0f, 50.0f, 60.0f);

    glTexCoord2f(1, 0);
    glVertex3f(50.0f, -50.0f, 60.0f);

    glTexCoord2f(1, 1);
    glVertex3f(50.0f, -50.0f, -40.0f);
    glEnd();

    // back
    glBindTexture(GL_TEXTURE_2D, mapbox->back);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex3f(-50.0f, -50.0f, -40.0f);

    glTexCoord2f(0, 0);
    glVertex3f(-50.0f, -50.0f, 60.0f);

    glTexCoord2f(1, 0);
    glVertex3f(-50.0f, 50.0f, 60.0f);

    glTexCoord2f(1, 1);
    glVertex3f(-50.0f, 50.0f, -40.0f);
    glEnd();

    // left
    glBindTexture(GL_TEXTURE_2D, mapbox->left);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1);
    glVertex3f(50.0f, 50.0f, -40.0f);

    glTexCoord2f(1, 0);
    glVertex3f(50.0f, 50.0f, 60.0f);

    glTexCoord2f(0, 0);
    glVertex3f(-50.0f, 50.0f, 60.0f);

    glTexCoord2f(0, 1);
    glVertex3f(-50.0f, 50.0f, -40.0f);
    glEnd();

    // right
    glBindTexture(GL_TEXTURE_2D, mapbox->right);
    glBegin(GL_QUADS);
    glTexCoord2f(1, 1);
    glVertex3f(-50.0f, -50.0f, -40.0f);

    glTexCoord2f(1, 0);
    glVertex3f(-50.0f, -50.0f, 60.0f);

    glTexCoord2f(0, 0);
    glVertex3f(50.0f, -50.0f, 60.0f);

    glTexCoord2f(0, 1);
    glVertex3f(50.0f, -50.0f, -40.0f);
    glEnd();
}