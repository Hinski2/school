select pm.Name, Count(p.ProductID) as NumberOfProducts
from SalesLT.Product p 
join SalesLT.ProductModel pm on p.ProductModelID = pm.ProductModelID
group by pm.ProductModelID, pm.Name
having COUNT(p.ProductID) > 1
order by NumberOfProducts desc;

-- jeśli byśmy grupowali nie po productId tylko po name to jeśli dwa modele miały by takie samo id to byśmy niepoprawnie je połączyli