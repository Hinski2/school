using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using EShop.Domain;
using EShop.Domain.interfaces;

namespace EShop.Infrastructure
{
    public class InMemoryProductRepository : InMemoryGenericRepository<Product>, IProductRepository
    {
        public void Save(Product product)
        {
            base.Save(product.Id, product);
        }
    }
}