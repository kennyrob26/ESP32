# ESP32

Iniciando os estudos com o microcontrolador esp32, os artigos de introdução utilizados podem ser encontrados em: 

**ESP32: Detalhes internos e pinagem - Blog do fernando K**
https://www.fernandok.com/2018/03/esp32-detalhes-internos-e-pinagem.html

**Introdução à Programação do ESP32 - Blog do fernando K**
https://www.fernandok.com/2018/10/introducao-programacao-do-esp32.html

**Conhecendo o ESP32 - Curto Circuito**
https://curtocircuito.com.br/blog/Categoria%20IoT/conhecendo-esp32

## Observações importantes:
1. Sempre se atentar a pinagem do ESP32, pois existem diferentes modelos, com diferentes quantidades de pinos. Então sempre tenha o dataseet em mãos
2. Não se esquecer que alguns pinos são apenas para input, outros apenas output.. e assim por diante. Lembrando que em alguns modelos não é possivel utilizar o pino gpio0
3. Quando for gravar um novo código no ESP, quando aparecer a mesagem "connecting........", pressionar o botão BOOT.

## Informações Importantes (fonte: blog do Fernando K)
1. O INPUT não funciona apenas no GPIO0
2. O OUTPUT não funciona nas GPIOs 34 e 35, que são VDET 1 e 2
3. **Muito importante:** Alguns pinos iniciam com **HIGH**, diferente do arduino, que sempre inicia em **LOW**, são eles os pinos GPIO 0, 1 , 3, 5, 9, 10,  11, 14 e 15
4. **Muito importante:** As GPIOs 01, 06, 07, 08 e 11 apresentam uma pequena oscilação quando o ESP inicia, então é importante evitar essas porta quando trabalhar com relés.
