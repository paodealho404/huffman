
# HUFFMAN

Projeto apresentado como requisito avaliativo para a disciplina de [Estruturas de Dados / Programação II](https://sites.google.com/a/ic.ufal.br/comp208/), ministrada no Instituto de Computação da Universidade Federal de Alagoas (UFAL).

Integrantes do grupo:
* Clemens August
* João Victor Falcão Santos Lima
* Pedro Henrique de Brito Nascimento
* Rodrigo Santos da Silva

## Módulos do projeto

* Seminário de um algoritmo ou estrutura de dados não vista em sala
    * [Trie](https://github.com/paodealho404/huffman/blob/master/Apresenta%C3%A7%C3%A3o%20-%20Trie.pdf)
* Codificação de Huffman
    * [Compactador e Descompactador de Arquivos](https://github.com/paodealho404/huffman/tree/master/implementacao_huffman)
* Contagem e plotagem de comparações de duas estruturas usadas
    * [Árvore de Busca Binária desbalanceada vs. AVL](https://github.com/paodealho404/huffman/tree/master/comparison-plotting)
* Casos de Testes Unitários
    * [Testes Unitários com CUnit](https://github.com/paodealho404/huffman/blob/master/implementacao_huffman/tests/tests.c)
* Uso obrigatório do Git.

## Executando o projeto

### Huffman

Para compilar o compactador e descompactador de arquivos:

```bash
    cd implementacao_huffman
    make huff
```

Para executar:

```bash
    ./main
```
* As opções do programa serão apresentadas via terminal.
* Arquivos compactados serão salvos com a extensão *.huff* adicionada ao seu nome original.

### Testes Unitários

```bash
    cd implementacao_huffman
    make test
    ./testes
```

### Contagem e Plotagem

Para compilar e executar o programa que realizará a comparação entre as estruturas:

```bash
    cd comparison-plotting
    make plot
    ./main
```
* A saída será gravada no arquivo out.txt.

Depois disso, para gerar os gráficos:

```bash
    python3 plot.py
```
* Requerimentos: Python 3, Matplotlib, Numpy.
* Serão geradas 3 figuras.
