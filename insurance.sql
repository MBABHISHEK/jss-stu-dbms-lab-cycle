PERSON (driver id#: string, name: string, address: string)
CAR (regno: string, model: string, year: int) 
ACCIDENT (report_ number: int, acc_date: date, location: string)
OWNS (driver id#: string, regno: string)
PARTICIPATED(driver id#:string, regno:string, report_ number: int,damage_amount: int)



CREATE TABLE PERSON(
driver_id char(10) primary key,
dname varchar(20),
address text
);

CREATE TABLE CAR
(
reg_no char(10) primary key,
model varchar(20),
year int  
);

CREATE TABLE ACCIDENT
(
 report_number int,
 acc_date date,
 location text   
);

CREATE TABLE OWNS
(
 driver_id char(10),
 reg_no char(10), 


  
);
