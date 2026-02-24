let student = {
    name: "Rehan",
    age: 20
};

for (let key in student) {
    console.log(key);
    console.log(student[key]);
}

for (let i = 0; i < 5; i++) {
    console.log("i =", i);
}

let fruits = ['apple', 'mango', 'strawberry'];

for (let fruit of fruits) {
    console.log(fruit);
}

function add (num1, num2) {
    return num1 + num2;
}

var Add = (num1, num2) => num1 + num2;

let sum = Add(1, 2)
console.log(sum);