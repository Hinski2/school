using EShop.Application;
using EShop.Infrastructure;
using EShop.Domain.interfaces;
using NHibernate.Cfg;
using NHibernate.Dialect;
using NHibernate.Driver;

var builder = WebApplication.CreateBuilder(args);
var nhConfig = new NHibernate.Cfg.Configuration().Configure("hibernate.cfg.xml");
var sessionFactory = nhConfig.BuildSessionFactory();

// nhibernate configuration
builder.Services.AddControllersWithViews();
builder.Services.AddAuthorization();
builder.Services.AddScoped<IProductRepository, DbProductRepository>();
builder.Services.AddScoped<ICartRepository, DbCartRepository>();
builder.Services.AddScoped<ProductService>();
builder.Services.AddScoped<CartService>();
builder.Services.AddScoped<NHibernate.ISession>(factory => sessionFactory.OpenSession());

var app = builder.Build();

// Configure the HTTP request pipeline.
if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Home/Error");
    // The default HSTS value is 30 days. You may want to change this for production scenarios, see https://aka.ms/aspnetcore-hsts.
    app.UseHsts();
}

app.UseHttpsRedirection();
app.UseRouting();

app.UseAuthorization();

app.MapStaticAssets();

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}")
    .WithStaticAssets();


app.Run();
