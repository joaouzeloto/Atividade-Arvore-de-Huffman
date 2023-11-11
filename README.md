# Exercício Prático: Árvore de Huffman para codificar palavras de uma frase

## O primeiro programa deverá ter: 

- a) Um algoritmo para construção da árvore de Huffman (utilize uma lista encadeada 
ordenada no processo de construção da árvore). A árvore não deverá ter a palavra e sim 
um símbolo (numérico, um código). Os espaços em branco da frase também devem ser 
considerados e terá um símbolo na árvore. A frequência das palavras e dos espaços 
deverá ser contada e armazenada na lista do item b) antes de montar a árvore.

- b) Uma lista (de registos) para armazenar: o símbolo, a palavra, a frequência e os códigos 
de Huffman. Essa lista deverá ser gravada em arquivo em disco (arquivo binário).
Exemplo de frase para usar na construção da árvore de huffman (ignore a pontuação e 
tamanho da caixa dos caracteres!). Utilize frases com palavras repetidas!!!
“Amo como ama o amor. Não conheço nenhuma outra razão para amar senão amar. 
Que queres que te diga, além de que te amo, se o que quero dizer-te é que te 
amo?” Fernando Pessoa

- c) Codificação de uma frase e armazenamento do resultado (uma sequência de bits sem 
espaços gravada em arquivo texto). Utilize uma frase diferente da que foi usada na 
construção da árvore.

## O segundo programa deverá ter:

- a) Um algoritmo que abra os arquivos binário e texto (frase codificada), faça a decodificação 
da frase e mostre na tela. Para fazer a decodificação monte uma árvore binária a partir 
dos códigos de huffman armazenados da tabela (arquivo binário), e com varreduras na 
árvore seguindo as sequências binárias você chegará nas folhas, onde estão os códigos 
das palavras. Vá no arquivo, busque o código e pegue a palavra ou o espaço em branco, 
concatene em uma string e você terá a frase decodificada. Após ter a frase decodificada 
mostre na tela.
