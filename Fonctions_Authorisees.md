```cpp
(B) accept() :
    
    int accept(int sockfd, sockaddr *addr, socklen_t *addrlen);
```

    Fonction utilisée pour accepter une connexion entrante sur un socket serveur en C++98.
    Lorsqu'un socket serveur est en mode d'écoute pour les connexions entrantes,
    la fonction attend qu'une connexion entrante soit reçue sur le socket.
    Lorsqu'une connexion est reçue et acceptee, elle retourne un nouveau descripteur
    de socket pour le client, ou un entier négatif en cas d'erreur.
    Le nouveau descripteur de socket retourné peut être utilisé pour communiquer avec le client
    et gérer sa demande.

    La fonction prend trois arguments :
        sockfd : le descripteur de socket serveur (retourné par la fonction socket)
        addr : une structure 'sockaddr' pour stocker l'adresse du client qui se connecte
        addrlen : un pointeur vers une variable qui contient la taille de cette structure
            (ce qui est nécessaire pour lui permettre de remplir correctement la structure avec
            les données de l'adresse client).

```cpp
(B) bind() :
    
    int bind(int sockfd, const sockaddr *addr, socklen_t addrlen);
```
    Fonction qui est utilisée pour lier un socket à une adresse et un port spécifiés en C++98.
    Cela permet aux clients de se connecter au socket en utilisant cette adresse et ce port.

    La fonction prend trois arguments :
        sockfd : le descripteur de socket (retourné par la fonction socket) à lier à l'adresse
            et au port spécifiés.
        addr : un pointeur vers une structure 'sockaddr' contenant les informations d'adresse 
            et de port à lier au socket.
        addrlen : la taille de la structure 'sockaddr' pointée par 'addr', en octets.

    Retourne 0 si elle a réussi à lier le socket à l'adresse et au port spécifiés, ou un entier
    négatif en cas d'erreur. 

```cpp
(B) connect() :

    int connect(int sockfd, const sockaddr *addr, socklen_t addrlen);
```

    Fonction qui est utilisée pour établir une connexion avec un socket serveur en C++98.
    Lorsqu'un socket client appelle la fonction, il envoie une demande de connexion au socket
    serveur sur l'adresse et le port spécifiés. Si le serveur accepte la connexion, le socket
    client et le socket serveur sont connectés et peuvent échanger des données.

    La fonction prend trois arguments :
        sockfd : le descripteur de socket client (retourné par la fonction socket) à utiliser
            pour envoyer la demande de connexion.
        addr : un pointeur vers une structure sockaddr contenant les informations d'adresse
            et de port du socket serveur auquel se connecter.
        addrlen : la taille de la structure sockaddr pointée par addr, en octets.
    
    La fonction retourne 0 si la connexion a été établie avec succès, ou un entier négatif en cas
    d'erreur.

```cpp
(B) fcntl() :

    int fcntl(int fd, int cmd, ... /* int arg */);
```
    La fonction fcntl (pour "file control") est utilisée pour configurer les options et les flags d'un
    descripteur de fichier ou d'un socket en C++98. 

    La fonction prend trois arguments :
        fd : le descripteur de fichier ou de socket à configurer.
        cmd : l'opération à effectuer sur le descripteur. Cela peut être une constante prédéfinie
            comme F_GETFL pour récupérer les flags du descripteur ou F_SETFL pour modifier les
            flags  du descripteur, par exemple.
        arg : un argument facultatif contenant les options ou les flags à utiliser pour l'opération
            spécifiée par cmd. Par exemple, si cmd est F_SETFL, arg peut être une constante prédéfinie
            comme O_NONBLOCK pour configurer le descripteur en mode non-bloquant.

    La fonction retourne 0 si l'opération a été effectuée avec succès, ou un entier négatif en cas d'erreur.

```cpp
(B) freeaddrinfo() :

    void freeaddrinfo(addrinfo *ai);
```
     Fonction utilisée pour libérer la mémoire allouée pour une liste d'informations d'adresse en C++98.
     Cette fonction est souvent utilisée après avoir utilisé la fonction getaddrinfo pour récupérer une
     liste d'adresses correspondant à un nom d'hôte et un service spécifiés.

    Elle ne prend au'un seul argument :
        ai : un pointeur vers la structure 'addrinfo' à libérer.

    La fonction ne retourne rien. Elle libère simplement la mémoire allouée pour la structure addrinfo et
    toutes ses sous-structures associées.

```cpp
fstat() :

    int fstat(int fd, struct stat *buf);
```
    Fcontion utilisée pour récupérer des informations sur un descripteur de fichier en C++98. Cette fonction
    peut être utilisée pour obtenir des informations sur le type de fichier (fichier ordinaire, répertoire, etc.),
    les droits d'accès, la date de dernière modification, la taille, etc.

    La fonction prend deux arguments :
        fd : le descripteur de fichier à examiner.
        buf : un pointeur vers une structure stat où stocker les informations récupérées sur le fichier.

    La fonction retourne 0 si les informations ont été récupérées avec succès, ou un entier négatif en cas
    d'erreur.
    On peut utiliser les champs de la structure stat pour accéder aux informations récupérées sur le fichier.
    Par exemple, le champ st_mode contient le type de fichier et les droits d'accès, le champ st_mtime contient
    la date de dernière modification, et le champ st_size contient la taille du fichier en octets.

```cpp
(B) getaddrinfo() :

    int getaddrinfo(const char *node, const char *service, const addrinfo *hints, addrinfo **res);
```
    Fonction  utilisée pour résoudre un nom d'hôte et un service en une ou plusieurs adresses IP et ports en C++98.
    Cette fonction est souvent utilisée pour se connecter à un serveur en utilisant son nom d'hôte et son port plutôt
    que son adresse IP et son port, car cela permet de résoudre le nom d'hôte en une ou plusieurs adresses IP et de 
    résoudre le service en un ou plusieurs ports. La fonction getaddrinfo prend plusieurs arguments pour spécifier le
    nom d'hôte et le service à résoudre, ainsi que des options de résolution.

    La fonction prend quatre arguments :
        node : un pointeur vers une chaîne de caractères contenant le nom d'hôte à résoudre. Si cet argument vaut NULL,
            la fonction essaie de résoudre l'adresse de l'hôte local.
        service : un pointeur vers une chaîne de caractères contenant le service (port) à résoudre. Si cet argument vaut
            NULL, la fonction retourne une liste d'adresses IP associées au nom d'hôte, mais pas de ports associés.
        hints : un pointeur vers une structure 'addrinfo' contenant des options de résolution pour le nom d'hôte et le
            service. Si cet argument vaut NULL, la fonction utilise des options par défaut pour la résolution.
        res : un double pointeur vers une structure 'addrinfo', qui sera utilisé pour stocker la liste des adresses et
            des ports résolus pour le nom d'hôte et le service. Si la fonction réussit, cet argument sera modifié pour 
            pointer vers une liste chaînée de structures 'addrinfo', une pour chaque adresse et port résolus.
            Si la fonction échoue, cet argument restera inchangé.
    
    La fonction retourne 0 si la résolution a réussi et que la liste des adresses et des ports a été stockée dans res,
    ou un code d'erreur négatif en cas d'échec. On peut utiliser la constante 'EAI_SYSTEM' pour vérifier si l'erreur
    a été causée par un problème système, ou utiliser la fonction 'gai_strerror' pour obtenir un message d'erreur plus
    détaillé.

```cpp
    // Appel de la fonction getaddrinfo
    int err = getaddrinfo(node, service, hints, &res);
    // nous vérifions si elle a réussi en vérifiant si son code de retour est égal à 0
    if (err != 0) {
    // La fonction getaddrinfo a échoué
    if (err == EAI_SYSTEM) {
        //  Si la fonction a échoué, nous vérifions si l'erreur a été causée par un problème système en comparant
        // son code de retour avec la constante EAI_SYSTEM. Si l'erreur a été causée par un problème système, nous
        // traitons l'erreur système ici. 
    } else {
        // Si l'erreur n'a pas été causée par un problème système
        // Obtenez un message d'erreur plus détaillé en utilisant gai_strerror
        const char *err_msg = gai_strerror(err);
        // Traitez l'erreur ici en utilisant err_msg comme message d'erreur
    }
    } else {
    // La fonction getaddrinfo a réussi et la liste des adresses résolues est
    // stockée dans la variable res
    // Utilisez les adresses résolues ici
    }

```

```cpp
gethostbyname() :

    struct hostent* gethostbyname(const char *name);
```
    Fonction qui permet de résoudre des noms d'hôtes en adresses IP.
    Elle prend en argument un pointeur vers une chaîne de caractères contenant le nom d'hôte à résoudre, et renvoie
    un pointeur vers une structure 'hostent' contenant les informations sur l'hôte.

    Si la fonction échoue, elle renvoie un pointeur nul.

       -> La structure 'hostent' comprend les champs suivants :
```cpp
            char *h_name : un pointeur vers une chaîne de caractères contenant le nom complet de l'hôte. 
            char **h_aliases : un pointeur vers un tableau de pointeurs vers des chaînes de caractères
                contenant les alias de l'hôte.
            int h_addrtype : un entier contenant le type d'adresse de l'hôte (IPv4 ou IPv6).
            int h_length : un entier contenant la longueur, en octets, de l'adresse de l'hôte.
            char **h_addr_list : un pointeur vers un tableau de pointeurs vers des chaînes de caractères
                contenant les adresses IP de l'hôte.
```
    Cette structure peut varier selon les implémentations et les versions du compilateur C++ utilisé.
    Il est donc recommandé de consulter la documentation de votre compilateur pour plus de détails.

```cpp
getprotobyname() :

    struct protoent* getprotobyname(const char *name);
```
    Fonction qui permet de résoudre des noms de protocoles en numéros de protocoles. 
    Cette fonction prend en argument un pointeur vers une chaîne de caractères contenant le nom du protocole à résoudre,
    et renvoie un pointeur vers une structure protoent contenant les informations sur le protocole.

    Si la fonction échoue, elle renvoie un pointeur nul.

    Notez que cette fonction n'est plus recommandée pour de nouveaux développements en C++, car elle n'est
    pas thread-safe et peut poser des problèmes de portabilité.

    La structure protoent en C++ contient les informations sur un protocole résolu par la fonction getprotobyname(). Cette structure contient les champs suivants :
```cpp
        char *p_name : un pointeur vers une chaîne de caractères contenant le nom du protocole.
        char **p_aliases : un pointeur vers un tableau de pointeurs vers des chaînes de caractères
            contenant les alias du protocole.
        int p_proto : un entier contenant le numéro du protocole.
```    
    Cette structure peut varier selon les implémentations et les versions du compilateur C++ utilisé. Il est donc recommandé de
    consulter la documentation de votre compilateur pour plus de détails.

```cpp
getsockname() :

    int getsockname(int sockfd, struct sockaddr *local_addr, socklen_t *addrlen);
```
    Fonction qui permet de récupérer les informations sur l'adresse locale d'une socket. 
    
    Elle prend en argument un descripteur de socket 'sockfd', un pointeur vers une structure 'sockaddr' où
    seront stockées les informations sur l'adresse locale de la socket, et un pointeur vers un entier
    'addrlen' qui contiendra la taille de cette structure.

    La fonction renvoie 0 en cas de succès, et un entier négatif en cas d'échec.

    Notez que cette fonction n'est plus recommandée pour de nouveaux développements en C++, car elle n'est
    pas thread-safe et peut poser des problèmes de portabilité.
    
    La structure sockaddr en C++98 est une structure générique utilisée pour stocker des informations sur une adresse de socket. Cette structure contient les champs suivants :
```cpp
        sa_family_t sa_family : un entier indiquant le type de l'adresse (IPv4 ou IPv6).
        char sa_data : un tableau de caractères contenant les données de l'adresse.
```
    Pour stocker des informations plus détaillées, vous devez utiliser des structures plus spécifiques telles que sockaddr_in
    pour les adresses IPv4 ou sockaddr_in6 pour les adresses IPv6.

```cpp
htonl() :

    uint32_t htonl(uint32_t hostlong);
```
     Fonction qui permet de convertir un entier non-signé en un entier non-signé de quatre octets stocké
     dans le format de réseau (big-endian).

     Cette fonction prend en argument un entier non-signé 'hostlong' et renvoie l'entier non-signé
     converti au format de réseau.

    Notez que cette fonction est définie dans l'en-tête <arpa/inet.h> en C++98. Il est donc recommandé de
    l'inclure dans votre programme avant de l'utiliser.

```cpp
htons() :

    uint16_t htons(uint16_t hostshort);
```
    Fonction qui permet de convertir un entier non-signé en un entier non-signé de deux octets stocké
    dans le format de réseau (big-endian).

    Cette fonction prend en argument un entier non-signé hostshort et renvoie l'entier non-signé
    converti au format de réseau.

    Notez que cette fonction est définie dans l'en-tête <arpa/inet.h> en C++98. Il est donc recommandé
    de l'inclure dans votre programme avant de l'utiliser.


Note sur htonl() et htons() :

    Il est fréquent de vouloir convertir des entiers non-signés en des entiers non-signés stockés dans
    le format de réseau (big-endian) lorsque vous travaillez avec des sockets en réseau en C++.
    Le format de réseau est un standard pour stocker des données de manière à ce qu'elles puissent
    être transmises sur un réseau et lues correctement par les différents appareils connectés au réseau.

    En général, le format de réseau utilise un codage en big-endian, c'est-à-dire que les octets les
    plus significatifs d'une donnée sont stockés en premier. Cela permet de s'assurer que les données
    seront lues correctement par les différents appareils, quel que soit l'endianness (codage en
    petit-endian ou en big-endian) de leur processeur.

