let gameManager = {
    factory: {},
    entities: [],
    player: null,
    laterKill: [],
    started: false,
    collectedBon: 0,
    is_bullet: 2,
    intervalId: 0,
    enemyIntervalId: 0,
    lvlNum: "",
    num_maked_enemys: 0,


    initPlayer(obj) {
        this.player = obj;
    },

    kill(obj) {
        this.laterKill.push(obj);
    },

    initGame(){
        if(!this.started) {
            this.entities.forEach(function (e)
            {
                if (e.name === "bullet")
                    e.move_x = 1
            })
            this.started = true;
        }
    },

    update() {
        if(this.player === null)
            return;
        this.player.move_x = 0;
        this.player.move_y = 0;

        if (eventsManager.action["up"])
            this.player.move_y = -1;
        if (eventsManager.action["down"])
            this.player.move_y = 1;

        if (eventsManager.action["space"] && this.is_bullet !== 0) {
            let obj = Object.create(this.factory["bullet"]);
            obj.size_x = 50;
            obj.size_y = 13;
            obj.pos_x = this.player.pos_x + obj.size_x;
            obj.pos_y = this.player.pos_y + obj.size_y + 10;
            obj.name = "bullet";
            obj.move_x = 1
            gameManager.entities.push(obj);
            soundManager.play("sound/shoot.mp3")

            this.is_bullet--
        }

        this.entities.forEach(function (e) {
            e.update()
        })

        //удаление с поля всех уничтоженных элементов в том числе и пули
        for(let i = 0; i < this.laterKill.length; i++) {
            const idx = this.entities.indexOf(this.laterKill[i]);
            if(idx > -1){
                let check = this.entities[idx].name;
                if (check === "bullet")
                    this.is_bullet++
                this.entities.splice(idx, 1);
            }
        }


        let flag = 0
        this.entities.forEach(function (e) {
            if(e.name === "Enemy"){
                flag++
            }
        })

        if(flag === 0 && this.num_maked_enemys === this.lvlNum*15)
            this.onGameOver("win")

        if(this.laterKill.length > 0)
            this.laterKill.length = 0;


        mapManager.draw(ctx);
        this.draw(ctx);
    },

    updateEnemies() {
        this.num_maked_enemys++
        let obj = Object.create(this.factory["Enemy"]);
        obj.size_x = 50;
        obj.size_y = 50;
        obj.pos_x = 930;
        obj.pos_y = 20 + (Math.random()*6)*50;
        obj.name = "Enemy";
        obj.move_x = -1
        obj.speed *= this.lvlNum
        gameManager.entities.push(obj);
        if(this.lvlNum * 15 === this.num_maked_enemys)
            clearInterval(this.enemyIntervalId)
    },

    onGameOver(result) {
        this.player = null
        clearInterval(this.intervalId)
        clearInterval(this.enemyIntervalId)
        if (result === "win") {
            soundManager.play("sound/win.mp3")

            if(this.lvlNum === 2){
                let a = this.collectedBon
                setTimeout(() => {alert(`Вы выиграли с ${a}/45 очками!`)}, 1000)
                this.collectedBon = 0
                this.lvlNum = 0
                mapManager.drawLevel()
                mapManager.drawCount()
                document.getElementById("start").disabled = false
                setTimeout(() => {ctx.clearRect(0,0,1000, 400)}, 10)
            }
            if(this.lvlNum === 1){
                setTimeout(() => {alert("Вы открыли 2-й уровень!")}, 10)
                gameManager.reload("maps/tilemap.json", 2)
                gameManager.play()
            }
        }
        else {
            soundManager.play("sound/lose.mp3")
            setTimeout(() => {alert("Вы проиграли!")}, 10)
            this.collectedBon = 0
            this.lvlNum = 0
            mapManager.drawLevel()
            mapManager.drawCount()
            document.getElementById("start").disabled = false
            setTimeout(() => {ctx.clearRect(0,0,1000, 400)}, 10)
        }
    },

    reload(jsonName, num) {
        this.lvlNum = num
        gameManager.clear()
        mapManager.clear()
        gameManager.loadAll(jsonName)
        gameManager.initGame()
    },

    clear() {
        this.started = false;
        eventsManager.action["up"] = false;
        eventsManager.action["down"] = false;
        eventsManager.action["space"] = false;
        this.player = null
        this.is_bullet = 2
        this.entities.length = 0
        this.num_maked_enemys = 0
    },

    draw(ctx) {
        for (let e = 0; e < this.entities.length; e++)
            this.entities[e].draw(ctx);
    },

    loadAll(jsonName) {
        this.factory['Player'] = Player;
        this.factory['Enemy'] = Enemy;
        this.factory['bullet'] = Bullet
        mapManager.loadMap(jsonName);
        spriteManager.loadAtlas("./maps/sprites.json", "./maps/img/spritesheet.png");
        mapManager.parseEntities();
        mapManager.draw(ctx);
        eventsManager.setup();
        mapManager.drawLevel()
        mapManager.drawCount();
        soundManager.init();
        soundManager.loadArray(['sound/shoot.mp3', 'sound/lose.mp3', 'sound/win.mp3', 'sound/destroy.mp3', 'sound/start.mp3']);
    },

    play() {
        soundManager.play('sound/start.mp3')
        this.intervalId = setInterval(updateWorld, 50);
        this.enemyIntervalId = setInterval(updateEnemies, 1000);
    },
};

function updateEnemies() {
    gameManager.updateEnemies()
}

function updateWorld() {
    gameManager.update();
}
