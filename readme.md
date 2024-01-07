# Projet Huffman Compression

Ce répertoire contient un projet de compression de données implémenté en langage C, utilisant l'algorithme de compression sans perte basé sur le codage de Huffman.

## Structure du Projet

- **bin/** : Répertoire où les fichiers exécutables seront générés.
- **src/** : Contient les fichiers source du projet.
- **include/** : Contient les fichiers d'en-tête.
- **latex/** : Contient les fichiers LaTeX pour la documentation.
- **doc/** : Répertoire où la documentation générée sera stockée.
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

Pour exécuter les tests, utilisez la commande suivante :

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

## Nettoyage du Projet

Pour nettoyer le projet, y compris les fichiers générés et les exécutables, utilisez la commande suivante :

```
make clean
```

Cela supprimera les répertoires "bin/", "tests/", "latex/", et "doc/", ainsi que les fichiers objets dans le répertoire "src/".

N'hésitez pas à personnaliser le Makefile en fonction de vos besoins spécifiques.