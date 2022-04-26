# PI3_2022_1: Vaso Inteligente
O objetivo deste projeto é implementar um vaso inteligente baseado em Internet das Coisas, que irá monitorar os parâmetros de umidade, luminosidade e temperatura de uma planta, e a partir destes parâmetros avaliar o estado da planta, com base em um banco de dados que contenha informações de espécies de plantas. Detectando o estado da planta, será gerada uma expressão facial em um display contido no vaso, que representará esse estado, como por exemplo, em caso de falta de água para a planta, o vaso exibiria uma expressão triste. O usuário poderá selecionar a espécie da planta, bem como manter um histórico de fotos da mesma, através de um aplicativo de celular baseado na plataforma Home Assistant.



<img src="imagens PI3/Diagrama PI3 Vaso Inteligente.png" style="width:800px;height:300px;">


# Pesquisa bibliográfica

Os links a seguir referem-se a pesquisa sobre os parâmetros de umidade, temperatura e luminosidade para os cuidados com diferentes espécies de plantas. 
Esses parâmetros foram utilizados para a criação do banco de dados das espécies para o aplicativo de celular.

1. https://feelingsandflowers.com/cactus-care-guide-watering

2. https://www.colibriorquideas.com.br/pagina-Dicas_de_Cultivo

3. https://www.cpt.com.br/artigos/orquideas-luminosidade#:~:text=Para%20a%20maioria%20das%20orquídeas,fotômetro%20de%20uma%20máquina%20fotográfica.

4. http://www.paisagismobauru.com.br/curiosidades/curiosidades/

5. http://paisagismobauru.com.br/data/documents/CatalogoPlantasOrnamentais.pdf

6. https://www.cultivando.com.br/sol-pleno-meia-sombra-sombra-entenda-a-diferenca-para-as-plantas/#:~:text=Em%20uma%20sala%20muito%20bem,100%20lux%2C%20ou%2050.000%20lux!

7. https://www.gabrielkehdi.com/single-post/plantas-para-sombra


Serão monitorados os seguintes itens no vaso/planta:

* Temperatura;
* Umidade;
* Umidade do solo (para indicar o momento de rega);
* Luminosidade

## Luminosidade

Conforme o site "Paisagismo Bauru" em sua postagem ["Dicas de luminosidade para seu jardim", link 4](http://www.paisagismobauru.com.br/curiosidades/curiosidades/), a medição de luminosidade será dividida em três faixas:
* **Sol**:
O dia inteiro com iluminação solar direta. Luminosidade acima de 20.000 lux.

* **Meia Sombra**:
Variando de iluminação de poucas horas na parte da manhã e mais algumas poucas horas de iluminação na parte da tarde. Luminosidade variando de 5.000 a 20.000 lux.

* **Sombra**:
Iluminação indireta. Luminosidade de 2.500 a 5.000 lux.

