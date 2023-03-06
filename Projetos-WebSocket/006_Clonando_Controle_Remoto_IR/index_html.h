const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Servidor Web Socket</title>
    <style>
        body{
            background-color: rgb(65, 64, 64);
            font-family: Arial, Helvetica, sans-serif;
            width: 350px;
            margin: auto;
            text-align: center;
            color: rgba(255, 255, 255, 0.747);
        }
        section{
            margin: auto;
            padding: 10px;
            width: 120px;
            border: 1px solid rgba(255, 255, 255, 0.336);
            box-shadow: 1px 1px 3px rgba(0, 0, 0, 0.425);

        }
        h1{
            text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.719);
        }
        p{
            font-size: 1.2em;
            font-weight: bold;
            margin: 5px 0px 5px 0px;
            text-shadow: 1px 1px 3px black;
        }
        #onOff{
            color: red;
        }
        div{
            display: inline-block;
            border: 1px solid rgba(255, 255, 255, 0.336);
            padding: 2px;
            font-size: 10px;
        }
        div#volume{
            margin-right: 0px;
        }
        button#mute{
            
        }
        div#canal{
            margin-left: 0px;

        }
        p#tv{
            padding-top: 30px;
        }
        

    </style>
</head>
<body>
    <h1>Controle TV</h1>
    <section>
        <p><button class="botao" id="onOff">⏻</button></p>
        <p><button class="botao" id="menu">Menu</button></p>
        <p><button class="botao" id="input">input</button></p>
        <div id="volume">
            <p>VOL</p>
            <p><button class="botao" id="vmais">+</button></p>
            <p><button class="botao" id="vmenos">-</button></p>
           
        </div>

        <button class="botao" id="mute">🔇</button>

        <div id="canal">
            <p>CH</p>
            <p><button class="botao" id="cmais">⇧</button></p>
            <p><button class="botao" id="cmenos">⇩</button></p>
        </div>
        <p><button class="botao" id="cima">⬆️</button></p>
        <p>
            <button class="botao" id="esquerda">⬅️</button>
            <button class="botao" id="ok">🆗</button>
            <button class="botao" id="direita">➡️</button>
        </p>
        <p><button class="botao" id="baixo">⬇️</button></p>
        <p id="tv">TV</p>
    </section>

    <script>
        var gateway = `ws://${window.location.hostname}/ws`;
        var websocket;
        window.addEventListener('load', onLoad);



        function iniciarWebSocket(){
            console.log('Tentando iniciar uma conexão websocket');
            websocket = new WebSocket(gateway);
            websocket.onopen = onOpen;
            websocket.onclose = onClose;
            websocket.onmessage = onMessage;
        }

        function onOpen(event){
            console.log("Conexão aberta");
            
        }

        function onClose(event){
            console.log("A conexão foi fechada");
            //Ou seja, se a conexão for fechada ele inicia novamente em 2 segundos
            setTimeout(iniciarWebSocket, 2000);
        }

        //Esse projeto não recebe mensagens, apenas envia
        function onMessage(event){

        }

        function onLoad(event){
            iniciarWebSocket();
            checaBotao();
        }

        function checaBotao(){
            const botao = document.getElementsByClassName("botao");
            for(var i = 0; i < botao.length; i++){
                botao[i].addEventListener('click', pressionou);
            }

            //O trecho de código a baixo foi substituido pela const botao
            //Deixarei ele comentado para consultados posteriores,
            //o laço for gera menos linhas de códigos, mas pode ser um pouco mais
            //dificil de entender
            /*
            var m = document.getElementById('menu');
            var vmais = document.getElementById('vmais');
            var vmenos = document.getElementById('vmenos');

            m.addEventListener('click', pressionou);
            vmais.addEventListener('click', pressionou);
            vmenos.addEventListener('click', pressionou);
            */
        }

        //A função pressionou recebe pega o id do elemento pressionado e passa para o servidor
        function pressionou(event){
          var mensagem = event.target.id
          websocket.send(mensagem);
        }

        //Trecho de código antigo que foi substituido por pressionou
        //Esse trecho de código é mais fácil de entender, 
        //mas gera muitas linhas de código conforme a quantidade de botões aumenta
        /*
        function menu(){
            websocket.send('menu');
        }
        function mais(){
            websocket.send('vmais');
        }
        function menos(){
            websocket.send('vmenos');
        }
        */
    </script>
</body>
</html>
)rawliteral"; 