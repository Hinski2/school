using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace EShop.Infrastructure
{
    public abstract class InMemoryGenericRepository<T>
    {
        protected readonly Dictionary<Guid, T> _storage = new();

        public IEnumerable<T> GetAll()
        {
            return _storage.Values.ToList();
        }

        public T? GetById(Guid id)
        {
            if(_storage.ContainsKey(id))
            {
                return _storage[id];
            } else
            {
                return default(T);
            }
        } 

        public virtual void Save(Guid id, T entity)
        {
            _storage[id] = entity;
        }


        public void Delete(Guid id)
        {
            if(_storage.ContainsKey(id))
            {
                _storage.Remove(id);
            }
        }
    }
}