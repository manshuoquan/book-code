var GameHeroBullet = cc.Layer.extend({
    //成员变量
    isvisable:false,
    //成员函数
    GameHeroBullet:function(){
       isvisable = false
       sys.dumpRoot();
       sys.garbageCollect();
    },
    onEnter:function(){
       this._super();
       this.setContentSize(cc.size(21,52));
       var mainsprite = cc.Sprite.create("YuGuZD.png");
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
       this.runAction(cc.Sequence.create(
        cc.MoveTo.create((-this.getPosition().y + 550)/150,cc.p(this.getPosition().x,550)),
        cc.CallFunc.create(this.setIsNotVisable,this)));
    }
});