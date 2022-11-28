#include <iostream>
#include <exception>

#include <SDL2pp/SDL2pp.hh>
#include "box2d/include/box2d/box2d.h"
#include <list>


b2World* world;

const int MET2PIX = 80; // 640 / 80 = 8

const int WIDTH = 640;
const int HEIGHT = 480;

const int SCALED_WIDTH = WIDTH / MET2PIX; // 4 | 3
const int SCALED_HEIGHT = HEIGHT / MET2PIX;

//1 rad × 180/π = 57,296°
const float RAD2DEG = 180 / M_PI;

using namespace std;
using namespace SDL2pp;

// EJE X {-4;4}
// EJE Y {-3;3}
// box2d trabaja en metros y sdl en pixeles.

int main() try
{

    //Se inicia SDL y se crea una ventada y un render
    SDL sdl(SDL_INIT_VIDEO);

    Window window("Game",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WIDTH, HEIGHT,
            SDL_WINDOW_SHOWN);

    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    b2Vec2 gravity(0.0f, 9.8f); // new b2World(gravity));
    b2World world(gravity);

    //CREACION DEL PISO

    // cartesian origin
    float ground_x = 0.0f;
    float ground_y = 0.0f;

    // LineGround
    b2BodyDef myGroundDef;
    myGroundDef.type = b2_staticBody;
    myGroundDef.position.Set(ground_x, ground_y); // set the starting position x and y cartesian
    myGroundDef.angle = 0;

    b2Body* groundLineBody = world.CreateBody(&myGroundDef);

    //CREACION DE LOS PUNTOS PARA EL PISO
    b2FixtureDef edgeFixtureDef;
    b2EdgeShape edge;
    edge.SetTwoSided(b2Vec2(-2.5,0), b2Vec2(2.5,0)); // Tamaño del piso
    edgeFixtureDef.shape = &edge;
    groundLineBody->CreateFixture(&edgeFixtureDef);


// CREACION DE LA TEXTURA DE CAJA
    Texture texture_box(renderer, DATA_PATH "/box.png");

// CREACION DE LA TEXTURA DEL PISO
    Texture texture_ground(renderer, DATA_PATH "/ground.png");



//CREACION DE LA CAJA EN BOX2D

    // cartesian origin box
    float x_box = 0.0f;
    float y_box = -2.5f;

    // size of box
    float w_box = 0.5;
    float h_box = 0.5;

    // angle of the box
    float angle_box = 45.0f; //45.0f;

    // Box
    Rect box;
    b2Body* body;

    b2BodyDef boxBodyDef;
    boxBodyDef.type = b2_dynamicBody;
    boxBodyDef.angle = 45; // flips the whole thing -> 180 grad drehung
    boxBodyDef.position.Set(x_box, y_box);
    b2Vec2 vel;
   // vel.Set(0f, 0.1f);

    body = world.CreateBody(&boxBodyDef);
    //body->SetLinearVelocity(vel);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(w_box/2.0f,h_box/2.0f); // toma la mitad del tamaño

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.5f;
    body->CreateFixture(&fixtureDef);

    // box: convert Metres back to Pixels for width and height
    box.w = w_box * MET2PIX;
    box.h = h_box * MET2PIX;

    // point to center of box for angle
    /*
    Point center;
    center.x = box.w*0.5f;
    center.y = box.h - (box.w * 0.5);
*/
    // cartesian origin of _0019_PLATF.png 89 x 22
    //float x_plat = -3.6f; // to edge
    //float y_plat = -0.14f;// to edge

    // size of the platform
    //float w_plat = 89.0f / MET2PIX;
    //float h_plat = 22.0f / MET2PIX;

    // define a Rect for this platform and its body def
    /*
    Rect platform;
    b2Body* Body_platform;

    b2BodyDef platformBoyDef;
    platformBoyDef.type = b2_staticBody;
    platformBoyDef.position.Set(x_plat, y_plat);

    Body_platform = world.CreateBody(&platformBoyDef);

    b2PolygonShape platformTile;    // subtracting radius fixes the incorrect little gap that can appear when working with really small resolutions
    platformTile.SetAsBox((w_plat / 2.0f) - platformTile.m_radius, (h_plat / 2.0f) - platformTile.m_radius); // subtracting the radius kills the gap issue:
    b2FixtureDef fixturePlat;
    fixturePlat.shape = &platformTile;
    fixturePlat.density = 1.0f;
    fixturePlat.friction = 0.3f;
    fixturePlat.restitution = 0.5f;
    Body_platform->CreateFixture(&fixturePlat);

    // set the SDL_RECT rendering values
    platform.w = w_plat * MET2PIX;
    platform.h = h_plat * MET2PIX;
    platform.x = ((SCALED_WIDTH / 2.0f) + x_plat) * MET2PIX - platform.w / 2;
    platform.y = ((SCALED_HEIGHT / 2.0f) + y_plat) * MET2PIX - platform.h / 2;

    */

    bool close_game = false;
    SDL_Event event;

    // The game Loop
    while(close_game != true)
    {
        b2Vec2 pos = body->GetPosition(); // Body from box
        float angle = body->GetAngle(); // Body from box

        //RAD2DEG
        angle = angle*RAD2DEG;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                close_game = true;

            else if(event.key.keysym.sym == SDLK_ESCAPE)
                close_game = true;

            else if (event.key.keysym.sym == SDLK_r)
            {
                body->SetTransform(b2Vec2(x_box, y_box), angle_box);
                body->SetLinearVelocity(vel);
                break;
            }
        }

        // question box, update x and y destination
        box.x = ((SCALED_WIDTH / 2.0f) + pos.x) * MET2PIX  - box.w / 2;
        box.y = ((SCALED_HEIGHT / 2.0f) + pos.y) * MET2PIX - box.h / 2 ;

        cout << "X of box:" << endl << box.x << endl;
        cout << "Y of box:" << endl << box.y << endl;

        renderer.Clear();
        renderer.SetDrawColor(255, 255, 0); // (255, 255, 0, 0)

        // Draw ground
        renderer.DrawLine(((SCALED_WIDTH / 2.0f) + edge.m_vertex1.x) * MET2PIX, ((SCALED_HEIGHT / 2.0f) + edge.m_vertex1.y) * MET2PIX, ((SCALED_WIDTH / 2.0f) + edge.m_vertex2.x) * MET2PIX, ((SCALED_HEIGHT / 2.0f) + edge.m_vertex2.y) * MET2PIX);
        //renderer.DrawLine(65, 200, 400, 200);
        //renderer.SetDrawColor(0, 255, 0);
        //renderer.Copy(texture_ground, NullOpt, platform);

        renderer.Copy(texture_box, NullOpt, box, angle, NullOpt, SDL_FLIP_NONE);

        renderer.SetDrawColor(0, 0, 0); // (32, 70, 49, 0);

        renderer.Present();
        world.Step(1.0f / 60.0f, 6.0f, 2.0f); // update
        SDL_Delay(10);

    }

    SDL_Quit();
    return EXIT_SUCCESS;
} catch (std::exception& e) {
    // If case of error, print it and exit with error
    std::cerr << e.what() << std::endl;
    return 1;
}
