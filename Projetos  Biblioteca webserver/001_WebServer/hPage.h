
const char hPage[] =
R"=====(
    <!DOCTYPE html>
    <html lang="pt-BR">
    <head>
        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Somando números</title>
        <style>
            h1{
                font-family: Arial, Helvetica, sans-serif;
                font-size: 2em;
                text-align: center;
            }
            #btn{
                background-color: green;
                color: white;
            }
        </style>
    </head>
    <body>
        <h1>Somando valores</h1>
        <input type="number" name="txtn1" id="txtn1" > +
        <input type="number" name="txtn2" id="txtn2">
        <input type="button" value='somar' onclick="botao()" id='btn'>
        <p>Resultado</p>
        <script>
            var txtn1 = window.document.getElementById('txtn1')
            var txtn2 = window.document.getElementById('txtn2')
            var res = window.document.getElementsByTagName('p')[0]
            function botao(){
                var n1 = Number(txtn1.value)
                var n2 = Number(txtn2.value)
                var s = n1 + n2
                res.innerHTML = `O resultado da soma entre ${n1} e ${n2} é <strong>${s}</strong>`
            }
        </script>
    </body>
    </html>
)=====";
