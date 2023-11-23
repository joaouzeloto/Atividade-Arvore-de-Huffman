
struct arvore
{
	char simb;
	int qtde;
	struct arvore *dir, *esq;
};
typedef struct arvore Tree;

struct caixas
{
	Tree *arv;
	struct caixas	*prox;
};
typedef struct caixas Box;

struct auxiliarString
{
	char palavra[30], codHuff[15],simbo;
	int qtde;
	struct auxiliarString *prox;
};
typedef struct auxiliarString auxStr;

char criaSimbAl() {
    int numeroAleatorio = rand() % 26 + 65;
    char letraSorteada = (char)numeroAleatorio;
    return letraSorteada;
}

char existe(Box *B, char a)
{
	while(B!=NULL)
	{
		if(B->arv->simb!=a)
			B = B->prox;
		else
			return 1;
	}
	return 0;
}

void ordenaBox(Box **B,Box **novo)
{
	Box *ant=NULL,*prox=*B;
	while(prox!=NULL&&(*novo)->arv->qtde>prox->arv->qtde)
	{
		ant = prox;
		prox = prox->prox;
	}
	if(ant==NULL)
	{
		(*novo)->prox = *B;
		*B = *novo;
	}
	else
		if(prox==NULL)
			ant->prox = *novo;
		else
			{
				ant->prox = *novo;
				(*novo)->prox = prox;
			}
}
	

void criaCaixas(Box **boxI,auxStr **auxS)
{
	Box *novoB = (Box*) malloc(sizeof(Box));
	Tree *novo = (Tree*) malloc(sizeof(Tree));
	novo->qtde = (*auxS)->qtde;
	novo->esq = novo->dir = NULL;
	novo->simb = criaSimbAl();
	while(existe(*boxI,novo->simb))
		novo->simb = criaSimbAl();
	novoB->arv = novo;
	novoB->prox = NULL;
	(*auxS)->simbo = novo->simb;
	if(*boxI==NULL)
		*boxI = novoB;
	else
	{
		ordenaBox(*&boxI,&novoB);
	}
}

void criaNovaCaixa(Tree **pri,Tree **seg,Box **novo)
{
	*novo = (Box*) malloc(sizeof(Box));
	Tree *nArvo = (Tree*) malloc(sizeof(Tree));
	nArvo->qtde = (*pri)->qtde + (*seg)->qtde;
	nArvo->simb = '#';
	if((*pri)->qtde>(*seg)->qtde)
	{
		nArvo->esq = *seg;
		nArvo->dir = *pri;
	}
	else
	{
		nArvo->dir = *seg;
		nArvo->esq = *pri;
	}
	(*novo)->arv = nArvo;
	(*novo)->prox = NULL;
	
}

void criaHuffman(Box **boxI)
{
	Box *aux=*boxI,*novo,*prox;
	while(aux->prox!=NULL)
	{
		criaNovaCaixa(&aux->arv,&aux->prox->arv,&novo);
		prox = aux->prox;
		free(aux);
		if(prox->prox==NULL)
		{
			free(prox);
			*boxI = novo;
		}
		else
		{
			*boxI = prox->prox;
			free(prox);
			ordenaBox(*&boxI,&novo);
		}
		aux=*boxI;		
	}
}

void exibeTree(Tree *raiz)
{
	if(raiz!=NULL)
	{
		printf("\nDIR: %s,ESQ: %s",raiz->dir,raiz->esq);
		exibeTree(raiz->esq);
		exibeTree(raiz->dir);
	}
}


void adicionaHuffmanCod(Tree *raiz,char cod[20],int *TL,auxStr **list)
{
	auxStr *aux;
	if(raiz!=NULL)
	{
		if(raiz->esq!=NULL)
		{
			cod[*TL] = '0';
			*TL = *TL + 1;
			cod[*TL] = '\0';
		}
		else
			*TL = *TL + 1;
		adicionaHuffmanCod(raiz->esq,cod,&*TL,&*list);
		*TL = *TL - 1;
		if(raiz->dir!=NULL)
		{
			cod[*TL] = '1';
			*TL = *TL + 1;
			cod[*TL] = '\0';
		}
		else
			*TL = *TL + 1;
		adicionaHuffmanCod(raiz->dir,cod,&*TL,&*list);
		*TL = *TL - 1;
		aux = *list;
		while(aux!=NULL&&aux->simbo!=raiz->simb)
			aux = aux ->prox;
		if(aux!=NULL)
			strcpy(aux->codHuff,cod);
	}
}

