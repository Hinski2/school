using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Blog.Domain.Model.Post
{
    public class Comment
    {
        public int Id { get; set; }

        public DateTime PublishDate { get; set; }

        public string Content { get; set; }

        public string Email { get; set; }

        public string Nick { get; set; }

        public bool IsAccepted { get; set; }
    }
}
