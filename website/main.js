// JavaScript Document

function init() {
	loadMain();
}

function loadMain() {

	var request = new XMLHttpRequest();
	request.open('GET', 'main.json');
	request.overrideMimeType('application/json');
	request.onload = function() {
		var data = JSON.parse(request.responseText);
		document.getElementById('title').innerHTML = data.title;
		document.getElementById('motd').innerHTML = data.motd;
		document.getElementById('body').style.backgroundColor = data.bgColor;
	};
	request.send();
	
}