using Blog.Domain.Model.Post;
using Blog.Domain.Model.Post.Repositories;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Blog.Infrastructure.Repositories
{
    public class PostIM : IPostRepository
    {
        private List<Post> posts = new List<Post>();

        public PostIM()
        {
            posts = new List<Post>
            {
                new Post { Id = 101, Content = "Test1", Author = "Winnie The Pooh", PublishDate = DateTime.Now, Comments = new List<Comment>() },
                new Post { Id = 102, Content = "Test2", Author = "Winnie The Pooh", PublishDate = DateTime.Now, Comments = new List<Comment>() },
                new Post { Id = 103, Content = "Test3", Author = "Piglet", PublishDate = DateTime.Now, Comments = new List<Comment>() },
                new Post { Id = 104, Content = "Test4", Author = "Piglet", PublishDate = DateTime.Now, Comments = new List<Comment>() }
            };
        }

        public void Insert(Post post)
        {
            posts.Add(post);
        }

        public void Delete(int id)
        {
            foreach (var p in posts)
                if (p.Id == id)
                    posts.Remove(p);
        }

        public Post Find(int id)
        {
            foreach (var p in posts)
                if (p.Id == id)
                    return p;

            return null;
        }

        public List<Post> FindAll()
        {
            return posts;
        }
    }
}
