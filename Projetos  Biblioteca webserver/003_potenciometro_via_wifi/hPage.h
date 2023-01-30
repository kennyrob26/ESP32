
const char hPage[] =
R"=====(
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>LEDS</title>
    <style>
        body{
            background-color: rgb(65, 64, 64);
            font-family: Arial, Helvetica, sans-serif;
            text-align: center;
            color: rgba(255, 255, 255, 0.747);
        }
        main{
            margin: auto;
            width: 350px;
            padding: 3px 30px 30px 30px;
            border: 1px solid rgba(255, 255, 255, 0.336);
            box-shadow: 1px 1px 3px rgba(0, 0, 0, 0.425);
        }
        h1{
            text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.719);
        }
        p{
            font-size: 1.2em;
            font-weight: bold;
            text-shadow: 1px 1px 3px black;
        }
        p#barra{
            text-align: left;
            padding: 2px 5px 2px 5px;
            border: 1px solid rgba(255, 255, 255, 0.336);
            margin: auto;
        }

    </style>
</head>
<body>
    <h1>Controlando LEDs</h1>
    <main>

        <p id="valor">Potenciômetro: </p>
        <p id="barra"></p>

    </main>

    <script>

        atualiza();
        setInterval(atualiza, 100);
        function atualiza(){
            var req = new XMLHttpRequest();
            req.onreadystatechange = function(){
                if(req.readyState == 4 && req.status == 200){
                    var valor = document.getElementById("valor");
                    valor.innerHTML = "Potenciômetro: " + JSON.parse(req.responseText).leitura; 

                    var barra = (JSON.parse(req.responseText).leitura)/68;
                    p = document.getElementById("barra");
                    p.innerHTML = "";
                    for(i = 1; i <= barra; i++){
                        p.innerHTML += "|" 
                    }
                }

            }
            req.open('GET', 'http://10.0.0.125/leitura', true);
            req.send();
        }
    </script>
</body>
</html>
)=====";
