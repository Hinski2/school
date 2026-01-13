using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using EShop.Domain;
using EShop.Domain.interfaces;
using Microsoft.VisualBasic;

namespace EShop.Application
{
    public class CartService
    {
        private readonly ICartRepository _cartRepository;
        private readonly IProductRepository _productRepository;

        public CartService(ICartRepository cartRepository, IProductRepository productRepository)
        {
            _cartRepository = cartRepository;
            _productRepository = productRepository; 
        }

        public Cart Get(Guid cartId)
        {
            var cart = _cartRepository.GetById(cartId); 
            if(cart == null)
            {
                cart = new Cart(cartId);
                _cartRepository.Save(cart);
            } 

            return cart;
        }

        public void AddProductToCart(Guid cartId, Guid productId, decimal quantity)
        {
            var cart = Get(cartId);
            var product = _productRepository.GetById(productId);

            if(product == null)
                throw new Exception($"product with giud {productId} doesnt exist");
            
            cart.AddProduct(product, quantity);
            _cartRepository.Save(cart);
        }

        public void RemoveProductFromCart(Guid cartId, Guid productId)
        {
            var cart = Get(cartId);
            cart.RemoveProduct(productId);
            _cartRepository.Save(cart);
        }
    }
}