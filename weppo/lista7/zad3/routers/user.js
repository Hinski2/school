const express = require('express')
const router = express.Router()

router.get('/new', (req, res) =>{
    res.render('./../views/form/new.ejs');
})

router.post('/res', (req, res) => {
    const {firstName, lastName, subject, tasks} = req.body;
    let selectedTasks = [];
    if(tasks){
        if(Array.isArray(tasks)) selectedTasks = tasks
        else selectedTasks = [tasks]
    }

    res.render('./../views/form/print.ejs', {
        firstName, 
        lastName,
        subject,
        tasks: selectedTasks
    })
})

module.exports = router