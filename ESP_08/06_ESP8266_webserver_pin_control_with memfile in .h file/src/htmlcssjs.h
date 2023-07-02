//Our HTML webpage contents in program memory
const char MAIN_page[] PROGMEM = R"====(
<!DOCTYPE html>
<!--[if lt IE 7]>      <html class="no-js lt-ie9 lt-ie8 lt-ie7"> <![endif]-->
<!--[if IE 7]>         <html class="no-js lt-ie9 lt-ie8"> <![endif]-->
<!--[if IE 8]>         <html class="no-js lt-ie9"> <![endif]-->
<!--[if gt IE 8]>      <html class="no-js"> <!--<![endif]-->
<html>

<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>Calculator using GenetatorJs</title>
    <meta name="description" content="">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="style.css">
    <style>
    * {
  box-sizing: border-box;
  margin: 0;
  padding: 0;
}
body {
  font-size: 16px;
  color: white;
  background-color: #333;
  font-family: Sans serif, Consolas;
}

#buttonControl {
  display: flex;
  flex-direction: column;
  gap: 1em;
  margin: 1em auto;
}

#app {
  display: flex;
  flex-direction: column;
  justify-items: center;
  gap: 1em;
}

button {
  max-width: 5em;
  font-size: 2em;
  padding: 0.5em;
  cursor: pointer;
  border: 0;
  box-shadow: 2px 2px 5px rgba(250, 230, 230, 0.5);
  border-radius: 8px;
}

button[data-state~="on"] {
  background-color: green !important;
}
button[data-state~="off"] {
  background-color: red !important;
}

    </style>
</head>

<body style="background-color:#333;">
    <div id="app" class="app">
<div id="buttonControl">
    <h1>Led toggle dashboard</h1>
    <p>
        <h2>LED Buildin</h2>
        <a href=\"/?led=0\">Turn it ON!</a
        <button onclick="handleButtonClick(this)" data-state="on">On</button>
    </p>
    <p>
        <h2>LED Buildin</h2>
        <a href=\"/?led=1\">Turn it OFF!</a
        <button onclick="handleButtonClick(this)" data-state="off">Off</button>
    </p>
</div>
    </div>

    <script>
        
function handleButtonClick(e){
    var button = e;
    var state = button.innerText
    console.log(state)
    var xhr = new XMLHttpRequest();
    var url='/led?state=' + state;
    xhr.open('GET',url , true);
    xhr.send();
}
    </script>

</body>

</html>




)====";