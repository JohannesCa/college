var pageTitle = document.querySelector(".header")
var color = 0x00;
var shift = true;

function cycleColor(past_value) {
  if (past_value == 0xffffff) {
      color = 0;
      return "#000000";
  }
  color = color + 1;
  var r = color&0xff0000
  r = r >> 4
  var g = color&0xff00
  g = g >> 4
  var b = color&0xff
  return "rgb(" + r + ", " + g + ", " + b + ")";
}

function randomColor() {
  var r = Math.floor(Math.random() * 255);
  var g = Math.floor(Math.random() * 255);
  var b = Math.floor(Math.random() * 255);
  return "rgb(" + r + ", " + g + ", " + b + ")";
}

// var refreshIntervalId = setInterval(function () {
//       pageTitle.style.color = randomColor();
//     }, 300);

pageTitle.addEventListener("click", function() {
  this.style.color = randomColor();
});
