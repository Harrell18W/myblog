// JavaScript Document

var posts = 0;

window.onload = function() {
	loadMain();
	loadPosts();
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
		posts = data.posts;
	};
	request.send();
	
}

function loadPosts() {
	
	var request = new XMLHttpRequest();
	request.open('GET', 'posts.json');
	request.overrideMimeType('application/json');
	request.onload = function() {
		var data = JSON.parse(request.responseText);
		for(var x = 0; x < posts; x++) {
			document.getElementById('posts').innerHTML = '<div class="post">\
							<h3>' + data[x].title + '</h3>\
							<h6>' + data[x].timestamp + '</h6>\
							<p>' + data[x].content + '</p>\
							</div>' + document.getElementById('posts').innerHTML;
		}
	};
	request.send();
	
}