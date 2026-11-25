#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void bubble(int copia[], int n){
	int aux;
	if(n == 1) return;
	for(int i = 0; i < n; ++i){
		for(int j = i+1; j < n; ++j){
			// Compara pares e empurra os maiores valores para o fim
			if(copia[i] > copia[j]){
				aux = copia[i];
				copia[i] = copia[j];
				copia[j] = aux;
			}
		}
	}
}

void selection(int copia[], int n){
	int min_idx, aux;
	for(int i = 0; i < n - 1; ++i){
		min_idx = i;
		// Busca o índice do menor elemento na parte não ordenada
		for(int j = i + 1; j < n; ++j){
			if(copia[j] < copia[min_idx]){
				min_idx = j;
			}
		}
		// Faz uma única troca direta por iteração
		if(min_idx != i){
			aux = copia[i];
			copia[i] = copia[min_idx];
			copia[min_idx] = aux;
		}
	}
}

void insertion(int copia[], int n){
	int chave, j;
	for(int i = 1; i < n; ++i){
		chave = copia[i];
		j = i - 1;
		// Desloca elementos maiores para a direita para abrir espaço
		while(j >= 0 && copia[j] > chave){
			copia[j + 1] = copia[j];
			j = j - 1;
		}
		// Insere a chave na sua posição ordenada
		copia[j + 1] = chave;
	}
}

void merge(int copia[], int esq, int dir){
	if(esq < dir){
		int meio = esq + (dir - esq) / 2;
		// Divide o vetor recursivamente ao meio
		merge(copia, esq, meio);
		merge(copia, meio + 1, dir);

		int n1 = meio - esq + 1;
		int n2 = dir - meio;
		int *L = (int *) malloc(n1 * sizeof(int));
		int *R = (int *) malloc(n2 * sizeof(int));
		
		for(int i = 0; i < n1; ++i) L[i] = copia[esq + i];
		for(int j = 0; j < n2; ++j) R[j] = copia[meio + 1 + j];
		
		// Intercala (mescla) as duas metades já ordenadas
		int i = 0, j = 0, k = esq;
		while(i < n1 && j < n2){
			if(L[i] <= R[j]) copia[k++] = L[i++];
			else copia[k++] = R[j++];
		}
		while(i < n1) copia[k++] = L[i++];
		while(j < n2) copia[k++] = R[j++];
		
		free(L);
		free(R);
	}
}

void quick(int copia[], int baixo, int alto){
	if(baixo < alto){
		// Define o último elemento como pivô para particionar o vetor
		int pivo = copia[alto];
		int i = (baixo - 1);
		int aux;
		
		// Move elementos menores que o pivô para a esquerda
		for(int j = baixo; j <= alto - 1; ++j){
			if(copia[j] < pivo){
				++i;
				aux = copia[i];
				copia[i] = copia[j];
				copia[j] = aux;
			}
		}
		// Posiciona o pivô entre os menores e os maiores
		aux = copia[i + 1];
		copia[i + 1] = copia[alto];
		copia[alto] = aux;
		int pi = i + 1;

		// Ordena recursivamente as sub-partições
		quick(copia, baixo, pi - 1);
		quick(copia, pi + 1, alto);
	}
}

void heap(int copia[], int n){
	int aux;
	
	// Constrói o max-heap (maior elemento na raiz)
	for(int i = n / 2 - 1; i >= 0; --i){
		int atual = i;
		while(1){
			int maior = atual;
			int esq = 2 * atual + 1;
			int dir = 2 * atual + 2;
			
			if(esq < n && copia[esq] > copia[maior]) maior = esq;
			if(dir < n && copia[dir] > copia[maior]) maior = dir;
			
			if(maior != atual){
				aux = copia[atual];
				copia[atual] = copia[maior];
				copia[maior] = aux;
				atual = maior;
			} else {
				break;
			}
		}
	}
	
	// Extrai o maior elemento (raiz) para o fim e reestrutura o heap
	for(int i = n - 1; i > 0; --i){
		aux = copia[0];
		copia[0] = copia[i];
		copia[i] = aux;
		
		int atual = 0;
		while(1){
			int maior = atual;
			int esq = 2 * atual + 1;
			int dir = 2 * atual + 2;
			
			if(esq < i && copia[esq] > copia[maior]) maior = esq;
			if(dir < i && copia[dir] > copia[maior]) maior = dir;
			
			if(maior != atual){
				aux = copia[atual];
				copia[atual] = copia[maior];
				copia[maior] = aux;
				atual = maior;
			} else {
				break;
			}
		}
	}
}

void counting(int copia[], int n){
	if(n <= 1) return;
	
	// Descobre o maior valor para dimensionar o vetor de contagem
	int max = copia[0];
	for(int i = 1; i < n; ++i){
		if(copia[i] > max) max = copia[i];
	}
	
	int *contagem = (int *) calloc(max + 1, sizeof(int));
	int *saida = (int *) malloc(n * sizeof(int));
	
	// Conta a frequência de cada valor e acumula as posições
	for(int i = 0; i < n; ++i){
		contagem[copia[i]]++;
	}
	for(int i = 1; i <= max; ++i){
		contagem[i] += contagem[i - 1];
	}
	// Monta o vetor de saída ordenado sem realizar comparações
	for(int i = n - 1; i >= 0; --i){
		saida[contagem[copia[i]] - 1] = copia[i];
		contagem[copia[i]]--;
	}
	
	memcpy(copia, saida, n * sizeof(int));
	
	free(contagem);
	free(saida);
}

