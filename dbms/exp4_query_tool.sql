-- 1
CREATE TABLE client_master (
    client_no VARCHAR(6),
    client_name VARCHAR(20),
    address VARCHAR(30),
    city VARCHAR(15),
    pincode NUMERIC(8),
    cm_state VARCHAR(15),
    bal_due NUMERIC(10,2)
);


CREATE TABLE product_master (
    product_no VARCHAR(6),
    description VARCHAR(15),
    profit_percent NUMERIC(4,2),
    unit_measure VARCHAR(10),
    qty_on_hand NUMERIC(8),
    reorder_level NUMERIC(8),
    sell_price NUMERIC(8,2),
    cost_price NUMERIC(8,2)
);

-- 2
INSERT INTO client_master VALUES
	('C001','Sam','Kothrud','Pune',411077,'Maharashtra',10000.23),
	('C002','John','Kurla','Mumbai',400087,'Maharashtra',50000.55),
	('C003','Jack','Kishan Nagar','Gandhi Nagar',400055,'Gujarat',25000.93),
	('C004','Ann','Charminar','Hyderabad',400090,'Andhra Pradesh',77000.00),
	('C005','Pitter','Bandra','Mumbai',400045,'Maharashtra',88000.23),
	('C006','Nick','Vasai','Mumbai',400077,'Maharashtra',10000.23);

INSERT INTO product_master VALUES
	('P1','Laptop',30.12,'Low',1200,13000,60000.23,50000.34),
	('P2','Refrigerator',30.92,'Medium',4354,42255,42423.24,35000.55),
	('P3','Hard disk',10.00,'High',5678,8723,3500.00,2500.00),
	('P4','Mixture',40.12,'Low',2535,44000,10000.23,8000.34),
	('P5','Washing machine',35.12,'High',9000,90000,40000.99,28000.90);


SELECT * FROM client_master;
SELECT * FROM product_master;

-- 3
SELECT client_name FROM client_master;

-- 4
SELECT * FROM client_master;

-- 5
SELECT client_name, city FROM client_master;

-- 6
SELECT description FROM product_master;

-- 7
SELECT * FROM client_master
WHERE city ILIKE 'mumbai';

-- 8
UPDATE client_master
SET city = 'Mumbai'
WHERE client_no = 'C001';

-- 9
UPDATE client_master
SET bal_due = 10000
WHERE client_no = 'C005';

-- 10
UPDATE product_master
SET cost_price = 3000
WHERE description ILIKE 'hard disk';

-- 11
DELETE FROM product_master
WHERE qty_on_hand < 5500;

-- 12
DELETE FROM client_master
WHERE cm_state = 'Andhra Pradesh';

SELECT * FROM client_master;
SELECT * FROM product_master;