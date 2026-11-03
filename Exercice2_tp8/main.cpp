
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

using namespace std;

// Structure 3D
struct Vec3 {
    float x, y, z;

    Vec3(float x = 0, float y = 0, float z = 0)
        : x(x), y(y), z(z) {}
};

// Classe abstraite
class Lumiere {
public:
    virtual float intensite(const Vec3& position) = 0;

    virtual ~Lumiere() {}
};

// Lumiere directionnelle
class LumiereDirectionnelle : public Lumiere {
private:
    Vec3 direction;
    float couleur;

public:
    LumiereDirectionnelle(Vec3 d, float c)
        : direction(d), couleur(c) {}

    float intensite(const Vec3& position) override {
        return couleur;
    }
};

// Lumiere ponctuelle
class LumierePonctuelle : public Lumiere {
private:
    Vec3 position;
    float attenuation;

public:
    LumierePonctuelle(Vec3 p, float a)
        : position(p), attenuation(a) {}

    float intensite(const Vec3& point) override {
        float dx = point.x - position.x;
        float dy = point.y - position.y;
        float dz = point.z - position.z;

        float distance = sqrt(dx * dx + dy * dy + dz * dz);

        return 1.0f / (1.0f + attenuation * distance * distance);
    }
};

// Lumiere Spot
class LumiereSpot : public Lumiere {
private:
    Vec3 position;
    Vec3 direction;
    float angle;

public:
    LumiereSpot(Vec3 p, Vec3 d, float a)
        : position(p), direction(d), angle(a) {}

    float intensite(const Vec3& point) override {
        float dx = point.x - position.x;
        float dy = point.y - position.y;
        float dz = point.z - position.z;

        float distance = sqrt(dx * dx + dy * dy + dz * dz);

        if (distance == 0)
            return 1.0f;

        float produit = dx * direction.x
                      + dy * direction.y
                      + dz * direction.z;

        float normeDirection = sqrt(
            direction.x * direction.x +
            direction.y * direction.y +
            direction.z * direction.z
        );

        if (normeDirection == 0)
            return 0.0f;

        float cosAngle = produit / (distance * normeDirection);

        float angleRad = (angle / 2.0f) * 3.14159265f / 180.0f;

        if (cosAngle >= cos(angleRad)) {
            return 1.0f / (1.0f + distance * distance);
        }

        return 0.0f;
    }
};

// Collection des lumieres
vector<unique_ptr<Lumiere>> lumieres;

// Calcul de l'eclairage total
float calculerEclairage(const Vec3& point) {
    float total = 0.0f;

    for (const auto& lumiere : lumieres) {
        total += lumiere->intensite(point);
    }

    return total;
}

// Programme principal
int main() {

    // Creation des lumieres

    lumieres.push_back(
        make_unique<LumiereDirectionnelle>(
            Vec3(0, -1, 0), 0.5f
        )
    );

    lumieres.push_back(
        make_unique<LumierePonctuelle>(
            Vec3(0, 0, 0), 0.1f
        )
    );

    lumieres.push_back(
        make_unique<LumiereSpot>(
            Vec3(0, 0, 5), Vec3(0, 0, -1), 45.0f
        )
    );

    // Points de test

    Vec3 points[] = {
        Vec3(1, 2, 3),
        Vec3(2, 3, 4),
        Vec3(5, 5, 5)
    };

    // Calcul et affichage

    for (int i = 0; i < 3; i++) {
        cout << "Point " << i + 1 << " : ";

        float resultat = calculerEclairage(points[i]);

        cout << "Intensite totale = "
             << resultat << endl;
    }

    return 0;
}
