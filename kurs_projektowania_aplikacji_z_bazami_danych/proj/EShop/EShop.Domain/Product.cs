using System;
using System.Collections.Generic;
using System.Data.SqlTypes;
using System.Linq;
using System.Threading.Tasks;
using EShop.Shared;

namespace EShop.Domain
{
    public class Product
    {
        public Guid Id { get; private set; }
        public string Name { get; private set; }
        public string Description { get; private set; }
        public Money Price { get; private set; }
        public string PictureUrl { get; private set; }
        public UnitType Unit { get; private set; }
        public ProductLifecycle Status { get; private set; }

        public Product(Guid id, string name, string description, Money price, string pictureUrl, UnitType unit, ProductLifecycle status)
        {
            Id = id;
            Name = name;
            Description = description;
            Price = price;
            PictureUrl = pictureUrl;
            Unit = unit;
            Status = status;
        }

        public void Activate()
        {
            Status = ProductLifecycle.Active;
        }        

        public void Discontinue()
        {
            Status = ProductLifecycle.Discontinued;
        }

        public void Update(string name, string description, Money price, UnitType unit, string pictureUrl)
        {
            if(price.Amount < 0)
            {
                throw new ArgumentException("price cant be negative");
            }

            Name = name;
            Description = description;
            Price = price;
            Unit = unit;
            PictureUrl = pictureUrl;
        }
    }
}