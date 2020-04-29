## Generateur de type Geffe

Ce génerateur emploie trois LFSR L0, L1 et L2 de taille 16 bits chacun. Ces trois LFSR sont initialisés avec une clé K de 48 bits
Les coefficients de retroaction pour chacun des trois registres sont :
L0 : (0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1)
L1 : (0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1)
L2 : (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1)

Compilez et executez le programme avec :
```
$ make 
$ make run
```
