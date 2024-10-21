/*
    Pola i medoty można dodać przez przypisanie i przy użyciu defineProperty
    Własnosci można dodać tylko przez defineProperty
         
*/

let person = {
    name: "Kuba",   // pole 
    _age: 19,       // własność

    // metoda
    display_name: function(){
        console.log(this.name)
    },

    // akcesory
    get age(){
        return this._age;
    },

    set age(new_age){
        this._age = new_age;
    }
}

person._height = 178;               // dodanie nowej właności
person.display_age = function(){    // dodanie noew moteody
    console.log(this._age)
};

Object.defineProperty(person, 'height', { // dodanie akcesorów
    get: function() {
        return this._height;
    }, 
    set: function(new_height) {
        this._height = new_height
    }
})

person.display_age()
person.age = 20
person.display_age()

