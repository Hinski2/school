using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Blog.ObjectMothers;

namespace Blog.Domain.UnitTests
{
    [TestClass]
    public class PostTests
    {
        [TestMethod]
        public void CheckNotAcceptedCommentsWithNotAcceptedCommentsReturnTrue()
        {
            // Arrange
            var post = PostObjectMother.CreateBlogPostWithNoComments();
            var comment = PostObjectMother.CreateNotAcceptedComment(100);
            post.Comments.Add(comment);

            // Act
            bool result = post.AreNotAcceptedComments();

            // Assert
            Assert.IsTrue(result);
        }

        [TestMethod]
        public void CheckNotAcceptedCommentsWithAllAcceptedCommentsReturnFalse()
        {
            // Arrange
            var post = PostObjectMother.CreateBlogPostWithNoComments();
            var comment = PostObjectMother.CreateAcceptedComment(100);

            // Act
            post.Comments.Add(comment);
            bool result = post.AreNotAcceptedComments();

            // Assert
            Assert.IsFalse(result);
        }

        [TestMethod]
        public void CheckNotAcceptedCommentsNoCommentsReturnTrue()
        {
            // Arrange
            var post = PostObjectMother.CreateBlogPostWithNoComments();

            // Act
            bool result = post.AreNotAcceptedComments();

            // Assert
            Assert.IsTrue(result);
        }

    }
}
