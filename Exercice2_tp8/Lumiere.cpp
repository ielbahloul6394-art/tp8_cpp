
#include "Lumiere.hpp"

vector<unique_ptr<Lumiere>> lumieres;

// Lumiere directionnelle
LumiereDirectionnelle::LumiereDirectionnelle(Vec3 d, float c)
    : direction(d), couleur(c) {}

float LumiereDirectionnelle::intensite(const Vec3& position) {
    return couleur;
}

// Lumiere ponctuelle
LumierePonctuelle::LumierePonctuelle(Vec3 p, float a)
    : position(p), attenuation(a) {}

float LumierePonctuelle::intensite(const Vec3& point) {
    float dx = point.x - position.x;
    float dy = point.y - position.y;
    float dz = point.z - position.z;

    float distance = sqrt(dx*dx + dy*dy + dz*dz);

    return 1.0f / (1.0f + attenuation * distance * distance);
}

// Lumiere Spot
LumiereSpot::LumiereSpot(Vec3 p, Vec3 d, float a)
    : position(p), direction(d), angle(a) {}

float LumiereSpot::intensite(const Vec3& point) {
    float dx = point.x - position.x;
    float dy = point.y - position.y;
    float dz = point.z - position.z;

    float distance = sqrt(dx*dx + dy*dy + dz*dz);

    if (distance == 0)
        return 1.0f;

    float produit = dx * direction.x +
                    dy * direction.y +
                    dz * direction.z;

    float cosAngle = produit / distance;

    if (cosAngle >= cos(angle * 3.14159f / 180.0f))
        return 1.0f / (1.0f + distance * distance);

    return 0.0f;
}

// Calcul de l'eclairage total
float calculerEclairage(const Vec3& point) {
    float total = 0.0f;

    for (const auto& lumiere : lumieres) {
        total += lumiere->intensite(point);
    }

    return total;
}
