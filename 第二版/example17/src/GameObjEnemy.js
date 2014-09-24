var GameObjEnemy = cc.Layer.extend({
    //成员变量
    mainbody:null,
    boom:null,
    type:0,
    islife:true,
    //成员函数
    GameObjEnemy:function(){
       isvisable = false
       sys.dumpRoot();
       sys.garbageCollect();
    },
    onEnter:function(){
       this._super();
       this.setContentSize(cc.size(99,111));
       mainbody = cc.Sprite.create("DrDog1.png");
       var animation = cc.Animation.create();
       animation.addSpriteFrameWithFile("DrDog1.png");
       animation.addSpriteFrameWithFile("DrDog2.png");
       animation.setDelayPerUnit(0.1);
       animation.setRestoreOriginalFrame(true);
       mainbody.runAction(cc.RepeatForever.create(cc.Animate.create(animation)));
       this.addChild(mainbody);
       boom = cc.Sprite.create("boom1.png");
       this.addChild(boom);
       boom.setVisible(false);
       this.schedule(this.releasebullet, 1.2);
    },
    onExit:function(){
       this._super()
    },
    setType:function(mtype){
       type = mtype
    },
    releasebullet:function(){
       var pos = this.getPosition()
       var size = cc.Director.getInstance().getWinSize();
       if(pos.y > 20 && pos.y < size.height && this.islife){
           this.getParent().releaseenemyBullet(pos.x,pos.y - 30)
       }
    },
    movestart:function(){
       this.islife = true;
       var mtype = type
       //贝塞尔曲线移动
       var controlPoints1 = [cc.p(this.getPosition().x - 400,330)
                        ,cc.p(this.getPosition().x + 400,280)
                        ,cc.p(this.getPosition().x,-70)]
       var bezierBy2 = cc.BezierTo.create(6, controlPoints1);
       var controlPoints2 = [cc.p(this.getPosition().x + 400,330)
                        ,cc.p(this.getPosition().x - 400,280)
                        ,cc.p(this.getPosition().x,-70)]
       var bezierBy1 = cc.BezierTo.create(6, controlPoints2);
       if (mtype == 1 ){
           this.runAction(cc.Sequence.create(cc.MoveBy.create(6,cc.p(0,-600)),
            cc.CallFunc.create(this.restart,this)));
       }else if (mtype == 2) {
           this.runAction(cc.Sequence.create(bezierBy1,
            cc.CallFunc.create(this.restart,this)));
       }else if (mtype == 3) {
            this.runAction(cc.Sequence.create(bezierBy2,
            cc.CallFunc.create(this.restart,this)));
       }
    }, 
    restart:function(){
       type = Math.floor(Math.random() * 2) + 1;
       mainbody.setVisible(true);
       boom.setVisible(false);
       var size = cc.Director.getInstance().getWinSize();
       this.setPosition(cc.p(size.width/4 * type,size.height + 50));
       this.islife = true;
       mainbody.setVisible(true);
       boom.setVisible(false);
       this.movestart();
    },
    setdie:function(){
       this.islife = false;
       mainbody.setVisible(false);
       boom.setVisible(true);
       this.stopAllActions();
       //爆炸动画
       var boomAnimation = cc.Animation.create();
       boomAnimation.addSpriteFrameWithFile("boom1.png");
       boomAnimation.addSpriteFrameWithFile("boom2.png");
       boomAnimation.addSpriteFrameWithFile("boom3.png");
       boomAnimation.addSpriteFrameWithFile("boom4.png");
       boomAnimation.addSpriteFrameWithFile("boom5.png");
       boomAnimation.setDelayPerUnit(0.1);
       boomAnimation.setRestoreOriginalFrame(true);
       boom.runAction(cc.Sequence.create(cc.Animate.create(boomAnimation),
        cc.CallFunc.create(this.restart,this)));
    }
});