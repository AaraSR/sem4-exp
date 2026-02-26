// document.getElementById("para");
// document.getElementsByClassName("myclass");
// document.getElementsByTagName("p");

// console.log(document);

// WINDOW EVENTS
document.addEventListener("DOMContentLoaded", function () {
    console.log("Window Loaded");
});

window.addEventListener("resize", function () {
    console.log("Window Resized");
});

window.addEventListener("scroll", function () {
    console.log("Window Scrolled");
});

// COMMON EVENTS
document.getElementById("clickBtn").addEventListener("click", function () {
    alert("Button Clicked!");
});

let focusInput = document.getElementById("focusInput");

focusInput.addEventListener("focus", function () {
    focusInput.style.backgroundColor = "lightgreen";
});

focusInput.addEventListener("blur", function () {
    focusInput.style.backgroundColor = "white";
});

// KEYBOARD EVENTS
let keyboardInput = document.getElementById("keyboardInput");

keyboardInput.addEventListener("keydown", function (e) {
    console.log("Key Down:", e.key);
});

keyboardInput.addEventListener("keyup", function (e) {
    console.log("Key Up:", e.key);
});

keyboardInput.addEventListener("keypress", function (e) {
    console.log("Key Pressed:", e.key);
});

// FORM EVENTS
let form = document.getElementById("myForm");
let nameInput = document.getElementById("nameInput");

form.addEventListener("submit", function (e) {
    e.preventDefault();
    alert("Form Submitted: " + nameInput.value);
});

nameInput.addEventListener("change", function () {
    console.log("Input Changed");
});

nameInput.addEventListener("input", function () {
    console.log("Typing:", nameInput.value);
});

// MOUSE EVENTS
let mouseBox = document.getElementById("mouseBox");

mouseBox.addEventListener("mouseenter", function () {
    mouseBox.style.backgroundColor = "orange";
});

mouseBox.addEventListener("mouseleave", function () {
    mouseBox.style.backgroundColor = "lightblue";
});

// CLIPBOARD EVENTS
let clipboardInput = document.getElementById("clipboardInput");

clipboardInput.addEventListener("copy", function () {
    console.log("Text Copied");
});

clipboardInput.addEventListener("cut", function () {
    console.log("Text Cut");
});

clipboardInput.addEventListener("paste", function () {
    console.log("Text Pasted");
});

// DRAG AND DROP EVENTS
let dragItem = document.getElementById("dragItem");
let dropZone = document.getElementById("dropZone");

dragItem.addEventListener("dragstart", function () {
    console.log("Drag Started");
});

dragItem.addEventListener("dragend", function () {
    console.log("Drag Ended");
});

dropZone.addEventListener("dragover", function (e) {
    e.preventDefault(); // Allow drop
});

dropZone.addEventListener("drop", function () {
    dropZone.appendChild(dragItem);
    console.log("Item Dropped");
});