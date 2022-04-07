# TODO

## une interface graphique

La ligne de commande c'est cool, mais c'est pas très _user friendly_. Le problème principal est de choisir la bibliothèque qui doit répondre à ces critères dans l'ordre de priorité:

- simplicité d'utilisation:
  - pour créer des boîtes de dialogue,
  - afficher des images.
- écrite en _C_, à la rigueur mais vraiment du bout des doigts, en _C++_,
- être _open source_, 
- être bien suivie,
- éventuellement, être multi-plateformes.

Les bibliothèques en vues sont actuellement:

- _OpenGL_ et _DevIL_, sont des paquets pour _Ubuntu_ et il y a un bon exemple (dans le répertoire [opengl](opengl/)) trouvé sur le WEB,
- _Elementary_, du projet _Enlightenment_,
- _GTK_, de _GNOME_,
- _Clutter_, basé sur _OpenGL_, mais semble abandonné,
- _[GLFW](https://www.glfw.org/)_, basée sur _OpenGL_.

## _OpenGL_ et _DevIL_

Il faut installer _Glut_ et _DevIL_, ce qui est simple avec _Ubuntu_ et ses dérivées. J'ai trouvé un très bon exemple qui fonctionne parfatement sur [How to load an image in Opengl?](https://community.khronos.org/t/how-to-load-an-image-in-opengl/71231/5) donné par [The_Little_Body](https://community.khronos.org/u/The_Little_Body).

