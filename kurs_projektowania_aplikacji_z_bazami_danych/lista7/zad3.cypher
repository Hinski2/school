// zwróć filmy w których gra osoba a 
match (a:Person)-[r:ACTED_IN]->(m:Movie)
return a, r, m;

// zwróć filmy gdize a była zarówno aktorei i reżyserem
match (p:Person:Actor {name: 'Kuba Iliński'}) // trzeba dodać osobe która jest reżyserem i aktorem w jednym filmie bo teraz nie ma takiej
match (m:Movie {title: 'Wall Street'})
create (p)-[:DIRECTED]->(m);

match (p:Person)-[a:ACTED_IN]->(m:Movie)
match (p)-[d:DIRECTED]->(m)
return p, m, a, d;

// zwróć aktorów którzy nie grali w rzadnym filmie 
match (p:Person)
where not (p)-[:ACTED_IN]->(:Movie)
RETURN p;

// zwróć aktorów którzy graliw ponad 2 filmach 
create (:Movie {title: 'Star Wars'});

match (p:Person:Actor {name: 'Kuba Iliński'})
match (m1:Movie {title: 'The American President'})
match (m2:Movie {title: 'Star Wars'})
create  (p)-[:ACTED_IN]->(m1),
        (p)-[:ACTED_IN]->(m2);

match (p:Person)-[:ACTED_IN]->(m:Movie)
with p, count(m) as no  // with grupuje wyniki po aktorze p
where no > 2
return p, no;

// zwróć filmy z największą liczbą aktorów
match (m:Movie)-[:ACTED_IN]-(p:Person)
return m, count(p) as no 
order by no desc 
limit 1;
