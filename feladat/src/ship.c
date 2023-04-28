#include "ship.h"


void init_ship(Ship* ship)
{
    load_model(&(ship->model), "assets/models/ship.obj");
    ship->texture_id = load_texture("assets/textures/shipBase.jpg");
}