using System;
using System.Collections.Generic;
using System.Data.SqlTypes;
using System.Linq;
using System.Threading.Tasks;
using EShop.Shared;

namespace EShop.Domain
{
    public class Cart
    {
        public Guid Id { get; private set; }
        private readonly List<CartItem> _items = new();

        public Cart(Guid id)
        {
            Id = id;
        }

        public void AddProduct(Product product, decimal quantity)
        {
            if(product.Status == ProductLifecycle.Discontinued)
            {
                throw new InvalidOperationException("You cant buy inactive product");
            }

            if(quantity < 0)
            {
                throw new InvalidOperationException("your cant add negative ammount, just remove old");
            }

            var productInCart = _items.FirstOrDefault(x => x.Id == product.Id);
            if(productInCart == null)
            {
                _items.Add(new CartItem(product, quantity));
            } else
            {
                productInCart.updateQuantity(productInCart.Quantity + quantity);
            }
        }

        public void RemoveProduct(Guid id)
        {
            var item = _items.FirstOrDefault(x => x.Id == id);
            if(item != null)
            {
                _items.Remove(item);
            }
        }

        public void Clear()
        {
            _items.Clear();
        }

        public Money TotalAmount()
        {
            if(!_items.Any()) return Money.Zero();
            var sum = _items.Sum(i => i.TotalPrice.Amount);
            string currencty = _items.First().UnitPrice.Currency;

            return new Money(sum, currencty);
        }
    }
}

