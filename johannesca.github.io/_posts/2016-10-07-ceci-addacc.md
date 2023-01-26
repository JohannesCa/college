---
title: Concepção Estruturada de Circuitos Integrados - Somador/Subtrator de 4 bits com Acumulador
layout: page
permalink: /ceci_addacc/
---

Este é um relatório de atividades referente ao _Somador/Subtrator de 4 bits com Acumulador_, para a cadeira de **Concepção Estruturade de Sistemas Integrados**, ministrada pelo Prof. Antonio Carlos, no Centro de Informática, UFPB. Período de 2016.1.



## 1. Modelo de Ouro (Golden Model)

O Modelo de Ouro consiste no modelo comportamental de referência para o circuito em questão. Ele analisa as situações possíveis de entrada de um circuito e dita como o circuito deve se comportar (apresentar as saídas) mediante estas situações. Sendo assim, este é um modelo de comparação, onde podemos obter uma tabela-verdade para um circuito e comparar com o circuito produzido, para ter certeza que este funcionará corretamente.
Para este trabalho começamos preparando o Modelo de Ouro para o Circuito Somador/Subtrator de 4 bits com Acumulador em liguagem C pura com o auxílio do alto nível. Em seguida passamos parar o Genpat, para gerar o Modelo de Ouro customizado.



## 2. Diagrama do Somador/Subtrator de 4 Bits com Acumulador

Segue então o Diagrama para o circuito Somador/Subtrator de 4 Bits com Acumulador:

![addacc4bit](/images/2016-10-07-ceci-addacc/addacc.jpg "Esquema AddAcc 4bits")

O circuito possui apenas um barramento de entrada de 4 bits e outros dois sinais de entrada ***Sel0*** e ***Sel1***. Estes sinais ___'Sel'___ é que dirão quais operações serão realizadas no circuito. O circuito deve operar como o seguinte:

|*Sel0*|*Sel1*| Resposta                        |
|:----:|:----:|---------------------------------|
|   0  |   0  | Copia A para ACC                |
|   0  |   1  | Soma A com ACC e grava em ACC   |
|   1  |   0  | Copia !A para ACC               |
|   1  |   1  | Subtrai A de ACC e grava em ACC |

Isso considerando a subida do clock.

Percebamos que todo o circuito é sequencial, ou seja, mudando a entrada a qualquer momento, a saída deve ter uma resposta, independemente do clock. Apenas o __Acumulador__ é influenciado pelo clock, gravando a entrada apenas na subida desse.



## 3. Modelo de Ouro em C puro

