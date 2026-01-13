using Blog.Domain.Model.Post.Repositories;
using Blog.Infrastructure.Repositories;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Blog.Application
{
    public class BlogService : IBlogService
    {
        private IPostRepository postRepository;


        public BlogService()
        {
            postRepository = new PostIM();
        }

        public BlogService(IPostRepository postRepository)
        {
            this.postRepository = postRepository;
        }

        public IList<Domain.Model.Post.Post> GetAllPosts()
        {
            return postRepository.FindAll();
        }

        public void CreateNewPost(Domain.Model.Post.Post p)
        {
            postRepository.Insert(p);
        }
    }
}
