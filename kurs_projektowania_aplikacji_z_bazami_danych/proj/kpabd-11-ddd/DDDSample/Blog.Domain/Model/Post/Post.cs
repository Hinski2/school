using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Blog.Domain.Model.Post
{
    public class Post
    {
        public int Id { get; set; }

        public string Content { get; set; }

        public DateTime PublishDate { get; set; }

        public string Author { get; set; }

        public IList<Comment> Comments { get; set; }

        public bool AreNotAcceptedComments()
        {
            return Comments.Count == 0 || Comments.Any<Comment>(c => !c.IsAccepted);
        }
    }
}
