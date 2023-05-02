#include "app.h"

#include <SDL2/SDL_image.h>

void init_app(App *app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0)
    {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "Cube!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL);
    if (app->window == NULL)
    {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0)
    {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL)
    {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;
}

void init_opengl()
{
    glShadeModel(GL_SMOOTH);

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO)
    {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else
    {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(
        -.08, .08,
        -.06, .06,
        .1, 70);
}

void handle_app_events(App *app)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            case SDL_SCANCODE_KP_PLUS:
                app->scene.lightingLevel += 0.2f;
                set_lighting(app->scene.lightingLevel);
                break;
            case SDL_SCANCODE_KP_MINUS:
                app->scene.lightingLevel -= 0.2f;
                set_lighting(app->scene.lightingLevel);
                break;
            case SDL_SCANCODE_W:
                if (app->camera.locked)
                {
                    if (!app->scene.apache.backward)
                    {
                        set_apache_speed(&(app->scene.apache), 3);
                        set_tilt_speed(&(app->scene.apache), 3);
                        app->scene.apache.forward = true;
                    }
                }
                else
                {
                    set_camera_speed(&(app->camera), 3);
                }
                break;
            case SDL_SCANCODE_S:
                if (app->camera.locked)
                {
                    if (!app->scene.apache.forward)
                    {
                        set_apache_speed(&(app->scene.apache), -3);
                        set_tilt_speed(&(app->scene.apache), -3);
                        app->scene.apache.backward = true;
                    }
                }
                else
                {
                    set_camera_speed(&(app->camera), -3);
                }
                break;
            case SDL_SCANCODE_A:
                if (app->camera.locked)
                {
                    set_apache_side_speed(&(app->scene.apache), 3);
                }
                else
                {
                    set_camera_side_speed(&(app->camera), 3);
                }
                break;
            case SDL_SCANCODE_D:
                if (app->camera.locked)
                {
                    set_apache_side_speed(&(app->scene.apache), -3);
                }
                else
                {
                    set_camera_side_speed(&(app->camera), -3);
                }
                break;
            case SDL_SCANCODE_SPACE:
                if (app->camera.locked)
                {
                    set_rotorTop_speed(&(app->scene.apache), 5);
                    set_rotorBack_speed(&(app->scene.apache), 5);
                    set_apache_vertical_speed(&(app->scene.apache), 3);
                }
                else
                {
                    set_camera_vertical_speed(&(app->camera), 3);
                }
                break;
            case SDL_SCANCODE_LSHIFT:
                if (app->camera.locked)
                {
                    set_apache_vertical_speed(&(app->scene.apache), -3);
                }
                else
                {
                    set_camera_vertical_speed(&(app->camera), -3);
                }
                break;
            case SDL_SCANCODE_L:
                if (app->camera.locked)
                {
                    app->camera.locked = false;
                }
                else
                {
                    app->camera.locked = true;
                    app->camera.rotation.x = 350.0;
                    app->camera.rotation.y = 0.0;
                    app->camera.rotation.z = 268.0;
                }
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                if (app->camera.locked)
                {
                    set_apache_speed(&(app->scene.apache), 0);
                    set_tilt_speed(&(app->scene.apache), -3);
                    app->scene.apache.forward = false;
                    app->scene.apache.backward = false;
                }
                else
                {
                    set_camera_speed(&(app->camera), 0);
                }
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                if (app->camera.locked)
                {
                    set_apache_side_speed(&(app->scene.apache), 0);
                }
                else
                {
                    set_camera_side_speed(&(app->camera), 0);
                }
                break;
            case SDL_SCANCODE_SPACE:
            case SDL_SCANCODE_LSHIFT:
                if (app->camera.locked)
                {
                    set_apache_vertical_speed(&(app->scene.apache), 0);
                }
                else
                {
                    set_camera_vertical_speed(&(app->camera), 0);
                }
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down && !app->camera.locked)
            {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;
        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;
        case SDL_QUIT:
            app->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_app(App *app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    update_camera(&(app->camera), elapsed_time);
    update_scene(&(app->scene));
    move_apache(&(app->scene.apache), elapsed_time);
    rotate_rotor(&(app->scene.apache), elapsed_time);

    lock_apache_camera(app);

    tilt_apache_forward(&(app->scene.apache), elapsed_time, app->scene.apache.forward);
    tilt_apache_backward(&(app->scene.apache), elapsed_time, app->scene.apache.backward);

    printf("%f \n ",app->scene.apache.tilt.x);
}

void render_app(App *app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
    glPopMatrix();

    if (app->camera.is_preview_visible)
    {
        show_texture_preview();
    }

    SDL_GL_SwapWindow(app->window);
}

void destroy_app(App *app)
{
    if (app->gl_context != NULL)
    {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL)
    {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
}

void lock_apache_camera(App *app)
{
    if (app->camera.locked)
    {
        app->camera.position.x = app->scene.apache.pos.x;
        app->camera.position.z = app->scene.apache.pos.z + 4.5;
        app->camera.position.y = app->scene.apache.pos.y + 8.0;
    }
    else
    {
        set_view(&(app->camera));
    }
}
