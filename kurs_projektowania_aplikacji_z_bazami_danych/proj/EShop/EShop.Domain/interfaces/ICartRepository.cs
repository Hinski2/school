using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace EShop.Domain.interfaces
{
    public interface ICartRepository
    {
        Cart? GetById(Guid id);
        void Save(Cart cart);
        void Delete(Guid id);
    }
}