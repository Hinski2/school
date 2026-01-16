using EShop.Domain;
using EShop.Domain.interfaces;
using NHibernate;

namespace EShop.Infrastructure
{
    public class DbCartRepository : DbGenericRepository<Cart>, ICartRepository
    {
        public DbCartRepository(ISession session) : base(session)
        {
        }
    }
}
