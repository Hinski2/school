using System;

namespace zad2b
{
    public class Part
    {
        public virtual int Id { get; set; }
        public virtual string OEM { get; set; }
        public virtual string Manufacturer { get; set; }
        public virtual string Number { get; set; }
        public virtual string Description { get; set; }
    }

    public class Tire : Part
    {
        public virtual int Speed { get; set; }
        public virtual int Rating { get; set; }
    }

    public class NewTire : Tire
    {
        public virtual bool OnStock { get; set; }
    }

    public class UsedTire : Tire
    {
        public virtual int ProductionYear { get; set; }
        public virtual float ConsumptionLevel { get; set; }
    }

    public class RefurbishedTire : UsedTire
    {
        public virtual float ConsumptionLevelAfterFixing { get; set; }
    }
}
