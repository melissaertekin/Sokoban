# Sokoban
Vous trouverez ici les fichiers de base pour le TP noté concernant le jeu du Sokoban
Les consignes et l'énoncé se trouve à cette address [TP Sokoban](https://techdevprintemps2022.pages.unistra.fr/TP_TechDevEnonce/)

# Information Generales
Le jeu commence par l'affichage du grid du niveau 1. Vous pouvez deplacer le joueur en saisant h,j,k,l. Vous pouvez passer au nivau suivant en saisant n mais attention vous ne pouvez pas passer au niveau suivant sans avoir completer le niveau courant. Si vous avez finit toutes les niveau, le jeu s'arrete automatiquement.
Si vous poussez le box à cote des murs et s'il n'y a pas une objective dans la ligne ou colonne (selon le movement de joueur) alors on regarde si le nombre des boxs restent est plus grands que le nombre des objectives restent. Si oui alors vous pouvez continuer, pas de probleme et sinon vous perdre le jeu.
Dans le cas vous perdre le jeu, une option de rejouer le meme niveau vont etre affiche. Vous pouvez rejouer le meme niveau en saisant r. 
Vous pouvez quitter le jeu en saisant q.

# Passage au niveau suivant
Dans le fichier main.c :
J'ai crée une tableau de type Path (ie. const char *)
Dans le jeu, en cas de saisi d'un n: On passe au prochaine element dans cette tableau des Path.
Si vous voulez ajouter des niveau, il faut augmenter la taille de cette tableau et ajouter les element dans l'ordre de la dificultée.
Si toute les élements de cette tableau est jouée alors le joueur a finit le jeu. On affiche une message pour le dire aux joueur et on quitte le jeu.

# IMPORTANT
Si vous voulez essayer le code source avec une autre fichier txt, il faut voir s'il y a 4 elements écrit dans le 1ère ligne du fichier:
1. nombre = Nombre des colonnes
2. nombre = Nombre des linges
3. nombre = Nombre des objectives
4. nombre = Nombre des box
(Nombre de box est ajoutée afin de voir la psoibbilité de perdre)


# Version GCC/CLANG
C'est une copie-colle de la commande écrit dans le terminal:
melissaertekin@Melissa-MacBook-Pro ~ % gcc --version
Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/Library/Developer/CommandLineTools/SDKs/MacOSX12.1.sdk/usr/include/c++/4.2.1
Apple clang version 12.0.5 (clang-1205.0.22.11)
Target: x86_64-apple-darwin20.6.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin