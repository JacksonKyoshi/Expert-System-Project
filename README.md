Voici le code c de notre projet d'algo N3 sur les expert system.
Nous avons choisi de créer un expert system capable de recommander des cadeaux en fonction :
- des hobbies de la personne 
- de l’âge de la personne 
- de la relation avec la personne 
- du budget 

========== Faits ========== 
- Hobbies de la personne
	Lecture
	Cinéma
	Plein Air
	Technologie
	Cuisine
	Musique
	Voyage
	Art
	Vin
- Age de la personne 
	Moins de 18 ans (1)
	18 - 50 ans (2)
	Plus de 50 ans (3)
- Relation avec la personne
	Enfant
	Famille (parents, grand-parents, tantes, oncles…)
	Epoux/se
	Ami
- Budget
	Moins de 20€ (a)
	20 - 100€ (b)
	Plus de 100€ (c)


========== Comment utiliser notre programme ? ========== 

Nous avons créer une interface graphique SDL afin de simplifier l'utilisation du programme.
Mais en cas d'incapacité à utiliser cette interface, le programme est aussi utilisable directement sur la console. Dans ce cas il suffit de make, puis d'exécuter ./main.

Pour l'interface graphique SDL, il faut make, puis exécuter ./display.

========== Comment installer SDL ? ==========

Pour installer sdl2, il y a trois commandes à installer sur le terminal :

sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-ttf-dev

Une fois cela fait, vous pouvez make !!!!!

========== Interface graphique SDL ========== 

En exécutant le programme, une fenêtre SDL apparaît et il y a 4 choix possibles :
- Afficher règles 
	permet d'afficher toutes les règles présentent dans le fichier .kbs, utilisées par l'expert system
- Test cadeau 
	permet de tester si un cadeau en particulier est une bonne idée en fonction des faits choisis par l'utilisateur (algo backward chaining)
- Trouve cadeau 
	permet de trouver un cadeau en fonction des faits choisis par l'utilisateur (algo forward chaining)
- Quitter
	quitter le programme

---------- Test cadeau ----------
L'utilisateur doit choisir les faits :
- Hobbies : lecture, cinéma, plein air, technologie, cuisine, musique, art ou vin
- Age : enfant (-18 ans), adulte (entre 18 et 50 ans) ou sénior (+50 ans)
- Relation : enfant (forcément - de 18 ans), famille (parent, grand-parent, oncle, tante,... forcément adulte ou sénior), couple (forcément adulte ou sénior), ami
- Budget : moins de 20€, entre 20 et 100€, plus de 100€
- Idée cadeau : choisir un cadeau parmis tous les cadeaux présents dans la liste de règles
==> Cliquer sur le bouton "Est ce que j'ai pris le bon cadeau" pour voir le résulat.

/!\ Pour chaque catégorie de fait (hobbies, age, relation, budget, idée cadeau), l'utilisateur ne peut faire qu'un choix (le budget ne peut pas être à la fois -20€ et +100€).

---------- Trouve cadeau ----------
L'utilisateur doit choisir les faits :
- Hobbies : lecture, cinéma, plein air, technologie, cuisine, musique, art ou vin
- Age : enfant (-18 ans), adulte (entre 18 et 50 ans) ou sénior (+50 ans)
- Relation : enfant (forcément - de 18 ans), famille (parent, grand-parent, oncle, tante,... forcément adulte ou sénior), couple (forcément adulte ou sénior), ami
- Budget : moins de 20€, entre 20 et 100€, plus de 100€
==> Cliquer sur le bouton "Trouver le bon cadeau" pour voir le résulat.

/!\ Pour chaque catégorie de fait (hobbies, age, relation, budget), l'utilisateur ne peut faire qu'un choix (le budget ne peut pas être à la fois -20€ et +100€).
