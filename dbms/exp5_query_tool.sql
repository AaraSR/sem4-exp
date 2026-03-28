-- 1
CREATE TABLE sales_order (
	order_no VARCHAR(6),
	order_date DATE,
	client_no VARCHAR(6),
	dely_add VARCHAR(25),
	salesman_no VARCHAR(6),
	dely_type CHAR(1),
	billed_yn CHAR(1),
	dely_date DATE,
	order_status VARCHAR(30)
);

-- 2
INSERT INTO sales_order VALUES
	('100','2020-01-12','C001','Bandra','S001','A','Y','2020-04-23','Despatching'),
	('200','2019-12-22','C002','Malad','S002','B','N','2020-03-02','Out for delivery'),
	('300','2018-08-10','C003','Virar','S003','A','Y','2018-09-30','Reached'),
	('400','2018-03-15','C004','Kurla','S004','A','Y','2018-04-25','Complete'),
	('500','2020-05-09','C005','Vasai','S005','B','N','2020-06-20','Done');

SELECT * FROM sales_order;

-- 3
SELECT client_no FROM sales_order
WHERE client_no LIKE '_0%';

-- 4
SELECT * FROM sales_order
WHERE dely_add LIKE '_u%';

-- 5
SELECT * FROM sales_order
WHERE dely_add ILIKE 'mumbai'
ORDER BY client_no;

-- 6
SELECT client_no FROM sales_order;

-- 7
SELECT * FROM sales_order
WHERE EXTRACT(MONTH FROM order_date) = 1;

-- 8
SELECT * FROM sales_order
WHERE client_no IN ('C001','C002');

-- 9


-- 10


-- 11
SELECT COUNT(*) FROM sales_order;

-- 12


-- 13


-- 14


-- 15
SELECT order_no, EXTRACT(DAY FROM order_date) AS day, TO_CHAR(order_date,'Month') AS month 
FROM sales_order;

-- 16
SELECT TO_CHAR(order_date,'DD-Month-YY') FROM sales_order;

-- 17
SELECT TO_CHAR(dely_date,'Month') AS month, EXTRACT(DAY FROM dely_date) AS day FROM sales_order;

-- 18
SELECT CURRENT_DATE + INTERVAL '15 days' FROM sales_order
LIMIT 1;

-- 19
SELECT order_no, dely_date - CURRENT_DATE AS days_elapsed FROM sales_order;


SELECT * FROM sales_order;