```cpp
inet_ntoa() :

    char* inet_ntoa(struct in_addr in);
```
    Fonction qui permet de convertir une adresse IPv4 en une chaîne de caractères au format dot-decimal. 
    
    Cette fonction prend en argument une structure 'in_addr' contenant l'adresse IPv4 à convertir, et
    renvoie un pointeur vers une chaîne de caractères contenant l'adresse au format dot-decimal.

    Par exemple, l'adresse IPv4 192.168.1.1 sera représentée sous forme de chaîne de caractères au
    format dot-decimal comme "192.168.1.1".

    La structure in_addr en C++98 est une structure utilisée pour stocker une adresse IPv4.
    Cette structure contient le champ suivant :
```cpp
        in_addr_t s_addr : un entier non-signé contenant l'adresse IPv4 au format binaire.
```
    Notez que cette fonction est définie dans l'en-tête <arpa/inet.h> en C++98. De plus, cette
    fonction n'est pas thread-safe et peut poser des problèmes de portabilité.

```cpp
inet_addr() :
    
    in_addr_t inet_addr(const char *cp);
```
    Fonction qui permet de convertir une adresse IPv4 en format dot-decimal en un entier non-signé au
    format binaire. 

    Cette fonction prend en argument un pointeur vers une chaîne de caractères contenant l'adresse IPv4
    au format dot-decimal, et renvoie un entier non-signé contenant l'adresse au format binaire.

    Le format binaire est un format couramment utilisé pour stocker des adresses IPv4 en mémoire, car
    il permet de représenter l'adresse sous forme d'un seul entier non-signé, ce qui est plus efficace
    en termes de mémoire et de performance.

    Par exemple, l'adresse IPv4 192.168.1.1 sera représentée en format binaire sous la forme d'un entier
    non-signé tel que 0xC0A80101.

    Notez que cette fonction est définie dans l'en-tête <arpa/inet.h> en C++98. De plus, cette fonction
    n'est pas thread-safe et peut poser des problèmes de portabilité.