void radix(int copia[], int n){
	if(n <= 1) return;
	
	int max = copia[0];
	for(int i = 1; i < n; ++i){
		if(copia[i] > max) max = copia[i];
	}
	
	int *saida = (int *) malloc(n * sizeof(int));
	
	// Ordena dígito por dígito (unidade, dezena, centena...) usando Counting Sort estável
	for(int exp = 1; max / exp > 0; exp *= 10){
		int contagem[10] = {0};
		
		for(int i = 0; i < n; ++i){
			contagem[(copia[i] / exp) % 10]++;
		}
		for(int i = 1; i < 10; ++i){
			contagem[i] += contagem[i - 1];
		}
		for(int i = n - 1; i >= 0; --i){
			saida[contagem[(copia[i] / exp) % 10] - 1] = copia[i];
			contagem[(copia[i] / exp) % 10]--;
		}
		
		memcpy(copia, saida, n * sizeof(int));
	}
	
	free(saida);
}

void bucket(int copia[], int n){
	if(n <= 1) return;
	
	int max = copia[0];
	for(int i = 1; i < n; ++i){
		if(copia[i] > max) max = copia[i];
	}
	
	int num_baldes = n;
	int **baldes = (int **) malloc(num_baldes * sizeof(int *));
	int *tamanhos = (int *) calloc(num_baldes, sizeof(int));
	int *capacidades = (int *) malloc(num_baldes * sizeof(int));
	
	for(int i = 0; i < num_baldes; ++i){
		capacidades[i] = 4;
		baldes[i] = (int *) malloc(capacidades[i] * sizeof(int));
	}
	
	// Distribui cada elemento proporcionalmente no seu respectivo balde
	for(int i = 0; i < n; ++i){
		int idx = (int)(((long long)copia[i] * num_baldes) / (max + 1));
		if(tamanhos[idx] == capacidades[idx]){
			capacidades[idx] *= 2;
			baldes[idx] = (int *) realloc(baldes[idx], capacidades[idx] * sizeof(int));
		}
		baldes[idx][tamanhos[idx]++] = copia[i];
	}
	
	// Ordena cada balde com Insertion Sort e concatena de volta no vetor
	int pos = 0;
	for(int i = 0; i < num_baldes; ++i){
		if(tamanhos[i] > 0){
			insertion(baldes[i], tamanhos[i]);
			for(int j = 0; j < tamanhos[i]; ++j){
				copia[pos++] = baldes[i][j];
			}
		}
		free(baldes[i]);
	}
	
	free(baldes);
	free(tamanhos);
	free(capacidades);
}

int timeTaken(int vetor[], int copia[], int n, int sort){
	// Restaura o vetor original desordenado antes de cada teste
	memcpy(copia, vetor, n * sizeof(int));
	
	struct timespec inicio, fim;
    
    clock_gettime(CLOCK_MONOTONIC, &inicio); 
    
    switch(sort){
    	case 1:
    		bubble(copia, n);
    		printf("\nbubble()");
    		break;
    	case 2:
    		selection(copia, n);
    		printf("\nselection()");
    		break;
    	case 3:
    		insertion(copia, n);
    		printf("\ninsertion()");
    		break;
    	case 4:
    		merge(copia, 0, n - 1);
    		printf("\nmerge()");
    		break;
    	case 5:
    		quick(copia, 0, n - 1);
    		printf("\nquick()");
    		break;
    	case 6:
    		heap(copia, n);
    		printf("\nheap()");
    		break;
    	case 7:
    		counting(copia, n);
    		printf("\ncounting()");
    		break;
    	case 8:
    		radix(copia, n);
    		printf("\nradix()");
    		break;
    	case 9:
    		bucket(copia, n);
    		printf("\nbucket()");
    		break;
	}
    
    clock_gettime(CLOCK_MONOTONIC, &fim); 
    
    // Calcula o tempo total em segundos com precisão de nanossegundos
    double time_taken = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    
    printf(" levou %fs para ordenar\n", time_taken);
    
//    for(int i = 0; i < n; ++i){
//		printf("%i ", copia[i]);
//	}
	
    return 0;
}

int main(){
	srand(time(NULL));
	int n;
	int r;
	printf("Tamanho: ");
	scanf("%i", &n);
	printf("Alcance: ");
	scanf("%i", &r);
	
	int *vetor = (int *) calloc(n, sizeof(int));
	if(vetor == NULL){
		printf("Erro ao alocar memoria");
		return 1;
	}
	
	int *copia = (int *) malloc(n * sizeof(int));
	if(copia == NULL){
		printf("Erro ao alocar memoria");
		return 1;
	}
	
	// Preenche o vetor base com números aleatórios dentro do alcance
	// Forma adaptada do rand() para passar a limitação de 32.767
	for(int i = 0; i < n; ++i){
    vetor[i] = (int)(((double)rand() / (RAND_MAX + 1.0)) * r);
}
	
//	for(int i = 0; i < n; ++i){
//		printf("%i ", vetor[i]);
//	}
	
	// Executa e cronometra os 9 algoritmos sequencialmente
	for(int i = 1; i <= 9; ++i){
		timeTaken(vetor, copia, n, i);
	}
	
	free(vetor);
	free(copia);
}
