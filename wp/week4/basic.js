console.log("Hello World!");

let myName = "ToxRA";
const age = 19;

console.log(`My name is ${myName} and I am ${age} years old.`);


let a = 10;
let b = 5;

console.log(`Adding ${a} and ${b}: ${a+b}`)
console.log(`Substracting ${a} and ${b}: ${a-b}`)
console.log(`Multiplying ${a} and ${b}: ${a*b}`)
console.log(`Dividing ${a} and ${b}: ${a/b}`)

// const marks = 49;

// user input :  prompt("Enter marks:");
const marks = prompt("Enter marks:");

if(marks >= 50) {
    console.log("Passed");
}
else {
    console.log("Failed");
}


let i = 0;
while(i < 5) {
    console.log(i);
    i++;
}

function print(name) {
    console.log(name);
}

print("hello using python's print function!");

let fruit = ["Apple", "Banana", "Cherry"];
console.log(fruit);
console.log(fruit.length);


//Object

let student = {
    name: "Om",
    age: 5,
    course: "CSE"
};


console.log(student.name);
console.log(student.age);
console.log(student.course);