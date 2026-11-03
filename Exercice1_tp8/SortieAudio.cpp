#include "SortieAudio.hpp"

// Classe HautParleur
class HautParleur : public SortieAudio {
public:
    void ouvrir() override {
        cout << "Haut-parleur ouvert" << endl;
    }

    void jouer(const string& son) override {
        cout << "Haut-parleur joue : " << son << endl;
    }

    void fermer() override {
        cout << "Haut-parleur ferme" << endl;
    }
};

// Classe CasqueBT
class CasqueBT : public SortieAudio {
public:
    void ouvrir() override {
        cout << "Casque Bluetooth ouvert" << endl;
    }

    void jouer(const string& son) override {
        cout << "Casque Bluetooth joue : " << son << endl;
    }

    void fermer() override {
        cout << "Casque Bluetooth ferme" << endl;
    }
};

// Classe SortieHDMI
class SortieHDMI : public SortieAudio {
public:
    void ouvrir() override {
        cout << "Sortie HDMI ouverte" << endl;
    }

    void jouer(const string& son) override {
        cout << "Sortie HDMI joue : " << son << endl;
    }

    void fermer() override {
        cout << "Sortie HDMI fermee" << endl;
    }
};

// Fonction de test
void tester(SortieAudio* sortie) {
    sortie->ouvrir();
    sortie->jouer("Musique.mp3");
    sortie->fermer();
}