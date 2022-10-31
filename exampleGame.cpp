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
// EJE Y {-3;3} -3 BORDE SUPERIOR / 3 BORDE INFERIOR
// box2d trabaja en metros y sdl en pixeles.
void set_pixel(Renderer &renderer, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    renderer.SetDrawColor(r,g,b,a);
    renderer.DrawPoint( x, y);
}

void draw_circle(Renderer &renderer , int n_cx, int n_cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    // if the first pixel in the screen is represented by (0,0) (which is in sdl)
    // remember that the beginning of the circle is not in the middle of the pixel
    // but to the left-top from it:

    double error = (double)-radius;
    double x = (double)radius - 0.5;
    double y = (double)0.5;
    double cx = n_cx - 0.5;
    double cy = n_cy - 0.5;

    while (x >= y) {
        set_pixel(renderer, (int)(cx + x), (int)(cy + y), r, g, b, a);
        set_pixel(renderer, (int)(cx + y), (int)(cy + x), r, g, b, a);
        if (x != 0) {
            set_pixel(renderer, (int)(cx - x), (int)(cy + y), r, g, b, a);
            set_pixel(renderer, (int)(cx + y), (int)(cy - x), r, g, b, a);
        }
        if (y != 0) {
            set_pixel(renderer, (int)(cx + x), (int)(cy - y), r, g, b, a);
            set_pixel(renderer, (int)(cx - y), (int)(cy + x), r, g, b, a);
        }
        if (x != 0 && y != 0) {
            set_pixel(renderer, (int)(cx - x), (int)(cy - y), r, g, b, a);
            set_pixel(renderer, (int)(cx - y), (int)(cy - x), r, g, b, a);
        }

        error += y;
        ++y;
        error += y;

        if (error >= 0) {
            --x;
            error -= x;
            error -= x;
        }
    }
}
void fill_circle(Renderer &renderer, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    // Note that there is more to altering the bitrate of this
    // method than just changing this value.  See how pixels are
    // altered at the following web page for tips:
    //   http://www.libsdl.org/intro.en/usingvideo.html
    static const int BPP = 4;

    //double ra = (double)radius;

    for (double dy = 1; dy <= radius; dy += 1.0)
    {
        // This loop is unrolled a bit, only iterating through half of the
        // height of the circle.  The result is used to draw a scan line and
        // its mirror image below it.

        // The following formula has been simplified from our original.  We
        // are using half of the width of the circle because we are provided
        // with a center and we need left/right coordinates.

        double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
        int x = cx - dx;
        renderer.SetDrawColor(r, g, b, a);
        renderer.DrawLine(cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
        renderer.DrawLine(cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);

    }
}
/*
void drawCircle(Renderer& renderer, int32_t centreX, int32_t centreY, int32_t radius) {
    Texture texture_ball(renderer, DATA_PATH "/grass.png");
    renderer.SetDrawColor(255,255,255);
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y) {
        // Each of the following renders an octant of the circle
        renderer.DrawPoint(centreX + x, centreY - y);
        renderer.DrawPoint(centreX + x, centreY + y);
        renderer.DrawPoint(centreX - x, centreY - y);
        renderer.DrawPoint(centreX - x, centreY + y);
        renderer.DrawPoint(centreX + y, centreY - x);
        renderer.DrawPoint(centreX + y, centreY + x);
        renderer.DrawPoint(centreX - y, centreY - x);
        renderer.DrawPoint(centreX - y, centreY + x);

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        } else if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}
*/
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
    edge.SetTwoSided(b2Vec2(-4,2.5), b2Vec2(4,2.5)); // Tamaño del piso

    edgeFixtureDef.shape = &edge;
    groundLineBody->CreateFixture(&edgeFixtureDef);

// CREACION DE LA TEXTURA DE FONDO
    Texture texture_stadium(renderer, DATA_PATH "/stadium2.png");
// CREACION DE LA TEXTURA DE CAJA
    Texture texture_box(renderer, DATA_PATH "/box.jpg");
// CREACION DE LA TEXTURA DEL PISO
    Texture texture_ground(renderer, DATA_PATH "/grass.png");
// CREACION DE LA TEXTURA DE PELOTA
    Texture texture_ball(renderer, DATA_PATH "/ball.png");



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

//CREACION PELOTA EN BOX2D
    // Ball
    // cartesian origin box
    float x_ball = -2.0f;
    float y_ball = -2.0f;

    // size of ball
    float radius = 0.2;


    b2Body* circle;

    //b2BodyDef boxBodyDef;
    boxBodyDef.type = b2_dynamicBody;
    boxBodyDef.position.Set(x_ball, y_ball);
    circle = world.CreateBody(&boxBodyDef);

    b2CircleShape shapeCircle;
    shapeCircle.m_p.Set(x_ball, y_ball);
    shapeCircle.m_radius = radius;

    b2FixtureDef fixtureCircle;
    fixtureCircle.shape = &shapeCircle;
    fixtureCircle.density = 1;
    fixtureCircle.friction = 0.3f;
    fixtureCircle.restitution = 0.5f;
    circle->CreateFixture(&fixtureCircle);
    bool close_game = false;
    SDL_Event event;

    // The game Loop
    while(close_game != true)
    {
        b2Vec2 posBox = body->GetPosition(); // Body from box
        float angle = body->GetAngle(); // Body from box
        b2Vec2 posBall = circle->GetPosition();
        Point pointBall(posBall.x*MET2PIX,posBall.y*MET2PIX);


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
        box.x = ((SCALED_WIDTH / 2.0f) + posBox.x) * MET2PIX  - box.w / 2;
        box.y = ((SCALED_HEIGHT / 2.0f) + posBox.y) * MET2PIX - box.h / 2;

        cout << "X of box:" << endl << box.x << endl;
        cout << "Y of box:" << endl << box.y << endl;

        renderer.Clear();
        renderer.SetDrawColor(255, 255, 0); // (255, 255, 0, 0)
        renderer.Copy(texture_stadium);

        // Draw ground
        //renderer.DrawLine(((SCALED_WIDTH / 2.0f) + edge.m_vertex1.x) * MET2PIX, ((SCALED_HEIGHT / 2.0f) + edge.m_vertex1.y) * MET2PIX, ((SCALED_WIDTH / 2.0f) + edge.m_vertex2.x) * MET2PIX, ((SCALED_HEIGHT / 2.0f) + edge.m_vertex2.y) * MET2PIX);
        //renderer.DrawLine(65, 200, 400, 200);
        //renderer.SetDrawColor(0, 255, 0);
        //renderer.Copy(texture_ground, NullOpt, platform);

        renderer.Copy(texture_box, NullOpt, box, angle, NullOpt, SDL_FLIP_NONE);
        for(int i = 0; i < 9; i++){
            renderer.Copy(texture_ground, Rect(15,59,10,13), Rect(0+(i*(MET2PIX/2+32)), 5.5*MET2PIX, MET2PIX/2+32, MET2PIX/2));
        }
        //drawCircle(renderer, (((SCALED_WIDTH / 2.0f) + posBall.x) * MET2PIX  - radius*MET2PIX / 2),(((SCALED_WIDTH / 2.0f) + posBall.y) * MET2PIX  - radius*MET2PIX / 2)/2+60,radius*MET2PIX);
        //draw_circle(renderer, (((SCALED_WIDTH / 2.0f) + posBall.x) * MET2PIX  - radius*MET2PIX / 2), (((SCALED_WIDTH / 2.0f) + posBall.y) * MET2PIX  - radius*MET2PIX / 2)/2+60, 20, 0x00, 0x00, 0xFF, 0xFF);
        //fill_circle(renderer, (((SCALED_WIDTH / 2.0f) + posBall.x) * MET2PIX  - radius*MET2PIX / 2), (((SCALED_WIDTH / 2.0f) + posBall.y) * MET2PIX  - radius*MET2PIX / 2)/2+60, 20, 0xFF, 0x00, 0xFF, 0xFF);
        cout <<"Pos y ball:" << ((SCALED_WIDTH / 2.0f) + posBall.y) * MET2PIX - radius*MET2PIX / 2<< endl;
        renderer.Copy(texture_ball,NullOpt, Rect(((SCALED_WIDTH / 2.0f) + posBall.x) * MET2PIX - 28,(((SCALED_WIDTH / 2.0f) + posBall.y) * MET2PIX  - radius*MET2PIX / 2)/2+40,40,40));
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

