-- 1
CREATE TABLE IF NOT EXISTS company1(
    id INT,
    name VARCHAR NOT NULL,
    age INT NOT NULL,
    address VARCHAR(50),
    salary NUMERIC
);

-- 2
INSERT INTO company1 VALUES (1, NULL, 25, 'Mumbai', 50000);
INSERT INTO company1 VALUES (2, 'Aara', NULL, 'Pune', 40000);

-- 3
CREATE TABLE company3 (
    id INT NOT NULL,
    name VARCHAR NOT NULL,
    age INT UNIQUE,
    address VARCHAR(50),
    salary NUMERIC
);

-- 4
INSERT INTO company3 VALUES (1, 'Om', 25, 'Kohlapur', 30000);
INSERT INTO company3 VALUES (2, 'Aditya', 25, 'Gujarat', 35000);

-- 5
CREATE TABLE company4(
   id INT PRIMARY KEY,
   name VARCHAR,
   age INT,
   address VARCHAR(50),
   salary NUMERIC
);

-- 6
INSERT INTO company4 VALUES (1, 'Sian', 28, 'Chennai', 45000);
INSERT INTO company4 VALUES (1, 'Rebekah', 30, 'Bangalore', 50000);

-- 7
CREATE TABLE department(
    id INT PRIMARY KEY,
    name VARCHAR(50) NOT NULL
);

CREATE TABLE employee(
    id INT PRIMARY KEY,
    name VARCHAR,
    age INT,
    address VARCHAR(50),
    salary NUMERIC,
    dept_id INT REFERENCES department(id) ON DELETE CASCADE
);

-- 8
INSERT INTO department VALUES (1, 'HR');
INSERT INTO department VALUES (2, 'IT');
INSERT INTO department VALUES (3, 'Sales');

-- 9
INSERT INTO employee VALUES (1, 'Jonah', 26, 'Mumbai', 40000, 1);
INSERT INTO employee VALUES (2, 'Nihira', 29, 'Pune', 45000, 3);

-- 10
DELETE FROM department WHERE id = 1;

-- 11
CREATE TABLE company5(
   id INT,
   name TEXT,
   age INT,
   address VARCHAR(50),
   salary REAL CHECK (salary > 0)
);

-- 12
INSERT INTO company5 VALUES (1, 'Chandler', 27, 'New York', -5000);