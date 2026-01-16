using System;
using System.Collections.Generic;

namespace EShop.Domain.interfaces
{
	public interface IRepository<T>
	{
		T GetById(Guid id);
		IEnumerable<T> GetAll(); 
		void Save(T entity);
		void Delete(Guid id);
	}
}