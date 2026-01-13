using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using EShop.Domain;
using EShop.Domain.interfaces;
using EShop.Shared;

namespace EShop.Application
{
    public class ProductService
    {
        private readonly IProductRepository _productRepository;

        public ProductService(IProductRepository productRepository)
        {
            _productRepository = productRepository; 
        }

        public IEnumerable<Product> GetAll()
        {
            return _productRepository.GetAll();
        }

        public Product? GetById(Guid id)
        {
            return _productRepository.GetById(id);
        }

        public void Create(string name, string description, decimal price, UnitType unit, string pictureUrl)
        {
            var product = new Product(
                Guid.NewGuid(),
                name,
                description,
                new Money(price),
                pictureUrl,
                unit,
                ProductLifecycle.Active
            );

            _productRepository.Save(product);
        }

        public void Update(Guid id, string name, string description, decimal price, UnitType unit, string pictureUrl)
        {
            var product = _productRepository.GetById(id);
            if(product == null)
                throw new Exception($"product with guid {id} doesn't exist");

            product.Update(name, description, new Money(price), unit, pictureUrl);
            _productRepository.Save(product);
        }

        public void Delete(Guid id)
        {
            _productRepository.Delete(id);
        }
    }
}