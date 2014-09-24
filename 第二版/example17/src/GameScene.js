
require("GameObjHero.js")
require("GameObjEnemy.js")
require("GameMark.js")
require("GameHeroBullet.js")
require("GameEnemyBullet.js")
var GameScene = function() {
        
    var self = {};
    var m_layer;
    var bg1;
    var bg2;
    var hero;
    var gamemark;
    var bullets;
    var enemys;
    var enemybullets;
    var bloods;
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
           isreduce:false,
           isover:false,
           ctor:function () {
               this._super();
               this.init();
           },
           isCollion:function(p1,p2,w1,h1,w2,h2){
               //判断两个矩形是否碰撞
              if(Math.abs(p1.x - p2.x) < w1 + w2 && Math.abs(p1.y - p2.y) < h1 + h2){
                 return true;
              }
              return false;
           },
           update:function() {
               bg1.setPosition(cc.p(bg1.getPosition().x,bg1.getPosition().y - 2));
               bg2.setPosition(cc.p(bg2.getPosition().x,bg2.getPosition().y - 2));
               if(bg2.getPosition().y < 0){
                   var temp = bg2.getPosition().y + 480;
                   bg1.setPosition(cc.p(bg2.getPosition().x,temp));
               }
               if(bg1.getPosition().y < 0){
                   var temp = bg1.getPosition().y + 480;
                   bg2.setPosition(cc.p(bg1.getPosition().x,temp));
               }
               var hpos = hero.getPosition();
               //敌人和子弹碰撞检测
               for(var i = 0;i < 1;i ++){
                  enemy = enemys[i];
                  var epos = enemy.getPosition();
                  if(enemy.islife){
                  for(var j = 0;j < 5;j ++){
                      if(bullets[j].getIsvisble()){
                      if(this.isCollion(bullets[j].getPosition(),epos,5,13,21,28)){
                          enemy.setdie();
                          gamemark.addnumber(200);
                          break;
                      }}
                  }
                  }
                  if(this.isreduce && enemy.islife && this.isCollion(hpos,epos,21,22.5,21,28)){
                     enemy.setdie();
                     this.setherohurt();
                  }
               }
               //主角和敌人子弹碰撞
               if(!this.isreduce){
               for(var i = 0;i < 5;i ++){
                   if(this.isCollion(hpos,enemybullets[i].getPosition(),21,22.5,5,13)){
                      this.setherohurt();
                   }
               }
               }
           },
           setherohurt:function(){
               //主角受伤，减血
               hero.stopAllActions();
               if (blood == 0){
                   if(! this.isover){
                     this.isover = true;
                     this.setover();
                   }
               }else{
                   bloods[3 - blood].setVisible(false);
                   blood --;
               }
               var  action = cc.Blink.create(5, 10);
               hero.runAction(action);
               this.scheduleOnce(this.resetreduce, 5.0);
               this.isreduce = true;
          },
          resetreduce:function(){
               this.isreduce = false;
          },
          releaseheroBullet:function(x,y){
               //遍历子弹数组，不在使用的子弹释放
              for(var i = 0;i < 5;i ++){
                  if(!bullets[i].getIsvisble()){
                      //设置位置，并设置为显示
                      bullets[i].setPosition(cc.p(x,y));
                      bullets[i].setIsVisable();
                      break; 
                  }
              }
           },
           releaseenemyBullet:function(x,y){
               //遍历子弹数组，不在使用的子弹释放
              for(var i = 0;i < 10;i ++){
                  if(!enemybullets[i].getIsvisble()){
                      //设置位置，并设置为显示
                      enemybullets[i].setPosition(cc.p(x,y));
                      enemybullets[i].setIsVisable();
                      break; 
                  }
              }
           },
           setover:function(){
              //设置游戏结束
              var pMenu = this.getChildByTag(25);
              pMenu.setVisible(true);
              pMenu.setEnabled(true);
              gameover.setVisible(true);
              gameover.setScale(0);
              //pMenu.setScale(0);
              //pMenu.runAction(cc.ScaleTo.create(0.5,1));
              gameover.runAction(cc.ScaleTo.create(0.5,0.5));
          }
       });
       var layer = new MainLayer();
       bg1 = cc.Sprite.create("bg.png");
       bg1.setScale(0.5);
       bg2 = cc.Sprite.create("bg.png");
       bg2.setScale(0.5);
       bg1.setAnchorPoint(cc.p(0,0));
       bg2.setAnchorPoint(cc.p(0,0));
       bg1.setPosition(cc.p(0,0));
       bg2.setPosition(cc.p(0,winSize.height));
       layer.addChild(bg1,0);
       layer.addChild(bg2,0);
       layer.scheduleUpdate();
       hero = new GameObjHero();
       hero.setScale(0.5);
       hero.setPosition(cc.p(winSize.width / 2,100));
       layer.addChild(hero,2,1);
       gamemark = new GameMark();
       layer.addChild(gamemark,4);
       blood = 3;
       bloods = []
       var ui = cc.SpriteBatchNode.create("cat.png");
       blood1 = cc.Sprite.create(ui.getTexture());
       blood1.setPosition(cc.p(20,winSize.height - 20));
       blood1.setScale(0.2);
       ui.addChild(blood1);
       bloods[0] = blood1
       blood2 = cc.Sprite.create(ui.getTexture());
       blood2.setPosition(cc.p(50,winSize.height - 20));
       blood2.setScale(0.2);
       ui.addChild(blood2);
       bloods[1] = blood2
       blood3 = cc.Sprite.create(ui.getTexture());
       blood3.setPosition(cc.p(80,winSize.height - 20));
       blood3.setScale(0.2);
       ui.addChild(blood3);
       bloods[2] = blood3
       layer.addChild(ui,4);
       enemys = []
       for(var i = 0;i < 1;i ++){
           var enemy = new GameObjEnemy();
           var type = i + 1
           enemy.setPosition(cc.p(winSize.width/4 * type,winSize.height + 50));
           enemy.setScale(0.5);
           enemy.setType(type)
           enemys[i] = enemy;
           layer.addChild(enemy,1);
           enemy.movestart();
       }
       bullets = []
       for(var i = 0;i < 5;i ++){
           var mybullet = new GameHeroBullet()
           mybullet.setIsNotVisable();
           mybullet.setScale(0.5);
           bullets[i] = mybullet
           layer.addChild(mybullet,3);
       }
       enemybullets = []
       for(var i = 0;i < 5;i ++){
           var mybullet = new GameEnemyBullet()
           mybullet.setIsNotVisable();
           mybullet.setScale(0.5);
           enemybullets[i] = mybullet
           layer.addChild(mybullet,3);
       }
       gameover = cc.Sprite.create("gameover.png");
       gameover.setAnchorPoint(cc.p(0.5,0.5));
       gameover.setPosition(cc.p(0,0));
       gameover.setPosition(cc.p(winSize.width/2,winSize.height/2 + 70));
       gameover.setVisible(false);
       gameover.setScale(0.5);
       layer.addChild(gameover,5);
       var pCloseItem = cc.MenuItemImage.create("back.png","back.png",
                        self.callbacks.menuBackCallback,self.callbacks);
        pCloseItem.setPosition( cc.p(winSize.width/2,winSize.height/2 - 50) );
        pCloseItem.setScale(0.5);
        var pMenu = cc.Menu.create(pCloseItem);
        pMenu.setPosition(cc.p(0,0));
        layer.addChild(pMenu,5,25);
        pMenu.setVisible(false);
        pMenu.setEnabled(false);
       return layer;
    };
    sys.dumpRoot();
    sys.garbageCollect();
    return self;
};