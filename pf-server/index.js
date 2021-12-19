
const express = require('express');
const cors = require('cors');
const { findThread, startPerf, stopPerf } = require('./shell');
const app = express();
const port = 3000;

app.use(cors());

const sleep = (ms) => {
    return new Promise((resolve) => {
        setTimeout(resolve, ms);
    });
}

app.get('/start', async (req, res) => {
    const tid = await findThread('Dedicat').catch(e => {
        console.log(e);
    });

    if(tid) {
        console.log(tid);
        startPerf(tid);
        res.send(`Start performance counter on thread ${tid}`);
    } else {
        res.statusCode = 500;
        res.send('Error starting performance counter');
    }
});

app.get('/stop', async (req, res) => {
    stopPerf();
    res.send('Stop performance counter');
});

app.listen(port, () => {
    console.log(`Performance server listening at http://localhost:${port}`);
});