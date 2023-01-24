
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
        button.on{
            background-color: green;
            margin: 3px;
            padding: 4px;
            color: white;
        }
        button.off{
            background-color: red;
            margin: 3px;
            padding: 4px;
            color: white;
        }
    </style>
</head>
<body>
    <h1>Controlando LEDs</h1>
    <main>

        <p>LED 1: <button class="on" onclick="led1oN()">ON</button><button class="off" onclick="led1oFF()">OFF</button></p>
        <p>LED 2: <button class="on" onclick="led2oN()">ON</button><button class="off" onclick="led2oFF()">OFF</button></p>
        <p>LED 3: <button class="on" onclick="led3oN()">ON</button><button class="off"onclick="led3oFF()">OFF</button></p>
        <p>LED 4: <button class="on" onclick="led4oN()">ON</button><button class="off" onclick="led4oFF()">OFF</button></p>
        <p>LED 5: <button class="on" onclick="led5oN()">ON</button><button class="off" onclick="led5oFF()">OFF</button></p>
        <p>LED 6: <button class="on" onclick="led6oN()">ON</button><button class="off" onclick="led6oFF()">OFF</button></p>
    </main>

    <script>
        function led1oN(){
            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open('GET', 'http://10.0.0.125/led1oN', true);
            xmlhttp.send();
    }
        function led2oN(){
            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open('GET', 'http://10.0.0.125/led2oN', true);
            xmlhttp.send();
        }
        function led3oN(){
            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open('GET', 'http://10.0.0.125/led3oN', true);
            xmlhttp.send();
        }
        function led4oN(){
            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open('GET', 'http://10.0.0.125/led4oN', true);
            xmlhttp.send();
        }
        function led5oN(){
            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open('GET', 'http://10.0.0.125/led5oN', true);
            xmlhttp.send();
        }
        function led6oN(){
            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open('GET', 'http://10.0.0.125/led6oN', true);
            xmlhttp.send();
        }

        function led1oFF(){
            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open('GET', 'http://10.0.0.125/led1oFF', true);
            xmlhttp.send();
        }
        function led2oFF(){
            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open('GET', 'http://10.0.0.125/led2oFF', true);
            xmlhttp.send();
        }
        function led3oFF(){
            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open('GET', 'http://10.0.0.125/led3oFF', true);
            xmlhttp.send();
        }
        function led4oFF(){
            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open('GET', 'http://10.0.0.125/led4oFF', true);
            xmlhttp.send();
        }
        function led5oFF(){
            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open('GET', 'http://10.0.0.125/led5oFF', true);
            xmlhttp.send();
        }
        function led6oFF(){
            var xmlhttp = new XMLHttpRequest();
            xmlhttp.open('GET', 'http://10.0.0.125/led6oFF', true);
            xmlhttp.send();
        }

    </script>
</body>
</html>
)=====";
