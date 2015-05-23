var hostnames = [
	"urist.is-a-geek.com",
	"68.103.234.45",
	"95.96.39.104",
	"108.28.90.228"
];

var ports = {
	"urist.is-a-geek.com": "1235",
	"108.28.90.228": "80"
};

var tags = {
};

var data = {
};

function qs(selecta) {
	return document.querySelector(selecta);
}

function init(root, i) {
	var host = hostnames[i];
	tags[host] = i;
	console.log("init " + host);
	var node = document.createElement("tr");
	node.id = "id"+i;
	root.appendChild(node);

	update(host);
}

function update(host) {
	var d = data[host] || {};
	var version = "";
	if (d.dfhack_version) {
		version += d.dfhack_version;
	}

	if (d.webfort_version) {
		version += (version? "-" : "") + d.webfort_version;
	}

	if (version === "") {
		version = "Unknown";
	}

	var c = tags[host];
	var node = qs("#id" + c);
	node.innerHTML = ""+
		"<td>" + host + "</td>" +
		"<td>" + (d.status || "Waiting...") + "</td>" +
		"<td>" + (d.active_players || 0) + "</td>" +
		"<td>" + version + "</td>";
}

function makeLoad(host) {
	return function() {
		if (this.readyState == 4) {
			if (this.status == 200) {
				var j = JSON.parse(this.responseText);
				if (j.is_somebody_playing) {
					j.status = (j.current_player || "Somebody") + " is playing";
				} else {
					j.status = "Nobody is playing";
				}
				data[host] = j;
			} else {
				data[host] = {status: "Offline"};
			}
			update(host);
		}
	};
}

var countDown = 0;
function tick() {
	qs(".countdown").innerHTML = countDown + "...";
	if (countDown < 1) {
		for (var i=0; i < hostnames.length; ++i) {
			var host = hostnames[i];
			var port = ports[host] || "1234";
			var r = new XMLHttpRequest();
			r.onreadystatechange = makeLoad(host); // TODO: cache these maybe?
			r.open("get", "http://" + host + ":" + port + "/api/status.json");
			r.send();
		}
		countDown = 10;
	} else {
		countDown--;
	}
	setTimeout(tick, 1000);
}

tick();

var root = qs(".insert-servers");

for (var i=0; i < hostnames.length; ++i) {
	init(root, i);
}

