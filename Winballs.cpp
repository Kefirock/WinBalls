#include "TXLib.h"
#include <math.h>
#include <iostream>

enum BallType
{
    Player,
    Enemy,
    Bonus
};

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

    BallType type;
};

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
    ball->x = ball->x + ball->vx * dt;
    ball->y = ball->y + ball->vy * dt;

    if (ball->x - ball->radius <= 0 or ball->x + ball->radius >= 1280)
    {
        ball->vx = -ball->vx;
    }

    if (ball->y - ball->radius <= 0 or ball->y + ball->radius >= 720)
    {
        ball->vy = -ball->vy;
    }
}

bool isCollision(Ball *ball, Ball *ball2)
{
    if (ball->radius + ball2->radius > sqrt(pow((ball->x - ball2->x),2) + pow((ball->y - ball2->y),2)))
    {
        return true;
    }
    return false;
}

void collision(Ball* ball, Ball* ball2, int* life)
{
    if (!isCollision(ball, ball2))
        return;

    if (ball->type == BallType::Enemy and ball2->type == BallType::Bonus or ball->type == BallType::Bonus and ball2->type == BallType::Enemy)
        {
            BallType btype = ball -> type;
            int bgreen = ball -> green;
            int bred = ball -> red;

            BallType btype2 = ball2 -> type;
            int bgreen2 = ball2 -> green;
            int bred2 = ball2 -> red;

            ball->type = btype2;
            ball->red = bred2;
            ball->green = bgreen2;

            ball2->type = btype;
            ball2->red = bred;
            ball2->green = bgreen;

            *life = *life + 1;
            std::cout << "Life:" << *life << std::endl;
        }

    if (ball->type == BallType::Player and ball2->type == BallType::Enemy)
        {
            *life = *life - 5;
            std::cout << "Life:" << *life << std::endl;
        }

    float vx1 = ball->vx;
    float vx2 = ball2->vx;

    float vy1 = ball->vy;
    float vy2 = ball2->vy;

    ball->vy = vy2;
    ball2->vy = vy1;

    ball->vx = vx2;
    ball2->vx = vx1;
}



int main()
{
    int width = 1280;
    int height = 720;

    txCreateWindow(width, height);

    float dt = 1;
    int life = 10;

    Ball player = {80, 200, 200, 0, 0, 0, 0, 255, BallType::Player};
    Ball enemy = {100, 600, 200, 10, -10, 255, 0, 0, BallType::Enemy};
    Ball bonus = {50, 800, 500, -10, 10, 0, 255, 0, BallType::Bonus};


    while(life > 0)
    {
        moveBall(&player, dt);
        moveBall(&enemy, dt);
        moveBall(&bonus, dt);
        controls(&player);

        txBegin ();

        txSetFillColor(RGB(0,0,0));
        txClear();

        createBall(player);
        createBall(enemy);
        createBall(bonus);

        txEnd ();

        collision(&player, &enemy, &life);
        collision(&player, &bonus, &life);
        collision(&enemy, &bonus, &life);
    }

    return 0;
}



