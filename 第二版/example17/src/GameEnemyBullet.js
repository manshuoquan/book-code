var GameEnemyBullet = cc.Layer.extend({
    //成员变量
    isvisable:false,
    //成员函数
    GameEnemyBullet:function(){
       isvisable = false
       sys.dumpRoot();
       sys.garbageCollect();
    },
    onEnter:function(){
       this._super();
       this.setContentSize(cc.size(21,52));
       var mainsprite = cc.Sprite.create("DrDogZD.png");
       mainsprite.runAction(cc.RepeatForever.create(cc.RotateBy.create(1,360)));
       this.addChild(mainsprite);
    },
    onExit:function(){
       this._super()
    },
    setIsNotVisable:function(){
       this.setVisible(false)
       this.isvisable = false
       this.stopAllActions()
    },
    getIsvisble:function(){
       return this.isvisable
    },
    setIsVisable:function(){
       this.setVisible(true);
       this.isvisable = true;
       this.runAction(cc.RepeatForever.create(cc.RotateBy.create(1,360)));
       this.runAction(cc.Sequence.create(
       	cc.MoveTo.create((this.getPosition().y + 50)/150,cc.p(this.getPosition().x,-50)),
        cc.CallFunc.create(this.setIsNotVisable,this)));
    }
});