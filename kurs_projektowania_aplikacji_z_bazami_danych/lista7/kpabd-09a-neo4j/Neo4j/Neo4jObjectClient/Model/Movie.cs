using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Neo4jObjectClient.Model
{
    public class Movie
    {
        public int id { get; set; }
        public int released { get; set; }
        public string tagline { get; set; }
        public string title { get; set; }
    }
}