```cpp
listen() :

    #include <sys/types.h>
    #include <sys/socket.h>

    int listen(int socket, int backlog);
```
    Permet à un socket d'entrer en mode écoute, c'est-à-dire qu'il attend des connexions entrantes
    de clients.
    Cette fonction est utilisée conjointement avec la fonction bind(), qui attribue une adresse à un socket, et la fonction accept(), qui accepte les connexions entrantes et retourne un nouveau 
    socket pour communiquer avec le client.

    Cette fonction prend en arguments le descripteur de socket (socket) et le nombre maximal de 
    connexions entrantes en attente (backlog). La fonction retourne 0 en cas de succès ou -1 en
    cas d'erreur.

    example d'utilisation :
```cpp
            #include <sys/types.h>
            #include <sys/socket.h>
            #include <netinet/in.h>
            #include <unistd.h>

            int main()
            {
                // Création d'un socket
                int sock = socket(AF_INET, SOCK_STREAM, 0);
                if (sock < 0) {
                    // Erreur
                    return 1;
                }

                // Attribue une adresse à ce socket
                struct sockaddr_in addr;
                addr.sin_family = AF_INET;
                addr.sin_port = htons(12345);
                addr.sin_addr.s_addr = htonl(INADDR_ANY);
                bind(sock, (struct sockaddr*)&addr, sizeof(addr));

                // Entre en mode écoute
                listen(sock, 5);

                // Accepte les connexions entrantes
                int client_sock = accept(sock, NULL, NULL);
                if (client_sock < 0) {
                    // Erreur
                    return 1;
                }

                // Communique avec le client via le nouveau socket
                ...

                // Ferme les sockets
                close(client_sock);
                close(sock);

                return 0;
            }
```

