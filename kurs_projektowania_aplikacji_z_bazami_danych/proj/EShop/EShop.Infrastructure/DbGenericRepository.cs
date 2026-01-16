using System;
using System.Collections.Generic;
using EShop.Domain.interfaces;
using NHibernate;

namespace EShop.Infrastructure
{
    public abstract class DbGenericRepository<T> : IRepository<T> where T : class
    {
        protected readonly ISession _session;
        public DbGenericRepository(ISession session)
        {
            _session = session;
        }

        public T? GetById(Guid id)
        {
            return _session.Get<T>(id);
        }

        public IEnumerable<T> GetAll()
        {
            return _session.CreateQuery($"from {typeof(T).Name}").List<T>();
        }

        public void Save(T entity)
        {
            using (var transaction = _session.BeginTransaction())
            {
                _session.SaveOrUpdate(entity);
                transaction.Commit();
            }
        }

        public void Delete(Guid id)
        {
            using (var transaction = _session.BeginTransaction())
            {
                var entity = _session.Load<T>(id);
                _session.Delete(entity);
                transaction.Commit();
            }
        }
    }
}