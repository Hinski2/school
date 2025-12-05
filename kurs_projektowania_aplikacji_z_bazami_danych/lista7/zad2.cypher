// dodanie 2 nowych aktorów 
create  (kuba:Person:Actor {name: 'Kuba Iliński'}),
        (janek:Person:Actor {name: 'Jan Mączyński'});

// dodanie 2 mowych właściwości do jednego filmu 
match (m:Movie {title: 'Wall Street'})
set m.score = 9.5, m.genre = 'crime'
return m;

// dodanie 2 nowch relacji acted_in do już istniejąccego node
match (p:Person:Actor {name: 'Kuba Iliński'})
match (m1:Movie {title: 'Wall Street'})
match (m2:Movie {title: 'The American President'})
create (p)-[:ACTED_IN]->(m1) 
create (p)-[:ACTED_IN]->(m2)
return p;

// update 1 właściwości filmu
match (m: Movie {title: 'Wall Street'})
set m.score = 9.7
return m;

// usunięcie 1 relacji acted_in
match (:Person:Actor {name: 'Kuba Iliński'})-[r:ACTED_IN]->(:Movie {title: 'The American President'})
delete r;

// wypisanie całego grafu, 
match (n)-[r]->(m)
match (x) // specjalnie dla aktora 'jan mączyński', bo nie ma rzadnego r 
return r, x