```cpp
lseek() :

    off_t lseek(int fildes, off_t offset, int whence);
```
    Permet de déplacer le curseur d'un fichier à une position spécifiée. Cette fonction est utilisée
    pour naviguer dans un fichier et lire ou écrire des données à des positions spécifiques.

    Cette fonction prend en arguments le descripteur de fichier (fildes), le décalage à partir de
    la position spécifiée par whence (offset) et l'origine à partir de laquelle le décalage est
    calculé (whence). La fonction retourne la position finale du curseur dans le fichier, ou -1 en
    cas d'erreur.

    Le paramètre whence peut prendre l'une des valeurs suivantes :
        SEEK_SET : déplace le curseur à la position absolue spécifiée par offset
        SEEK_CUR : déplace le curseur à partir de sa position actuelle en ajoutant offset
        SEEK_END : déplace le curseur à partir de la fin du fichier en ajoutant offset

```cpp
ntohl() :

    #include <arpa/inet.h>

    uint32_t ntohl(uint32_t netlong);
```
    Permet de convertir un nombre entier stocké en format réseau en format hôte. Le format réseau
    est utilisé pour représenter les nombres entiers lorsqu'ils sont transmis sur un réseau, tandis
    que le format hôte correspond au format utilisé par le système d'exploitation en cours d'exécution.

    Cette fonction prend en argument un nombre entier au format réseau (netlong) et retourne la
    valeur convertie au format hôte. Le type uint32_t est un type entier non signé sur 32 bits,
    ce qui correspond au type utilisé pour représenter les nombres entiers sur un réseau.

