-- Active: 1761461509284@@127.0.0.1@3306@pertemuan6
CREATE TABLE customers (
    ID INT PRIMARY KEY,
    NAME VARCHAR(50),
    AGE INT,
    ADDRESS VARCHAR(100),
    SALARY DECIMAL(10, 2)
);

INSERT INTO customers (`ID`, `NAME`, `AGE`, `ADDRESS`, `SALARY`) VALUES
(1, 'Ramesh', 32, 'Ahmedabad', 2000.00),
(2, 'Khilan', 25, 'Delhi', 1500.00),
(3, 'kaushik', 23, 'Kota', 2000.00),
(4, 'Chaitali', 25, 'Mumbai', 6500.00),
(5, 'Hardik', 27, 'Bhopal', 8500.00),
(6, 'Komal', 22, 'MP', 4500.00);

CREATE VIEW HighSalaryCustomers AS
SELECT NAME, SALARY, AGE
FROM customers
WHERE SALARY > 2000.00;

CREATE VIEW SalaryPercentageView AS
SELECT 
    NAME, 
    (SALARY / (SELECT SUM(SALARY) FROM customers)) * 100 AS Percentage
FROM customers
ORDER BY Percentage DESC;

CREATE TABLE salary_log (
    IDLog INT AUTO_INCREMENT PRIMARY KEY,
    date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    previous_salary DECIMAL(10,2),
    next_salary DECIMAL(10,2)
);

DELIMITER //
CREATE TRIGGER AfterSalaryUpdate
AFTER UPDATE ON customers
FOR EACH ROW
BEGIN
    IF OLD.SALARY <> NEW.SALARY THEN
        INSERT INTO salary_log (date, previous_salary, next_salary)
        VALUES (NOW(), OLD.SALARY, NEW.SALARY);
    END IF;
END; //
DELIMITER ;

DELIMITER //
CREATE TRIGGER BeforeInsertSalary
BEFORE INSERT ON customers
FOR EACH ROW
BEGIN
    IF NEW.SALARY > 8500 THEN
        SET NEW.SALARY = 8500;
    ELSEIF NEW.SALARY < 1500 THEN
        SET NEW.SALARY = 1500;
    END IF;
END; //
DELIMITER ;

DELIMITER //
CREATE TRIGGER BeforeUpdateSalary
BEFORE UPDATE ON customers
FOR EACH ROW
BEGIN
    IF NEW.SALARY > 8500 THEN
        SET NEW.SALARY = 8500;
    ELSEIF NEW.SALARY < 1500 THEN
        SET NEW.SALARY = 1500;
    END IF;
END; //
DELIMITER ;

INSERT INTO customers (ID, NAME, AGE, ADDRESS, SALARY) 
VALUES (7, 'Anton', 24, 'Bandung', 1000.00);

INSERT INTO customers (ID, NAME, AGE, ADDRESS, SALARY) 
VALUES (8, 'Siti', 29, 'Surabaya', 10000.00);