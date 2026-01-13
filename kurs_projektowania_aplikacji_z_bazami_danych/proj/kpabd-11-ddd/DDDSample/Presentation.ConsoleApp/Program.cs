using Blog.Application;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Presentation.ConsoleApp
{
    class Program
    {
        static void Main(string[] args)
        {
            IBlogService blogService = new BlogService();

            foreach (var p in blogService.GetAllPosts())
                Console.WriteLine(string.Format("{0}, {1}", p.PublishDate, p.Content));
        }
    }
}
