#include <poll.h>

//fds[0].events = POLLIN | POLLOUT; pour voir quc'est possible ..
// Définition des structures de données pour les sockets
struct pollfd fds[N]; // N est le nombre de sockets à surveiller
int sockets[N]; // Tableau contenant les descripteurs de fichiers des sockets

// Initialisation des structures de données pour les sockets
for (int i = 0; i < N; i++) {
    fds[i].fd = sockets[i];
    fds[i].events = POLLIN;
}

// Boucle de surveillance des sockets
while (1) {
    int ret = poll(fds, N, -1);
    if (ret == -1) {
        // Erreur lors de l'appel à poll()
        // Traitement de l'erreur...
    } else {
        // Vérification de l'état des sockets
        for (int i = 0; i < N; i++) {
            if (fds[i].revents & POLLIN) {
                // Données à lire sur le socket i
                // Traitement des données...
            }
        }
    }
}



--------------------------------------------------------------------

#include <iostream>
#include <sys/poll.h>

int main() {
  // Créez un tableau de structures pollfd pour stocker les descripteurs de fichiers
  // que vous souhaitez surveiller avec la fonction poll
  struct pollfd fds[1];

  // Configurez la première entrée du tableau pour surveiller le descripteur de fichier standard d'entrée (stdin)
  fds[0].fd = STDIN_FILENO;
  fds[0].events = POLLIN;

  // Appelez la fonction poll avec un délai de 1000 ms (1 seconde)
  int retval = poll(fds, 1, 1000);
  if (retval == -1) {
    // Une erreur est survenue
    std::cerr << "Erreur lors de l'appel à poll" << std::endl;
    return 1;
  } else if (retval == 0) {
    // Aucun descripteur de fichier n'était prêt à l'entrée ou à la sortie
    std::cout << 


-------------------------------

// Déclarez un tableau de structures pollfd pour stocker les descripteurs de fichiers à surveiller
struct pollfd fds[NUM_FDS];

// Remplissez le tableau fds avec les descripteurs de fichiers à surveiller et les options de surveillance souhaitées

// Appelez la fonction poll en lui passant le tableau fds et la taille de ce tableau
int ret = poll(fds, NUM_FDS, TIMEOUT);

// Traitez les résultats de la fonction poll en vérifiant les valeurs de retour de chaque descripteur de fichier dans le tableau fds

------------------------------------

#include <poll.h>
#include <unistd.h>

int main() {
  // Créer un descripteur de fichier à surveiller
  int fd = STDIN_FILENO;

  // Préparer un objet pollfd pour surveiller ce descripteur de fichier
  struct pollfd fds;
  fds.fd = fd;
  fds.events = POLLIN;

  // Appeler poll() pour attendre qu'un événement d'E/S se produise
  int ret = poll(&fds, 1, -1);

  // Vérifier si poll() a renvoyé une erreur
  if (ret == -1) {
    // Traiter l'erreur
  } else if (ret > 0) {
    // Vérifier si le descripteur de fichier est prêt pour la lecture
    if (fds.revents & POLLIN) {
      // Lire les données depuis le descripteur de fichier
    }
  }
}
