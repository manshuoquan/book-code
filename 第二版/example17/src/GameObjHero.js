//oop
var GameObjHero = cc.Layer.extend({
    //成员变量
    _lefthand:null,
    _righthand:null,
    _offset:null,
    _iscontrol:null,
    //成员函数
    GameObjHero:function(){
       sys.dumpRoot();
       sys.garbageCollect();
    },
    rect:function(){
       var h = 90;
       var w = 85;
       return cc.rect(-w/2,-h/2,w,h);
    },
    containsTouchLocation:function(touch){
       var r = this.rect();
       return cc.rectContainsPoint(r,touch);
    },
    ccTouchBegan:function(touch,event){
       //if(this.getParent().isover)
       //   return false;
       var touchPoint = this.convertToNodeSpace(touch.getLocation());
       if(! this.containsTouchLocation(touchPoint)){
           return false;
       }else{
          this._iscontrol = true;
          _offset.x = touch.getLocation().x - this.getPosition().x;
          _offset.y = touch.getLocation().y - this.getPosition().y;
       }
    },
    ccTouchMoved:function(touch,event){
       if(this._iscontrol){
          var touchPoint = touch.getLocation(); 
          var x = touchPoint.x - _offset.x;
          var y = touchPoint.y - _offset.y;
          if(x < this.getPosition().x){
             _lefthand.setFlippedY(true);
             _righthand.setFlippedY(false);
          }else{
             _lefthand.setFlippedY(false);
             _righthand.setFlippedY(true);
          }
          this.setPosition(x,y);       
       }
    },
    ccTouchEnded:function(touch,event){
       if(this._iscontrol){
          this._iscontrol = false;
          _lefthand.setFlippedY(false);
          _righthand.setFlippedY(false);
       }
    },
    onMouseDown:function(touch,event){
       this.ccTouchBegan(touch,event)
    },
    onMouseDragged:function(touch,event){
       this.ccTouchMoved(touch,event)
    },
    onMouseUp:function(touch,event){
       this.ccTouchEnded(touch,event)
    },
    onTouchesBegan:function(touch,event){
       this.ccTouchBegan(touch[0],event)
    },
    onTouchesMoved:function(touch,event){
       this.ccTouchMoved(touch[0],event)
    },
    onTouchesEnded:function(touch,event){
       this.ccTouchEnded(touch[0],event)
    },
    releasebullet:function(){
       if(this._iscontrol){
           var pos = this.getPosition()
           this.getParent().releaseheroBullet(pos.x,pos.y + 30)
       }
    },
    onEnter:function(){
       this._super();
       this.setContentSize(cc.size(85,90));
       if( 'touches' in sys.capabilities )
          this.setTouchEnabled(true);
       else if( 'mouse' in sys.capabilities )
          this.setMouseEnabled(true);
       var mainsprite = cc.Sprite.create("catBody1.png");
       var animation = cc.Animation.create();
       animation.addSpriteFrameWithFile("catBody1.png");
       animation.addSpriteFrameWithFile("catBody2-4.png");
       animation.addSpriteFrameWithFile("catBody3.png");
       animation.addSpriteFrameWithFile("catBody2-4.png");
       animation.setDelayPerUnit(0.1);
       animation.setRestoreOriginalFrame(true);
       mainsprite.setPosition(cc.p(0,0))
       mainsprite.runAction(cc.RepeatForever.create(cc.Animate.create(animation)));
       this.addChild(mainsprite);

       //tails
       var tail = cc.Sprite.create("catTail.png");
       tail.setAnchorPoint(cc.p(0.5,1));
       tail.setPosition(cc.p(-5,-29));
       tail.setScale(0.5);
       tail.setRotation(20);
       tail.runAction(cc.RepeatForever.create(cc.Sequence.create(cc.RotateBy.create(0.5,-40),
        cc.RotateBy.create(0.5,40))));
       this.addChild(tail);

       _lefthand = cc.Sprite.create("catHand1.png");
       _lefthand.setAnchorPoint(cc.p(1,0.5));
       _lefthand.setPosition(cc.p(-18,-20));
       this.addChild(_lefthand);
       _righthand = cc.Sprite.create("catHand2.png");
       _righthand.setPosition(cc.p(18,-20));
       _righthand.setAnchorPoint(cc.p(0,0.5));
       this.addChild(_righthand);
       _offset = cc.p(0,0);
       _iscontrol = false;
       this.schedule(this.releasebullet,1.0);
    }
});
