#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio2.h>
#include<time.h>
#include"TAD_HUFFMAN.h"

int main()
{
	//teste de inserção
	Box *tree = NULL,* aux;
	criaCaixas(&tree,4); 
	criaCaixas(&tree,5); 
	criaCaixas(&tree,3); 
	criaCaixas(&tree,15); 
	criaCaixas(&tree,10); 
	// mostrando resultado
	aux = tree;
	while(aux!=NULL)
	{
		printf("\nSIMBOLO: %c - QUANTIDADE: %d",aux->arv->simb,aux->arv->qtde);
		aux = aux->prox;
	}
}
