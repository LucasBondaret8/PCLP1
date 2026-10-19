//Bondaret Lucas 312CB
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void swap(int *x, int *y)
{
	int aux = *x;
	*x = *y;
	*y = aux;
}

int afla_determinant(int **cheie_codificata)
{
	int det = 0;
	det = det + cheie_codificata[1][1] * cheie_codificata[2][2]
	* cheie_codificata[3][3];
	det = det + cheie_codificata[2][1] * cheie_codificata[3][2]
	* cheie_codificata[1][3];
	det = det + cheie_codificata[3][1] * cheie_codificata[1][2]
	* cheie_codificata[2][3];
	det = det - cheie_codificata[1][3] * cheie_codificata[2][2]
	* cheie_codificata[3][1];
	det = det - cheie_codificata[2][3] * cheie_codificata[3][2]
	* cheie_codificata[1][1];
	det = det - cheie_codificata[3][3] * cheie_codificata[1][2]
	* cheie_codificata[2][1];

	return det;

}

int modulo_det_lung(int det)
{
	int modulo = 0;
	if (det < 0)
		det = det * (-1);
	modulo = det % 37;
	return modulo;
}

int inversul_multiplicativ(int A)
{
	for (int i = 1; i < 37; i++)
		if ((A * i) % 37 == 1) {
			return i;
		}
	return 0;
}

void calcul_adjuncta(int **adjuncta_cheii)
{
	int **transpusa = (int **)malloc(4 * sizeof(int *));//Alocare matrice
			for (int i = 0; i < 4; i++)
				transpusa[i] = malloc(4 * sizeof(int));
	for (int j = 1; j <= 3; j++)
		for (int i = 1; i <= 3; i++)
			transpusa[i][j] = adjuncta_cheii[j][i];
	adjuncta_cheii[1][1] = transpusa[2][2] * transpusa[3][3]
	- transpusa[2][3] * transpusa[3][2];
	adjuncta_cheii[1][2] = -(transpusa[2][1] * transpusa[3][3]
		- transpusa[2][3] * transpusa[3][1]);
	adjuncta_cheii[1][3] = transpusa[2][1] * transpusa[3][2]
	- transpusa[2][2] * transpusa[3][1];
	adjuncta_cheii[2][1] = -(transpusa[1][2] * transpusa[3][3]
		- transpusa[1][3] * transpusa[3][2]);
	adjuncta_cheii[2][2] = transpusa[1][1] * transpusa[3][3]
	- transpusa[1][3] * transpusa[3][1];
	adjuncta_cheii[2][3] = -(transpusa[1][1] * transpusa[3][2]
		- transpusa[1][2] * transpusa[3][1]);
	adjuncta_cheii[3][1] = transpusa[1][2] * transpusa[2][3]
	- transpusa[1][3] * transpusa[2][2];
	adjuncta_cheii[3][2] = -(transpusa[1][1] * transpusa[2][3]
		- transpusa[1][3] * transpusa[2][1]);
	adjuncta_cheii[3][3] = transpusa[1][1] * transpusa[2][2]
	- transpusa[1][2] * transpusa[2][1];
	for (int i = 0; i < 4; i++)
		free(transpusa[i]);
	free(transpusa);
}

void inmultire_modulo_adjuncta(int **adjuncta_cheii, int X)
{
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			if (adjuncta_cheii[i][j] < 0)
				adjuncta_cheii[i][j] = -(adjuncta_cheii[i][j]) * X % 37;
			else
				adjuncta_cheii[i][j] = adjuncta_cheii[i][j] * X % 37;
}

char *inmultire_cheie_mesaj(int **matrice_bloc, int **adjuncta_cheii)
{
	char *bucatica_cod = (char *)malloc(4 * sizeof(char));
	//Alocarea bucatii pe care o returnez
	int temporar = (adjuncta_cheii[1][1] * matrice_bloc[1][1]
		+ adjuncta_cheii[1][2] * matrice_bloc[2][1]
		+ adjuncta_cheii[1][3] * matrice_bloc[3][1]) % 37;
		//Prima litera din bucatica
	if (temporar >= 0 && temporar <= 9)
		bucatica_cod[0] = temporar + '0';
	else
		if (temporar >= 10 && temporar <= 35)
			bucatica_cod[0] = temporar - 10 + 'A';
		else
			bucatica_cod[0] = '.';
	temporar = (adjuncta_cheii[2][1] * matrice_bloc[1][1]
		+ adjuncta_cheii[2][2] * matrice_bloc[2][1]
		+ adjuncta_cheii[2][3] * matrice_bloc[3][1]) % 37;
		//A doua litera din bucatica
	if (temporar >= 0 && temporar <= 9)
		bucatica_cod[1] = temporar + '0';
	else
		if (temporar >= 10 && temporar <= 35)
			bucatica_cod[1] = temporar - 10 + 'A';
		else
			bucatica_cod[1] = '.';
	temporar = (adjuncta_cheii[3][1] * matrice_bloc[1][1]
		+ adjuncta_cheii[3][2] * matrice_bloc[2][1]
		+ adjuncta_cheii[3][3] * matrice_bloc[3][1]) % 37;
		//A treia litera din bucatica
	if (temporar >= 0 && temporar <= 9)
		bucatica_cod[2] = temporar + '0';
	else
		if (temporar >= 10 && temporar <= 35)
			bucatica_cod[2] = temporar - 10 + 'A';
		else
			bucatica_cod[2] = '.';
	return bucatica_cod;
}

