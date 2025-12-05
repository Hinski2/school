async function run_querry(driver, query) {
    const db = driver.session();

    try {
        return await db.run(query);
    } catch (error) {
        console.error("błąd: ", error);
        process.exit(1);
    } finally {
        await db.close();
    }
}

function clean(result) {
    return result.records.map(record => {
        const row = record.toObject();

        for (const key in row) 
            row[key] = row[key].properties || row[key]

        return row;
    })
}

/*
input ma pola { // w zależności od operacji
    status,
    node1,
    node2
    relation, 
    property_key
    property_val
    error // jeśli wystąpi => status = error
}
*/

export async function create_node(input, driver) {
    const query = `
        create (a {name: '${input.node1}' })
        return a
        `
    return clean(await run_querry(driver, query));
}

export async function create_relation(input, driver) {
    const query = `
        match (a {name: '${input.node1}' }) 
        match (b {name: '${input.node2}' })
        create (a)-[r:${input.relation}]->(b)
        return a, r, b
    `
    return clean(await run_querry(driver, query));
}

export async function read(input, driver) {
    const query = `
        match (a {name: '${input.node1}' })
        return a
    `
    return clean(await run_querry(driver, query));
}

export async function update(input, driver) {
    const query = `
        match (a {name: '${input.node1}' }) 
        set a.${input.property_key} = '${input.property_val}'
        return a
    `
    return clean(await run_querry(driver, query));
}

export async function delete_node(input, driver) {
    const query = `
        match (a {name: '${input.node1}' }) 
        detach delete a
    `
    return clean(await run_querry(driver, query));
}

export async function delete_relation(input, driver) {
    const query = `
        match (a {name: '${input.node1}' })-[r:${input.relation}]->(b {name: '${input.node2}' })
        delete r
    `
    return clean(await run_querry(driver, query));
}