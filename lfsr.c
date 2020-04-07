#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	//3 LFSR composant le systeme
	int LFSR1[16];
	int LFSR2[16];
	int LFSR3[16];

	//bits de sorties réutilisés lors du decalage
	int bit1;
	int bit2;
	int bit3;


	int F[8];	

}GEFFE;



void affSequence ( int * s, int n)	{
	//Affichage de la sequence
	printf ("\nAffichage des %d bits de la sequence :\n",n);
	for (int i = 0; i < n; i++)
		printf ("[%d]", s[i]);
	printf ("\n");	
}

void affLFSR (GEFFE * Geffe)	{

	printf ("Affichage LFSR :\n");

	//Affichage LFSR 1
    for (int j = 0; j < 16; j++)
    {
      printf ("[%d]", Geffe->LFSR1[j]);
    }
    printf ("\n");

	//Affichage LFSR 2
	for (int j = 0; j < 16; j++)
    {
      printf ("[%d]", Geffe->LFSR2[j]);
    }
    printf ("\n");

	//Affichage LFSR 3
	for (int j = 0; j < 16; j++)
    {
      printf ("[%d]", Geffe->LFSR3[j]);
    }
    printf ("\n");
  
		
		
}

void correlation(int F[]){
	
	int x[3][8]={
					       {0,1,0,1,0,1,0,1},
						   {0,0,1,1,0,0,1,1},
						   {0,0,0,0,1,1,1,1}
					};
					//F[] ={1,1,1,1,1,1,1,1};
					//01010010
	float correl[3]={0.,0.,0.};

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0;  j< 3; j++)
			{
				if (x[j][i]==F[i]){correl[j]=correl[j]+1;}
			}
			
		}

		printf("\nF=");
		for (int i = 0; i < 8; i++)
		{
			printf("[%d]",F[i]);
		}
		printf("\n\n");

		for (int i = 0; i < 3; i++)
		{
			correl[i]=correl[i]/8*100;
		}

		printf("La correlation de F avec x0 est de %f\nLa correlation de F avec x1 est de %f\nLa correlation de F avec x2 est de %f\n\n",
		correl[0],correl[1],correl[2]);

}

int F(int x0,int x1,int x2){
	
	int a;

	//Recherche du f correspondant

	if (x0==0 && x1==0)
	{
		if(x2==0)a=0;	//000
		else a=4;		//001
	}
	if (x0==0 && x1==1)
	{
		if(x2==0)a=2;	//010
		else a=6;		//011
	}
	if (x0==1 && x1==0)
	{
		if(x2==0)a=1;	//100
		else a=5;		//101
	}
	if (x0==1 && x1==1)
	{
		if(x2==0)a=3;	//110
		else a=7;		//111
	}

	return a;
}

int decalage ( GEFFE * Geffe)	{

	//dernier bit de chaque lfsr pour savoir quel indice de f prendre
	int a= F ( (Geffe->LFSR1[15]), (Geffe->LFSR2[15]), (Geffe->LFSR3[15])); 


	//XOR entre les bits correspondants

	//L0 : (c15,c14,...,c1,c0)=(0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,1)
	//L1 : (c15,c14,...,c1,c0)=(0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,1)
	//L2 : (c15,c14,...,c1,c0)=(0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1)
	Geffe->bit1= (Geffe->LFSR1[0]) ^ (Geffe->LFSR1[1]) ^ (Geffe->LFSR1[4]) ^ (Geffe->LFSR1[7]);
	Geffe->bit2= (Geffe->LFSR2[0]) ^ (Geffe->LFSR2[1]) ^ (Geffe->LFSR2[7]) ^ (Geffe->LFSR2[11] );
	Geffe->bit3= (Geffe->LFSR3[0]) ^ (Geffe->LFSR3[2]) ^ (Geffe->LFSR3[3]) ^ (Geffe->LFSR3[5]);


	//Décalage des bits
	for (int i = 15; i > 0; i--)	{
		Geffe->LFSR1[i] = Geffe->LFSR1[i-1];
		Geffe->LFSR2[i] = Geffe->LFSR2[i-1];
		Geffe->LFSR3[i] = Geffe->LFSR3[i-1];
	}
	
	//Remise des bits sortis au début
	Geffe->LFSR1[0] = Geffe->bit1;
	Geffe->LFSR2[0] = Geffe->bit2;
	Geffe->LFSR3[0] = Geffe->bit3;


	//pour verifier le decalage
  	//printLFSR(Geffe); //pour verifier le decalage
  
  return Geffe->F[a];
}


int * generateur(GEFFE* Geffe, int n) { 
	
	int * s =malloc ( n * sizeof (int));
	
	for (int i = 0; i < n; i++)	{
		s[i] = decalage (Geffe);
	}
	affSequence(s,n);

	free(s);
	
	return s;
}


void initLFSR(GEFFE* Geffe){


	//Inittialisation des LFSR avec des valeurs aux choix
	int L1[] ={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
 	int L2[] ={0,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0};
	int L3[] ={0,1,0,1,0,1,0,1,0,0,1,0,1,0,1,0};
	int F[] ={0,1,0,1,0,0,1,0};
	//int F[] ={1,1,1,1,1,1,1,1};

 	
	//copie des tableaux dans la structure de donées
     memcpy(Geffe->LFSR1,L1,sizeof(L1));
     memcpy(Geffe->LFSR2,L2,sizeof(L2));
     memcpy(Geffe->LFSR3,L3,sizeof(L3));
     memcpy(Geffe->F,F,sizeof(F));

	 correlation(F);
		

    affLFSR(Geffe);
      
}


void exo1(int n){
	GEFFE* Geffe =malloc(sizeof(GEFFE));
	initLFSR(Geffe);
	int *s=generateur( Geffe,n);
  	free(Geffe);
}

int main(int argc, char const *argv[])
{
	exo1(8);
	
	return 0;
}
