function get_fields_of_object(o){
    return Object.keys(o)
}

function get_fields_of_object_and_ancestors(o){
    keys = get_fields_of_object(o)
    p = Object.getPrototypeOf(o)
    while(p){
        keys = keys.concat(get_fields_of_object(p))
        p = Object.getPrototypeOf(p)
    }
    return keys
}

function belongs_to_object(o, f){
    return get_fields_of_object(o).includes(f)
}

let person = {
    age: 6,
    foo: function(){
        console.log(this.age);
    }
};

let programmer = {
    name: 'kuba',
    lvl: 'tech-lead'
}

Object.setPrototypeOf(programmer, person)

console.log(get_fields_of_object(programmer))
console.log(get_fields_of_object(person))

console.log()
console.log(get_fields_of_object_and_ancestors(programmer))
console.log(get_fields_of_object_and_ancestors(person))

console.log()
console.log(belongs_to_object(programmer, 'name'))
console.log(belongs_to_object(programmer, 'age'))


