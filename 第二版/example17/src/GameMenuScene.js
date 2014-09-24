require("jsb.js");
require("GameAboutScene.js");
require("GameScene.js")

try {
    cc.view.adjustViewPort(true);
    cc.view.setDesignResolutionSize(320,480,cc.ResolutionPolicy.SHOW_ALL);
    cc.view.resizeWithBrowserSize(true);
    director = cc.Director.getInstance();
    winSize = director.getWinSize();
    centerPos = cc.p( winSize.width/2, winSize.height/2 );


    var GameMenu = function() {
        
        var self = {};
        var m_layer;
        var issound = true;
        var soundItem;
        //回调函数对象，和回调函数集合
        self.callbacks = {
           menuNewGameCallback:function(sender) {
              var scene = director.getRunningScene()
              scene.removeAllChildren()
              var game = GameScene()
              var layer = game.getPlayScene();
              scene.addChild(layer);
           },
           menuContinueCallback:function(sender) {
              var scene = director.getRunningScene()
              scene.removeAllChildren()
              var game = GameScene()
              var layer = game.getPlayScene();
              scene.addChild(layer);
           },
           menuAboutCallback:function(sender) {
              var scene = director.getRunningScene()
              scene.removeAllChildren()
              var game = GameAbout()
              var layer = game.getPlayScene();
              scene.addChild(layer);
           },
           menuSoundCallback:function(sender) {
              if(! issound){
                 soundItem.setNormalImage(cc.Sprite.create("sound-on-A.png"));
                 soundItem.setDisabledImage(cc.Sprite.create("sound-on-B.png"));
                 cc.audioEngine.playMusic("res/background.mp3",true)
                 issound = true;
              }else{
                 soundItem.setNormalImage(cc.Sprite.create("sound-off-A.png"));
                 soundItem.setDisabledImage(cc.Sprite.create("sound-off-B.png"));
                 cc.audioEngine.stopMusic()
                 issound = false;
           }
           },
           menuEnter:function() {
               var menu = m_layer.getChildByTag(3);
               menu.setEnabled(true);
           }
        };
        
        self.getPlayScene = function() {
            var MainLayer = cc.Layer.extend({
               ctor:function () {
                   this._super();
                   this.init();
               },
               onEnter:function () {
                  this._super();
                  var mainmenu = m_layer.getChildByTag(3);
                  mainmenu.setOpacity(0)
                  mainmenu.runAction(cc.Sequence.create(
                      cc.FadeIn.create(0.5),
                      cc.CallFunc.create(self.callbacks.menuEnter,self.callbacks)));
                  var title = m_layer.getChildByTag(2);
                  title.setPositionY(winSize.height + 20);
                  title.runAction(cc.EaseElasticIn.create(cc.MoveBy.create(0.5,cc.p(0,-100))));
                  var bgstar = m_layer.getChildByTag(1);
                  bgstar.setPositionX(winSize.width/3 * 2);
                  bgstar.runAction(cc.MoveBy.create(0.5,cc.p(winSize.width/3,0)));
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
            bgstar.setPosition(cc.p(winSize.width/3 * 2, 0));
            layer.addChild(bgstar,1,1);
            //init title
            var title = cc.Node.create();
            title.setContentSize(cc.size(winSize.width - 40,50));
            //line meowstar
            var ptmLabel = cc.Sprite.create("meowstar.png");
            ptmLabel.setScale(0.5);
            ptmLabel.setPosition(cc.p(0,30));
            title.addChild(ptmLabel);
            //line battle
            var ptbLabel = cc.Sprite.create("battle.png");
            ptbLabel.setScale(0.5);
            ptbLabel.setPosition(cc.p(0,-30) );
            title.addChild(ptbLabel);
            title.setPosition(cc.p(winSize.width / 2, winSize.height - 80));
            layer.addChild(title,2,2);

            //init button
            var newGameItem = cc.MenuItemImage.create("newgameA.png", "newgameB.png",self.callbacks.menuNewGameCallback,self.callbacks);
            newGameItem.setScale(0.5);
            newGameItem.setPosition(cc.p(winSize.width / 2,winSize.height / 2 - 20));
            var continueItem = cc.MenuItemImage.create("continueA.png", "continueB.png",self.callbacks.menuContinueCallback,self.callbacks);
            continueItem.setScale(0.5);
            continueItem.setPosition(cc.p(winSize.width / 2,winSize.height / 2 - 80));
            var aboutItem = cc.MenuItemImage.create("aboutA.png", "aboutB.png",self.callbacks.menuAboutCallback,self.callbacks);
            aboutItem.setScale(0.5);
            aboutItem.setPosition(cc.p(winSize.width / 2,winSize.height / 2 - 140));
            soundItem = cc.MenuItemImage.create("sound-on-A.png", "sound-on-B.png",self.callbacks.menuSoundCallback,self.callbacks);
            soundItem.setScale(0.5);
            soundItem.setPosition(cc.p(40,40));
            //create menu
            var mainmenu = cc.Menu.create(newGameItem,continueItem,aboutItem,soundItem);
            mainmenu.setPosition(cc.p(0,0));
            mainmenu.setEnabled(false);
            layer.addChild(mainmenu,1,3);
            mainmenu.runAction(cc.Sequence.create(
                                                  cc.FadeIn.create(0.5),
                                                  cc.CallFunc.create(self.callbacks.menuEnter,self.callbacks)));
            m_layer = layer;

            cc.audioEngine.playMusic("res/background.mp3",true)
            return m_layer;
        };
        sys.dumpRoot();
        sys.garbageCollect();
        
        return self;
    };
    var scene = cc.Scene.create();
    var game = GameMenu();
    scene.addChild(game.getPlayScene());
    director.runWithScene(scene);
    
    __jsc__.garbageCollect();
    
} catch(e) {log(e);}