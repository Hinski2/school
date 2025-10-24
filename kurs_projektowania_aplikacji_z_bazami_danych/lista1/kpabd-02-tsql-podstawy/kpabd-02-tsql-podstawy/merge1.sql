DROP TABLE IF EXISTS Work;
DROP TABLE IF EXISTS Production;
GO

CREATE TABLE Work (id int primary key, tresc varchar(30));
CREATE TABLE Production (id int primary key, tresc varchar(30));
GO

INSERT Work VALUES(1, 'Test1');
INSERT Work VALUES(2, 'Test2');
INSERT Work VALUES(3, 'Test3');

INSERT Production VALUES(1, 'XXX');
GO

SELECT * FROM Work;
SELECT * FROM Production;
GO

MERGE Production as TARGET
USING WORK as SOURCE ON TARGET.id=SOURCE.id
WHEN MATCHED THEN UPDATE SET TARGET.tresc=SOURCE.tresc
WHEN NOT MATCHED THEN INSERT VALUES(SOURCE.id, SOURCE.tresc);
GO

SELECT * FROM Work;
SELECT * FROM Production;
GO