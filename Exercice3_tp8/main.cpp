
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <cctype>

using namespace std;

// Fonction pour remplacer un mot dans une chaine
void remplacer(string& texte, const string& ancien, const string& nouveau) {
    size_t position = 0;

    while ((position = texte.find(ancien, position)) != string::npos) {
        texte.replace(position, ancien.length(), nouveau);
        position += nouveau.length();
    }
}

// Classe abstraite Plugin
class Plugin {
public:
    virtual string nom() const = 0;
    virtual string traiter(const string& texte) = 0;

    virtual ~Plugin() {}

    static unique_ptr<Plugin> creerPlugin(const string& type);
};

// Plugin correcteur orthographique
class CorrecteurOrthographique : public Plugin {
public:
    string nom() const override {
        return "Correcteur orthographique";
    }

    string traiter(const string& texte) override {
        string resultat = texte;

        remplacer(resultat, "bonjor", "bonjour");
        remplacer(resultat, "salu", "salut");
        remplacer(resultat, "mercie", "merci");
        remplacer(resultat, " language", " langage");

        return resultat;
    }
};

// Plugin traducteur français-anglais
class TraducteurAnglais : public Plugin {
public:
    string nom() const override {
        return "Traducteur anglais";
    }

    string traiter(const string& texte) override {
        string resultat = texte;

        remplacer(resultat, "bonjour", "hello");
        remplacer(resultat, "salut", "hi");
        remplacer(resultat, "merci", "thank you");
        remplacer(resultat, "maison", "house");
        remplacer(resultat, "ami", "friend");

        return resultat;
    }
};

// Plugin analyseur de style
class AnalyseurStyle : public Plugin {
public:
    string nom() const override {
        return "Analyseur de style";
    }

    string traiter(const string& texte) override {
        string resultat = texte;
        string phrase;
        int phrasesLongues = 0;

        for (char caractere : texte) {
            phrase += caractere;

            if (caractere == '.' || caractere == '!' || caractere == '?') {
                istringstream flux(phrase);
                string mot;
                int nombreMots = 0;

                while (flux >> mot) {
                    nombreMots++;
                }

                if (nombreMots > 15) {
                    phrasesLongues++;
                }

                phrase.clear();
            }
        }

        if (phrasesLongues > 0) {
            resultat += "\n[Style] Attention : ";
            resultat += to_string(phrasesLongues);
            resultat += " phrase(s) trop longue(s).";
        } else {
            resultat += "\n[Style] Aucune phrase trop longue.";
        }

        return resultat;
    }
};

// Factory : création du plugin selon son type
unique_ptr<Plugin> Plugin::creerPlugin(const string& type) {
    if (type == "correcteur") {
        return make_unique<CorrecteurOrthographique>();
    }

    if (type == "traducteur") {
        return make_unique<TraducteurAnglais>();
    }

    if (type == "style") {
        return make_unique<AnalyseurStyle>();
    }

    return nullptr;
}

int main() {
    string texte;

    cout << "Entrez votre texte : ";
    getline(cin, texte);

    // Simulation du chargement dynamique des plugins
    vector<unique_ptr<Plugin>> plugins;

    plugins.push_back(Plugin::creerPlugin("correcteur"));
    plugins.push_back(Plugin::creerPlugin("traducteur"));
    plugins.push_back(Plugin::creerPlugin("style"));

    // Application successive des plugins
    for (const auto& plugin : plugins) {
        texte = plugin->traiter(texte);

        cout << "\nPlugin applique : " << plugin->nom() << endl;
        cout << "Texte transforme : " << texte << endl;
    }

    return 0;
}
