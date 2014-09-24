module(..., package.seeall)
require "AudioEngine"
local visibleSize = cc.Director:getInstance():getVisibleSize()
--眼睛动画显示
local function createShiningSprite()
	local eyeSp = cc.Sprite:create(HZ_GETRESOURCE("eye.png"))

	local scale1 = cc.ScaleTo:create(0.1, 2, 0.4)
	local scale2 = cc.ScaleTo:create(0.1, 2, 2)	
	local delay = cc.DelayTime:create(2)		

	local sequence = cc.Sequence:create(scale1,scale2,delay)

	local repeatFunc = cc.RepeatForever:create(sequence)
	eyeSp:runAction(repeatFunc)

	return eyeSp
end
--标题文字
local function createTitleLabel()
    local titLabel = cc.LabelTTF:create(HZ_LANG.stringFormDic("title"), "Arial", 50)
	titLabel:setColor(cc.c3b(255, 0, 0))
	titLabel:setOpacity(0)		
	local fade1 = cc.FadeIn:create(0.5)
	local fade2 = cc.FadeOut:create(0.5)			

	local sequence = cc.Sequence:create(fade1,fade2)

	local repeatFunc = cc.RepeatForever:create(sequence)
	titLabel:runAction(repeatFunc)

	titLabel:setPosition(visibleSize.width / 2, visibleSize.height - 500)

	return titLabel
end
--提示文字
local function createTipLabel()
    local tipLabel = cc.LabelTTF:create(HZ_LANG.stringFormDic("pressScreen"), "Arial", 30)
			
	local scale1 = cc.ScaleTo:create(1.5, 1.2)
	local scale2 = cc.ScaleTo:create(1.5, 1)			

	local sequence = cc.Sequence:create(scale1,scale2)

	local repeatFunc = cc.RepeatForever:create(sequence)
	tipLabel:runAction(repeatFunc)

	tipLabel:setPosition(visibleSize.width / 2, 300)

	return tipLabel
end
--填充ui
local fillUi = function(rootLayer)
    local splashSp = cc.Sprite:create(HZ_GETRESOURCE("splash_bg.png"))
	splashSp:setPosition(visibleSize.width / 2, splashSp:getContentSize().height / 2)
    rootLayer:addChild(splashSp)

    local eyeSp1 = createShiningSprite()
	eyeSp1:setPosition(visibleSize.width / 2 - 80, visibleSize.height / 2 + 180)
	rootLayer:addChild(eyeSp1)

	local eyeSp2 = createShiningSprite()
	eyeSp2:setPosition(visibleSize.width / 2 + 80, visibleSize.height / 2 + 180)
	rootLayer:addChild(eyeSp2)

	rootLayer:addChild(createTipLabel())
	rootLayer:addChild(createTitleLabel())
end
--显示
show = function()
    local rootLayer = cc.Layer:create()
    fillUi(rootLayer)

    local function onTouch(eventType, x, y)
        if eventType == "began" then
            HZ_SHOW_UI_LAYER(HZ_GAME)   
            return true
        end
    end

    rootLayer:registerScriptTouchHandler(onTouch)
    rootLayer:setTouchEnabled(true)
    --播放声音
    AudioEngine.playMusic("res/bgm_game.wav", true)
	return rootLayer
end	