using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Neo4j.Driver;
using Neo4jClient;
using Neo4jObjectClient.Model;

namespace Neo4jObjectClient
{
    class ClientApp
    {

        public async Task<IEnumerable<Person>> GetPersons()
        {
            var client = new BoltGraphClient(new Uri("neo4j://localhost"), "neo4j", "password");

            await client.ConnectAsync();
            var persons = await client.Cypher
                .Match("(p:Person)")
                .Where((Person p) => p.name.StartsWith("M"))
                .Return(p => p.As<Person>()).ResultsAsync;

            return persons;
        }

        static void Main(string[] args)
        {
            var client = new ClientApp();
            var persons = client.GetPersons();
            persons.Wait();

            foreach(var i in persons.Result)
            {
                Console.WriteLine(i.name);
            }
        }
    }
}
