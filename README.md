## Generateur de type Geffe

Ce génerateur emploie trois LFSR L , L 1 et L 2 de taille 16 bits chacun. Ces trois LFSR sont initialisés avec une clé K = (k 0 , k 1 , k 2 ) de 48 bits.
Les coefficients de retroaction
(c 15, c 14 , . . . , c 1 , c 0 ) pour chacun des trois registres sont :
L 0 : (c 15, c 14 , . . . , c 1 , c 0 ) = (0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1)
L 1 : (c 15, c 14 , . . . , c 1 , c 0 ) = (0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1)
L 2 : (c 15, c 14 , . . . , c 1 , c 0 ) = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1)

Compilez et executez le programme avec :

k_{n+1}

$\alpha A$

```
$ make 
$ make run
```
