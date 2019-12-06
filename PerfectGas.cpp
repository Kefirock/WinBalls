#include "TXLib.h"
#include <math.h>
#include <iostream>

struct Ball
{
    int radius;
    int x;
    int y;
    float vx;
    float vy;

    int red;
    int green;
    int blue;
};

float pointsDistance(Ball *ball, Ball *ball2)
    {
        return sqrt(pow((ball->x - ball2->x),2) + pow((ball->y - ball2->y),2));
    }

void controls(Ball* ball)
{
    if (GetAsyncKeyState (VK_LEFT))
    {
        if (ball->vx > -10)
        {
            ball->vx = ball->vx - 1;
        }
    }

    if (GetAsyncKeyState (VK_RIGHT))
    {
        if (ball->vx < 10)
        {
            ball->vx = ball->vx + 1;
        }
    }

    if (GetAsyncKeyState (VK_UP))
    {
        if (ball->vy > -10)
        {
            ball->vy = ball->vy - 1;
        }
    }

    if (GetAsyncKeyState (VK_DOWN))
    {
        if (ball->vy < 10)
        {
            ball->vy = ball->vy + 1;
        }
    }
}


void createBall(Ball ball)
{
    for (int i = 0; i < ball.radius; i++)
    {
        txSetFillColor(RGB(i * ball.red / ball.radius, i * ball.green / ball.radius, i * ball.blue / ball.radius));

        txSetColor(RGB(i * ball.red / ball.radius, i * ball.green / ball.radius, i * ball.blue / ball.radius));

        txCircle(ball.x + i/2, ball.y - i/2, ball.radius - i);
    }
}


void moveBall(Ball *ball, float dt)
{
    float ballx = ball->x;
    float bally = ball->y;

    float len = sqrt(pow((ball->x),2) + pow((ball->y),2));
    //std::cout << "Len:" << len << std::endl;




    ball->x = ball->x + ball->vx * dt;
    ball->y = ball->y + ball->vy * dt;

    if (ball->x - ball->radius <= 0 or ball->x + ball->radius >= 1280)
    {
        ball->vx = -ball->vx;

        if (ball->x - ball->radius < 0)
        {
            ball->x = 0 + ball->radius;
        }

        if (ball->x - ball->radius > 1280)
        {
            ball->x = 1280 - ball->radius;
        }

    }

    if (ball->y - ball->radius <= 0 or ball->y + ball->radius >= 720)
    {
        ball->vy = -ball->vy;


        if (ball->y - ball->radius > 720)
        {
            ball->y = 720 - ball->radius;
        }


        if (ball->y - ball->radius < 0)
        {
            ball->y = 0 + ball->radius;
        }
    }
}

bool isCollision(Ball *ball, Ball *ball2)
{
    if (ball->radius + ball2->radius > pointsDistance(ball, ball2))
    {
        return true;
    }
    return false;
}

void resolveByImpulse(Ball* ball, Ball* ball2)
{
    float vx1 = ball->vx;
    float vx2 = ball2->vx;

    float vy1 = ball->vy;
    float vy2 = ball2->vy;

    ball->vy = vy2;
    ball2->vy = vy1;

    ball->vx = vx2;
    ball2->vx = vx1;

    float coll = ball->radius + ball2->radius - pointsDistance(ball, ball2);

    if (coll > 0)
    {
        float ballx = ball->x;
        float bally = ball->y;
        float ball2x = ball2->x;
        float ball2y = ball2->y;

        float len = pointsDistance(ball, ball2);

        ball->x = ball->x + (ballx - ball2x) * coll / len;
        ball->y = ball->y + (bally - ball2y) * coll / len;
    }
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

    Ball gas[100];

    for (int i = 0; i<100; i++)
        gas[i] = {25, 1 + rand() % 1200, 1 + rand() % 640, 1 + rand() % 20, 1 + rand() % 20, 1 + rand() % 255, 1 + rand() % 255, 1 + rand() % 255};


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



