USE Test;

-- startujemy
drop table if exists automat

create table automat (id int identity(10,2) not null primary key, nazwa varchar(20));

insert into automat(nazwa) values('ala');
insert into automat values('ania');
insert into automat values('basia');

select $identity, id from automat

select @@identity

dbcc checkident (automat)

-- reczne wstawianie
set identity_insert automat on

insert into automat(id,nazwa) values(8,'ewa');

set identity_insert automat off

dbcc checkident (automat,noreseed)

insert into automat(nazwa) values('gosia');
insert into automat(nazwa) values('kasia');

select @@identity

-- resetujemy licznik
dbcc checkident (automat,reseed, 6)

insert into automat(nazwa) values('felicja'); -- probuje wstawic z 8
insert into automat(nazwa) values('zuzanna');

-- ponownie resetujemy, ale juz rozsadnie 
declare @max int
set @max=(select max(id) from automat)
dbcc checkident (automat,reseed, @max)

insert into automat(nazwa) values('felicja');
insert into automat(nazwa) values('zuzanna');

select @@identity

-- porownujemy @@identity i ident_current; odpalamy bliüniaczy skrypt
-- wstawiamy rekord w innej sesji: insert into automat(nazwa) values('w1')
select @@identity
--select scope_identity()
select ident_current('automat')
