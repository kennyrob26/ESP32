# Trabalhando com PWM
Antes de tudo é importante entendermos 3 parâmetros:
1. **Canal PWM:** o ESP 32 possui 16 canais PWM que podem variar de 0 a 15. Basicamente, podemos dizer que cada canal pode ser configurado de forma independente, e sempre que desejarmos utilizar aquela configuração utilizamos esse canal.
2. **Frequência de PWM:** também trbalha com 16 bits, com frequência que podem variar de 0 a 40MHz
3. **Ciclo de trabalho:** é a resolução que vamos trabalhar, que também pode ser de até 16 bits, para leds 8 bits é interressante, pois conseguimos variar a intensidade de 0 a 255, o que casa perfeitamente com o padrão RGB ex: cor branca (R =255, G=255, B=255) 

## Métodos para trabalhar com PWM

**`ledcSetup(canal, frequencia, cicloDeTrabalho);`**
São os parâmetros que vimos a cima

**`ledcAttachPin(GPIO, canal);`**
**GPIO:** é o pino de saida do pwm
**canal:** é qual canal vamos utilizar

**`ledcWrite(canal, valor);`**
**canal:** é o canal que definimos
**valor:** como estamos trabalhando com 8 bits, o valor pode variar de 0 a 255
