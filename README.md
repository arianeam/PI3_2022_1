# PI3_2022_1: Vaso Inteligente
<img src="imagens PI3/ze_vasinho.svg" style="width:500px;height:500px;">
O objetivo deste projeto é implementar um vaso inteligente baseado em Internet das Coisas, que irá monitorar os parâmetros de umidade do solo, luminosidade e temperatura de uma planta, e a partir destes parâmetros avaliar o estado da planta, com base em um banco de dados que contenha informações de espécies de plantas, ou dados personalizados pelo usuário. Detectando o estado da planta, será gerada uma expressão facial em um display contido no vaso, que representará esse estado, como por exemplo, em caso de falta de água para a planta, o vaso exibiria uma expressão de sede. O usuário poderá selecionar configurar os parâmetros da planta através do aplicativo de celular. Essa configuração poderá ser manual ou automática (selecionando a espécie de planta no aplicativo). 



<img src="imagens PI3/Diagrama PI3 Vaso Inteligente.png" style="width:800px;height:300px;">


# Pesquisa bibliográfica

Os links a seguir referem-se a pesquisa sobre os parâmetros de umidade, temperatura e luminosidade para os cuidados com diferentes espécies de plantas. 
Esses parâmetros foram utilizados para entender quais parâmetros medir e como trabalhá-los no firmware e app.

1. https://feelingsandflowers.com/cactus-care-guide-watering

2. https://www.colibriorquideas.com.br/pagina-Dicas_de_Cultivo

3. https://www.cpt.com.br/artigos/orquideas-luminosidade#:~:text=Para%20a%20maioria%20das%20orquídeas,fotômetro%20de%20uma%20máquina%20fotográfica.

4. http://www.paisagismobauru.com.br/curiosidades/curiosidades/

5. http://paisagismobauru.com.br/data/documents/CatalogoPlantasOrnamentais.pdf

6. https://www.cultivando.com.br/sol-pleno-meia-sombra-sombra-entenda-a-diferenca-para-as-plantas/#:~:text=Em%20uma%20sala%20muito%20bem,100%20lux%2C%20ou%2050.000%20lux!

7. https://www.gabrielkehdi.com/single-post/plantas-para-sombra

8. https://www.tecnologiaetreinamento.com.br/jardim/floricultura-jardim/cultivo-de-orquideas-substrato-clima-e-luminosidade

9. https://www.floresefolhagens.com.br/plantas-por-categorias/

10. https://www.cpt.com.br/artigos/orquideas-luminosidade#:~:text=Para%20a%20maioria%20das%20orquídeas,fotômetro%20de%20uma%20máquina%20fotográfica. 

11. https://plantasemcasa.com.br/plantas-de-meia-sombra-para-vasos/

12. https://casa.abril.com.br/jardins-e-hortas/tudo-que-voce-precisa-saber-sobre-iluminacao-plantas-internas/

13. https://casa.abril.com.br/jardins-e-hortas/6-dicas-regar-plantas/

14. https://comozed.com/quantos-lumens-são-necessários-para-cultivar-plantas

15. https://www.youtube.com/watch?v=gclYWybQeI4

16. https://www.emporioluz.com.br/blog/a-influencia-da-luz-nas-plantas/

17. https://greenpower.net.br/blog/iluminacao-tamanho-do-grow/

18. https://wchristianeletrotecnica.wordpress.com/2013/01/23/a-luz-e-as-plantas/

19. https://www.gazetadopovo.com.br/haus/paisagismo-jardinagem/voce-sabe-como-regar-corretamente-suas-plantas/

20. https://revistacasaejardim.globo.com/Casa-e-Jardim/Paisagismo/Plantas/noticia/2021/09/plantas-de-sol-11-especies-resistentes-e-que-demandam-luz-direta.html

21. https://cantinhodovideo.com/10-tipos-de-plantas-para-plantar-em-sol-pleno/

