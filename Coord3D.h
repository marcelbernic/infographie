#ifndef COORD3D_H
#define COORD3D_H

#endif // COORD3D_H

#pragma once
class Coord3D
{
private:
    double m_x;
    double m_y;
    double m_z;

public:
    Coord3D();
    Coord3D(double p_x, double p_y, double p_z);
    Coord3D(int p_x, int p_y, int p_z);
    /*Coord(Coord p_coord);*/
    double getX();
    void setX(double p_x);
    void setX(int p_x);
    double getY();
    void setY(double p_y);
    void setY(int p_y);
    double getZ();
    void setZ(double p_z);
    void setZ(int p_z);

    void addToX(double p_x);
    void addToX(int p_x);
    void addToY(double p_y);
    void addToY(int p_y);
    void addToZ(double p_z);
    void addToZ(int p_z);
    void addToCoord(Coord3D p_coord);
    void addToCoord(double p_x, double p_y, double p_z);

    ~Coord3D();
};
