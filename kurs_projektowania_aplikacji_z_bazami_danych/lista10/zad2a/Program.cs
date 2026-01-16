using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NHibernate.Cfg;
using NHibernate;
using System.Diagnostics;

namespace zad2a
{
    class Program
    {
        static ISessionFactory CreateFactory()  // konfiguracja fabryki
        {
            return new Configuration().Configure("Part.cfg.xml").BuildSessionFactory();
        }

        static void TestInsert(ISessionFactory factory, int count)
        {
            using (var session = factory.OpenSession())
            using (var transaction = session.BeginTransaction())
            {
                for(int i = 0; i < count; i++)
                {
                    session.Save(new Part { OEM = "OEM" + i, Description = "Description" });
                    session.Save(new NewTire { OEM = "OEM" + i, Speed = 42, OnStock = true });
                    session.Save(new RefurbishedTire { OEM = "OEM" + i, Speed = 67, ConsumptionLevel = 0.67f, ConsumptionLevelAfterFixing = 0.42f });
                }

                transaction.Commit();
            }
        }

        static void TestSelect(ISessionFactory factory)
        {
            using (var session = factory.OpenSession())
            {
                var list = session.Query<Part>().ToList();
            }
        }


        static void Main(string[] args)
        {
            var factory = CreateFactory();
            int count = 1000;

            var stopwatch = Stopwatch.StartNew();
            TestInsert(factory, count);
            stopwatch.Stop();
            Console.WriteLine($"czas {stopwatch.ElapsedMilliseconds} ms");

            stopwatch.Restart();
            TestSelect(factory);
            stopwatch.Stop();
            Console.WriteLine($"czas {stopwatch.ElapsedMilliseconds} ms");

            Console.ReadLine();
        }
    }
}