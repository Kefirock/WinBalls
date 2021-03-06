#include "Math.h"

struct Ball
{
    int radius;
    Vector2f position;
    Vector2f v;

    int red;
    int green;
    int blue;

    void controls(Ball* ball)
    {
        if (GetAsyncKeyState (VK_LEFT))
        {
            if (ball->position.x > -10)
            {
                ball->position.x = ball->position.x - 1;
            }
        }

        if (GetAsyncKeyState (VK_RIGHT))
        {
            if (ball->position.x < 10)
            {
                ball->position.x = ball->position.x + 1;
            }
        }

        if (GetAsyncKeyState (VK_UP))
        {
            if (ball->position.y > -10)
            {
                ball->position.y = ball->position.y - 1;
            }
        }

        if (GetAsyncKeyState (VK_DOWN))
        {
            if (ball->position.y < 10)
            {
                ball->position.y = ball->position.y + 1;
            }
        }
    }

    void drawBall()
    {
        for (int i = 0; i < radius; i++)
        {
            txSetFillColor(RGB(i * red / radius, i * green / radius, i * blue / radius));

            txSetColor(RGB(i * red / radius, i * green / radius, i * blue / radius));

            txCircle(position.x + i/2, position.y - i/2, radius - i);
        }
    }

    void changeCoordinate(float coordinate, int type)
    {
        if (type == 1)

        {
            float S = coordinate - position.x + radius;
            float xTime = S / v.x;

            position.y = position.y + xTime * (v.y);
            position.x = coordinate + radius;
        }

        if (type == 2)

        {
            float S = position.x + radius - coordinate;
            float xTime = S / v.x;
            position.y = position.y + xTime * v.y;
            position.x = coordinate - radius;
        }

        if (type == 3)

        {
            float S = position.y + radius - coordinate;

            float yTime = S / v.y;
            position.x = position.x + yTime * v.x;
            position.y = coordinate - radius;
        }

        if (type == 4)
        {
            float S = coordinate - position.y + radius;
            float yTime = S / v.y;
            position.x = position.x + yTime * v.x;
            position.y = coordinate + radius;
        }
    }

    void moveBall(float dt)
    {

        position = position + v * dt;

        if (position.x - radius < 0)
        {
            changeCoordinate(0, 1);
            v.x = -v.x;
        }

        if (position.x + radius > 1280)
        {
            changeCoordinate(1280, 2);
            v.x = -v.x;
        }

        if (position.y + radius > 720)
        {
            changeCoordinate(720, 3);
            v.y = -v.y;
        }

        if (position.y - radius < 0)
        {
            changeCoordinate(0, 4);
            v.y = -v.y;
        }
    }

    void resolveByImpulse(Ball* ball2)
    {
        //V
        Vector2f ball1v = v;
        Vector2f ball2v = ball2->v;

        v = ball2v;
        ball2->v = ball1v;

        //Position

        float len = (ball2->position - position).len();
        float shift = radius + ball2->radius - len;

        position = position - (ball2->position - position).normalize() * shift;
    }

    bool isCollision(Ball *ball2)
    {
        if (radius + ball2->radius > (position - ball2->position).len())
        {
            return true;
        }
        return false;
    }

    void collision(Ball* ball2)
    {
        if (!isCollision(ball2))
            return;

        resolveByImpulse(ball2);
    }

};

struct BallManager
{
    void create(Ball* ball, int count)
    {
        int i = 0;
        while (i < count)
        {
            ball[i].drawBall();
            i++;
        }
    }

    void move(Ball* ball, float dt, int count)
    {
        int i = 0;
        while (i < count)
        {
            ball[i].moveBall(dt);
            i++;
        }
    }


    void collide(Ball* ball, float dt, int count)
    {
        for (int i = 0; i < count; i++)
            for (int u = i; u < count; u++)
                if (&ball[i] != &ball[u])
                {
                    ball[i].collision(&ball[u]);
                }
    }
};


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
    BallManager manager;

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
        manager.move(gas, dt, ballCount);

        txBegin ();

        txSetFillColor(RGB(0,0,0));
        txClear();

        manager.create(gas, ballCount);

        txEnd ();

        manager.collide(gas, dt, ballCount);
    }

    return 0;
}
