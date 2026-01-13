using Blog.Domain.Model.Post;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Blog.ObjectMothers
{
    public class PostObjectMother
    {
        public static Post CreateBlogPostWithNoComments()
        {
            Post p = new Post { Id = 1, Content = "Siakiś post", PublishDate = DateTime.Now, Comments = new List<Comment>() };

            return p;
        }

        public static Comment CreateAcceptedComment(int id)
        {
            return new Comment { Id = id, Content = "Nowy komentarz", Email = "drugiautor@domena.com", Nick = "drugi", PublishDate = DateTime.Now.AddHours(5), IsAccepted = true };
        }
        public static Comment CreateNotAcceptedComment(int id)
        {
            return new Comment { Id = id, Content = "Nowy komentarz", Email = "drugiautor@domena.com", Nick = "drugi", PublishDate = DateTime.Now.AddHours(5), IsAccepted = false };
        }
    }
}
