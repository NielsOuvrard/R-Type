/*
** ooooooooo.           ooooooooooooo
** `888   `Y88.         8'   888   `8
**  888   .d88'              888      oooo    ooo oo.ooooo.   .ooooo.
**  888ooo88P'               888       `88.  .8'   888' `88b d88' `88b
**  888`88b.    8888888      888        `88..8'    888   888 888ooo888
**  888  `88b.               888         `888'     888   888 888    .o
** o888o  o888o             o888o         .8'      888bod8P' `Y8bod8P'
**                                    .o..P'       888
**                                    `Y8P'       o888o
**
** Transform
*/

#pragma once

class Transform
{
public:
    Transform() = default;
    Transform(int x = 0, int y = 0, double rotation = 0, double scale = 0)
        : _x(x), _y(y), _rotation(rotation), _scale(scale) {}

    // getters
    int getX() const { return _x; }
    int getY() const { return _y; }
    int getRotation() const { return _rotation; }
    int getScale() const { return _scale; }

    void setX(int x) { _x = x; }
    void setY(int y) { _y = y; }
    void setRotation(double rotation) { _rotation = rotation; }
    void setScale(double scale) { _scale = scale; }

private:
    int _x;
    int _y;
    double _rotation;
    double _scale;
};

class Object2D
{
public:
    Object2D() = default;
    Object2D(int x = 0, int y = 0, int rotation = 0, int scale = 1)
        : _x(x), _y(y), _rotation(rotation), _scale(scale) {}

    // getters
    int getX() const { return _x; }
    int getY() const { return _y; }
    double getRotation() const { return _rotation; }
    double getScale() const { return _scale; }

    void setX(int x) { _x = x; }
    void setY(int y) { _y = y; }
    void setRotation(double rotation) { _rotation = rotation; }
    void setScale(double scale) { _scale = scale; }

    void addX(int x) { _x += x; }
    void addY(int y) { _y += y; }
    void addRotation(double rotation) { _rotation += rotation; }
    void addScale(double scale) { _scale += scale; }

private:
    int _x;
    int _y;
    double _rotation;
    double _scale;
};