```cpp
ntohs() :

    uint16_t ntohs(uint16_t netshort);
```
    Fonction qui convertit un nombre entier court (short) stocké en ordre de réseau (network order)
    en ordre d'hôte (host order). Cela signifie que la fonction convertit un nombre stocké sur 16
    bits dans le format utilisé par les protocoles réseau pour l'échange d'informations sur un réseau
    (généralement l'Internet) en le format utilisé par l'ordinateur local sur lequel le nombre est lu.

     La fonction prend donc en paramètre un nombre entier non signé sur 16 bits stocké en ordre de
     réseau, et retourne un nombre entier non signé sur 16 bits stocké en ordre d'hôte.


Note sur le format hote :
    Le format hôte est utilisé dans les cas où un programme doit manipuler des nombres entiers
    à l'intérieur du système d'exploitation, par exemple pour effectuer des calculs, stocker des
    données dans des variables, etc.

    Le format hôte est également utilisé lorsqu'un programme doit envoyer ou recevoir des données
    sur un réseau, mais que ces données doivent être interprétées par le système d'exploitation.
    Dans ce cas, les données doivent être converties du format réseau au format hôte avant d'être utilisées par le programme.

```cpp
poll() :

    int poll(struct pollfd *fds, nfds_t nfds, int timeout);
```
    Permet de surveiller plusieurs files d'entrée-sortie (I/O) en même temps pour déterminer si
    elles sont prêtes à être lues ou écrites. Elle fonctionne de manière similaire à la fonction
    select en C, mais est plus facile à utiliser et plus efficace sur certains systèmes d'exploitation.

    La fonction prend en paramètres :
        pollfd : un tableau de structures (une pour chaque file d'I/O à surveiller)
        nfds : le nombre d'éléments dans ce tableau
        timeout : un délai d'attente en millisecondes

    La structure 'pollfd' contient les elements suivants :
        fd : un entier qui représente le descripteur de fichier à surveiller.
        events : un entier bit-à-bit qui indique les événements pour lesquels on souhaite
            recevoir des notifications.
        revents : un entier bit-à-bit qui indique les événements qui se sont produits pour le
            descripteur de fichier spécifié dans le champ fd.

    Les événements qui peuvent être surveillés et notifiés sont définis par les constantes suivantes :
        POLLIN : indique qu'il y a des données en attente de lecture sur le descripteur de fichier.
        POLLPRI : indique qu'il y a des données prioritaires en attente de lecture sur le descripteur
            de fichier.
        POLLOUT : indique qu'il est possible d'écrire sur le descripteur de fichier sans bloquer.
        POLLERR : indique qu'il y a eu une erreur sur le descripteur de fichier.
        POLLHUP : indique qu'il y a eu un décrochage sur le descripteur de fichier (par exemple, si
            la connexion réseau associée au descripteur de fichier a été interrompue).
        POLLNVAL : indique que le descripteur de fichier spécifié dans le champ fd n'est pas valide.

    La fonction retourne le nombre de files d'I/O qui sont prêtes à être lues ou écrites, ou 0 si
    aucune file n'est prête avant que le délai d'attente ne soit écoulé, ou -1 si une erreur se produit.

        Example d'utilisation :
```cpp
            #include <poll.h>

            // Tableau de structures pollfd pour stocker les files d'I/O à surveiller
            struct pollfd fds[2];

            // Initialisation des structures pollfd
            fds[0].fd = STDIN_FILENO;  // Surveiller l'entrée standard
            fds[0].events = POLLIN;    // Attendre des données en entrée

            fds[1].fd = STDOUT_FILENO; // Surveiller la sortie standard
            fds[1].events = POLLOUT;   // Attendre des données en sortie

            // Surveiller les files d'I/O pendant un délai de 100 ms
            int nready = poll(fds, 2, 100);

            if (nready == -1) {
                // Erreur
            } else if (nready == 0) {
                // Aucune file d'I/O prête avant le délai d'attente
            } else {
                if (fds[0].revents & POLLIN) {
                    // L'entrée standard est prête à être lue
                }
                if (fds[1].revents & POLLOUT) {
                    // La sortie standard est prête à être écrite
                }
            }
```
```cpp
recv() :

    ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```
    Permet de recevoir des données depuis un socket. Elle prend en paramètre un descripteur de socket,
    un tampon où stocker les données reçues, la taille du tampon et un entier indiquant les options
    de réception. Elle retourne le nombre d'octets reçus, ou -1 en cas d'erreur.

    Arguments :
        sockfd : le descripteur de socket depuis lequel on souhaite recevoir des données.
        buf : un pointeur vers le tampon où stocker les données reçues.
        len : la taille du tampon buf, en octets.
        flags : un entier indiquant les options de réception.

    La fonction recv() est utilisée en conjonction avec les sockets pour recevoir des données envoyées
    par un autre programme sur le réseau. Elle peut être utilisée avec différents protocoles réseau,
    tels que TCP ou UDP, pour implémenter des applications client-serveur. Par exemple, un serveur
    peut utiliser recv() pour recevoir des requêtes envoyées par des clients, et un client peut
    utiliser recv() pour recevoir les réponses du serveur.

```cpp
send() :

```


```cpp
setsockopt() :

```


```cpp
signal() :

```


```cpp
socket() :

```