namespace EShop.Shared
{
    public record Money(decimal Amount, string Currency = "PLN")
    {
        public override string ToString() => $"{Amount:N2} {Currency}";
        public static Money Zero(string Currency = "PLN") => new (0, Currency);

        public static Money operator+ (Money a, Money b)
        {
            if(a.Currency != b.Currency)
            {
                throw new InvalidCastException("Cant add different currency");
            } else
            {
                return new Money(a.Amount + b.Amount, a.Currency);
            }
        }

        public static Money operator* (Money a, decimal mult)
        {
            return new (a.Amount * mult, a.Currency);
        }

        protected Money() : this(0, "PLN") { }
    }
}