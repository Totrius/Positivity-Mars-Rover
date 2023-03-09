
let tablicaId=["czZeroMinus", "czZeroPlus", "czJedenMinus", "czJedenPlus", "czDwaMinus", "czDwaPlus", "czTrzyMinus", "czTrzyPlus", "czCzteryMinus", "czCzteryPlus", "klapkaPojemnikaGora", "klapkaPojemnikaDol", "pojemnikObrotLewo", "pojemnikObrotPrawo"];
window.addEventListener("DOMContentLoaded", start);

function sendRequest(nazwaZapytania) {
    const zapytanie = new XMLHttpRequest();                  
    zapytanie.open("GET", nazwaZapytania);
    zapytanie.send(); 
    console.log(`wysylam: ${nazwaZapytania}`);
}

function start () {
    for (let i = 0; i<tablicaId.length; i++){
        document.getElementById(tablicaId[i]).addEventListener('mousedown', (event) =>{
            sendRequest(`/${tablicaId[i]}`);                
        });
        document.getElementById(tablicaId[i]).addEventListener('mouseup', (event) =>{
            sendRequest(`/servoStop`);
        });

    }
    document.getElementById("hClose").addEventListener('mousedown', (event) =>{
        sendRequest(`/hClose`);
    });
    document.getElementById("hClose").addEventListener('mouseup', (event) =>{
        sendRequest(`/hStop`);
    });
    document.getElementById("hOpen").addEventListener('mousedown', (event) =>{
        sendRequest(`/hOpen`);
    });
    document.getElementById("hOpen").addEventListener('mouseup', (event) =>{
        sendRequest(`/hStop`);
    });
}
