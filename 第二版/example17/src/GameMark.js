var GameMark = cc.Layer.extend({
    //成员变量
    mark:0,
    _arr:null,
    //成员函数
    GameMark:function(){
       sys.dumpRoot();
       sys.garbageCollect();
    },
    onEnter:function(){
       this._super();
       director = cc.Director.getInstance();
       winSize = director.getWinSize();
       this.setContentSize(winSize);
       var title = cc.Sprite.create("score.png");
       title.setPosition(cc.p(winSize.width/2 + 40,winSize.height - 15));
       title.setScale(0.5);
       this.addChild(title);
       var array = []
       for(var i = 0;i < 5;i ++){
           var shu = cc.Sprite.create("shu.png");
           ui = shu.getTexture()
           shu.setScale(0.5);
           shu.setTextureRect(cc.rect(234,0,26,31));
           shu.setPosition(cc.p(winSize.width - 15 - i * 15,winSize.height - 15));
           array[i] = shu
           this.addChild(shu,10 + i,10 + i)
       }
       this._arr = array
    },
    addnumber:function(num){
       this.mark += num;
       var mark = this.mark 
       var temp = mark % 10;
       var node = this._arr[0]
       if(temp > 0){
          node.setTexture(ui);
          node.setTextureRect(cc.rect((temp - 1) * 26,0,26,31)); 
       }else{
          node.setTexture(ui);
          node.setTextureRect(cc.rect(234,0,26,31)); 
       }
       node = this._arr[1]
       temp = Math.floor((mark % 100) / 10);
       if(temp > 0){
          node.setTexture(ui);
          node.setTextureRect(cc.rect((temp - 1) * 26,0,26,31)); 
       }else{
          node.setTexture(ui);
          node.setTextureRect(cc.rect(234,0,26,31)); 
       }
       node = this._arr[2]
       temp = Math.floor((mark % 1000) / 100);
       if(temp > 0){
          node.setTexture(ui);
          node.setTextureRect(cc.rect((temp - 1) * 26,0,26,31)); 
       }else{
          node.setTexture(ui);
          node.setTextureRect(cc.rect(234,0,26,31)); 
       }
       node = this._arr[3]
       temp = Math.floor((mark % 10000) / 1000);
       if(temp > 0){
          node.setTexture(ui);
          node.setTextureRect(cc.rect((temp - 1) * 26,0,26,31)); 
       }else{
          node.setTexture(ui);
          node.setTextureRect(cc.rect(234,0,26,31)); 
       } 
       node = this._arr[4] 
       temp = Math.floor(mark / 10000);
       if(temp > 0){
          node.setTexture(ui);
          node.setTextureRect(cc.rect((temp - 1) * 26,0,26,31)); 
       }else{
          node.setTexture(ui);
          node.setTextureRect(cc.rect(234,0,26,31)); 
       }   
    }
});