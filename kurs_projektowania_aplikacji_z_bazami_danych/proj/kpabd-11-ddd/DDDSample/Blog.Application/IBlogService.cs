using Blog.Domain.Model.Post;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Blog.Application
{
    public interface IBlogService
    {
        IList<Post> GetAllPosts();

        void CreateNewPost(Post p);
    }
}
