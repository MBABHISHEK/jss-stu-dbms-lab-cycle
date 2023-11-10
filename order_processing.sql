CREATE DATABASE order_processing;
USE order_processing;

CREATE TABLE Customers (
    cust_id INT PRIMARY KEY,
    cname VARCHAR(35) NOT NULL,
    city VARCHAR(35) NOT NULL
);

CREATE TABLE Orders (
    order_id INT PRIMARY KEY,
    odate DATE NOT NULL,
    cust_id INT,
    order_amt INT NOT NULL,
    FOREIGN KEY (cust_id) REFERENCES Customers(cust_id) ON DELETE CASCADE
);

CREATE TABLE Items (
    item_id INT PRIMARY KEY,
    unitprice INT NOT NULL
);

CREATE TABLE OrderItems (
    order_id INT NOT NULL,
    item_id INT NOT NULL,
    qty INT NOT NULL,
    FOREIGN KEY (order_id) REFERENCES Orders(order_id) ON DELETE CASCADE,
    FOREIGN KEY (item_id) REFERENCES Items(item_id) ON DELETE CASCADE
);

CREATE TABLE Warehouses (
    warehouse_id INT PRIMARY KEY,
    city VARCHAR(35) NOT NULL
);

CREATE TABLE Shipments (
    order_id INT NOT NULL,
    warehouse_id INT NOT NULL,
    ship_date DATE NOT NULL,
    FOREIGN KEY (order_id) REFERENCES Orders(order_id) ON DELETE CASCADE,
    FOREIGN KEY (warehouse_id) REFERENCES Warehouses(warehouse_id) ON DELETE CASCADE
);

INSERT INTO Customers VALUES
(0001, "Customer_1", "Mysuru"),
(0002, "Customer_2", "Bengaluru"),
(0003, "Kumar", "Mumbai"),
(0004, "Customer_4", "Dehli"),
(0005, "Customer_5", "Bengaluru");

INSERT INTO Orders VALUES
(001, "2020-01-14", 0001, 2000),
(002, "2021-04-13", 0002, 500),
(003, "2019-10-02", 0003, 2500),
(004, "2019-05-12", 0005, 1000),
(005, "2020-12-23", 0004, 1200);

INSERT INTO Items VALUES
(0001, 400),
(0002, 200),
(0003, 1000),
(0004, 100),
(0005, 500);

INSERT INTO Warehouses VALUES
(0001, "Mysuru"),
(0002, "Bengaluru"),
(0003, "Mumbai"),
(0004, "Dehli"),
(0005, "Chennai");

INSERT INTO OrderItems VALUES 
(001, 0001, 5),
(002, 0005, 1),
(003, 0005, 5),
(004, 0003, 1),
(005, 0004, 12);

INSERT INTO Shipments VALUES
(001, 0002, "2020-01-16"),
(002, 0001, "2021-04-14"),
(003, 0004, "2019-10-07"),
(004, 0003, "2019-05-16"),
(005, 0005, "2020-12-23");

SELECT * FROM Customers;
SELECT * FROM Orders;
SELECT * FROM OrderItems;
SELECT * FROM Items;
SELECT * FROM Shipments;
SELECT * FROM Warehouses;

CREATE VIEW ShipmentDatesFromWarehouse2 AS
SELECT order_id, ship_date
FROM Shipments
WHERE warehouse_id = 2;

SELECT * FROM ShipmentDatesFromWarehouse2;

CREATE VIEW WharehouseWithKumarOrders AS
SELECT s.warehouse_id
FROM Warehouses w, Customers c, Orders o, Shipments s
WHERE w.warehouse_id = s.warehouse_id AND s.order_id = o.order_id AND o.cust_id = c.cust_id AND c.cname = "Kumar";

SELECT * FROM WharehouseWithKumarOrders;

DELETE FROM Orders WHERE cust_id = (SELECT cust_id FROM Customers WHERE cname LIKE "%Kumar%");

DELIMITER $$

CREATE TRIGGER PreventWarehouseDelete
    BEFORE DELETE ON Warehouses
    FOR EACH ROW
BEGIN 
    IF OLD.warehouse_id IN (SELECT warehouse_id FROM Shipments NATURAL JOIN Warehouses) THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'An item has to be shipped from this warehouse!';
    END IF;
END;
$$

DELIMITER ;

DELETE FROM Warehouses WHERE warehouse_id = 2;

DELIMITER $$

CREATE TRIGGER UpdateOrderAmt
    AFTER INSERT ON OrderItems
    FOR EACH ROW
BEGIN
    UPDATE Orders SET order_amt = (new.qty * (SELECT DISTINCT unitprice FROM Items NATURAL JOIN OrderItems WHERE item_id = new.item_id)) WHERE Orders.order_id = new.order_id;
END;

$$

DELIMITER ;

INSERT INTO Orders VALUES
(006, "2020-12-23", 0004, 1200);

INSERT INTO OrderItems VALUES 
(006, 0001, 5);

SELECT * FROM Orders;
