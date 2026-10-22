# MSSIS-ProjetC-CS
## Présentation
Ce projet est organisé en plusieurs fichiers sources compilables situés dans le repertoire src/

* main.c : point d'entrée du projet, parsing des arguments
* mode_g.c : fonctions relatives au mode G, le main appelle la fonction mode_g_run
* mode_l.c : fonctions relatives au mode L, le main appelle la fonction mode_l_run
* binary_tree.c : fonctions relatives à la gestion d'un arbre binaire (et liste chainée, cf representation)

## Compilation

Un fichier Dockerfile est présent à la racine ainsi qu'un Makefile.
```bash
docker build -t t3c . 
```
puis :
```bash
docker run --rm -ti -v "$(realpath .)":/usr/src/app t3c
```
## Utilisation 

### Mode G 
```bash
./t3c G -i <dictionnaire> -o <t3c_output> [-a <algo>]
```
* -i <dictionnaire> : Obligatoire, fichier contenant des mots de passe de longueur maximum 127 caractères, séparés par '\n', doit être accessible en lecture
* -o <t3c_output> : Obligatoire, fichier de sortie, doit être accessible en écriture

### Mode L
```bash
./t3c L -t <t3c_path>
```
* -t <t3c_path> : Obligatoire, fichier table de correspondance mot de passe/hash, sous la forme [mot_de_passe]\t[hash_MD5]\n

L'utilisateur doit ensuite entrer un hash dans le terminal puis [ENTER]
Si le hash est lié à un ou plusieurs mots de passe, ils sont imprimés en sortie séparées par '\t'
Si aucun mot de passe n'est trouvé, une ligne vide est imprimée dans le terminal.

## Fonctionnement 

### Parsing des arguments
Le parsing est effectué avec argp. 
La liste des options est contenues dans options[]
Les arguments sont sauvegardés dans une structure arguments_t.
Le mode (de type enum t3c_mode) determine l'appel à mode_g_run ou mode_l_run.

### Mode G
Le fichier input est lu ligne par ligne. Un mot de passe ne doit pas dépasser 127 caractères.
Chaque ligne est hashé par MD5 grâce à la librairie openssl/evp.
Le fichier t3c de sortie est construit en écriavnt pour chaque ligne :
>[mot de passe]\t[hash_MD5]\n

### Mode L
Le contenu de la table est lu ligne par ligne et stocké sous forme d'un arbre binaire.
Chaque noeud a pour attribut le hash (qui est la valeur utilisée pour parcourir l'arbre) et une liste chainée de mots de passe.
Dans le cas général, chaque noeud aura une liste chainée de mot de passe d'une longueur d'un seul noeud.
Si plusieurs mots de passe ont le même hash, la liste chaînée aura autant de noeud que de mot de passe avec hash identique.
A chaque entrée utilisateur sur stdin, le programme retourne :
* une ligne vide, si aucun mot de passe ne correspond au hash demandé
* un ou plusieurs mots de passe séparés par \t correspondant au hash

La sortie se fait en entrant 
```bash
exit
```

