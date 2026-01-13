using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace EShop.Domain.interfaces
{
    public interface IProductRepository
    {
        Product? GetById(Guid id);
        IEnumerable<Product> GetAll();
        void Save(Product product);
        void Delete(Guid id);
    }
}