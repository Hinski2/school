using EShop.Domain;
using EShop.Domain.interfaces;
using NHibernate;

namespace EShop.Infrastructure
{
    public class DbProductRepository : DbGenericRepository<Product>, IProductRepository
    {
        public DbProductRepository(ISession session) : base(session)
        {
        }
    }
}
