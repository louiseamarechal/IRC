// Inclure les fichiers d'en-tête de la bibliothèque IRC
#include "ircsock.h"

int main()
{
  // Déclarer une instance de la classe CIRCSock
  CIRCSock sock;

  // Créer un socket pour le serveur IRC
  if (!sock.Create())
  {
    // Afficher un message d'erreur si la création du socket a échoué
    std::cerr << "Erreur : impossible de créer le socket du serveur IRC" << std::endl;
    return 1;
  }

  // Lier le socket à un port sur le serveur
  if (!sock.Bind(6667))
  {
    // Afficher un message d'erreur si le binding du socket a échoué
    std::cerr << "Erreur : impossible de lier le socket à un port" << std::endl;
    return 1;
  }

  // Écouter les connexions entrantes sur le port
 
  }