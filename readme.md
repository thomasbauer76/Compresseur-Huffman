# Projet Huffman Compression

Ce répertoire contient un projet de compression de données implémenté en langage C, utilisant l'algorithme de compression sans perte basé sur le codage de Huffman.

## Structure du Projet

### Dossier rapport
- **latex/** : Contient les fichiers LaTeX pour la documentation.
- main.pdf : le rapport de notre projet

### Dossier programme
- **bin/** : Répertoire où les fichiers exécutables seront générés.
- **include/** : Contient les fichiers d'en-tête.
- **lib/** : Contient les bibliothèques du projet.
- **src/** : Contient les fichiers source du projet.
- **doc/** : Répertoire où la documentation générée sera stockée. Ce dernier est crée après la commande "make doc".
- **tests/** : Répertoire où les fichiers de tests seront générés.

## Fichiers Importants

- **Makefile** : Le fichier de configuration Makefile pour compiler, exécuter les tests, générer la documentation, et nettoyer le projet.
- **main.c** : Le fichier principal du programme.
- **doxyfile** : Le fichier de configuration pour Doxygen.

## Compilation

Pour compiler le projet, utilisez la commande suivante :

```
make all
```

Cela générera un exécutable nommé "huffman" dans le répertoire "bin/".

## Tests

Pour créer les tests, utilisez la commande suivante :

```
make tests
```

Cela générera deux exécutables de tests, "testsTADs" et "testsFonctionsMetier", dans le répertoire "tests/".

## Génération de la Documentation

Pour générer la documentation, utilisez la commande suivante :

```
make doc
```

La documentation générée sera disponible dans le répertoire "doc/".

## Génération du rapport

Pour générer le rapport du projet, utilisez la commande suivante :

```
make pdf
```

La documentation générée sera disponible dans le répertoire "doc/".

## Nettoyage du Projet

Pour nettoyer le projet, y compris les fichiers générés et les exécutables, utilisez la commande suivante :

```
make clean
```

Cela supprimera les répertoires "bin/", "tests/", "latex/", et "doc/", ainsi que les fichiers objets dans le répertoire "src/".

N'hésitez pas à personnaliser le Makefile en fonction de vos besoins spécifiques.