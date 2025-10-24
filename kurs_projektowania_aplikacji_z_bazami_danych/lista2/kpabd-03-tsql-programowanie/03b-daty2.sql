SET DATEFORMAT dmy;
GO

print str(12345.6789, 10,2)

declare @x int, @d datetime
set @x='2004'
set @d='31/01/2005 13:25:59.333'

print ':'+convert(char(10),@x)+':'

print convert(varchar, @d, 0)
print convert(varchar, @d, 1)
print convert(varchar, @d, 2)
print convert(varchar, @d, 3)
print convert(varchar, @d, 4)
print convert(varchar, @d, 5)
print convert(varchar, @d, 6)
print convert(varchar, @d, 7)

print convert(varchar(40), @d, 100)
print convert(varchar(40), @d, 101)
print convert(varchar(40), @d, 102)
print convert(varchar(40), @d, 103)
print convert(varchar(40), @d, 104)
print convert(varchar(40), @d, 105)
print convert(varchar(40), @d, 106)
print convert(varchar(40), @d, 107)

print convert(varchar(40), @d, 8)
print convert(varchar(40), @d, 9)
print convert(varchar(40), @d, 10)
print convert(varchar(40), @d, 11)
print convert(varchar(40), @d, 12)
print convert(varchar(40), @d, 13)
print convert(varchar(40), @d, 14)

print convert(varchar(40), @d, 108)
print convert(varchar(40), @d, 109)
print convert(varchar(40), @d, 110)
print convert(varchar(40), @d, 111)
print convert(varchar(40), @d, 112)
print convert(varchar(40), @d, 113)
print convert(varchar(40), @d, 114)

print convert(varchar(40), @d, 20)
print convert(varchar(40), @d, 21)
print convert(varchar(40), @d, 120)
print convert(varchar(40), @d, 121)
