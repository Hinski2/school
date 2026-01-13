using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using EShop.Domain;
using EShop.Domain.interfaces;

namespace EShop.Infrastructure
{
    public class InMemoryCartRepository : InMemoryGenericRepository<Cart>, ICartRepository
    {
        public void Save(Cart cart)
        {
            base.Save(cart.Id, cart);
        }
    }
}