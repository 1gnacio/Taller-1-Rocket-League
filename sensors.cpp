
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

// EJE X {-4;4} -4 BORDE IZQUIERDO / 4 BORDE DERECHO
// EJE Y {-3;3} -3 BORDE SUPERIOR / 3 BORDE INFERIOR
// box2d trabaja en metros y sdl en pixeles.

int main() try {
    //Se inicia SDL y se crea una ventada y un render
    SDL sdl(SDL_INIT_VIDEO);

    Window window("Game",
                  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                  WIDTH, HEIGHT,
                  SDL_WINDOW_SHOWN);

    Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    b2Vec2 gravity(0.0f, 9.8f); // new b2World(gravity));
    b2World world(gravity);

    // cartesian origin
    float ground_x = 0.0f;
    float ground_y = 0.0f;

    // LineGround
    b2BodyDef myGroundDef;
    myGroundDef.type = b2_staticBody;
    myGroundDef.position.Set(ground_x, ground_y); // set the starting position x and y cartesian
    myGroundDef.angle = 0;

    b2Body* groundLineBody = world.CreateBody(&myGroundDef);
    b2Body* groundLine2 = world.CreateBody(&myGroundDef);
    b2Body* groundLine3 = world.CreateBody(&myGroundDef);
    b2Body* groundLine4 = world.CreateBody(&myGroundDef);

    // CREACION SUELO
    b2FixtureDef edgeFixtureDef;
    b2EdgeShape edge;

    edge.SetTwoSided(b2Vec2(-4,2.5), b2Vec2(4,2.5)); // Tamaño del piso
    edgeFixtureDef.shape = &edge;
    edgeFixtureDef.filter.categoryBits = 4;
    edgeFixtureDef.filter.maskBits = 1 | 2;
    groundLineBody->CreateFixture(&edgeFixtureDef);

    // PARED IZQUIERDA
    edge.SetTwoSided(b2Vec2(-4,-3), b2Vec2(-4,3));
    edgeFixtureDef.shape = &edge;
    groundLine2->CreateFixture(&edgeFixtureDef);

    // PARED DERECHA
    edge.SetTwoSided(b2Vec2(4,-3), b2Vec2(4,3));
    edgeFixtureDef.shape = &edge;
    groundLine3->CreateFixture(&edgeFixtureDef);

    // TECHO
    edge.SetTwoSided(b2Vec2(-4,-3), b2Vec2(4,-3));
    edgeFixtureDef.shape = &edge;
    groundLine4->CreateFixture(&edgeFixtureDef);



// CREACION DE LA TEXTURA DE FONDO
    Texture texture_stadium(renderer, DATA_PATH "/stadium2.png");
// CREACION DE LA TEXTURA DE CAJA
    Texture texture_car(renderer, DATA_PATH "/car/car4.png");
// CREACION DE LA TEXTURA DEL PISO
    Texture texture_ground(renderer, DATA_PATH "/grass.png");
// CREACION DE LA TEXTURA DE PELOTA
    Texture texture_ball(renderer, DATA_PATH "/ball.png");
// CREACION DE LA TEXTURA DE ARCO
    Texture texture_goal(renderer, DATA_PATH "/goal.png");



    // CREACION DEL AUTO

    // cartesian origin
    float xCar = 2.0f;
    float yCar = -2.0f;

    // size
    float wCar = 1.2;
    float hCar = 0.5;

    // angle
    float angleCar = 0.0f;;

    Rect car;
    b2Body* body;

    b2BodyDef boxBodyDef;
    boxBodyDef.type = b2_dynamicBody;
    boxBodyDef.angle = angleCar;
    boxBodyDef.position.Set(xCar, yCar);
    b2Vec2 vel0;
    vel0.Set(0.0f, 0.0f);

    body = world.CreateBody(&boxBodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(wCar / 2.0f, hCar / 2.0f); // toma la mitad del tamaño

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = 0.0f;
    fixtureDef.filter.categoryBits = 2;
    fixtureDef.filter.maskBits = 4;
    body->CreateFixture(&fixtureDef);

    // convierte metros a pixeles para dibujar.
    car.w = wCar * MET2PIX;
    car.h = hCar * MET2PIX;

    // CREACION PELOTA EN BOX2D
    float xBall = -0.0f;
    float yBall = -2.8f;
    float radius = 0.2;

    b2Body* circle;
    b2BodyDef circleDef;
    circleDef.type = b2_dynamicBody;
    circleDef.position.Set(xBall, yBall);
    circle = world.CreateBody(&circleDef);

    b2CircleShape shapeCircle;
    shapeCircle.m_radius = radius;

    b2FixtureDef fixtureCircle;
    fixtureCircle.shape = &shapeCircle;
    fixtureCircle.density = 0.5;
    fixtureCircle.friction = 0.3f;
    fixtureCircle.restitution = 0.6f; //  Capacidad de rebote
    fixtureCircle.filter.categoryBits = 1;
    fixtureCircle.filter.maskBits = 4;
    circle->CreateFixture(&fixtureCircle);

    // Estados iniciales
    bool close_game = false;
    bool is_running_right = false;
    bool is_running_left = false;
    bool is_jump = false;
    bool jumped = false;
    b2Vec2 velLeft(-2.0f,0.0f);
    b2Vec2 velRight(2.0f,0.0f);
    b2Vec2 velJump(0.0f,-3.0f);
    int src_y = 35;
    // The game Loop
    while(close_game != true) {
        SDL_Event event;
        b2Vec2 posCar = body->GetPosition(); // Posicion de auto
        float angle = body->GetAngle(); // Angulo del auto
        b2Vec2 posBall = circle->GetPosition();
        is_jump = false;
        //RAD2DEG
        angle = angle*RAD2DEG;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT)
                close_game = true;
            else if(event.key.keysym.sym == SDLK_ESCAPE)
                close_game = true;
            else if (event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                    case SDLK_RIGHT: is_running_right = true; break;
                    case SDLK_LEFT: is_running_left = true; break;
                    case SDLK_SPACE:
                        if(!jumped ){
                            is_jump = true;
                            break;
                        }
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT: is_running_right = false; break;
                    case SDLK_LEFT: is_running_left = false; break;
                }
            }
        }

        // Actualizo posiciones de los autos en SDL a partir de box2d
        car.x = ((SCALED_WIDTH / 2.0f) + posCar.x) * MET2PIX - car.w / 2;
        car.y = ((SCALED_HEIGHT / 2.0f) + posCar.y) * MET2PIX - car.h / 2;

        if (is_running_left) {
            body->ApplyForceToCenter(velLeft,SDL_TRUE);
            src_y = 0;

        } else if (is_running_right) {
            body->ApplyForceToCenter(velRight,SDL_TRUE);
            src_y = 0;

        }
        if(is_jump && !jumped){
            body->ApplyLinearImpulse(velJump, posCar, SDL_TRUE);
            jumped = true;
        }
        if(car.y == 398){
            jumped = false;
        }

        renderer.Clear();
        // DIBUJO BACKGROUND
        renderer.Copy(texture_stadium);
        // DIBUJO ARCOS
        renderer.Copy(texture_goal, Rect(15,0,200,400), Rect(0,HEIGHT-180,100,140));
        renderer.Copy(texture_goal, Rect(15,0,200,400), Rect(540,HEIGHT-180,100,140), 0, NullOpt,SDL_FLIP_HORIZONTAL);
        // DIBUJO AUTO
        renderer.Copy(texture_car, Rect(0, src_y, 1200, 635), car, angle, NullOpt, SDL_FLIP_NONE);

        // DIBUJO SUELO
        for(int i = 0; i < 9; i++){
            renderer.Copy(texture_ground, Rect(15,59,10,13), Rect(0+(i*(MET2PIX/2+32)), 5.5*MET2PIX, MET2PIX/2+32, MET2PIX/2));
        }

        renderer.Copy(texture_ball,NullOpt, Rect(((SCALED_WIDTH / 2.0f) + posBall.x) * MET2PIX - radius*MET2PIX/2,(((SCALED_HEIGHT / 2.0f) + posBall.y) * MET2PIX  - radius*MET2PIX / 2),25,25));

        renderer.Present();

        world.Step(1.0f / 60.0f, 6.0f, 2.0f); // updateToFrame box2d

        SDL_Delay(10);

    }

    SDL_Quit();
    return EXIT_SUCCESS;
} catch (std::exception& e) {
    // If case of error, print it and exit with error
    std::cerr << e.what() << std::endl;
    return 1;
}