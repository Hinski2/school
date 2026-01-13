using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Blog.Domain.Model.Post.Repositories
{
    public interface IPostRepository
    {
        void Insert(Post post);

        void Delete(int id);

        Post Find(int id);

        List<Post> FindAll();
    }
}
