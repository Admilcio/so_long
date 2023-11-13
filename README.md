<h1 align="center"> so_long - @42sp </h1>

<p align="center">:information_source: Um pequeno jogo 2D feito utilizando a Biblioteca Gráfica MiniLibX - Texturas, sprites e tiles incluídos. </p>

<p align="center"><a href="https://www.42sp.org.br/" target="_blank"><img src="https://img.shields.io/static/v1?label=&message=SP&color=000&style=for-the-badge&logo=42""></a></p>
<p align="center"><a href="https://github.com/augustobecker/so_long" target="_blank"><img align="center" alt="so_long" src="https://user-images.githubusercontent.com/81205527/179134510-48689e9e-f8e4-4165-be40-2e0ec8f5d60d.png"> </a></p>
<p align="center">123/100 :white_check_mark:</p>
<p align="center"><a href="https://github.com/augustobecker/SoLong/blob/main/README.md" target="_blank"><img src="https://img.shields.io/badge/available%20in-EN-blue"></a></p>
<p align="center"><img src="https://user-images.githubusercontent.com/81205527/174392536-21619238-638a-4173-a77c-1b168c6c7898.png"> </p>

<p align="center">:magic_wand: Tudo que é pequeno é uma versão menor de algo grande</p>
	
## Index
* [O que é so_long?](#o-que-e-so_long)
* [Requisitos](#requisitos)
* [Como funciona?](#como-funciona)
	* [Mapas](#mapas)
	* [Controles](#controles)
* [Como eu testo?](#como-eu-testo)
* [42 Cursus](#42-cursus)
* [Autor](#autor)

<h2 align="center" id="o-que-e-so_long"> O que é so_long? </h2>

O quinto projeto na escola de programação 42. Esse é o primeiro projeto gráfico que fazemos e podemos escolher entre 3 opções (FdF, Fractol e so_long),
que abordaram áreas diferentes mas são todos projetos gráficos. O so_long consiste em um jogo top-down, que codificamos do 0,
com auxilio da biblioteca MiniLibx. Envolve uma série de validações do mapa que recebemos, checagens para evitar leaks de memória,
lidar com a engenharia do jogo em si, gerenciamento de janelas, eventos, as sprites e os mapas.
    
<h2 align="center" id="requisitos"> Requisitos </h2>

<p  align="center"> :warning: O projeto deve estar de acordo com a <a href="https://github.com/42School/norminette/blob/master/pdf/pt_br.norm.pdf" target="blank">Norma</a> </p>
A Norma é um padrão de programação que define um conjunto de regras a seguir ao escrever um código na 42. A norma aplica-se a todos os projetos C dentro do currículo interno por padrão, e para qualquer projeto onde é especificado. Aqui algumas das regras:

    Cada função dever ter no máximo 25 linhas, não contando suas próprias chaves '{}'.
    
    Cada linha deve ter no máximo 80 colunas de largura, comentários incluídos.
    
    Uma função pode ter no máximo 4 parâmetros definidos.
   
    Não podem ser declaradas mais que 5 variáveis por função.
    
    Não é permitido o uso de: for , do...while , switch , case ,  goto  ,
    operadores ternários como `?' e VLAs - Matrizes de comprimento variável.
  A norminette (como chamamos a norma na 42) é feita em python e é open source.
  
  O repositório está disponível em https://github.com/42School/norminette
    
<h2 align="center" id="como-funciona"> Como funciona? </h2>    

    
Você só vai conseguir jogar uma vez que tenha instalado os recursos da <a href="https://github.com/42Paris/minilibx-linux">MiniLibx</a> ou que esteja usando
uma das máquinas da 42.
 

Para jogar, primeiro compile o projeto com make

	make
	
Ou caso queira jogar a versão com bônus:

	make bonus
	
Então, execute o ./so_long seguido do mapa que você quer jogar:
	
	./so_long assets/maps/valid/map2.ber	

Para o bônus seria:
	
	./so_long_bonus assets/maps/valid/map2.ber
	
<h3 id="mapas" align="center"> Mapas </h3>   
Qualquer mapa que você passar pode servir de input para o jogo, isso se respeitar as regras abaixo:

O mapa precisa ser um arquivo .ber

E só pode conter os seguintes caracteres:
    
| CARACTERE |	OBJETO   |
| --------- | ---------- |
| 1         |   Parede   |
| C	        | Coletáveis |
| E	        |    Saída   |
| P         |   Jogador  |      
| 0         |   Piso     |
    
E para o bônus coloquei um novo parâmetrs, que te faz perder uma vez que tente passar por cima:
    
| CARACTERE |	OBJETO   |
| --------- | ---------- |
| T         |   Poça Tóxica  |

    
O mapa deve ser retangular e cercado de paredes '1'.

Deve conter pelo menos uma saída 'E', um coletável 'C' e apenas um jogador 'P'.
    
Pode conferir alguns exemplos na pasta /assets/maps desse projeto. 
	
Como assets/maps/valid/map2.ber:

<img src="https://user-images.githubusercontent.com/81205527/163024984-1ff511c1-17d2-4eef-8d97-90cc8a884c73.png">
Esse arquivo .ber gera esse mapa:
    
    
<img src="https://user-images.githubusercontent.com/81205527/174420150-0ee15e42-c7c3-4854-936b-fffaf13683c2.png">
	
<h3 id="controles" align="center"> Controles </h3>   
    
| TECLA |	OBJETO   |
| --------- | ---------- |
| W ou ⬆️        |    Move para cima   |
| A	ou ⬅️        |    Move para esquerda |
| S	ou ⬇️     |    Move para baixo   |
| D ou ➡️       |   Move para direita|      
| Q ou Esc      |   Fecha o jogo     | 
    
    
Use WASD ou as setas para se mover.

Após pegar todos os sacos de dinheiro, a saída se abre e você pode escapar pela escada.

Pode fechar o jogo clicando no X no topo direito da janela, ou ainda pressionando Q ou Esc.
  
<h2 align="center" id="como-eu-testo"> Como eu testo? </h2>

Para testar o funcionamento do jogo em si recomendo que jogue com alguns mapas diferentes e tente fazer coisas como:
    
Caminhar rumo à um muro e ver se é barrado.
    
Ir para a saída do mapa sem ter coletado todos os itens.

Percorrer o mesmo caminho pelo menos uma vez.
    
Testar se consegue se movimentar tanto com as setas quanto com as teclas WASD.
    
Conferir se a janela fecha quando clica no X, também pressionando a tecla Q e Esc.
 
Para testar as validações de mapa como:
    
Extensão inválida, mapa faltando parâmetros ou com parâmetros extra, mapa inexistente, mapa não retangular, argumentos extra ou em falta na linha de comando. 

Eu resolvi criar um tester. Não tinha encontrado nenhum outro até o momento.

Para testar o código desse repositório:
    
Clone o repositório e entre nele:
    
    git clone https://github.com/augustobecker/so_long so_long
  
    cd so_long/

Agora, clone o so_long Tester do @augustobecker:
    
    git clone https://github.com/augustobecker/so_long_tester so_long_tester
 
Entre na pasta do Tester e rode com make:
    
    cd so_long_tester
    make

Se você fez tudo corretamente, deve ver algo como isso:

![image](https://user-images.githubusercontent.com/81205527/179400332-9e80f631-7d46-464b-a0eb-e481b48ad6b4.png)
    
<h2 align="center" id="42-cursus"> 42 Cursus </h2>
    
A 42 é uma iniciativa educacional global que propõe uma nova forma de aprender tecnologia: sem professores, sem salas de aula,
estudantes aprendendo com seus colegas estudantes (Aprendizado peer to peer),
com uma metodologia que desenvolve habilidades de computação e da vida.
Sem mencionar que é completamente gratuita e aberta para todos, sem pré-requisitos. 
    
As admissões na 42 são diferentes de outras escolas. Usamos um processo de admissão baseado em mérito.
O passo final no processo é a Piscina - parte parte do processo seletivo que requer 4 semanas de código intenso e imersivo.
Não é necessário experiência anterior em programação.
    
Você pode conferir mais sobre o processo de admissão no site da 42sp: https://www.42sp.org.br
    
ou no meu repositório do github: <a href="https://github.com/augustobecker/42sp_Piscine">42 Piscine</a>

Para ver outros projetos da 42 desenvolvidos por mim, clique aqui: <a href="https://github.com/augustobecker/42cursus">42 Cursus </a>

<h2  align="center" id="autor">Autor</h2>
<div align="center">
	<div>
	<img height="222em" src="https://user-images.githubusercontent.com/81205527/174709160-f4bc029d-b667-469b-b2a7-4e036f1c5349.png">
	</div>
	<div>
		<strong> Admilcio da Mata</strong>
	
:wave: Fale comigo: 
    	</div> 
    	<div>
  	<a href="https://github.com/Admilcio" target="_blank"><img align="center" alt="LinkedIn" height="60" src="https://user-images.githubusercontent.com/81205527/157161849-01a9df02-bf32-45be-add4-122bc40b48cf.png"></a>
	<a href="https://www.instagram.com/augusto.becker/" target="_blank"><img align="center" alt="Instagram" height="60" src="https://user-images.githubusercontent.com/81205527/157161841-19ec3ab2-2c8f-4ec0-8b9d-3cd885256098.png"></a>
</div>    	
