#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio2.h>
#include<time.h>
#include"TAD_HUFFMAN.h"

void insere(auxStr **a,auxStr b)
{
	auxStr *novo = (auxStr*) malloc(sizeof(auxStr));
	strcpy(novo->codHuff,b.codHuff);
	strcpy(novo->palavra,b.palavra);
	novo->qtde = b.qtde;
	novo->simbo = b.simbo;
	if(*a==NULL)
	{
		novo->prox = NULL;
		*a = novo;
	}
	else
	{
		novo->prox = *a;
		*a = novo;
	}
}

void transforma(auxStr **a,FILE *arq)
{
	auxStr aux;
	fread(&aux,sizeof(auxStr),1,arq);
	while(!feof(arq))
	{
		insere(*&a,aux);
		fread(&aux,sizeof(auxStr),1,arq);
	
	}
}

int main()
{
	char ola[4];
	Tree *arvore;
	FILE *ptrBin = fopen("tabela_codif.txt","rb"), *ptrCod = fopen("frase_codifi.txt","r");
	auxStr *tabela=NULL,*exibe;
	transforma(&tabela,ptrBin);//transforma o arq binario em tabela;
	recuperaTree(&arvore,tabela);
	exibeFrase(ptrCod,arvore,tabela);
}
