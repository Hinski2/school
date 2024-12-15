// Extract vs Pick
// Extract 
    //  jest do uni typów
    // np type MyUnion = number | string 

// Pick 
    //jest do struktur obiektowych
    // np type Person = {...}

    /*
    Extract, Exclude:
        * Extract<Keys, Keys>: z zadanej uni typowej zwraca wskazane elementy
        * Exclude<Keys, Keys>: z zadanej uni typowej wyrzuca wskazane elementy

    */

type MyUnion = 'a' | 'b' | 'c' | 'd' | 'e';

type Extracted = Extract<MyUnion, 'a' | 'd'> // a, d
type Excluded = Exclude<MyUnion, 'a' | 'd'>  // b, c, e

    /*
    Record, Required, Readonly, Partial:
        * Partial<T>: konstruuje z zadanego typu typ, który ma wszystkie składowe opcjonalne
        * Required<T>: pokstruuje z zadanego typu typ, który ma wszystkieskładowe wymagane
        * Readonly<T>: Konstruuje z zadanego typu typ, który ma wszystkie składowe tylko do odczytu 
        * Record<Keys, T>: Konstuuje typ z zadanyhc kluczy i typu wartości
    */

type Person2 = {
    name: string; 
    age: number; 
    occupation: string;
}
type PartialPerson2 = Partial<Person2>;
//  {
//      name?: string;
//      age?: number;
//      occupation?: string;
//  }

type Person3 = {
  name?: string;
  age?: number;
  occupation?: string;
};
type RequiredPerson3 = Required<Person3>;
//  {
//      name: string;
//      age: number;
//      occupation: string;
//  }

type Person4 = {
  name: string;
  age: number;
  occupation: string;
};
type ReadonlyPerson4 = Readonly<Person4>;
// {
//   readonly name: string;
//   readonly age: number;
//   readonly occupation: string;
// }

type Role = 'admin' | 'user'
type Permission = Record<Role, boolean>
// {
//   admin: boolean;
//   user: boolean;
// }

    /*
    Pick, Omit
        * Pick<T, Keys>: Z zadanego typu struktury zwraca podtyp ze wskazanych kluczy 
        * Omit<T, Keys>: Z zadanego typu struktury zwraca podtyp z wyrzuconymi wskazanymi kluczami 
    */

type Person5 = {
    name: string;
    age: number;
    occupation: string;
};

type PickPerson5 = Pick<Person5, "name" | "age">;
//  {
//      name: string
//      age: number
//  }    

type OmitPerson5 = Omit<Person5, "occupation">;
//  {
//      name: string
//      age: number
//  } 

    /*
    Index Acess Types
        * pozwalają na dostęp do typu wartości, która jest przypisana do konkretnego klucza w danym typu obiketu
        * podobne do indeksowania w obiektach, ale zamiast wartości dostajemy typ
    */

type Person = {
    name: string; 
    age: number; 
    occupation: string;
}

let p: Person = {name: "kuba", age: 19, occupation: "programmer"};

type NameType = Person['name'];             // typ: string 
type AgeTyep = Person['age'];               // typ: number
type OccupationType = Person['occupation']  // typ: string


// bezpierczniejsza opcja
function readKey<K extends keyof Person>(person: Person, person_field: K): Person[K] {
    return person[person_field]
}

// podczas kompulacji dostaniemy string
// podczas wykonywania dostaniemy 'programmer'
console.log(readKey(p, 'occupation'))



