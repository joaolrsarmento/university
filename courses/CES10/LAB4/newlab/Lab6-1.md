# Lab 6-1: Leitura de arquivo

## Prazo de submissão até 16/06/2019 às 22:00 (via GOOGLE CLASSROOM)

## Descrição

Faça um programa para ler o nome de um arquivo via linha de comando (parâmetro do comando do terminal). Para isto, use os parâmetros `argc` e `argv` de `main`.
Este deverá ser um arquivo texto.

Sua tarefa é ler o arquivo e retornar quantas linhas, palavras e caracteres não brancos o texto possui. Para isto use a função [`isspace`](https://en.cppreference.com/w/c/string/byte/isspace). Utilize como definição de palavras, qualquer sequência de caracteres considerados não whitespace por `isspace`.

## Importante

Infelizmente, o Run.codes não funciona com parâmetros de comandos. Apenas entrada via `stdin` e `stdout`. Assim, iremos o utilizar apenas para validar a parte do código referente a contagem de palavras, caracteres e linhas.

Para testar no run.codes, você irá remover a parte de leitura das entradas de comando (`argc` e `argv`) e irá ler o arquivo: `Lab6-1.md`. Este arquivo já estará no run.codes.

```c
char *arq = "Lab6-1.md";
... fopen(arq, "r") ...
```

## Avaliação

A avaliação deste lab será realizada observando as duas plataformas: Google Classroom e Run.Codes.
O Google Classroom deverá conter a versão do código-fonte via linha de comando, ou seja, deverá ler o arquivo via `argv`.
Já o Run.Codes deverá executar com sucesso o único caso de teste adicionado.

### Entrada

Na versão do Google Classroom, deve-se informar o caminho para o arquivo via parâmetro de comando do programa.

Saída:

```text
Quantidade de linhas: xx
Quantidade de palavras: xx
Quantidade de caracteres não whitespace: xx
```

## *Informativo sobre as avaliações no geral*

Para a avaliação final de cada exercício, serão considerados diversos aspectos do código, como a formatação, a lógica e o uso correto das estruturas de dados. Já o Run.Codes servirá apenas de apoio para automatização de alguns testes mais simples.

Importante: O Run.Codes ficará aberto para submissão por apenas 1 ou 2 dias, forçando com que os testes e depurações do código sejam realizados antes da submissão à plataforma. Veja o Exercício 0 (Hello World), para mais detalhes.

Importante: Apenas o último código-fonte enviado a plataforma, após o término do prazo de submissão, será considerado para avaliação.

O trabalho que não cumprir qualquer item da seção 'Requisitos exigidos' receberá **nota zero**, mesmo que a funcionalidade principal esteja implementada corretamente.

Fique atento aos prazos de submissão e envie antes do horário máximo permitido. A plataforma pode sobrecarregar, fazendo com que a submissão seja impedida.

#### Alguns dos itens avaliados

A seguir é listado alguns dos itens avaliados que reduzem a nota:

- Compilando o código com as flags `-Wall -Wextra -std=c11 -pedantic` nenhuma mensagem de `warning` deve ser retornado
- Nome de variáveis não condizentes com seu uso
- Boas práticas de programação e formatação
- Falta do 'cabeçalho' no início do código-fonte, como o modelo abaixo
- *Memory leak*

```text
/***********************************/
/* Aluno: Fulano de Tal            */
/* CES-10: Introdução à Computação */
/* Prof. Nome do professor         */
/***********************************/
```

#### Requisitos exigidos

1. Código-fonte com encoding UTF-8 sem BOM;
2. Código-fonte compilando com sucesso;
3. Indentação;
4. Seguir estritamente o solicitado, incluindo as entradas e saídas para os casos de teste;
5. Código-fonte no padrão C11 da linguagem C.

Exemplo de item (4): enunciado informa que o exercício deve ser resolvido usando laços, porém o aluno implementa a solulção de outra forma.
