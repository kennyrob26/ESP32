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
            background-color: rgba(250, 235, 229, 0.651);
            font-family: Arial, Helvetica, sans-serif;
            margin: auto;
            text-align: center;
            color: rgb(229, 231, 255);
        }
        header{
            border: 1px solid;
            background-color: rgb(65, 65, 167);
            box-shadow: 0px 3px 5px rgba(0, 0, 0, 0.178);;

        }
        section{
            margin: auto;
            margin-top: 10px;
            margin-bottom: 10px;

            background-color: rgb(146, 167, 212);

            padding: 30px 10px 30px 10px;
            width: 150px;
            border: 1px solid rgba(255, 255, 255, 0.336);
            box-shadow: 2px 2px 6px rgba(0, 0, 0, 0.199);
        }
        h1{
            text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.719);
        }
        main{
            width: 200px;
            margin: auto;
            margin-top: 30px;
            padding: 3px;
        }
        section > p{
            font-size: 1.2em;
            font-weight: bold;
            margin: 2px;
            color: rgb(7, 23, 77);
            text-shadow: 2px 2px 5px rgba(207, 233, 231, 0.664);
        }
        .resultado{
            color: rgb(44, 74, 163);
        }

    </style>
</head>
<body>
    <header>
        <h1>Humidade e temperatura</h1>
    </header>

    <main>
        <section id="humi">
            <p>Humidade</p>
            <p class="resultado" id="humidade">00.00</p>
        </section>
        <section id="temp">
            <p >Temperatura</p>
            <p class="resultado" id="temperatura">00.00 </p>
        </section>
    </main>

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

        function onMessage(event){
            var mensagem    = String(event.data);

            var parametro   = mensagem[0];   //recebe t ou h
            var valor       = mensagem.substring(2,7);//recebe o valor da humidade ou temperatura

            var temperatura = document.getElementById("temperatura");
            var humidade    = document.getElementById("humidade");

            if(parametro == "t"){
                temperatura.innerText = valor + "°C";
            }else if(parametro == "h"){
                humidade.innerText = valor + "%";
            }

        }

        function onLoad(event){
            iniciarWebSocket();
        }



    </script>
</body>
</html>
)rawliteral";