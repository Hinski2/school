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
        public virtual Guid Id { get; protected set; }
        public virtual string Name { get; protected set; }
        public virtual string Description { get; protected set; }
        public virtual Money Price { get; protected set; }
        public virtual string PictureUrl { get; protected set; }
        public virtual UnitType Unit { get; protected set; }
        public virtual ProductLifecycle Status { get; protected set; }

        protected Product() {
            Name = default!;
            Description = default!;
            PictureUrl = default!;
            Price = default!;
        }

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

        public virtual void Activate()
        {
            Status = ProductLifecycle.Active;
        }        

        public virtual void Discontinue()
        {
            Status = ProductLifecycle.Discontinued;
        }

        public virtual void Update(string name, string description, Money price, UnitType unit, string pictureUrl)
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