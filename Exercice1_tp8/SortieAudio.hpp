#ifndef SORTIEAUDIO_HPP
#define SORTIEAUDIO_HPP

#include <iostream>
#include <string>
using namespace std;

class SortieAudio {
public:
    virtual void ouvrir() = 0;
    virtual void jouer(const string& son) = 0;
    virtual void fermer() = 0;

    virtual ~SortieAudio() {
        cout << "Destruction de SortieAudio" << endl;
    }
};

#endif