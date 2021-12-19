
const { exec } = require('child_process');

exports.findThread = (searchString) => {
    const query = `top -H -b -n 1 | grep ${searchString}`;

    const promise = new Promise((resolve, reject) => {
        exec(query, (error, stdout, stderr) => {
            const rows = stdout.split('\n');
            rows.pop();
            
            if(rows.length == 0) {
                reject("Can't find thread")
            }

            if(rows.length > 1) {
                reject(`Can't isolate thread, found ${rows.length} candidates\n${rows}`)
            }

            const row = rows[0].trim().split(' ');
            resolve(row[0]);
        });
    });
    return promise;
}

exports.startPerf = (tid) => {
    const query = `perf stat -t ${tid} 2> stat.out`
    exec(query);
}

exports.stopPerf = () => {
    const query = `killall -INT perf`
    exec(query);
}
