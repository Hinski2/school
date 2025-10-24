drop table Employees
-- New tree table
create table Employees
(
	ID INT UNIQUE NOT NULL,
	Node HIERARCHYID PRIMARY KEY CLUSTERED, -- this index supports depth first search
	NodeLevel AS Node.GetLevel(),
	Name VARCHAR(100),
	Title VARCHAR(40)
)
GO


CREATE UNIQUE INDEX EmployeesIndex ON Employees(NodeLevel, Node) ; -- this index support breadth first search
GO

-- insert root
INSERT Employees (Node, ID, Name, Title)
VALUES (HIERARCHYID::GetRoot(), 6, 'A', 'Level1') ;
GO

SELECT Node.ToString() AS Text_OrgNode, Node, NodeLevel, ID, Name, Title FROM Employees;;

DECLARE @HID HIERARCHYID 
SELECT @HID = HIERARCHYID::GetRoot() FROM Employees;
INSERT Employees(Node, ID, Name, Title) VALUES (@HID.GetDescendant(NULL, NULL), 4, 'B', 'Level2, 1') ; 
GO

DECLARE @HID HIERARCHYID 
DECLARE @HID2 HIERARCHYID 
SELECT @HID = HIERARCHYID::GetRoot() FROM Employees;
SELECT @HID2 = Node FROM Employees WHERE ID = 4
INSERT Employees(Node, ID, Name, Title) VALUES (@HID.GetDescendant(@HID2, NULL), 8, 'C', 'Level2, 2') ; 
GO

DECLARE @HID HIERARCHYID 
SELECT @HID = Node FROM Employees WHERE ID = 4
INSERT Employees(Node, ID, Name, Title) VALUES (@HID.GetDescendant(NULL, NULL), 3, 'C', 'Level3, 1') ; 
GO

DECLARE @HID HIERARCHYID 
DECLARE @HID2 HIERARCHYID 
SELECT @HID = Node FROM Employees WHERE ID = 4
SELECT @HID2 = Node FROM Employees WHERE ID = 3
INSERT Employees(Node, ID, Name, Title) VALUES (@HID.GetDescendant(@HID2, NULL), 5, 'C', 'Level3, 2') ; 
GO

DECLARE @HID HIERARCHYID 
SELECT @HID = Node FROM Employees WHERE ID = 8
INSERT Employees(Node, ID, Name, Title) VALUES (@HID.GetDescendant(NULL, NULL), 7, 'C', 'Level3, 3') ; 
GO

DECLARE @HID HIERARCHYID 
DECLARE @HID2 HIERARCHYID 
SELECT @HID = Node FROM Employees WHERE ID = 8
SELECT @HID2 = Node FROM Employees WHERE ID = 7
INSERT Employees(Node, ID, Name, Title) VALUES (@HID.GetDescendant(@HID2, NULL), 9, 'C', 'Level3, 4') ; 
GO

SELECT Node.ToString() AS Text_OrgNode, Node, NodeLevel, ID, Name, Title FROM Employees;;

SELECT Node.ToString() AS Text_OrgNode, Node, NodeLevel, ID, Name, Title FROM Employees WHERE NodeLevel=2


HIERARCHYID:
http://technet.microsoft.com/en-us/library/bb677169(v=sql.105).aspx
http://msdn.microsoft.com/en-us/magazine/cc794278.aspx
http://technet.microsoft.com/pl-pl/library/hierarchyid---czyli-drzewa-po-nowemu.aspx
http://msdn.microsoft.com/en-us/library/bb677193.aspx
http://msdn.microsoft.com/en-us/library/bb677173.aspx



WITH:
http://msdn.microsoft.com/en-us/library/ms175972.aspx
http://blog.sqlauthority.com/2012/04/24/sql-server-introduction-to-hierarchical-query-using-a-recursive-cte-a-primer/