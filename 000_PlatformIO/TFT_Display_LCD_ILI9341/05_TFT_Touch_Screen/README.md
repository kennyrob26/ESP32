# Trabalhando com Touch Capacitivo

Este é um breve exemplo que tentei deixar o mais trivial possível, para isto este exemplo consiste em utilizar apenas **1 botão** com um texto que é descrito sempre que o usuário pressiona este botão. Também recebemos uma mensagem via serial sempre que o botão é pressionado  
Para começar recomendo fortemente assistir este [vídeo](https://www.youtube.com/watch?v=9vTrCThUp5U) que demonstra em detalhes como configurar a biblioteca [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) para a utilização de touch screen.  
Este exemplo é baseado no [Keypad_240x320](https://github.com/Bodmer/TFT_eSPI/tree/master/examples/320%20x%20240/Keypad_240x320) fornecido pela própria biblioteca, mas como dito tentei simplificar ao máximo por ser o meu primeiro contato com touch screen.  


## Algumas coisas importantes

Vou apontar alguns pontos importantes, além de alguns métodos que tive dificuldade de encontrar documentação

`#define CALIBRATION_FILE "/TouchCalData1"` -> Salva as configurações de calibração do touch no arquivo /TouchCalDat1 (cria este arquivo se não existir).  

`#define REPEAT_CAL false` -> Define se o display deverá ter seu touch calibrado a cada inicialização do microcontrolador, se `true` ele irá pedir para calibrar o display a cada inicialização, se `false`, ele calibra um única vez e salva as configurações no arquivo definido em `CALIBRATION_FILE` visto anteriormente.  

`touch_calibrate();` -> É uma função padrão da biblioteca que calibra o display.  
tft.getTouch(&t_x, &t_y) -> Retorna `true` se algum local da tela for pressionado, e **modifica** os valores das variáveis t_x e t_y com as coordenadas do toque.  

### A Classe TFT_eSPI_Button

`TFT_eSPI_Button botao;` -> Instância um objeto da classe chamado botao  

### Métodos importantes TFT_eSPI_Button

`botao.initButton(&tft, 120, 130, 100, 60, TFT_WHITE, TFT_BLUE, TFT_WHITE, "TESTE", 1);` -> Inicia o botão com as propriedades setadas.  

`botao.drawButton();` -> Desenha o botão setado anteriormente, ele pode receber `false` que desenhará conforme setado e `true` para desenhar com as cores invertidas.  

`botao.contains(t_x, t_y)` -> Verifica se o botão está na area pressionada com as coordenadas (t_x, t_y).  
`botao.press(true)` -> Recebe um booleano que permite alterar o estado do botão.  
`botao.justPressed()` -> Retorna `true` se o botão foi pressionado recentemente.  
`botao.justReleased()` -> Retorna `true` se o usuário soltou o botão.