O código do programa em C para o Modelo de Ouro do circuito está disponível [neste repositório](https://github.com/JohannesCa/4bit_adder_acc "JohannesCa/4bit_adder_acc") que criei. Nele criei funções para o bloco somador do circuito e para a verificação das entradas e cálculo correto das saídas.

Primeiro defini algumas structs para facilitar o manuseio:

{% highlight c %}
/***  Structs  ***/

struct aluRes
{
   char S;
   int Cout;
};


struct result4
{
   int S[4];
   int Cout;
};


struct result1
{
   int S;
   int Cout;
};
{% endhighlight %}

Comecei com uma função de soma de 1 bit apenas:

{% highlight c %}
struct result1 Sum_1bit(int A, int B, int Cin) // 1-bit sum
{
   struct result1 ret;

   ret.S = A^B^Cin;
   ret.Cout = (A&B)|(A&Cin)|(B&Cin);
   return ret;
}
{% endhighlight %}

E com ela pude fazer soma de 4 bits com um laço:

{% highlight c %}
struct result4 Sum_4bit(int A[], int B[], int Cin)
{
   struct result1 aux[4];
   struct result4 ret;

   for (int i = 0; i < 4; ++i)
      aux[3-i] = Sum_1bit(A[3-i], B[3-i], i == 0? Cin : aux[4-i].Cout);

   for (int i = 0; i < 4; ++i)
      ret.S[i] = aux[i].S;

   ret.Cout = aux[0].Cout;
   return ret;
}
{% endhighlight %}

Para receber as entradas do circuito fiz uma função maior, que recebe a entrada, o _clock_ e as seleções (_Sel0_ e _Sel1_):

{% highlight c %}
struct aluRes SumAcc(int Code[], int A[], int clk, int* aclk)
{
   struct aluRes res;
   struct result4 aux;

   aux = Sum_4bit(Code[0] == 0? A : Inv(A), ACC, Code[0]);
   
   if((clk == 1) && (*aclk == 0)){
      Copy(ACC, Code[1] == 0? (Code[0] == 0? A : Inv(A)) : aux.S);
      aux = Sum_4bit(Code[0] == 0? A : Inv(A), ACC, Code[0]);
   }

   res.S = Code[1] == 0? IntArrToChar(Code[0] == 0? A : Inv(A)) : IntArrToChar(aux.S);
   res.Cout = aux.Cout;

   return res;
}
{% endhighlight %}

Assim, eu chamo essa função em um laço no _main_ variando as entradas para testar as saídas:

{% highlight c %}
//(...)
   for(int i = 0; i < 2; ++i){
      selection[0] = i;
      for(int j = 0; j < 2; ++j){
         selection[1] = j;
         
         for(int k = 0; k < 16; ++k){
            for(clk = 0; clk < 2; ++clk){
               res = SumAcc(selection, a.S, clk, &aclk);
               printf("%i\t%i\t%i\t%i%i\t%i%i%i%i\t%i\t%i\t%i%i%i%i\n", cur_vect, aclk, clk, selection[0], selection[1], a.S[0], a.S[1], a.S[2], a.S[3], res.S < 8? res.S : res.S-16, res.Cout, ACC[0], ACC[1], ACC[2], ACC[3]);

               aclk = clk;
               ++cur_vect;
            }
            a = Sum_4bit(a.S, zero, 1);
         }
      }
   }
//(...)
{% endhighlight %}

E imprimo na saída padrão uma tabela com os resultados:

![printCPuro](/images/2016-10-07-ceci-addacc/cpuro.png)

Esta é uma tela parcial, não contém todos os resultados. Com esses testes o circuito deve seguir corretamente com as entradas.



## 4. Genpat

Para a geração do Genpat, incluimos sua biblioteca genpat.h no programa em C e adicionamos algumas macros para salvar os resultados.

Temos as macros:

* **DEF_GENPAT(_nome_)**: Define o nome do arquivo de saída (gerado pelo genpat; em formato .pat).


* **DECLAR(_ident_, _:spc_, _form_, _mode_, _size_, _opt_)**: Declara as entradas e saídas para o circuito de acordo com os parâmetros passados.
 
  * * _indent_ - Nome do sinal de entrada ou saída.
  * * _:spc_ - Espaçamento entre cada coluna de sinal no arquivo de saída.  
  * * _form_ - Formato em que os valores serão representados.  
  * * _mode_ - Tipo de sinal (Entrada ou Saída).
  * * _size_ - Largura do barramento.
  * * _opt_ - Opção extra (não utilizado).


* **AFFECT(_date_, _ident_, _value_)**: Altera o estado de determinado sinal. O estado é alterado apenas quando outro **AFFECT** é chamado.

  * * _date_ - Valor de tempo que indica quando o sinal será afetado.
  * * _ident_ - Nome do sinal que será afetado. Tal sinal precisa ter sido declarado anteriormente.
  * * _value_ - Novo valor para o sinal após o **AFFECT**.


* **SAV_GENPAT()**: Gera o arquivo .pat, seguindo os _AFFECTS_.

Utilizando tais macros no código C, temos a geração personalizada do Modelo de Ouro com o Genpat e conseguimos gerar o aquivo .pat com sucesso. Abaixo a imagem de um treho do .pat gerado.

![printGenpat](/images/2016-10-07-ceci-addacc/genpat.png)


O código para o Genpat encontra-se no mesmo [repositório](https://github.com/JohannesCa/4bit_adder_acc "JohannesCa/4bit_adder_acc"), sob o diretório "Genpat".