22. https://luxafrica.life/2021/02/5-tipos-de-plantas-para-ter-em-casa/

23. https://www.youtube.com/watch?v=qcFD-a5sp2o

24. https://www.youtube.com/watch?v=mpvMj9PM-7I

25. https://www.temarquitetura.com.br/single-post/2015/01/30/Plantas-X-sol

26. https://casa.umcomo.com.br/artigo/plantas-resistentes-ao-sol-e-ao-frio-29387.html

27. https://www.tgservices.com.br/efeito-da-temperatura-sobre-as-plantas/

28. https://100fronteiras.com/brasil/noticia/plantas-para-cultivar-ambientes-meia-sombra-sombra-total/

29. https://www.planejpb.com.br/post/jardinagem

30. https://www.casadevalentina.com.br/blog/papo-de-paisagista-plantas-para-sombra/

31. https://www.metodopaisagismo.com.br/single-post/2017/01/03/sol-sombra-ou-meia-sombra

32. https://portalvidalivre.com/articles/148

33. https://minhasplantas.com.br/tv/dentro-de-casa/descubra-quanto-de-luz-sua-planta-precisa/

34. https://www.jardinet.com.br/2019/04/sol-pleno-meia-sombra-luz-direta-ou.html

35. https://www.scielo.br/j/aa/a/4qHVqmHknnPWmwHx3KmMkrB/?lang=pt

36. https://www.atelierecul.com/single-post/2018/02/27/tipos-de-rega-e-luminosidade-em-plantas

37. https://cactosesuculentas.com/suculentas/qual-a-melhor-iluminacao-para-as-suculentas/

38. https://www.editorarealize.com.br/editora/anais/conimas-e-conidis/2019/TRABALHO_EV133_MD4_SA37_ID1471_01112019113159.pdf

39. https://viverorquideaseideias.blogspot.com/2017/02/como-definir-rega-para-suas-plantas.html

40. https://exame.com/casual/os-6-erros-mais-comuns-ao-cuidar-de-plantas-e-como-evita-los/

41. https://eos.com/pt/blog/umidade-do-solo/

42. https://www.vaisala.com/sites/default/files/documents/CEN-BAU-Greenhouse-Climate-Application-Note-B211142PT-A.pdf

43. https://greenpower.net.br/blog/cultivo-indoor-controle-de-temperatura/

44. https://www.orquideasnoape.com.br/2021/02/suculenta-echeveria-lilacina.html

# Plantas que foram inseridas no banco de dados:
## lírio da paz

https://guiadejardinagem.com.br/plantas-para-dentro-de-casa/#O_que_sao_Plantas_de_Interior

https://portalvidalivre.com/articles/96

https://casa.abril.com.br/jardins-e-hortas/como-cultivar-lirio-da-paz/

https://blog.plantei.com.br/lirio-da-paz/

https://vivercomplantas.wordpress.com/2018/01/30/lirio-da-paz-para-locais-sombreados-meia-sombra/



# planta-jade

https://www.jardineiro.net/plantas/planta-jade-crassula-ovata.html
https://portalvidalivre.com/articles/44
https://guiadassuculentas.com/suculenta-jade-saiba-tudo-sobre-essa-planta/
https://www.picturethisai.com/pt/care/Crassula_ovata.html#:~:text=Forneça%20temperatura%20adequada%20(%2025%20℃,luz%20(luz%20difusa%20brilhante).
https://www.noticiasdejardim.com/plantas-de-interior/crassula-ovata-arvore-de-jade-uma-especie-muito-facil-de-cultivar/


# planta fantasma 

https://www.floresefolhagens.com.br/planta-fantasma-graptopetalum/

https://portalvidalivre.com/articles/143

https://www.picturethisai.com/pt/care/Graptopetalum_paraguayense.html

https://cibercactus.com/pt/graptopetalum-paraguayense/



# Serão monitorados os seguintes itens no vaso/planta:

* Temperatura;
* Umidade do solo;
* Luminosidade

