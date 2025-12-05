// tak stworzyłem baze danych: 

// CREATE (charlie:Person:Actor {name: 'Charlie Sheen'}),
//        (martin:Person:Actor {name: 'Martin Sheen'}),
//        (michael:Person:Actor {name: 'Michael Douglas'}),
//        (oliver:Person:Director {name: 'Oliver Stone'}),
//        (rob:Person:Director {name: 'Rob Reiner'}),
//        (wallStreet:Movie {title: 'Wall Street'}),
//        (charlie)-[:ACTED_IN {role: 'Bud Fox'}]->(wallStreet),
//        (martin)-[:ACTED_IN {role: 'Carl Fox'}]->(wallStreet),
//        (michael)-[:ACTED_IN {role: 'Gordon Gekko'}]->(wallStreet),
//        (oliver)-[:DIRECTED]->(wallStreet),
//        (thePresident:Movie {title: 'The American President'}),
//        (martin)-[:ACTED_IN {role: 'A.J. MacInerney'}]->(thePresident),
//        (michael)-[:ACTED_IN {role: 'President Andrew Shepherd'}]->(thePresident),
//        (rob)-[:DIRECTED]->(thePresident)

// znajduje każdy węzeł n króty ma relacje r z węzłem m 
// więc pokazuje cała baze wraz z relacjami 
MATCH (n)-[r]->(m)
RETURN n, r, m