-- Na podstawie dokumentacji

-- 1 --

DROP TABLE IF EXISTS TestBatch;
GO
CREATE TABLE TestBatch (Cola INT PRIMARY KEY, Colb CHAR(3))
GO
DELETE FROM TestBatch
INSERT INTO TestBatch VALUES (1, 'aaa')
INSERT INTO TestBatch VALUES (2, 'bbb')
INSERT INTO TestBatch VALUSE (3, 'ccc')  /* Syntax error */
GO
SELECT * FROM TestBatch   /* Returns no rows */
GO

-- 2 --

DELETE FROM TestBatch
INSERT INTO TestBatch VALUES (1, 'aaa')
INSERT INTO TestBatch VALUES (2, 'bbb')
INSERT INTO TestBatch VALUES (1, 'ccc')  /* Duplicate key error */
GO
SELECT * FROM TestBatch   /* Returns rows 1 and 2 */
GO

-- 3 --

DELETE FROM TestBatch
INSERT INTO TestBatch VALUES (1, 'aaa')
INSERT INTO TestBatch VALUES (2, 'bbb')
INSERT INTO TestBch VALUES (3, 'ccc')  /* Table name error */
GO
SELECT * FROM TestBatch   /* Returns rows 1 and 2 */
GO

-- 4 --

drop table if exists t1
drop table if exists t2

create table t1 ( nr1 int, nazwa1 varchar(20) )
create table t2 ( nr2 int, nazwa2 varchar(20) )
go

insert t1 values( 1, 'AA' )
insert t1 values( 2, 'AB' )
insert t2 values( 1, 'BA' )
insert t2 values( 2, 'BB' )
go

select nr1,nazwa1 from t1
select nr1,nazwa1 from t5 -- t2
