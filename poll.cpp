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
