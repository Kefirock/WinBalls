class Vector2f
{
    public:

        float x;
        float y;

        Vector2f(float x, float y)
        {
            this->x = x;
            this->y = y;
        }

        Vector2f()
        {
        }

        //add
        Vector2f operator+ (Vector2f v)
        {
            return Vector2f (x + v.x, y + v.y);
        }

        //Vector + float
        Vector2f operator+ (float n)
        {
            return Vector2f (x + n, y + n);
        }

        //sub
        Vector2f operator- (Vector2f v)
        {
            return Vector2f (x - v.x, y - v.y);
        }

        //mul
        Vector2f operator* (Vector2f v)
        {
            return Vector2f (x * v.x, y * v.y);
        }

        //scalar
        Vector2f operator* (float n)
        {
            return Vector2f (x * n, y * n);
        }

        //div
        Vector2f operator/ (float n)
        {
            return Vector2f (x / n, y / n);
        }

        //len
        float len ()
        {
            return sqrt(x * x + y * y);
        }

        //normalize
        Vector2f normalize ()
        {
            return Vector2f(x / sqrt(x * x + y * y), y / sqrt(x * x + y * y));
        }

};

bool isEqual(double n, double m)
{
    if(abs(m - n) < 0.0000000001)
    {
        return true;
    }

    return false;
}