## Luminosidade

Conforme o site "Paisagismo Bauru" em sua postagem ["Dicas de luminosidade para seu jardim", link 4](http://www.paisagismobauru.com.br/curiosidades/curiosidades/), a medição de luminosidade será dividida em três faixas:
* **Sol**:
O dia inteiro com iluminação solar direta. Luminosidade acima de 20.000 lux.

* **Meia Sombra**:
Variando de iluminação de poucas horas na parte da manhã e mais algumas poucas horas de iluminação na parte da tarde. Luminosidade variando de 5.000 a 20.000 lux.

* **Sombra**:
Iluminação indireta. Luminosidade de 2.500 a 5.000 lux.

## Umidade do solo

* **Seco**
* **Úmido**
* **Molhado**


--------------------

# Sensores

Todos sensores, o display oled, e um dos ESP32 utilizados para o desenvolvimento do PI3, não foram comprados. Ambos integrantes da dupla já possuiam o material em casa. Foi efetuada a compra de mais um ESP32 para um dos integrantes da dupla. E o microprocessador utilizado na placa desenvolvida foi removido de um dos ESP32. Poderiam ter sido utilizados outros sensores de melhor desempenho, porém optou-se por manter o menor custo possível nesta primeira versão do Vaso Inteligente.

**OBS.: Os sensores que utilizam os canais de ADC passam pelo circuito de entradas analógicas antes de chegar aos canais ADC**

<img src="imagens PI3/entradas_analogicas.PNG">

## DHT11: sensor de temperatura e umidade

<img src="imagens PI3/dht11.jpg" style="width:381px;height:381px;">


Datasheet: https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf

[O elemento sensor de temperatura é um termistor do tipo NTC e o sensor de Umidade é do modelo HR202, o circuito interno faz a leitura dos sensores e se comunica a um microcontrolador, através de um sinal serial de uma via.](https://www.filipeflop.com/produto/modulo-sensor-de-umidade-e-temperatura-dht11-ky-015/)
O DHT11 foi alimentado com o 3v3 e o GND do ESP32, e o pino de dados foi ligado ao pino D27 do microcontrolador.

<img src="imagens PI3/dht11_especificacoes.PNG">


## LDR 5mm

<img src="imagens PI3/ldr.jpg" style="width:300px;height:300px;">

Datasheet: https://www.filipeflop.com/img/files/download/Datasheet_LDR.pdf

[O Sensor de Luminosidade LDR (Light Dependent Resistor) é um componente cuja resistência varia de acordo com a intensidade da luz. Quanto mais luz incidir sobre o componente, menor a resistência.](https://www.filipeflop.com/produto/sensor-de-luminosidade-ldr-5mm/). Foi utilizado o canal 5 do ADC1 do ESP32 para receber a tensão do LDR e o valor passou por uma função de linearização.

<img src="imagens PI3/luximetro_circuito.PNG">

<img src="imagens PI3/luximetro.PNG">


## Higrômetro HL-69 (YL-69)

<img src="imagens PI3/hl69.jpg" style="width:400px;height:400px;">

Guia (datasheet não encontrado): https://usermanual.wiki/Pdf/instructions.261306374.pdf

[Este Sensor de Umidade do Solo Higrômetro foi feito para detectar as variações de umidade no solo. Ele funciona da seguinte forma: quando o solo está seco, a saída do sensor fica em estado alto e quando úmido, a saída do sensor fica em estado baixo. O limite entre seco e úmido pode ser ajustado através do potenciômetro presente no sensor que regulará a saída digital D0. Contudo, para ter uma resolução melhor, é possível utilizar a saída analógica A0 e conectar a um conversor AD.](https://www.filipeflop.com/produto/sensor-de-umidade-do-solo-higrometro/). Para este projeto foi utilizada a saída analógica A0 ligada ao canal 4 do ADC1 do ESP32. A alimentação do sensor foi feita através do 3v3 e GND do ESP32.


# Desenvolvimento

## Firmware

O desenvolvimento ocorreu no microcontrolador ESP32-WROOM-32, da Espressif, utilizando o  framework oficial da Espressif, o ESP-IDF, que é voltado para o desenvolvimento de aplicações parar toda a família ESP32. Foi utilizada a extensão ESP-IDF no editor de códigos Visual Studio Code. 
A linguagem de programação utilizada no firmware foi C++/C. Os componentes do framework ESP-IDF são disponibilizados em C, porém, devido o uso de uma biblioteca em C++, necessária para comunicação com o banco de dados.

* **Github Espressif**: https://github.com/espressif

* **Github Espressif ESP-IDF**: https://github.com/espressif/esp-idf

* **Biblioteca utilizada para o DHT11**: https://github.com/UncleRus/esp-idf-lib/tree/master/components

* **Biblioteca utilizada para o Google Firebase Realtime Database**: https://github.com/dahmadjid/Firebase-idf 

## Display oled SSD1306 128x64

O display utilizado foi o oled SSD1306 de 128x64. As animações para o display foram desenhadas no software Inkscape, com a área de 128x64px, exportadas para PNG, e em seguida convertida para outra extensão bitmap, a extensão XBM, respeitando a função da biblioteca para display SSD1306 utilizada no firmware, ssd1306_load_xbm. É importante observar quais formatos as funções aceitam quando utilizar bibliotecas de terceiros, caso contrário a imagem será exibida no display de forma distorcida, devido a forma como os bits são dispostos em cada tipo de extensão bitmap. Uma melhoria interessante para a estética do projeto é utilizar um display maior e com uma melhor resolução. Como um dos integrantes da dupla já possuia o display SSD1306, optou-se por usá-lo no projeto, reduzindo os custos do protótipo.

<img src="imagens PI3/oled.jpg" style="width:400px;height:400px;">


## Armazenamento de dados e aplicativo de celular
Para armazenar os dados do aplicativo e dados lidos dos sensores do ESP32, e agilizar a comunicação com o aplicativo foi utilizada a ferramenta do Google Firebase.
O Firebase é uma plataforma para agilizar a criação e engajamento de aplicativos. Foi criado um projeto no Google Firebase, no qual foi vinculado o aplicativo de celular criado para o Vaso Inteligente. E para armazenar os dados e sincronizar em tempo real, tanto com o aplicativo quanto com o ESP32, foi utilizada a ferramenta Firebase Realtime Database. O Firebase Realtime Database é um banco de dados NoSQL hospedado na nuvem. Com ele, você armazena e sincroniza dados JSON entre os usuários em tempo real.
O aplicativo foi desenvolvido na plataforma Kodular, através de blocos lógicos de programação. Com o link do Realtime Database e a chave de API fornecida na criação do projeto no Firebase, além de algumas configurações de regras, é fácil realizar a comunicação com o aplicativo que foi desenvolvido no Kodular. E para o ESP32 se comunicar com o Firebase também foi utilizado o link do banco de dados e a chave API, aplicados na biblioteca utilizada, disponível no seguinte github: https://github.com/dahmadjid/Firebase-idf.

<img src="imagens PI3/firebase.PNG" style="width:500px;height:250px;">
<img src="imagens PI3/Kodular_dev_1.PNG" style="width:500px;height:250px;">
<img src="imagens PI3/Kodular_dev_2.PNG" style="width:500px;height:250px;">

# Hardware

O esquemático e roteamento da placa foi realizado no software Kicad. A placa foi desenvolvida com face dupla, e a transferência foi realizada com o método "transferência fotográfica de imagem". Para saber mais sobre o método acesse os seguintes links:
* https://tec-ci.com.br/blog/circuito-impresso/transferencia-fotografica-de-imagem-trilhas-circuito-impresso/

* https://portal.vidadesilicio.com.br/confeccionando-de-placas-de-circuito-impresso-com-tinta-fotossensivel/




