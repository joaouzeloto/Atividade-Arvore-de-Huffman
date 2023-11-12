#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio2.h>
#include<time.h>
#include"TAD_HUFFMAN.h"

void insereNaList(char pala[30],auxStr **lis)
{
	auxStr *novo = (auxStr*) malloc(sizeof(auxStr));
	strcpy(novo->palavra,pala);
	novo->prox = *lis;
	*lis = novo;
}

char buscaPala(char pala[30],auxStr *lis)
{
	while(lis!=NULL)
	{
		if(strcmp(lis->palavra,pala)==0)
			return 0;
		lis = lis->prox;
	}	
	return 1;
}

void separaPalavras(char frase[],auxStr **list)
{
	int i=0,j;
	char palavra[30];
	while(frase[i]!='\0')
	{
		if(frase[i]>64&&frase[i]<91||frase[i]>96&&frase[i]<123||frase[i]=='-')
		{
			
			for(j=0;frase[i]>64&&frase[i]<91||frase[i]>96&&frase[i]<123||frase[i]=='-';j++)
			{
				if(frase[i]>64&&frase[i]<91)
					palavra[j] = frase[i]+32;
				else
					palavra[j] = frase[i];
				i++;
			}
			palavra[j] = '\0';
			i--;
			if(buscaPala(palavra,*list))
				insereNaList(palavra,*&list);
		}
			i++;		
	}
	for(i=0;frase[i]!=' ';i++)
		i++;
	if(frase[i]!='\0')
	{
		palavra[0] = ' ';
		palavra[1] = '\0';
		insereNaList(palavra,*&list);
	}
	
}

void contaPalavras(auxStr **aux, char frase[])
{
	int i=0,j;
	(*aux)->qtde = 0;
	char palavra[30];
	if(strcmp((*aux)->palavra," ")!=0)
		while(frase[i]!='\0')
		{
			if(frase[i]>64&&frase[i]<91||frase[i]>96&&frase[i]<123||frase[i]=='-')
			{
				
				for(j=0;frase[i]>64&&frase[i]<91||frase[i]>96&&frase[i]<123||frase[i]=='-';j++)
				{
					if(frase[i]>64&&frase[i]<91)
						palavra[j] = frase[i]+32;
					else
						palavra[j] = frase[i];
					i++;
				}
				palavra[j] = '\0';
				i--;
				if(strcmp((*aux)->palavra,palavra)==0)
					(*aux)->qtde++;	
			}
				i++;		
		}
	else
		for(i=0;frase[i]!='\0';i++)
			if(frase[i]==' ')
				(*aux)->qtde++;		
}

void setQtdeAll(char frase[],auxStr **palavras)
{
	auxStr *auxS = *palavras;
	while(auxS!=NULL)
	{
		contaPalavras(&auxS,frase);
		auxS = auxS->prox;
	}
}

int main()
{
	//teste de inserção
	auxStr *list=NULL,*auxL;
	Box *tree = NULL,* aux;
	char frase[350];
	strcpy(frase,"Amo como ama o amor. Nao conheco nenhuma outra razao para amar senao amar.Que queres que te diga, alem de que te amo, se o que quero dizer-te e que te amo?");
	/*
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
	}*/
	//testando separador de palavras
	separaPalavras(frase, &list);
	setQtdeAll(frase,&list);
	//laço para mostrar as palavras encontradas
	auxL = list;
	while(auxL!=NULL)
	{
		printf("\nPALAVRA: %s	-	QTDE: %d",auxL->palavra,auxL->qtde);
		auxL = auxL->prox;
	}
}
