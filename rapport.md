# Introduction à la cryptographie : rapport du DM

__Question 1__: Comme le suggérait le sujet, nous avons choisi le C pour ce projet. Nous allons utiliser la librairie GMP pour gérer les nombres entiers de grande taille. Cette librairie permet d'effectuer les quatres opérations élémentaires sur des entiers de taille arbitraire, mais aussi de calculer des modulos et des PGCD.

__Question 2__: Un générateur de nombres aléatoires cryptographiquement sûr est traditionellement défini par la satisfaction de deux tests : 

- Le test du _next-bit_ : à partir du kème nombre aléatoire généré, il n'existe pas d'algorithme en temps polynomial pour déterminer le k+1ème nombre généré avec une probabilité supérieure à 0.5. Ce test vérifie les qualités __statistiques__ du générateur.

- Le test d'état compromis : à partir de l'état du générateur à un moment donné, il doit être impossible de déterminer les nombres précédents de la séquence. 

Pour générer des nombres aléatoires en C, nous allons utiliser `libsodium`, et plus particulièrement son API `randombytes` qui permet de générer des nombres aléatoires cryptographiquement sûrs.

