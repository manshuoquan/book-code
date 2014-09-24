var GameAbout = function() {
        
    var self = {};
    var m_layer;
    //回调函数对象，和回调函数集合
    self.callbacks = {
       menuBackCallback:function(sender) {
           var scene = director.getRunningScene()
           scene.removeAllChildren()
           var game = GameMenu()
           var layer = game.getPlayScene();
           scene.addChild(layer);
       },
       menuEnter:function() {
           var menu = m_layer.getChildByTag(4);
           menu.setEnabled(true);
       }
    };
        
    self.getPlayScene = function() {
       director = cc.Director.getInstance();
       winSize = director.getWinSize();
       centerPos = cc.p( winSize.width/2, winSize.height/2 );
       var MainLayer = cc.Layer.extend({
           ctor:function () {
               this._super();
               this.init();
           },
           onEnter:function () {
               this._super();
               var mainmenu = m_layer.getChildByTag(4);
               mainmenu.setPositionX(-100);
               mainmenu.runAction(cc.Sequence.create(
               cc.EaseElasticIn.create(cc.MoveBy.create(0.5,cc.p(100,0))),
               cc.CallFunc.create(self.callbacks.menuEnter,self.callbacks)));
               var title = m_layer.getChildByTag(3);
               title.setPositionY(winSize.height + 20);
               title.runAction(cc.EaseElasticIn.create(cc.MoveBy.create(0.5,cc.p(0,-100))));
               var bgstar = m_layer.getChildByTag(1);
               bgstar.setPositionX(winSize.width/3 * 2);
               bgstar.runAction(cc.MoveBy.create(0.5,cc.p(winSize.width/3,0)));
               var kuang = m_layer.getChildByTag(2);
               kuang.setPositionX(-200);
               kuang.runAction(cc.MoveTo.create(0.5,cc.p(winSize.width/2,winSize.height/2)));
           }
       });
       var layer = new MainLayer();
       //screen backGround
       var bg = cc.Sprite.create("bg.png");
       bg.setScale(0.5);
       bg.setPosition(cc.p(winSize.width / 2, winSize.height / 2));
       layer.addChild(bg,0,0);
       //moon star
       var bgstar = cc.Sprite.create("moon.png");
       bgstar.setScale(0.5);
       bgstar.setAnchorPoint(cc.p(0.5,0));
       bgstar.setPosition(cc.p(winSize.width/3, 0));
       layer.addChild(bgstar,1,1);
       //moon star
       var kuang = cc.Sprite.create("tb.png");
       kuang.setScale(0.5);
       kuang.setAnchorPoint(cc.p(0.5,0.5));
       kuang.setPosition(cc.p(winSize.width/2,winSize.height/2));
       layer.addChild(kuang,2,2);

       var abouttitle = cc.Sprite.create("about.png");
       abouttitle.setScale(0.5);
       abouttitle.setPosition(cc.p(winSize.width/2,winSize.height - 20));
       layer.addChild(abouttitle,3,3);

       var inf = "name:meow war\n\nprogram:shuoquan man\n\nart design:peng xu\n\ncompany:hz books\n\n    powered by cocos2D-x"
       var myjineng = cc.LabelTTF.create(inf,"Marker Felt",40,cc.size(400,400),cc.TEXT_ALIGNMENT_LEFT); 
       myjineng.setAnchorPoint(cc.p(0,1));
       myjineng.setColor(cc.color(200,200,200));
       myjineng.setPosition(cc.p(50,600));
       kuang.addChild(myjineng);

       var back = cc.MenuItemImage.create("backA.png", "backA.png",self.callbacks.menuBackCallback,self.callbacks);
       back.setScale(0.5);
       back.setPosition(cc.p(winSize.width - 20,winSize.height - 20));

       var mainmenu = cc.Menu.create(back);
       mainmenu.setPosition(cc.p(0,0));
       mainmenu.setEnabled(false);
       layer.addChild(mainmenu,3,4);
       m_layer = layer;

            
       return m_layer;
    };

    sys.dumpRoot();
    sys.garbageCollect();
    return self;
};
