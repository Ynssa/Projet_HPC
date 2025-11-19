# Code séquentiel


## Utilisation


### Compiler les programmes (à la racine du projet)

make


### Format du fichier d'entrée

Nx Ny Lx Ly D dt nmax eps cas

(sur la première ligne, dans l'ordre, un unique espace séparant les valeurs puis un retour à la ligne à la fin)

Voir les fichiers dans le répertoire 'input' pour un exemple


### Utilisation des programmes


#### Calculer la solution approchée à partir du fichier 'input.txt' et écrire le résultat dans le fichier de sortie 'output.txt'

./heat input.txt output.txt


#### Calculer l'ordre du schéma à partir du fichier 'input.txt' et écrire le résultat dans le fichier de sortie 'output.txt' (le nombre de noeuds est ignoré; les puissances de 2, de 2^2 à 2^7 sont choisies)

./order input.txt output.txt


#### Visualiser un fichier de sortie 'output.txt' sur gnuplot

gnuplot output.txt -e 'splot "output.txt" using 3:4:5; pause mouse close'


## Exemples (se placer à la racine du projet)


### Lancer un exemple

./heat input/cas1.in output/cas1.out

Des exemples de fichier d'entrées sont le répertoire 'input'


### Lancer tous les exemples

make output


### Visualiser les résultats des exemples

gnuplot display/cas1.gp # pour le cas 1
gnuplot display/cas2.gp # pour le cas 2
gnuplot display/order.gp # courbe de l'ordre


### Effacer les éxecutables et les objets

make clean


### Effacer les sorties des exemples dans le répertoire 'output' en plus

make clean_all


## Organisation du code

Les fichiers source sont dans le répertoire 'src'
Les en-têtes sont dans le répertoire 'include'
Les fichiers des exemples sont contenus dans les répertoires 'display', 'input' et 'output'

Les variables globales/paramètres du problème/schéma sont définies dans le fichier 'variables.c'

Les fonctions des cas tests sont définies dans le fichier 'fgh.c'

La multiplication par A est définie dans 'matmul_A.c'
La génération du second membre est définie dans 'right_hand_side.c'
L'algorithme du gradient conjugué est défini dans 'conjugate_gradient.c'
