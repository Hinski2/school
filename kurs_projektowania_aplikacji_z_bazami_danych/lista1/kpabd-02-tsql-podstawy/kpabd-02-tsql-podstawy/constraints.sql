use Test;
GO

drop table if exists dane
GO

create table dane (
  id int not null constraint PK_id primary key,
  imie varchar(20) constraint CK_imie check(imie like '[A-Z]%'),
  nazwisko varchar(30) constraint CK_nazwisko check(nazwisko like '[A-Z]%'),
  pesel char(11) constraint U_pesel unique,
  dataurodzenia datetime constraint CK_dataurodzenia check (dataurodzenia>'19000101' and dataurodzenia<getdate()),
  plec char(1) constraint DF_plec default '?',
  constraint U_imie_nazwisko unique(imie,nazwisko),
  constraint CK_plec check (plec in ('m','k','?'))
)
GO

insert into dane values(1,'Ala','Zemke','1','20031010', 'k')
insert into dane values(2,'Basia','Zemke','1','20031010', 'k')

-- tutaj dalej nie zadziala, unique nie mozna wylaczyc
alter table dane nocheck constraint U_pesel

-- poprawiamy
insert into dane values(2,'Basia','Zemke','2','20031010', 'f')

alter table dane nocheck constraint CK_plec

insert into dane values(2,'Basia','Zemke','2','20031010', 'f')

-- sprawdzamy stan wiêzów
dbcc checkconstraints ('dane')
dbcc checkconstraints ('dane') with all_constraints

alter table dane check constraint CK_plec

insert into dane values(3,'Ewa','Zemke','3','20031010', 'k')

select * from dane

-- sprawdzamy stan wiêzów ponownie
dbcc checkconstraints ('CK_plec')
