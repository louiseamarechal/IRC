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

```


```cpp
getprotobyname() :

```


```cpp
getsockname() :

```


```cpp
htonl() :

```


```cpp
htons() :

```


```cpp
inet_ntoa() :

```


```cpp
inet_addr() :

```


```cpp
listen() :

```


```cpp
lseek() :

```


```cpp
ntohl() :

```


```cpp
ntohs() :

```


```cpp
poll() :

```


```cpp
recv() :

```


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