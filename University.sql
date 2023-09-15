create database University;
use University;

create table Department(
  DNO int primary key,
  Dname varchar(30),
  Dphone int(15)
);
CREATE TABLE Professor (
    Eid INT PRIMARY KEY,
    DNO INT,
    Ename VARCHAR(50),
    Startyear DATE,
    Ephone INT,
    FOREIGN KEY (DNO) REFERENCES Department(DNO)
);
CREATE TABLE Student (
    Sname varchar(20),
    gender varchar(5),
    DNO INT,
    Eid INT,
    USN VARCHAR(10) primary key,
    FOREIGN KEY (DNO) REFERENCES Department(DNO),
    foreign key(Eid) references Professor(Eid)
);
insert into Department(DNO,Dname,Dphone)values(1,"Computer Sceince",90997891);
insert into Department(DNO,Dname,Dphone)values(2,"Information Sceince",90997892);
insert into Department(DNO,Dname,Dphone)values(3,"Electronics and Communication",90997893);
insert into Department(DNO,Dname,Dphone)values(4,"Civil Engineering",90997894);
insert into Department(DNO,Dname,Dphone)values(5,"Mechanical Engineerinng",90997895);

select * from Department;
alter table student modify gender varchar(5);
insert into Professor(Eid,DNO,Ename,Startyear,Ephone)values(1,1,"Srinath",'2011-01-01',9095789);
insert into Professor(Eid,DNO,Ename,Startyear,Ephone)values(2,1,"AnilKumar",'2002-12-01',9095789);
insert into Professor(Eid,DNO,Ename,Startyear,Ephone)values(3,1,"Sheela",'2009-09-26',90957891);
insert into Professor(Eid,DNO,Ename,Startyear,Ephone)values(4,2,"M P pushalatha",'2004-02-23',9095789);
insert into Professor(Eid,DNO,Ename,Startyear,Ephone)values(5,2,"Rakshith",'2007-04-20',9095789);

select * from Professor;
alter table student modify Sname varchar(20);

insert into student(Sname,gender,DNO,Eid,USN)values("Abhishek M B","Male",1,1,"JCE21CS003");
insert into student(Sname,gender,DNO,Eid,USN)values("ABHISHEK A C","Male",1,1,"JCE21CS002");
insert into student(Sname,gender,DNO,Eid,USN)values("Darshan","Male",1,1,"JCE21CS014");
insert into student(Sname,gender,DNO,Eid,USN)values("Sharath h k","Male",1,1,"JCE21CS017");

select * from student;


