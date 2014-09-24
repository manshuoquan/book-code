module(..., package.seeall)
--获得图标
function getGameIcon(type,id)
	local iconFrame = cc.SpriteFrameCache:getInstance():getSpriteFrame("icon"..type..id..".png")
	local iconSprite = cc.Sprite:createWithSpriteFrame(iconFrame)
	return iconSprite
end
--动画
function createBlinkIconSprite()
	local animFrames = {}

	for i = 1, HZ_CUBE_COUNT do
		local iconFrame = cc.SpriteFrameCache:getInstance():getSpriteFrame("icon4"..i..".png")
		animFrames[i] = iconFrame
	end

	local iconSp = getGameIcon(4, 1)

    local animation = cc.Animation:createWithSpriteFrames(animFrames, 0.1)
	local animate = cc.Animate:create(animation)

    iconSp:runAction(CCRepeatForever:create(animate))

	return iconSp
end
--是否选择某个格子
function chooseIcon(node,isChoose)
	if node == nil then
		return 
	end
	node:getChildByTag(HZ_NORMAL_TAG):setVisible(not isChoose)
    node:getChildByTag(HZ_SELECT_TAG):setVisible(isChoose)
end
--创建Node
function createIconById(id)
	local rootNode = CCNode:create()

    local matchSp  = getGameIcon(HZ_CUBE_TYPE_MATCH,  id)
	matchSp:setTag(HZ_MATCH_TAG)
	rootNode:addChild(matchSp)
    local selectSp = getGameIcon(HZ_CUBE_TYPE_SELECT, id)
	selectSp:setTag(HZ_SELECT_TAG)
	rootNode:addChild(selectSp)
	local normalSp = getGameIcon(HZ_CUBE_TYPE_NORMAL, id)
	normalSp:setTag(HZ_NORMAL_TAG)
	rootNode:addChild(normalSp)

	return rootNode
end
--清除点
function clearIcon(node)
	if node == nil then
		return 
	end
	node:getChildByTag(HZ_NORMAL_TAG):setVisible(false)
    node:getChildByTag(HZ_SELECT_TAG):setVisible(false)
    local matchSp = node:getChildByTag(HZ_MATCH_TAG)
    matchSp:setVisible(true)
    matchSp:runAction(cc.FadeOut:create(0.2))
end