# PI3_2022_1: Vaso Inteligente
O objetivo deste projeto é implementar um vaso inteligente baseado em Internet das Coisas, que irá monitorar os parâmetros de umidade do solo, luminosidade e temperatura de uma planta, e a partir destes parâmetros avaliar o estado da planta, com base em um banco de dados que contenha informações de espécies de plantas, ou dados personalizados pelo usuário. Detectando o estado da planta, será gerada uma expressão facial em um display contido no vaso, que representará esse estado, como por exemplo, em caso de falta de água para a planta, o vaso exibiria uma expressão de sede. O usuário poderá selecionar configurar os parâmetros da planta através do aplicativo de celular. Essa configuração poderá ser manual ou automática (selecionando a espécie de planta no aplicativo). 



<img src="imagens PI3/Diagrama PI3 Vaso Inteligente.png" style="width:800px;height:300px;">


# Pesquisa bibliográfica

Os links a seguir referem-se a pesquisa sobre os parâmetros de umidade, temperatura e luminosidade para os cuidados com diferentes espécies de plantas. 
Esses parâmetros foram utilizados paraentender quais parâmetros medir e como trabalhá-los.

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

---------


# planta-jade

https://www.jardineiro.net/plantas/planta-jade-crassula-ovata.html
https://portalvidalivre.com/articles/44
https://guiadassuculentas.com/suculenta-jade-saiba-tudo-sobre-essa-planta/
https://www.picturethisai.com/pt/care/Crassula_ovata.html#:~:text=Forneça%20temperatura%20adequada%20(%2025%20℃,luz%20(luz%20difusa%20brilhante).
https://www.noticiasdejardim.com/plantas-de-interior/crassula-ovata-arvore-de-jade-uma-especie-muito-facil-de-cultivar/

-------------

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

## DHT11: sensor de temperatura e umidade

<img src="imagens PI3/dht11.jpg" style="width:381px;height:381px;">

## LDR 5mm
## Higrômetro HL-69

<img src="imagens PI3/hl69.jpg" style="width:400px;height:400px;">

# Desenvolvimento

## Firmware

O desenvolvimento ocorreu no microcontrolador ESP32-WROOM-32, da Espressif, utilizando o  framework oficial da Espressif, o ESP-IDF, que é voltado para o desenvolvimento de aplicações parar toda a família ESP32. Foi utilizada a extensão ESP-IDF no editor de códigos Visual Studio Code. 
A linguagem de programação utilizada no firmware foi C++/C. Os componentes do framework ESP-IDF são disponibilizados em C, porém, devido o uso de uma biblioteca em C++, necessária para comunicação com o banco de dados.

**Github Espressif**: https://github.com/espressif
**Github Espressif ESP-IDF**: https://github.com/espressif/esp-idf
**Biblioteca utilizada para o DHT11**: https://github.com/UncleRus/esp-idf-lib/tree/master/components
**Biblioteca utilizada para o Google Firebase Realtime Database**: https://github.com/dahmadjid/Firebase-idf 

# Display oled SSD1306 128x64

O display utilizado foi o oled SSD1306 de 128x64. As animações para o display foram desenhadas no software Inkscape, com a área de 128x64px, exportadas para PNG, e em seguida convertida para outra extensão bitmap, a extensão XBM, respeitando a função da biblioteca para display SSD1306 utilizada no firmware, ssd1306_load_xbm. É importante observar quais formatos as funções aceitam quando utilizar bibliotecas de terceiros, caso contrário a imagem será exibida no display de forma distorcida, devido a forma como os bits são dispostos em cada tipo de extensão bitmap. 

## Armazenamento de dados e aplicativo de celular
Para armazenar os dados do aplicativo e dados lidos dos sensores do ESP32, e agilizar a comunicação com o aplicativo foi utilizada a ferramenta do Google Firebase.
O Firebase é uma plataforma para agilizar a criação e engajamento de aplicativos. Foi criado um projeto no Google Firebase, no qual foi vinculado o aplicativo de celular criado para o Vaso Inteligente. E para armazenar os dados e sincronizar em tempo real, tanto com o aplicativo quanto com o ESP32, foi utilizada a ferramenta Firebase Realtime Database. O Firebase Realtime Database é um banco de dados NoSQL hospedado na nuvem. Com ele, você armazena e sincroniza dados JSON entre os usuários em tempo real.
O aplicativo foi desenvolvido na plataforma Kodular, através de blocos lógicos de programação. Com o link do Realtime Database e a chave de API fornecida na criação do projeto no Firebase, além de algumas configurações de regras, é fácil realizar a comunicação com o aplicativo que foi desenvolvido no Kodular. E para o ESP32 se comunicar com o Firebase também foi utilizado o link do banco de dados e a chave API, aplicados na biblioteca utilizada, disponível no seguinte github: https://github.com/dahmadjid/Firebase-idf.

<img src="imagens PI3/firebase.PNG" style="width:500px;height:250px;">
<img src="imagens PI3/Kodular_dev_1.jpg" style="width:500px;height:250px;">
<img src="imagens PI3/Kodular_dev_2.jpg" style="width:500px;height:250px;">




