#include "TXLib.h"
#include "Math.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

struct Ball
{
    int radius;
    Vector2f position;
    Vector2f v;

    int red;
    int green;
    int blue;
};

void controls(Ball* ball)
{
    if (GetAsyncKeyState (VK_LEFT))
    {
        if (ball->v.x > -10)
        {
            ball->v.x = ball->v.x - 1;
        }
    }

    if (GetAsyncKeyState (VK_RIGHT))
    {
        if (ball->v.x < 10)
        {
            ball->v.x = ball->v.x + 1;
        }
    }

    if (GetAsyncKeyState (VK_UP))
    {
        if (ball->v.y > -10)
        {
            ball->v.y = ball->v.y - 1;
        }
    }

    if (GetAsyncKeyState (VK_DOWN))
    {
        if (ball->v.y < 10)
        {
            ball->v.y = ball->v.y + 1;
        }
    }
}


void createBall(Ball ball)
{
    for (int i = 0; i < ball.radius; i++)
    {
        txSetFillColor(RGB(i * ball.red / ball.radius, i * ball.green / ball.radius, i * ball.blue / ball.radius));

        txSetColor(RGB(i * ball.red / ball.radius, i * ball.green / ball.radius, i * ball.blue / ball.radius));

        txCircle(ball.position.x + i/2, ball.position.y - i/2, ball.radius - i);
    }
}

void changeCoordinate(Ball *ball, float coordinate, int type)
{
    if (type == 1)

    {
        float S = coordinate - ball->position.x + ball->radius;
        float xTime = S / (ball->v.x);

        ball->position.y = ball->position.y + xTime * (ball->v.y);
        ball->position.x = coordinate + ball->radius;
    }

    if (type == 2)

    {
        float S = ball->position.x + ball->radius - coordinate;
        float xTime = S / (ball->v.x);
        ball->position.y = ball->position.y + xTime * (ball->v.y);
        ball->position.x = coordinate - ball->radius;
    }

    if (type == 3)

    {
        float S = ball->position.y + ball->radius - coordinate;

        float yTime = S / (ball->v.y);
        ball->position.x = ball->position.x + yTime * (ball->v.x);
        ball->position.y = coordinate - ball->radius;
    }

    if (type == 4)
    {
        float S = coordinate - ball->position.y + ball->radius;
        float yTime = S / (ball->v.y);
        ball->position.x = ball->position.x + yTime * (ball->v.x);
        ball->position.y = coordinate + ball->radius;
    }
}


void moveBall(Ball *ball, float dt)
{

    ball->position = ball->position + ball->v * dt;

    if (ball->position.x - ball->radius < 0)
    {
        changeCoordinate(ball, 0, 1);
        ball->v.x = -ball->v.x;
    }

    if (ball->position.x + ball->radius > 1280)
    {
        changeCoordinate(ball, 1280, 2);
        ball->v.x = -ball->v.x;
    }

    if (ball->position.y + ball->radius > 720)
    {
        changeCoordinate(ball, 720, 3);
        ball->v.y = -ball->v.y;
    }

    if (ball->position.y - ball->radius < 0)
    {
        changeCoordinate(ball, 0, 4);
        ball->v.y = -ball->v.y;
    }

}

bool isCollision(Ball *ball, Ball *ball2)
{
    if (ball->radius + ball2->radius > (ball->position - ball2->position).len())
    {
        //cout << "Ah shit, here we go again" << endl;
        return true;
    }
    return false;
}

void resolveByImpulse(Ball* ball, Ball* ball2)
{
    //V
    Vector2f ball1v = ball->v;
    Vector2f ball2v = ball2->v;

    ball->v = ball2v;
    ball2->v = ball1v;

    //Position

    float len = (ball2->position - ball->position).len();
    float shift = ball->radius + ball2->radius - len;
    //cout << "Len:" << len << endl;
    //cout << "Shift:" << shift << endl;

    ball->position = ball-> position - (ball2->position - ball->position).normalize() * shift;
}

void collision(Ball* ball, Ball* ball2)
{
    if (!isCollision(ball, ball2))
        return;

    resolveByImpulse(ball, ball2);
}


void create(Ball* ball, int count)
{
    int i = 0;
    while (i < count)
    {
        createBall(ball[i]);
        i++;
    }
}

void move(Ball* ball, float dt, int count)
{
    int i = 0;
    while (i < count)
    {
        moveBall(&ball[i], dt);
        i++;
    }
}


void collide(Ball* ball, float dt, int count)
{
    for (int i = 0; i < count; i++)
        for (int u = i; u < count; u++)
            if (&ball[i] != &ball[u])
            {
                collision(&ball[i], &ball[u]);
            }
}

int main()
{
    int width = 1280;
    int height = 720;

    txCreateWindow(width, height);

    float dt = 1;
    int life = 10;
    int ballCount = 50;
    int radius = 20;

    Ball gas[ballCount];

    for (int i = 0; i < ballCount; i++)
    {
        gas[i].radius = radius;
        gas[i].position = Vector2f(radius + rand() % (width - radius), radius + rand() % (height - radius));
        gas[i].v = Vector2f(1 + rand() % 20, 1 + rand() % 20);
        gas[i].red = 1 + rand() % 255;
        gas[i].green = 1 + rand() % 255;
        gas[i].blue = 1 + rand() % 255;
    }


    while(life > 0)
    {
        move(gas, dt, ballCount);

        txBegin ();

        txSetFillColor(RGB(0,0,0));
        txClear();

        create(gas, ballCount);

        txEnd ();

        collide(gas, dt, ballCount);
    }

    return 0;
}
