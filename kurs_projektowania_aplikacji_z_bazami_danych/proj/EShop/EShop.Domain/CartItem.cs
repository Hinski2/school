using System;
using System.Collections.Generic;
using System.Data.SqlTypes;
using System.Linq;
using System.Threading.Tasks;
using EShop.Shared;

namespace EShop.Domain
{
    public class CartItem
    {
        public Guid Id { get; private set; }
        public string Name { get; private set; }
        public decimal Quantity { get; private set; }
        public Money UnitPrice { get; private set; }
        public Money TotalPrice => UnitPrice * Quantity;

        public CartItem(Product product, decimal quantity)
        {
            if(quantity < 0)
            {
                throw new ArgumentException("quantity cant be negative");
            }

            Id = product.Id;
            Name = product.Name;
            UnitPrice = product.Price;
            Quantity = quantity;
        }

        public void updateQuantity(decimal quantity)
        {
            if(quantity < 0)
            {
                throw new ArgumentException("quantity cant be negative");
            }

            Quantity = quantity;
        }
    }
}