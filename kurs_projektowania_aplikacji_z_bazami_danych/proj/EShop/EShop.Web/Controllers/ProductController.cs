using Microsoft.AspNetCore.Mvc;
using EShop.Application;
using System;
using System.ComponentModel.Design;
using EShop.Shared;

namespace EShop.Web.Controllers
{
    public class ProductController : Controller
    {
        private readonly ProductService _service; 

        public ProductController(ProductService service)
        {
            _service = service;

            if (!_service.GetAll().Any())
            {
                _service.Create("Marchewka", "Opis marchewki", 2.50m, UnitType.Kilogram, "/img/carrot.png");
                _service.Create("Ziemniaki", "Opis ziemniaka", 1.99m, UnitType.Kilogram, "/img/potato.png");
                _service.Create("Pomidor", "Opis maliny", 12.00m, UnitType.Kilogram, "/img/tomato.png");
                _service.Create("Seler", "Opis selera", 3.50m, UnitType.Piece, "/img/celery.png");
            }
        }

        public IActionResult Index()
        {
            var products = _service.GetAll();
            return View(products);
        }

        public IActionResult Details(Guid id)
        {
            var product = _service.GetById(id);
            if(product == null) return NotFound();

            return View(product);
        }

        [HttpGet]
        public IActionResult Create()
        {
            return View();
        }

        [HttpPost]
        public IActionResult Create(string name, string description, decimal price, UnitType unit, string pictureUrl)
        {
            _service.Create(name, description, price, unit, pictureUrl);
            return RedirectToAction("Index");
        }

        [HttpGet]
        public IActionResult Edit(Guid id)
        {
            var product = _service.GetById(id);
            if (product == null) return NotFound();

            return View(product);
        }

        [HttpPost]
        public IActionResult Edit(Guid id, string name, string description, decimal price, UnitType unit, string pictureUrl)
        {
            try
            {
                _service.Update(id, name, description, price, unit, pictureUrl);
                return RedirectToAction("Index");
            } catch (Exception)
            {
                return NotFound();
            }
        }


        [HttpGet]
        public IActionResult Delete(Guid id)
        {
            _service.Delete(id);
            return RedirectToAction("Index");
        }
    }
}