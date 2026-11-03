
#ifndef LUMIERE_HPP
#define LUMIERE_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
using namespace std;

struct Vec3 {
    float x, y, z;

    Vec3(float x = 0, float y = 0, float z = 0)
        : x(x), y(y), z(z) {}
};

class Lumiere {
public:
    virtual float intensite(const Vec3& position) = 0;
    virtual ~Lumiere() {}
};

class LumiereDirectionnelle : public Lumiere {
private:
    Vec3 direction;
    float couleur;

public:
    LumiereDirectionnelle(Vec3 d, float c);
    float intensite(const Vec3& position) override;
};

class LumierePonctuelle : public Lumiere {
private:
    Vec3 position;
    float attenuation;

public:
    LumierePonctuelle(Vec3 p, float a);
    float intensite(const Vec3& point) override;
};

class LumiereSpot : public Lumiere {
private:
    Vec3 position;
    Vec3 direction;
    float angle;

public:
    LumiereSpot(Vec3 p, Vec3 d, float a);
    float intensite(const Vec3& point) override;
};

float calculerEclairage(const Vec3& point);

#endif
