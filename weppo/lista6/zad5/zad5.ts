type User = {
    type: 'User';
    name: string;
    age: number;
    occupation: string;
}


type Admin = {
    type: 'Admin'
    name: string;
    age: number;
    role: string;
}

export type Person = User | Admin;

// type guard
// function isUser(p: Person): p is User {
//     return 'occupation' in p;
// }

// function isAdmin(p: Person): p is Admin {
//     return 'role' in p;
// }

function isUser(p: Person){
    return p.type === 'User';
}

function isAdmin(p: Person){
    return p.type === 'Admin';
}

export const persons: Person[] = [
    {
        type: 'User',
        name: 'Jan Kowalski',
        age: 17,
        occupation: 'Student'
    },
    {
        type: 'Admin',
        name: 'Tomasz Malinowski',
        age: 20,
        role: 'Administrator'
    }
];

function logPerson(person: Person){
    let additionalInformation: string;

    if(isAdmin(person)){
        additionalInformation = person.role;
    } 
    else {
        additionalInformation = person.occupation;
    }
    console.log(` - ${person.name}, ${person.age}, ${additionalInformation}`);
}

logPerson(persons[0]);
logPerson(persons[1]);
