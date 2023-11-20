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

void ajustar(auxStr *list,auxStr **alterado)
{
	auxStr *aux = list;
	while(aux!=NULL)
	{
		insereNaList(aux->palavra,*&alterado);
		aux = aux->prox;
	}
}

void clivar(char frase[],auxStr **list)
{
	auxStr *aux = NULL;
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
			insereNaList(palavra,*&list);
		}
		else
		{
			if(frase[i]==' ')
			{
				for(j=0;frase[i]==' ';i++,j++)
					palavra[j] = frase[i];
				palavra[j] = '\0';
				i--;
				insereNaList(palavra,*&list);
			}
		}
			i++;		
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
	//DECLARAÇÃO DE VARIÁVEIS
	auxStr *list=NULL,*auxL,*a,*alterado=NULL;
	Box *tree = NULL,* aux;
	int TL = 0;
	char frase[350],auxC[20];
	strcpy(frase,"Amo como ama o amor. Nao conheco nenhuma outra razao para amar senao amar.Que queres que te diga, alem de que te amo, se o que quero dizer-te e que te amo?");
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	separaPalavras(frase, &list);//SEPARA CADA PALAVRA DA FRASE
	
	setQtdeAll(frase,&list);//RODA PARA ACHAR A QTDE QUE AS PALAVRAS OCORREM
	
	//LAÇO PARA CRIAR AS LISTAS COM ÁRVORES
	auxL = list;
	while(auxL!=NULL)
	{
		criaCaixas(&tree,&auxL);
		auxL = auxL->prox;
	}
	
	//CRIA A ÁRVORE DE HUFFMAN
	criaHuffman(&tree);

	//ADICIONA O CAMINHO DE HUFFMAN
	adicionaHuffmanCod(tree->arv,auxC,&TL,&list);
	
	//SALVANDO A ESTRUTURA NO ARQUIVO BIN
	salvaTab(list);
	
	//CODIFICANDO FRASE PARA OUTRO PROGRAMA 
	auxL=NULL;
	clivar("amo, nao conheco outra razao de e para amar, amo, alem de amar",&auxL);
	ajustar(auxL,&alterado);
	codificaFrase(alterado,list);
	a = list;
	while(a!=NULL)
	{
		printf("\nPALAVRA: %s - CODIGO: %s - SIMBOLO: %c",a->palavra,a->codHuff,a->simbo);
		a = a->prox;
	}
	a = alterado;
	printf("\n\n");
	printf("Simb: %c",tree->arv->dir->dir->dir->esq->dir->simb);
	printf("\n\n");
	while(a != NULL)
	{
		printf("\nPALAVRA: %s",a->palavra);
		a = a->prox;
	}
}
