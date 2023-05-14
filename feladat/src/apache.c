#include "apache.h"

void init_apache(Apache *apache)
{
    load_model(&(apache->model), "assets/models/apache.obj");
    apache->texture_id = load_texture("assets/textures/apacheBase.jpg");

    load_model(&(apache->rotor.rotorBack), "assets/models/rotorBack.obj");
    load_model(&(apache->rotor.rotorTop), "assets/models/rotorTop.obj");

    apache->pos.x = 0.0;
    apache->pos.y = 0.0;
    apache->pos.z = 0.0;

    apache->speed.x = 0.0;
    apache->speed.y = 0.0;
    apache->speed.z = 0.0;

    apache->rotor.rotation.x = 0.0;
    apache->rotor.rotation.y = 0.0;
    apache->rotor.rotation.z = 0.0;

    apache->rotor.rotationSpeed.x = 0.0;
    apache->rotor.rotationSpeed.y = 0.0;
    apache->rotor.rotationSpeed.z = 0.0;

    apache->tilt.x = 0.0;
    apache->tilt.y = 0.0;
    apache->tilt.z = 0.0;

    apache->tiltSpeed.x = 0.0;
    apache->tiltSpeed.y = 0.0;
    apache->tiltSpeed.z = 0.0;

    apache->forward = false;
    apache->backward = false;
    apache->left = false;
    apache->right = false;

    apache->rotor.active = false;

    apache->tiltBlock = true;
    
    apache->rotor.pos.x = 0.0;
    apache->rotor.pos.y = 0.0;
    apache->rotor.pos.z = 0.0;

    apache->rotor.rotation.x = 0.0;
    apache->rotor.rotation.y = 0.0;
    apache->rotor.rotation.z = 0.0;

    apache->rotor.rotationSpeed.x = 0.0;
    apache->rotor.rotationSpeed.y = 0.0;
    apache->rotor.rotationSpeed.z = 0.0;

    apache->tilt.x = 0.0;
    apache->tilt.y = 0.0;
    apache->tilt.z = 0.0;

    apache->tiltSpeed.x = 0.0;
    apache->tiltSpeed.y = 0.0;
    apache->tiltSpeed.z = 0.0;
}

void set_apache_pos(Apache *apache, vec3 newPos)
{
    apache->pos.x += newPos.x;
    apache->pos.y += newPos.y;
    apache->pos.z += newPos.z;
}

void set_apache_speed(Apache *apache, double speed)
{
    apache->speed.y = -speed;
}

void set_apache_side_speed(Apache *apache, double speed)
{
    apache->speed.x = speed;
}

void set_apache_vertical_speed(Apache *apache, double speed)
{
    apache->speed.z = speed;
}

void move_apache(Apache *apache, double time)
{
    apache->pos.x += apache->speed.x * time;
    apache->pos.y += apache->speed.y * time;
    apache->pos.z += apache->speed.z * time;
}

void rotate_rotor(Apache *apache, double time)
{
    if (apache->rotor.rotation.z < 0)
    {
        apache->rotor.rotation.z += 360.0;
    }

    if (apache->rotor.rotation.z > 360.0)
    {
        apache->rotor.rotation.z -= 360.0;
    }

    if (apache->rotor.rotation.x < 0)
    {
        apache->rotor.rotation.x += 360.0;
    }

    if (apache->rotor.rotation.x > 360.0)
    {
        apache->rotor.rotation.x -= 360.0;
    }

    //top rotor speed up/slow donw
    apache->rotor.rotation.y += apache->rotor.rotationSpeed.y;
    if (apache->rotor.rotationSpeed.y <= 8 && apache->rotor.active)
    {
        apache->rotor.rotationSpeed.y += time;
    }

    if (!apache->rotor.active && apache->rotor.rotationSpeed.y >= 0.0)
    {
        apache->rotor.rotationSpeed.y -= time;
    }

    //slow down the top rotor speed to 0
    if (apache->rotor.rotationSpeed.y < 0.0)
    {
        apache->rotor.rotationSpeed.y = 0.0;
    }

    //back rotor speed up/slow donw
    apache->rotor.rotation.x += apache->rotor.rotationSpeed.x;
    if (apache->rotor.rotationSpeed.x <= 8 && apache->rotor.active)
    {
        apache->rotor.rotationSpeed.x += time;
    }

    if (!apache->rotor.active && apache->rotor.rotationSpeed.x >= 0.0)
    {
        apache->rotor.rotationSpeed.x -= time;
    }

    //slow down the back rotor speed to 0
    if (apache->rotor.rotationSpeed.x < 0.0)
    {
        apache->rotor.rotationSpeed.x = 0.0;
    }
    
}

void set_rotorTop_speed(Apache *apache, double speed)
{
    apache->rotor.rotationSpeed.y = speed;
}

void set_rotorBack_speed(Apache *apache, double speed)
{
    apache->rotor.rotationSpeed.x = speed;
}

void set_tilt_speed(Apache* apache, double speed)
{
    apache->tiltSpeed.x = speed;
}

void set_side_tilt_speed(Apache* apache, double speed)
{
    apache->tiltSpeed.z = speed;
}

void tilt_apache_forward(Apache *apache, double time, bool tilt)
{
    if (tilt)
    {
        if (apache->tilt.x < 30.0)
        {
            apache->tilt.x += time * apache->tiltSpeed.x * 12;
        }
    }
    else
    {
        if (apache->tilt.x > 0)
        {
            apache->tilt.x -= time * apache->tiltSpeed.x * -12;
        }
    }
}

void tilt_apache_backward(Apache *apache, double time, bool tilt)
{
    if (tilt)
    {
        if (apache->tilt.x > -30.0)
        {
            apache->tilt.x += time * apache->tiltSpeed.x * 12;
        }
    }
    else
    {
        if (apache->tilt.x < 0)
        {
            apache->tilt.x -= time * apache->tiltSpeed.x * 12;
        }
    }
}

void tilt_apache_right(Apache *apache, double time, bool tilt)
{
    if (tilt)
    {
        if (apache->tilt.z < 30.0)
        {
            apache->tilt.z += time * apache->tiltSpeed.z * -12;
        }
    }
    else
    {
        if (apache->tilt.z > 0)
        {
            apache->tilt.z -= time * apache->tiltSpeed.z * -12;
        }
    }
}

void tilt_apache_left(Apache *apache, double time, bool tilt)
{
    if (tilt)
    {
        if (apache->tilt.z > -30.0)
        {
            apache->tilt.z += time * apache->tiltSpeed.z * -12;
        }
    }
    else
    {
        if (apache->tilt.z < 0)
        {
            apache->tilt.z -= time * apache->tiltSpeed.z * 12;
        }
    }
}
