using Neo4j.Driver;
using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace Neo4jSimpleClient
{
    class ClientApp : IDisposable
    {
        private IDriver _driver;

        public ClientApp(string uri, string user, string password)
        {
            _driver = GraphDatabase.Driver(uri, AuthTokens.Basic(user, password));
        }

        public async Task GetItems()
        {
            var session = _driver.AsyncSession();
            var result = await session.RunAsync(new Query("MATCH (p:Person) RETURN p"));
            var list = await result.ToListAsync();

            foreach (var i in list)
            {
                var item = (INode)i.Values["p"];
                Console.WriteLine(item.Properties["name"]);
            }
        }

        public void Dispose()
        {
            _driver?.Dispose();
        }

        public static void Main()
        {
            var clientApp = new ClientApp("neo4j://localhost", "neo4j", "password");

            clientApp.GetItems().Wait();
        }
    }
}
