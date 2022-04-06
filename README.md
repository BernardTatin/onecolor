# One Color

Le but de cet outil est de ne garder qu'une seule couleur d'une photo pour rendre en noir et blanc tout le reste. Pour la teinte (_hue_), voir [HSL and HSV](https://en.m.wikipedia.org/wiki/HSL_and_HSV) sur _Wikipedia_.

## le code

Pour le moment, tout est écrit en _C_ sur une plate-forme _Linux_. La compilation se fait très simplement:

```sh
$ mkdir build
$ cd build
$ cmake ..
-- The C compiler identification is GNU 11.2.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: .../build
$ make
/usr/bin/cmake -S... -B.../build --check-build-system CMakeFiles/Makefile.cmake 0
/usr/bin/cmake -E cmake_progress_start .../build/CMakeFiles .../build//CMakeFiles/progress.marks

-- a lot of lines --

[100%] Built target one-color
make[1] : on quitte le répertoire « .../build »
/usr/bin/cmake -E cmake_progress_start .../build/CMakeFiles 0
```



## versions

### 5 avril 2022

La version actuelle ([one-color-0.1.1](https://github.com/BernardTatin/onecolor/releases/tag/v0.1.1)) est un outil en ligne de commande dont l'aide (succinte) est la suivante:

```bash
one-color [-0|-R|-V|-B|-Y|-h hue] jpegin jpegout
```

Les options possibles sont en réalité les suivantes:

- affichage:
  - `-V`: mode verbeux,
- couleurs (options exclusives les unes des autres mais en fait, c'est la dernière qui est vraiment prise en compte)
  - `-0`: sortie en noir et blanc, pas de sélection de couleur,
  - `-R`: mise en évidence du rouge (équivaut à `-h 0`),
  - `-G`: mise en évidence du vert (équivaut à `-h 120`),
  - `-B`: mise en évidence du bleu (équivaut à `-h 240`),
  - `-Y`: mise en évidence du jaune (équivaut à `-h 60`),
  - `-h hue`: hue est une valeur entre 0 et 360 correspondant à la teinte choisie,
- fichiers:
  - `jpegin jpegout`
    - `jpegin`: fichier image en entrée, au format JPEG, le fichier doit exister et avoir un format JPEG valide,
    - `jpegout`: fichier image en sortie, écrase sans vergogne le fichier existant du même nom et supprime toutes les données EXIF du fichier en entrée.

