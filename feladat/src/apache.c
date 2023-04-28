#include "apache.h"

void init_apache(Apache* apache)
{
    load_model(&(apache->model), "assets/models/apache.obj");
    apache->texture_id = load_texture("assets/textures/apacheBase.jpg");

    load_model(&(apache->rotor.rotorTop), "assets/models/rotorTop.obj");
    load_model(&(apache->rotor.rotorBack), "assets/models/rotorBack.obj");

    apache->pos.x = 0.0;
    apache->pos.y = 0.0;
    apache->pos.z = 0.0;

    apache->rotor.pos.x = 0.0;
    apache->rotor.pos.y = 0.0;
    apache->rotor.pos.z = 0.0;
}


void set_apache_pos(Apache* apache, vec3 newPos)
{
    apache->pos.x += newPos.x;
    apache->pos.y += newPos.y;
    apache->pos.z += newPos.z;
}