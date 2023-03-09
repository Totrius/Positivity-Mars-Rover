
let tablicaId=["czZeroMinus", "czZeroPlus", "czJedenMinus", "czJedenPlus", "czDwaMinus", "czDwaPlus", "czTrzyMinus", "czTrzyPlus", "czCzteryMinus", "czCzteryPlus", "klapkaPojemnikaGora", "klapkaPojemnikaDol", "pojemnikObrotLewo", "pojemnikObrotPrawo"];

let tablicaIdLazika=["lazikPrzod", "lazikTyl", "lazikObrotLewo", "lazikObrotPrawo"];
let tablicaIdKamerki=["kameraGora", "kameraDol", "kameraLewo", "kameraPrawo"];
let tablicaPomiarow = ["pomiarTemperatury", "pomiarWilgotnosci", "pomiarKoloru", "pomiarMasy"];
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

    for (let i = 0; i<tablicaIdLazika.length; i++){
        document.getElementById(tablicaIdLazika[i]).addEventListener('mousedown', (event) =>{
            sendRequest(`/${tablicaIdLazika[i]}`);                
        });
        document.getElementById(tablicaIdLazika[i]).addEventListener('mouseup', (event) =>{
            sendRequest(`/lazikStop`);
        });
    }
    for (let i = 0; i<tablicaIdKamerki.length; i++){
        document.getElementById(tablicaIdKamerki[i]).addEventListener('mousedown', (event) =>{
            sendRequest(`/${tablicaIdKamerki[i]}`);                
        });
        document.getElementById(tablicaIdKamerki[i]).addEventListener('mouseup', (event) =>{
            sendRequest(`/kameraStop`);
        });
    }

    for (let i = 0; i<tablicaPomiarow.length; i++){
        document.getElementById(tablicaPomiarow[i]).addEventListener('click', (event) =>{
            const zapytanie = new XMLHttpRequest();            //wyślijmy zapytanie jak poprzednio
            zapytanie.open("GET", `/${tablicaPomiarow[i]}`);
            zapytanie.send();
            zapytanie.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById(tablicaPomiarow[i]).innerHTML = this.responseText;
                }
            };                 
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
    document.getElementById("pomiary").addEventListener('click', (event) =>{
        sendRequest("/pomiary");
    });
}