void salvaTab(auxStr *list)
{
	auxStr a;
	FILE *ptr = fopen("tabela_codif.txt","wb");
	while(list!=NULL)
	{
		strcpy(a.palavra,list->palavra);
		strcpy(a.codHuff,list->codHuff);
		a.qtde = list->qtde;
		a.simbo = list->simbo;
		a.prox = NULL;
		fwrite(&a,sizeof(auxStr),1,ptr);
		list = list->prox;
	}
	fclose(ptr);
}

void codificaFrase(auxStr *aux,auxStr *mapa)
{
	FILE *ptr = fopen("frase_codifi.txt","w+");
	char cod[250];
	int TL=0,i;
	auxStr *mapAux = mapa;
	while(aux != NULL)
	{
		while(mapAux!=NULL&&strcmp(aux->palavra,mapAux->palavra)!=0)
			mapAux = mapAux -> prox;
		if(mapAux!=NULL)
		{
			for(i=0;mapAux->codHuff[i]!='\0';i++,TL++)
				cod[TL] = mapAux->codHuff[i];
		}
		mapAux = mapa;
		aux = aux->prox;
	}
	printf("\n%s",cod);
	fprintf(ptr,"%s\n",cod);
}

void criaNo(Tree **raiz,char sim)
{
	*raiz = (Tree*) malloc(sizeof(Tree));
	(*raiz)->simb = sim;
	(*raiz)->esq = NULL;
	(*raiz)->dir =NULL;
	(*raiz)->qtde = 0;
}

void recuperaTree(Tree **raiz,auxStr *list)
{
	Tree *aux;
	int i;
	criaNo(*&raiz,'#');
	aux = *raiz;
	while(list!=NULL)
	{
		for(i=0;list->codHuff[i]!='\0';i++)
		{
			if(list->codHuff[i]=='0')
			{
				if((*raiz)->esq!=NULL)
				{
					if(list->codHuff[i+1]=='\0')
						(*raiz)->esq->simb = list->simbo;
					else
						*raiz = (*raiz)->esq;
				}
				else
				{
					if(list->codHuff[i+1]!='\0')
					{
						criaNo(&(*raiz)->esq,'#');
						*raiz = aux;
						i = -1;
					}
					else
					{
						criaNo(&(*raiz)->esq,list->simbo);
					}
						
				}
			}
			else
			{
				if(list->codHuff[i]=='1')
				{
					if((*raiz)->dir!=NULL)
					{
						if(list->codHuff[i+1]=='\0')
							(*raiz)->dir->simb = list->simbo;
						else
							*raiz = (*raiz)->dir;	
					}
					else
					{
						if(list->codHuff[i+1]!='\0')
						{
							criaNo(&(*raiz)->dir,'#');
							*raiz = aux;
							i = -1;
						}
						else
						{
							criaNo(&(*raiz)->dir,list->simbo);
						}
							
					}
				}
			}
		}
		*raiz = aux;
		list = list->prox;
	}	
}

void buscaSimbExibe(char a,auxStr *tab)
{
	while(tab!=NULL&&tab->simbo!=a)
		tab = tab->prox;
	if(tab!=NULL)
		printf("%s",tab->palavra);
}

void exibeFrase(FILE *ptr,Tree *arv,auxStr *tab)
{
	Tree *arvAux = arv;
	auxStr *a;
	char bit,frase[300];
	int i=0,TL=0,j=0;
	bit = getc(ptr);
	while(!feof(ptr)&&bit!='\0')
	{
		while(!feof(ptr)&&arvAux->dir!=NULL&&arvAux->esq!=NULL)
		{
			if(bit=='0')
				arvAux = arvAux->esq;
			else
				if(bit=='1')
					arvAux = arvAux->dir;
			bit = getc(ptr);
		}
		a = tab;
		while(a!=NULL&&a->simbo!=arvAux->simb)
			a = a->prox;
		if(a!=NULL)
		{
			for(j=0;a->palavra[j]!='\0';j++,TL++)
				frase[TL] = a->palavra[j];
			frase[TL] = 32;
			TL++;
		}
		arvAux = arv;
		if(!feof(ptr))
			bit = getc(ptr);
	}
	frase[TL] = '\0';
	printf("\n%s",frase);
	fclose(ptr);
}

void exibeArv(Tree *a)
{
	int i;
	static int n = -1;
	if( a==NULL) return;
	n++;
	exibeArv(a->dir);
	for(i=0; i<5*n;i++) printf(" ");
	printf(" (%c)\n",a->simb);
	exibeArv(a->esq);
	n--;
}




