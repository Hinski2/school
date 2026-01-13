using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Blog.Domain.Model.Post.Repositories;
using Moq;

namespace Blog.Application.UnitTests
{
    [TestClass]
    public class PostServiceTests
    {
        [TestMethod]
        public void CheckFindMethodCalled()
        {
            // Arrange
            Mock<IPostRepository> repositoryMock = new Mock<IPostRepository>();
            IBlogService bs = new BlogService(repositoryMock.Object);

            // Act
            bs.GetAllPosts();

            // Assert
            repositoryMock.Verify(k => k.FindAll(), Times.Once());
        }
    }
}
