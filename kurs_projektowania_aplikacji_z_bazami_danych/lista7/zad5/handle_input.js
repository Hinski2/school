import readline from 'readline/promises'

export async function handle_input() {
    const rl = readline.createInterface({ // tworzymy interface dla wczytywania inputu
        input: process.stdin,
        output: process.stdout,
    });

    console.log("wybierz: read, create_node, create_relation, delete_node, delete_relation, update, exit") 

    const command = await rl.question("> "); // wczytanie inputu

    let res = { // struktura którą zwrócimy
        status: command.trim(),
        error: null,
    }

    if(res.status === 'read') { // wybarnie odpowiedniej opcji
        res.node1 = (await rl.question("node: ")).trim();
    } else if(res.status === 'create_node') {
        res.node1 = (await rl.question("node: ")).trim();
    } else if(res.status === 'create_relation') {
        res.node1 = (await rl.question("node1: ")).trim();
        res.relation = (await rl.question("relation: ")).trim();
        res.node2 = (await rl.question("node2: ")).trim();
    } else if(res.status === 'delete_node') {
        res.node1 = (await rl.question("node: ")).trim();
    } else if(res.status === 'delete_relation') {
        res.node1 = (await rl.question("node1: ")).trim();
        res.relation = (await rl.question("relation: ")).trim();
        res.node2 = (await rl.question("node2: ")).trim();
    } else if(res.status === 'update') {
        res.node1 = (await rl.question("node1: ")).trim();
        res.property_key = (await rl.question("property name: ")).trim();
        res.property_val = (await rl.question("property value: ")).trim();
    } else if(res.status === 'exit') {
        res.status = 'exit';
    } else {
        res.error = `niepoprawny wybór, ${res.status}, nie ma takiej opcji`;
        res.status = 'error';
    }

    rl.close();
    return res;
}