int main(void)
{
	int J, tura;// TASK 1
	scanf("%d", &J);
	int **nr_lovituri_nimerite = (int **)malloc(3 * sizeof(int *));
	//Alocare pt lovituri nimerite -> 0 reprezinta Jucatorul 1
	// 1 reprezinta Jucatorul 2
	for (int k = 0; k < 3; k++)
		nr_lovituri_nimerite[k] = calloc(301, sizeof(int));
	int **nr_lovituri_totale = (int **)malloc(3 * sizeof(int *));
	//Alocare pt lovituri totale
	for (int k = 0; k < 3; k++)
		nr_lovituri_totale[k] = calloc(301, sizeof(int));
	int *nrtotalnave = malloc(301 * sizeof(int));
	//Alocare pt nr de nave din fiecare meci
	for (tura = 1; tura <= J; tura++) {
		int N, M, gol, L, i, j;
	if (scanf("%d%d", &N, &M) != 2)
		break;
	int **mat1 = (int **)malloc((N + 1) * sizeof(int *));//Alocare mat1
	for (i = 0; i < N + 1; i++) {
		mat1[i] = (int *)malloc((M + 1) * sizeof(int));
		memset(mat1[i], 0, (M + 1) * sizeof(int));
	}
	int **mat2 = (int **)malloc((N + 1) * sizeof(int *));//Alocare mat2
	for (i = 0; i < N + 1; i++) {
		mat2[i] = (int *)malloc((M + 1) * sizeof(int));
		memset(mat2[i], 0, (M + 1) * sizeof(int));
	}
	//Declararea numarului de nave disponibile etc.
	int nrshinano = (N * M) / 70;
	int nryamato = (N * M) / 55;
	int nrbelfast = (N * M) / 40;
	int nrlaffey = (N * M) / 30;
	int nralbacore = (N * M) / 20;
	int nr1totalnave = nrshinano + nryamato
	+ nrbelfast + nrlaffey + nralbacore;
	int nr2totalnave = nrshinano + nryamato
	+ nrbelfast + nrlaffey + nralbacore;
	int nr1actualnave = 0;
	int nr2actualnave = 0;
	nrtotalnave[tura] = nr1totalnave;
	int cnt1nave = 5 * nrshinano + 4 * nryamato
	+ 3 * nrbelfast + 2 * nrlaffey + nralbacore;
	int cnt2nave = 5 * nrshinano + 4 * nryamato
	+ 3 * nrbelfast + 2 * nrlaffey + nralbacore;
	int randullui = 1;
	char *orientare = malloc(21 * sizeof(char));
	char *tip = malloc(21 * sizeof(char));
	while (nr1actualnave != nr1totalnave || nr2actualnave != nr2totalnave) {
		//Pozitionarea navelor
		int x, y;
		if (scanf("%s %s %d %d", tip, orientare, &x, &y) != 4)
			break;
		switch (*tip) {///Lungimea navei in functie de tip
		case 'S':
		L = 5; break;
		case 'Y':
		L = 4; break;
		case 'B':
		L = 3; break;
		case 'L':
		L = 2; break;
		case 'A':
		L = 1; break;
		}
	if (x <= N && y <= M) {//Cazul in care datele sunt ok
		if (randullui % 2 == 1) {//Randul Jucator 1
			if (*orientare == 'H') {//Cazul orizontal
				if (y + L - 1 <= M) {//daca am loc
					gol = 1;
					for (j = y; j <= (y + L - 1) && gol == 1; j++) {
					//verific daca e gol
						if (mat1[x][j] != 0)
							gol = 0;
					}
					if (gol == 1) {//daca e gol
						for (j = y; j <= (y + L - 1); j++) {
							if (j == y)//capatul
								mat1[x][j] = L * 10 + 7;
							else
								mat1[x][j] = L;
					}
		randullui++;
		nr1actualnave++;
		}
		else {//daca nu e gol
			printf("Nava ");
			switch (L) {
			case 5:
			printf("Shinano "); break;
			case 4:
			printf("Yamato "); break;
			case 3:
			printf("Belfast "); break;
			case 2:
			printf("Laffey "); break;
			case 1:
			printf("Albacore "); break;
			}
		printf("nu poate fi amplasata orizontal la coordonatele (%d, %d).\n",
			x, y);
		}
		}
		else{//daca nu am loc
			printf("Nava ");
			switch (L) {
			case 5:
			printf("Shinano "); break;
			case 4:
			printf("Yamato "); break;
			case 3:
			printf("Belfast "); break;
			case 2:
			printf("Laffey "); break;
			case 1:
			printf("Albacore "); break;
			}
			printf("nu poate fi amplasata orizontal la coordonatele (%d, %d).\n"
				, x, y);
		}
		}
		else {//Cazul vertical
			if (x - L + 1 >= 1) {//daca am loc
				gol = 1;
				for (i = x; i >= (x - L + 1) && gol == 1; i--) {//verific daca e gol
					if (mat1[i][y] != 0)
						gol = 0;
				}
				if (gol == 1) {//daca e gol
					for (i = x; i >= (x - L + 1); i--){
						if (i == x)//capatul
							mat1[i][y] = L * 10 + 8;
						else
							mat1[i][y]= L;
				}
					randullui++;
					nr1actualnave++;
			}
			else {//daca nu e gol
			printf("Nava ");
			switch (L) {
			case 5:
			printf("Shinano "); break;
			case 4:
			printf("Yamato "); break;
			case 3:
			printf("Belfast "); break;
			case 2:
			printf("Laffey "); break;
			case 1:
			printf("Albacore "); break;
			}
			printf("nu poate fi amplasata vertical la coordonatele (%d, %d).\n", x, y);
			}

			}
			else {//daca nu am loc
			printf("Nava ");
			switch (L) {
			case 5:
			printf("Shinano "); break;
			case 4:
			printf("Yamato "); break;
			case 3:
			printf("Belfast "); break;
			case 2:
			printf("Laffey "); break;
			case 1:
			printf("Albacore "); break;
			}
			printf("nu poate fi amplasata vertical la coordonatele (%d, %d).\n", x, y);
			}
			}
	}
	else{//Randul Jucator 2
		if (*orientare == 'H') {//Cazul orizontal
			if(y + L -1 <= M) {//daca am loc
				gol = 1;
				for (j = y; j <= (y + L - 1) && gol == 1; j++) {//verific daca e gol
					if(mat2[x][j] != 0)
						gol = 0;
				}
			if (gol == 1) {//daca e gol
				for (j = y; j <= (y + L - 1); j++){
					if (j == y)//capatul
						mat2[x][j] = L * 10 + 7;
					else
						mat2[x][j] = L;
				}
				randullui++;
				nr2actualnave++;
		}
		else {//daca nu e gol
			printf("Nava ");
			switch (L) {
			case 5:
			printf("Shinano "); break;
			case 4:
			printf("Yamato "); break;
			case 3:
			printf("Belfast "); break; 
			case 2:
			printf("Laffey "); break;
			case 1:
			printf("Albacore "); break;
			}
			printf("nu poate fi amplasata orizontal la coordonatele (%d, %d).\n", x, y);
		}
		}
		else {//daca nu am loc
			printf("Nava ");
			switch (L) {
			case 5:
			printf("Shinano "); break;
			case 4:
			printf("Yamato "); break;
			case 3:
			printf("Belfast "); break;
			case 2:
			printf("Laffey "); break;
			case 1:
			printf("Albacore "); break;
			}
			printf("nu poate fi amplasata orizontal la coordonatele (%d, %d).\n", x, y);
		}

		}
		else {//Cazul vertical
			if(x - L + 1 >= 1) {//daca am loc
				gol = 1;
			for (i = x; i >= (x - L + 1) && gol == 1; i--) {//verific daca e gol
				if(mat2[i][y] != 0)
					gol = 0;
			}
			if (gol == 1) {//daca e gol
				for (i = x; i >= (x - L + 1); i--){
					if (i == x)//capatul
						mat2[i][y] = L * 10 + 8;
					else
						mat2[i][y] = L;
				}
				randullui++;
				nr2actualnave++;
			}
			else {//daca nu e gol
				printf("Nava ");
				switch (L) {
				case 5:
				printf("Shinano "); break; 
				case 4:
				printf("Yamato "); break;
				case 3:
				printf("Belfast "); break;
				case 2:
				printf("Laffey "); break;
				case 1:
				printf("Albacore "); break;
				}
				printf("nu poate fi amplasata vertical la coordonatele (%d, %d).\n", x, y);
			}

			}
			else {//daca nu am loc
				printf("Nava ");
				switch (L) {
				case 5:
				printf("Shinano "); break;
				case 4:
				printf("Yamato "); break;
				case 3:
				printf("Belfast "); break;
				case 2:
				printf("Laffey "); break;
				case 1:
				printf("Albacore "); break;
				}
				printf("nu poate fi amplasata vertical la coordonatele (%d, %d).\n", x, y);

			}
		}
	}
			}
			else {//Cazul in care datele nu sunt ok
				printf("Nava ");
				switch (L) {
				case 5:
				printf("Shinano "); break;
				case 4:
				printf("Yamato "); break;
				case 3:
				printf("Belfast "); break;
				case 2:
				printf("Laffey "); break;
				case 1:
				printf("Albacore "); break;
				}
				printf("nu poate fi amplasata ");
				switch ( *orientare) {
				case 'H':
				printf("orizontal "); break;
				case 'V':
				printf("vertical "); break;
				}
				printf("la coordonatele (%d, %d).\n", x, y);
			}

			
		}
		free(tip);//Dealocari
		free(orientare);
		for (i = 1; i <= N; i++){//Afisare mat1
			if(i > 1)
				printf("\n");
			for(j = 1; j <= M; j++) {
				if(mat1[i][j] > 9)
					printf("%d ", mat1[i][j] / 10);
				else
					printf("%d ", mat1[i][j]);
			}
		}
		printf("\n\n");
		for (i = 1; i <= N; i++){//Afisare mat2
			if(i > 1)
				printf("\n");
			for(j = 1; j <= M; j++) {
				if(mat2[i][j] > 9)
					printf("%d ", mat2[i][j] / 10);
				else
					printf("%d ", mat2[i][j]);
			}
		}
		printf("\n");
		randullui = 1;// Faza de atac
		while( cnt1nave && cnt2nave) {
			int x, y;
			if (scanf("%d %d", &x, &y) != 2)
				break;
			if( x > N || y > M)
				break;
			if (randullui % 2 == 1) {//Jucatorul 1 (modificam in mat2)
				if (mat2[x][y] == 6 || mat2[x][y] == 0 || mat2[x][y] == 7) {//Rateaza
					switch (mat2[x][y]) {
					case 0:
					printf("Jucatorul 1 a ratat o lovitura la coordonatele (%d, %d).\n", x, y); mat2[x][y] = 7; break;
					case 6:
					printf("Jucatorul 1 a ratat o lovitura la coordonatele (%d, %d).\n", x, y); mat2[x][y] = 7; break;
					case 7:
					printf("Coordonatele (%d, %d) au fost deja atacate de jucatorul 1.\n", x, y); break;
					}
				}
				else {
					if (mat2[x][y] >= 1 && mat2[x][y] <= 5) {//Loveste
						printf("Jucatorul 1 a lovit o nava ");
						switch (mat2[x][y]) {
						case 5:
						printf("Shinano "); break;
						case 4:
						printf("Yamato "); break;
						case 3:
						printf("Belfast "); break;
						case 2:
						printf("Laffey "); break;
						case 1:
						printf("Albacore "); break;
						}
						printf("la coordonatele (%d, %d).\n", x, y);
						cnt2nave--;
						mat2[x][y] = 7;
						nr_lovituri_nimerite[0][tura]++;
					}
					else {
						if (mat2[x][y] > 9) {//Distruge///
							int cpy = mat2[x][y];
							if (cpy % 10 == 7) {//caz orizontal
								for (j = y; j <= y + (cpy / 10) - 1; j++) {
									if ( j == y)
										{mat2[x][j] = 7; cnt2nave--;}
									if(mat2[x][j] == 6 || mat2[x][j] == 7)
										mat2[x][j] = 7;
									else {
										mat2[x][j] = 6;
										cnt2nave--;
									}
								}
							}
							else {
								if (cpy % 10 == 8) {//caz vertical
									for (i = x; i >= x - (cpy / 10) + 1; i--) {
										if( i == x)
											{mat2[i][y] = 7; cnt2nave--;}
										if(mat2[i][y] == 6 || mat2[i][y] == 7)
											mat2[i][y] = 7;
										else {
											mat2[i][y] = 6;
											cnt2nave--;
										}
									}
								}
							}
							nr_lovituri_nimerite[0][tura]++;
							printf("Jucatorul 1 a distrus o nava ");
							switch (cpy / 10) {
							case 5:
							printf("Shinano "); break;
							case 4:
							printf("Yamato "); break;
							case 3:
							printf("Belfast "); break;
							case 2:
							printf("Laffey "); break;
							case 1:
							printf("Albacore "); break;
							}
							printf("plasata intre coordonatele (%d, %d) si ", x, y);
							switch (cpy % 10) {
							case 7:
							printf("(%d, %d).\n", x, y + (cpy / 10) - 1); break;
							case 8:
							printf("(%d, %d).\n", x - (cpy / 10) + 1, y); break;
							}
						}
					}
				}
				nr_lovituri_totale[0][tura]++;
			}
			else {//Jucatorul 2 (modifica in mat1)
				if (mat1[x][y] == 6 || mat1[x][y] == 0 || mat1[x][y] == 7) {//Rateaza
					switch (mat1[x][y]) {
					case 0:
					printf("Jucatorul 2 a ratat o lovitura la coordonatele (%d, %d).\n", x, y); mat1[x][y] = 7; break;
					case 6:
					printf("Jucatorul 2 a ratat o lovitura la coordonatele (%d, %d).\n", x, y); mat1[x][y] = 7; break;
					case 7:
					printf("Coordonatele (%d, %d) au fost deja atacate de jucatorul 2.\n", x, y); break;
					}
				}
				else {
					if (mat1[x][y] >= 1 && mat1[x][y] <= 5) {//Loveste
						printf("Jucatorul 2 a lovit o nava ");
						switch (mat1[x][y]) {
						case 5:
						printf("Shinano "); break;
						case 4:
						printf("Yamato "); break;
						case 3:
						printf("Belfast "); break;
						case 2:
						printf("Laffey "); break;
						case 1:
						printf("Albacore "); break;
						}
						printf("la coordonatele (%d, %d).\n", x, y);
						mat1[x][y] = 7;
						cnt1nave--;
						nr_lovituri_nimerite[1][tura]++;
					}
					else {
						if (mat1[x][y] > 9) {//Distruge
							int cpy = mat1[x][y];
							if (cpy % 10 == 7) {//caz orizontal
								for (j = y; j <= y + (cpy / 10) - 1; j++) {
									if ( j == y)
										{mat1[x][j] = 7; cnt1nave--;}
									if(mat1[x][j] == 6 || mat1[x][j] == 7)
										mat1[x][j] = 7;
									else {
										mat1[x][j] = 6;
										cnt1nave--;
									}
								}
							}
							else {
								if (cpy % 10 == 8) {//caz vertical
									for (i = x; i >= x - (cpy / 10) + 1; i--) {
										if( i == x)
											{mat1[i][y] = 7; cnt1nave--;}
										if(mat1[i][y] == 6 || mat1[i][y] == 7)
											mat1[i][y] = 7;
										else {
											mat1[i][y] = 6;
											cnt1nave--;
										}
									}
								}
							}
							nr_lovituri_nimerite[1][tura]++;
							printf("Jucatorul 2 a distrus o nava ");
							switch (cpy / 10) {
							case 5:
							printf("Shinano "); break;
							case 4:
							printf("Yamato "); break;
							case 3:
							printf("Belfast "); break;
							case 2:
							printf("Laffey "); break;
							case 1:
							printf("Albacore "); break;
							}
							printf("plasata intre coordonatele (%d, %d) si ", x, y);
							switch (cpy % 10) {
							case 7:
							printf("(%d, %d).\n", x, y + (cpy / 10) - 1); break;
							case 8:
							printf("(%d, %d).\n", x - (cpy / 10) + 1, y); break;
							}
						}
					}
				}
				nr_lovituri_totale[1][tura]++;
			}
			
			if (cnt1nave == 0) {
				printf("Jucatorul 2 a castigat.\n");
				break;
			}
			if (cnt2nave == 0) {
				printf("Jucatorul 1 a castigat.\n");
				break;
			}
			randullui++;
		}
		for (i = 0; i < N + 1; i++)//Dealocare mat1
			free(mat1[i]);
		free(mat1);
		for (i = 0; i < N + 1; i++)//Dealocare mat2
			free(mat2[i]);
		free(mat2);
	}
	// TASK 2
	char *cheie = (char *)malloc(21 * sizeof(char));
	int *temp_nrtotalnave = malloc((J + 1) * sizeof(int));
	int *temp_nr_lovituri_nimerite = malloc((J + 1) * sizeof(int));
	int *temp_nr_lovituri_totale = malloc((J + 1) * sizeof(int));
	scanf("%s", cheie);
	if (cheie[0] == '-' && cheie[0] != 'Q') {//Cazul necriptat
		while (cheie[0] != 'Q') {
			scanf("%s", cheie);
			if (cheie[0] == 'Q')
				break;
			int cifra_sute = 0;//Obtin A si X din sir, indice respectiv acuratete
			int cifra_zeci = 0;
			int cifra_unitati = 0;
			int zecimala_1 = 0;
			int zecimala_2 = 0;
			cifra_sute = cheie[2] - '0';
			cifra_zeci = cheie[3] - '0';
			cifra_unitati = cheie[4] - '0';
			int A = cifra_sute * 100 + cifra_zeci * 10 + cifra_unitati;
			cifra_sute = cheie[5] - '0';
			cifra_zeci = cheie[6] - '0';
			cifra_unitati = cheie[7] - '0';
			int B = cifra_sute * 100 + cifra_zeci * 10 + cifra_unitati;
			zecimala_1 = cheie[9] - '0';
			zecimala_2 = cheie[10] - '0';
			double zecimale = zecimala_1 * 10 + zecimala_2;
			double X = B + (zecimale / 100);
			if(cheie[0] != 'Q') {//Cat timp n-am ajuns la final (Q)
				if(cheie[0] == 'O' && cheie[1] == 'U' && cheie[12] == 'I') {//Cazul 1 Cerinta 2 (dupa desen)
					int cpy = nr_lovituri_nimerite[0][A];
					double acc_meci = (double)cpy / (double)nr_lovituri_totale[0][A] * 100;
					acc_meci = (int)(acc_meci * 100) / 100.0;
					if (acc_meci > 100)
						printf("%.2lf.", acc_meci);
					if (acc_meci < 100 && acc_meci >= 10)
						printf("0%.2lf.", acc_meci);
					if (acc_meci < 10)
						printf("00%.2lf.", acc_meci);
					while (acc_meci < X) {
						cpy++;
						acc_meci = (double)cpy / (double)nr_lovituri_totale[0][A] * 100;
					}
					int lovituri = cpy - nr_lovituri_nimerite[0][A];
					printf("%d\n", lovituri);
				}
				if(cheie[0] == 'O' && cheie[1] == 'U' && cheie[12] == 'A') {//Cazul 2 Cerinta 4
					int cpy = nr_lovituri_nimerite[0][A];
					double acc_meci = (double)cpy / (double)nr_lovituri_totale[0][A]*100;
					acc_meci = (int)(acc_meci * 100) / 100.0;
					if (acc_meci > 100)
						printf("%.2lf.", acc_meci);
					if (acc_meci < 100 && acc_meci >= 10)
						printf("0%.2lf.", acc_meci);
					if (acc_meci < 10)
						printf("00%.2lf.", acc_meci);
					while (acc_meci > X) {
						cpy--;
						acc_meci = (double)cpy / (double)nr_lovituri_totale[0][A] * 100;
					}
					int lovituri = nr_lovituri_nimerite[0][A] - cpy;
					if(lovituri == 0)
						printf("%d\n", lovituri);
					else
						printf("%d\n", lovituri - 1);
				}
				if(cheie[0] == 'O' && cheie[1] == 'T' && cheie[12] == 'I') {//Cazul 3 Cerinta 1
					for (int k = 1; k <= J; k++) {
						temp_nrtotalnave[k] = nrtotalnave[k];
						temp_nr_lovituri_nimerite[k] = nr_lovituri_nimerite[0][k];
						temp_nr_lovituri_totale[k] = nr_lovituri_totale[0][k];
					}
					for (int n = 1; n < J; n++) {//Ordonez ca sa ma avantajeze pt numarul minim
						double castig_potential_1 = temp_nrtotalnave[n] * (1.0 - (double)temp_nr_lovituri_nimerite[n] / (double)temp_nr_lovituri_totale[n]);
						for (int m = n + 1; m <= J; m++) {
							double castig_potential_2 = temp_nrtotalnave[m] * (1.0 - (double)temp_nr_lovituri_nimerite[m] / (double)temp_nr_lovituri_totale[m]);
							if(castig_potential_1 < castig_potential_2) {
								swap(&temp_nrtotalnave[n], &temp_nrtotalnave[m]);
								swap(&temp_nr_lovituri_nimerite[n], &temp_nr_lovituri_nimerite[m]);
								swap(&temp_nr_lovituri_totale[n], &temp_nr_lovituri_totale[m]);
								castig_potential_1 = temp_nrtotalnave[n] * (1.0 - (double)temp_nr_lovituri_nimerite[n] / (double)temp_nr_lovituri_totale[n]);
							}
						}
					}
						double numitor_acc_total = 0;
						for (int n = 1; n <= J; n++) {
							numitor_acc_total = numitor_acc_total + temp_nrtotalnave[n];
						}
						double numarator_acc_total = 0;
						for (int n = 1; n <= J; n++) {
							double acc_meci = (double)temp_nr_lovituri_nimerite[n] / (double)temp_nr_lovituri_totale[n] * 100.0;
							acc_meci = (int)(acc_meci * 100) / 100.0;
							numarator_acc_total = numarator_acc_total + (acc_meci * temp_nrtotalnave[n]);
						}
						double acc_total = numarator_acc_total / numitor_acc_total;
						int cnt = 1;
						double cpy = acc_total;
						while (cpy < X && cnt <= J) {
							double acc_meci = (double)temp_nr_lovituri_nimerite[cnt] / (double)temp_nr_lovituri_totale[cnt] * 100;
							acc_meci = (int)(acc_meci * 100) / 100.0;
							numarator_acc_total = numarator_acc_total - (acc_meci * temp_nrtotalnave[cnt]);
							numarator_acc_total = numarator_acc_total + 100.0 * temp_nrtotalnave[cnt];
							cpy = numarator_acc_total / numitor_acc_total;
							cnt++;
						}
						long long acc_total_scalat = (long long)(acc_total * 1000 + 0.0001);
						int zecimala_3 = acc_total_scalat % 10;
						int acc_total_scalat_farazec3 = acc_total_scalat / 10;
						if (zecimala_3 >= 5)
							acc_total_scalat_farazec3 = acc_total_scalat_farazec3 + 1;
						acc_total = acc_total_scalat_farazec3 / 100.0;
						if (acc_total > 100)
							printf("%.2lf.", acc_total);
						if (acc_total < 100 && acc_total >= 10)
							printf("0%.2lf.", acc_total);
						if (acc_total < 10)
							printf("00%.2lf.", acc_total);
						printf("%d\n", cnt - 1);

					}
				if (cheie[0] == 'O' && cheie[1] == 'T' && cheie[12] == 'A') {//Cazul 4 Cerinta 3
					for (int k = 1; k <= J; k++) {
						temp_nrtotalnave[k] = nrtotalnave[k];
						temp_nr_lovituri_nimerite[k] = nr_lovituri_nimerite[0][k];
						temp_nr_lovituri_totale[k] = nr_lovituri_totale[0][k];
					}
					for (int n = 1; n < J; n++) {//Sortare
						double castig_potential_1 = temp_nrtotalnave[n] * ((double)temp_nr_lovituri_nimerite[n] / (double)temp_nr_lovituri_totale[n]);
						for (int m = n + 1; m <= J; m++) {
							double castig_potential_2 = temp_nrtotalnave[m] * ((double)temp_nr_lovituri_nimerite[m] / (double)temp_nr_lovituri_totale[m]);
							if (castig_potential_1 > castig_potential_2) {
								swap(&temp_nrtotalnave[n], &temp_nrtotalnave[m]);
								swap(&temp_nr_lovituri_nimerite[n], &temp_nr_lovituri_nimerite[m]);
								swap(&temp_nr_lovituri_totale[n], &temp_nr_lovituri_totale[m]);
								castig_potential_1 = temp_nrtotalnave[n] * ((double)temp_nr_lovituri_nimerite[n] / (double)temp_nr_lovituri_totale[n]);
							}
						}
					}
						double numitor_acc_total = 0;//Calcul numitor
						for (int n = 1; n <= J; n++) {
							numitor_acc_total = numitor_acc_total + temp_nrtotalnave[n];
						}
						double numarator_acc_total = 0;//Calcul numarator
						for (int n = 1; n <= J; n++) {
							double acc_meci = (double)temp_nr_lovituri_nimerite[n] / (double)temp_nr_lovituri_totale[n] * 100.0;
							acc_meci = (int)(acc_meci * 100) / 100.0;
							numarator_acc_total = numarator_acc_total + (acc_meci * temp_nrtotalnave[n]);
						}
						double acc_total = numarator_acc_total / numitor_acc_total;
						int cnt = 1;
						double cpy = acc_total;
						while (cpy >= X && cnt <= J) {
							double acc_meci = (double)temp_nr_lovituri_nimerite[cnt] / (double)temp_nr_lovituri_totale[cnt] * 100;
							acc_meci = (int)(acc_meci * 100) / 100.0;
							numarator_acc_total = numarator_acc_total - (acc_meci * temp_nrtotalnave[cnt]);
							cpy = numarator_acc_total / numitor_acc_total;
							if (cpy >= X)
								cnt++;
							else
								break;
						}
						long long acc_total_scalat = (long long)(acc_total * 1000 + 0.0001);
						int zecimala_3 = acc_total_scalat % 10;
						int acc_total_scalat_farazec3 = acc_total_scalat / 10;
						if (zecimala_3 >= 5)
							acc_total_scalat_farazec3 = acc_total_scalat_farazec3 + 1;
						acc_total = acc_total_scalat_farazec3 / 100.0;
						if (acc_total > 100)
							printf("%.2lf.", acc_total);
						if (acc_total < 100 && acc_total >= 10)
							printf("0%.2lf.", acc_total);
						if (acc_total < 10)
							printf("00%.2lf.", acc_total);
						printf("%d\n", cnt - 1);

					}
				if (cheie[0] == 'T' && cheie[1] == 'U' && cheie[12] == 'I') {//Cazul 5 Cerinta 2 (dupa desen)
					int cpy = nr_lovituri_nimerite[1][A];
					double acc_meci = (double)cpy / (double)nr_lovituri_totale[1][A] * 100;
					acc_meci = (int)(acc_meci * 100) / 100.0;
					if (acc_meci > 100)
						printf("%.2lf.", acc_meci);
					if (acc_meci < 100 && acc_meci >= 10)
						printf("0%.2lf.", acc_meci);
					if (acc_meci < 10)
						printf("00%.2lf.", acc_meci);
					while (acc_meci < X) {
						cpy++;
						acc_meci = (double)cpy / (double)nr_lovituri_totale[1][A] * 100;
					}
					int lovituri = cpy - nr_lovituri_nimerite[1][A];
					printf("%d\n", lovituri);
				}
				if (cheie[0] == 'T' && cheie[1] == 'U' && cheie[12] == 'A') {//Cazul 6 Cerinta 4
					int cpy = nr_lovituri_nimerite[1][A];
					double acc_meci = (double)cpy / (double)nr_lovituri_totale[1][A]*100;
					acc_meci = (int)(acc_meci * 100) / 100.0;
					if (acc_meci > 100)
						printf("%.2lf.", acc_meci);
					if (acc_meci < 100 && acc_meci >= 10)
						printf("0%.2lf.", acc_meci);
					if (acc_meci < 10)
						printf("00%.2lf.", acc_meci);
					while (acc_meci > X) {
						cpy--;
						acc_meci = (double)cpy / (double)nr_lovituri_totale[1][A] * 100;
					}
					int lovituri = nr_lovituri_nimerite[1][A] - cpy;
					if (lovituri == 0)
						printf("%d\n", lovituri);
					else
						printf("%d\n", lovituri - 1);
				}
				if (cheie[0] == 'T' && cheie[1] == 'T' && cheie[12] == 'I') {//Cazul 7 Cerinta 1
					for (int k = 1; k <= J; k++) {
						temp_nrtotalnave[k] = nrtotalnave[k];
						temp_nr_lovituri_nimerite[k] = nr_lovituri_nimerite[1][k];
						temp_nr_lovituri_totale[k] = nr_lovituri_totale[1][k];
					}
					for (int n = 1; n < J; n++) {//Ordonez ca sa ma avantajeze pt numarul minim
						double castig_potential_1 = temp_nrtotalnave[n] * (1.0 - (double)temp_nr_lovituri_nimerite[n] / (double)temp_nr_lovituri_totale[n]);
						for (int m = n + 1; m <= J; m++) {
							double castig_potential_2 = temp_nrtotalnave[m] * (1.0 - (double)temp_nr_lovituri_nimerite[m] / (double)temp_nr_lovituri_totale[m]);
							if (castig_potential_1 < castig_potential_2) {
								swap(&temp_nrtotalnave[n], &temp_nrtotalnave[m]);
								swap(&temp_nr_lovituri_nimerite[n], &temp_nr_lovituri_nimerite[m]);
								swap(&temp_nr_lovituri_totale[n], &temp_nr_lovituri_totale[m]);
								castig_potential_1 = temp_nrtotalnave[n] * (1.0 - (double)temp_nr_lovituri_nimerite[n] / (double)temp_nr_lovituri_totale[n]);

							}
						}
					}
						double numitor_acc_total = 0;
						for (int n = 1; n <= J; n++) {
							numitor_acc_total = numitor_acc_total + temp_nrtotalnave[n];
						}
						double numarator_acc_total = 0;
						for (int n = 1; n <= J; n++) {
							double acc_meci = (double)temp_nr_lovituri_nimerite[n] / (double)temp_nr_lovituri_totale[n] * 100.0;
							acc_meci = (int)(acc_meci * 100) / 100.0;
							numarator_acc_total = numarator_acc_total + (acc_meci * temp_nrtotalnave[n]);
						}
						double acc_total = numarator_acc_total / numitor_acc_total;
						int cnt = 1;
						double cpy = acc_total;
						while (cpy < X && cnt <= J) {
							double acc_meci = (double)temp_nr_lovituri_nimerite[cnt] / (double)temp_nr_lovituri_totale[cnt]*100;
							acc_meci = (int)(acc_meci * 100) / 100.0;
							numarator_acc_total = numarator_acc_total - (acc_meci * temp_nrtotalnave[cnt]);
							numarator_acc_total = numarator_acc_total + 100.0 * temp_nrtotalnave[cnt];
							cpy = numarator_acc_total / numitor_acc_total;
							cnt++;
						}
						long long acc_total_scalat = (long long)(acc_total * 1000 + 0.0001);
						int zecimala_3 = acc_total_scalat % 10;
						int acc_total_scalat_farazec3 = acc_total_scalat / 10;
						if (zecimala_3 >= 5)
							acc_total_scalat_farazec3 = acc_total_scalat_farazec3 + 1;
						acc_total = acc_total_scalat_farazec3 / 100.0;
						if (acc_total > 100)
							printf("%.2lf.", acc_total);
						if (acc_total < 100 && acc_total >= 10)
							printf("0%.2lf.", acc_total);
						if (acc_total < 10)
							printf("00%.2lf.", acc_total);
						printf("%d\n", cnt - 1);

					}
				if (cheie[0] == 'T' && cheie[1] == 'T' && cheie[12] == 'A') {//Cazul 8 Cerinta 3
					for (int k = 1; k <= J; k++) {
						temp_nrtotalnave[k] = nrtotalnave[k];
						temp_nr_lovituri_nimerite[k] = nr_lovituri_nimerite[1][k];
						temp_nr_lovituri_totale[k] = nr_lovituri_totale[1][k];
					}
				for (int n = 1; n < J; n++) {//Sortare
					double castig_potential_1 = temp_nrtotalnave[n] * ((double)temp_nr_lovituri_nimerite[n] / (double)temp_nr_lovituri_totale[n]);
					for (int m = n + 1; m <= J; m++) {
						double castig_potential_2 = temp_nrtotalnave[m] * ((double)temp_nr_lovituri_nimerite[m] / (double)temp_nr_lovituri_totale[m]);
						if (castig_potential_1 > castig_potential_2) {
							swap(&temp_nrtotalnave[n],
								&temp_nrtotalnave[m]);
							swap(&temp_nr_lovituri_nimerite[n],
								&temp_nr_lovituri_nimerite[m]);
							swap(&temp_nr_lovituri_totale[n],
								&temp_nr_lovituri_totale[m]);
							castig_potential_1 = temp_nrtotalnave[n] *
								((double)temp_nr_lovituri_nimerite[n] /
								(double)temp_nr_lovituri_totale[n]);
							}
						}
					}
			double numitor_acc_total = 0;//Calcul numitor
			for (int n = 1; n <= J; n++) {
				numitor_acc_total = numitor_acc_total + temp_nrtotalnave[n];
			}
			double numarator_acc_total = 0;//Calcul numarator
			for (int n = 1; n <= J; n++) {
				double acc_meci = (double)temp_nr_lovituri_nimerite[n]
				/ (double)temp_nr_lovituri_totale[n] * 100.0;
				acc_meci = (int)(acc_meci * 100) / 100.0;
				numarator_acc_total = numarator_acc_total +
				(acc_meci * temp_nrtotalnave[n]);
				}
			double acc_total = numarator_acc_total / numitor_acc_total;
			int cnt = 1;
			double cpy = acc_total;
		while (cpy >= X && cnt <= J) {
			double acc_meci = (double)temp_nr_lovituri_nimerite[cnt]
			/ (double)temp_nr_lovituri_totale[cnt] * 100;
			acc_meci = (int)(acc_meci * 100) / 100.0;
			numarator_acc_total = numarator_acc_total - (acc_meci
			* temp_nrtotalnave[cnt]);
			cpy = numarator_acc_total / numitor_acc_total;
			if (cpy >= X)						
				cnt++;
			else
				break;
						}
					long long acc_total_scalat = (long long)(acc_total *
							1000 + 0.0001);
					int zecimala_3 = acc_total_scalat % 10;
						int acc_total_scalat_farazec3 = acc_total_scalat / 10;
					if (zecimala_3 >= 5)
						acc_total_scalat_farazec3 = acc_total_scalat_farazec3
						+ 1;
					acc_total = acc_total_scalat_farazec3 / 100.0;
					if (acc_total > 100)
						printf("%.2lf.", acc_total);
					if (acc_total < 100 && acc_total >= 10)
						printf("0%.2lf.", acc_total);
					if (acc_total < 10)
						printf("00%.2lf.", acc_total);
					printf("%d\n", cnt - 1);
}			
}                                
			}
		}
if (cheie[0] != '-' && cheie[0] != 'Q') {//Cazul criptat	
		}
		free(cheie);//Dealocare cheie
		free(temp_nrtotalnave);
		free(temp_nr_lovituri_nimerite);
		free(temp_nr_lovituri_totale);
	for (int k = 0; k < 3; k++)//Dealocari vectori
		free(nr_lovituri_nimerite[k]);
	free(nr_lovituri_nimerite);
	for (int k = 0; k < 3; k++)
		free(nr_lovituri_totale[k]);
	free(nr_lovituri_totale);
	free(nrtotalnave);//Dealocare Nave
	}
