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
		exibeTree(raiz->esq);
		exibeTree(raiz->dir);
		printf("\nQTDE:%d SIMBOLO: %c",raiz->qtde,raiz->simb);
	}
}



