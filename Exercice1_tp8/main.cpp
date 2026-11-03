#include "SortieAudio.hpp"

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

void tester(SortieAudio* sortie) {
    sortie->ouvrir();
    sortie->jouer("Musique.mp3");
    sortie->fermer();
}

int main() {

    SortieAudio* sorties[3];

    sorties[0] = new HautParleur();
    sorties[1] = new CasqueBT();
    sorties[2] = new SortieHDMI();

    for (int i = 0; i < 3; i++) {
        cout << "\n----------------------" << endl;
        tester(sorties[i]);
    }

    for (int i = 0; i < 3; i++) {
        delete sorties[i];
    }

    return 0;
}