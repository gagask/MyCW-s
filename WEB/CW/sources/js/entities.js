let Entity = {
    pos_x: 0,
    pos_y: 0,
    size_x: 0,
    size_y:0,
    extend(extendProto)
    {
        let object = Object.create(this);
        for(let property in extendProto)
        {
            if(this.hasOwnProperty(property) || typeof object[property] === 'undefined')
            {
                object[property] = extendProto[property];
            }
        }
        return object;
    }
};

let Bullet = Entity.extend({
    move_x: 0,
    move_y: 0,
    speed: 30,
    draw(ctx) {
        spriteManager.drawSprite(ctx, "Shot", this.pos_x, this.pos_y);
        },

    update() {
        physicManager.update(this);
    },

    onTouchMap(idx)
    {
        this.kill()
    },

    onTouchEntity(obj)
    {
        if (obj.name === "Enemy")
        {
            gameManager.collectedBon++
            obj.kill()
            this.kill()
            mapManager.drawCount()
            soundManager.play("sound/destroy.mp3")
        }
    },
    kill(){
        gameManager.kill(this);
    }
})

let Player = Entity.extend({
    lifetime: 100,
    move_x: 0,
    move_y: 0,
    speed: 10,
    draw(ctx) {
        spriteManager.drawSprite(ctx,"Ship", this.pos_x,this.pos_y);
    },
    update(){
        physicManager.update(this);
    },

    onTouchEntity(obj){
        if(obj.name === "Enemy")
        {
            this.kill()
            obj.kill()
            gameManager.onGameOver("lose")
        }
    },
    kill(){
        gameManager.kill(this);
    }
});

let Enemy = Entity.extend({
    lifetime: 100,
    move_x: 0,
    move_y: 0,
    speed: 10,

    draw(ctx) {
        spriteManager.drawSprite(ctx, "Enemy", this.pos_x, this.pos_y);

    },
    update() {
        physicManager.update(this);
    },

    onTouchMap(idx){
        this.kill()
    },

    onTouchEntity(obj)
    {
        if (obj.name === "player") {
            obj.kill()
            this.kill()
            gameManager.onGameOver("lose")
        }
    },

    kill() {
        gameManager.kill(this);
    }

});

