let physicManager = {
    update: function (obj){
        if(obj.move_x === 0 && obj.move_y === 0)
            return "stop";
        var newX = obj.pos_x + obj.move_x * obj.speed;
        var newY = obj.pos_y + obj.move_y * obj.speed;

        var ts = mapManager.getTilesetIdx(newX, newY);
        var yts = mapManager.getTilesetIdx(newX, newY + obj.size_y - 5);
        var e = this.entityAtXY(obj, newX, newY);
        if(e !== null && obj.onTouchEntity)
            obj.onTouchEntity(e);
        if(ts !== 1 && obj.onTouchMap)
            obj.onTouchMap(ts);
        if (ts === 1 && e === null && yts === 1) {
            obj.pos_x = newX;
            obj.pos_y = newY;
        }
        else
            return "break";
        return "move";
    },

    entityAtXY: function(obj, x, y) {
        for(let i = 0; i < gameManager.entities.length; i++)
        {
            const e = gameManager.entities[i];
            if(e.name !== obj.name)
            {
                if(x + obj.size_x <= e.pos_x || y + obj.size_y <= e.pos_y ||
                   x >= e.pos_x + e.size_x || y >= e.pos_y + e.size_y)
                    continue;
                return e;
            }
        }
        return null;
    }
};
