function handleButtonClick(e){
    var button = e;
    var state = button.innerText
    console.log(state)
    var xhr = new XMLHttpRequest();
    var url='/led?state=' + state;
    xhr.open('GET',url , true);
    xhr.send();
}