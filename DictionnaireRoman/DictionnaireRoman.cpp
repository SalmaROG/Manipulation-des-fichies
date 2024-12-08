#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>


using namespace std;

// Fonction pour lire le fichier et le stocker dans une map
void lireFichier(const string& nomFichier, map<int, string>& contenu)
{
    ifstream fichier(nomFichier);
    if (!fichier)
    {
        cout << "Erreur : Impossible d'ouvrir le fichier " << nomFichier << endl;
        return;
    }
    contenu.clear();
    string ligne;
    int numeroLigne = 1;
    while (getline(fichier, ligne))
    {
        contenu[numeroLigne++] = ligne;
    }
}

// Fonction pour vérifier si un mot existe dans le roman
bool chercherMot(const map<int, string>& contenu, const string& mot)
{
    for (const auto& paire : contenu)
    {
        const string& ligne = paire.second;
        if (ligne.find(mot) != string::npos)
        {
            return true;
        }
    }
    return false;
}

// Fonction pour compter les occurrences d'un mot
int compterOccurrences(const map<int, string>& contenu, const string& mot)
{
    int occurrences = 0;
    for (const auto& paire : contenu)
    {
        const string& ligne = paire.second;
        size_t pos = ligne.find(mot);

        while (pos != string::npos)
        {
            occurrences++;
            pos = ligne.find(mot, pos + mot.length());
        }
    }
    return occurrences;
}

// Fonction pour trouver les emplacements d'un mot
vector<pair<int, int>> trouverEmplacements(const map<int, string>& contenu, const string& mot)
{
    vector<pair<int, int>> emplacements;

    for (const auto& paire : contenu) {
        int numeroLigne = paire.first;
        string ligne = paire.second;

        // Nettoyer la ligne pour retirer la ponctuation
        for (char& c : ligne) {
            if (ispunct(static_cast<unsigned char>(c))) { // Si c'est une ponctuation (virgule, point, etc.)
                c = ' ';     // Remplacer par un espace
            }
        }

        // Découper la ligne en mots
        istringstream stream(ligne);
        string motActuel;
        int positionMot = 1; // Position actuelle du mot dans la ligne

        while (stream >> motActuel) {
            // Comparer le mot actuel avec le mot recherché
            if (motActuel == mot) {
                emplacements.emplace_back(numeroLigne, positionMot); // Ligne, position dans la ligne
            }
            ++positionMot;
        }
    }

    return emplacements;
}

// Fonction pour afficher le contenu
void afficherContenu(const map<int, string>& contenu)
{
    for (const auto& paire : contenu)
    {
        cout << paire.first << ": " << paire.second << endl;
    }
}

int main()
{
    map<int, string> contenu;
    string nomFichier = "roman.txt";

    lireFichier(nomFichier, contenu);

    if (chercherMot(contenu, "Cosette"))
        cout << "Le mot existe dans le roman." << endl;
    else
        cout << "Le mot n'existe pas dans le roman." << endl;

    cout << "Le nombre d'occurrences de 'Cosette' est : " << compterOccurrences(contenu, "Cosette") << endl;

    // Recherche des emplacements
    vector<pair<int, int>> emplacements = trouverEmplacements(contenu, "Cosette");

    if (!emplacements.empty())
    {
        cout << "Le mot 'Cosette' se trouve aux emplacements suivants :\n";
        for (const auto& emplacement : emplacements)
        {
            cout << "Ligne " << emplacement.first << ", Position " << emplacement.second << endl;
        }
    }
    else
    {
        cout << "Le mot 'Cosette' n'a pas été trouvé dans le texte." << endl;
    }

    return 0;
}
