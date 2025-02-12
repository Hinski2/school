// npm run start 
const express = require('express')
const path = require('path')
const app = express()

// set permissions
app.use(express.static(path.join(__dirname, 'public')))     // enables using static files 
app.use(express.urlencoded({extended: true}))               // enables to read from forms 

app.set('view engine', 'ejs') 

const userRouter = require('./routers/user')
app.use('/user', userRouter)

app.listen(3000)