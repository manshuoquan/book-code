module(..., package.seeall)
local m_gameGrid  = require("src/gameLogic/gameGrid.lua")--棋盘
local m_gameObj   = require("src/gameLogic/gameObj.lua") --格子
local m_gridLogic = require("src/gameLogic/gridLogic.lua") --逻辑
local m_rootLayer = nil --根节点
local m_grid_start_tag  = 0--起始标签
local m_grid_romove_tag = 10000--删除时
local m_grid_down_tag   = 20000--下落时
--触摸相关
local m_isTouching = false
local m_isMoving = false
local m_isRefreshing = false
local m_touchStartPoint = {}
local m_touchCurPoint = {}
local m_touchStartIndex = {}
local m_touchCurIndex = {}
local m_curSelectTag = nil
local m_switchPair = {}
local m_grid_down_table = {}
-----------------------------------
--重置选择格子
local function resetSelectGrid()
    if m_curSelectTag ~= nil then
        local rootNode = m_rootLayer:getChildByTag(m_grid_start_tag + m_curSelectTag)
        m_gameObj.chooseIcon(rootNode,false)
        m_curSelectTag = nil
    end
end
--选择某个格子
local function chooseGrid(x,y)
    if x == 0 or y == 0 then
        return 
    end
    resetSelectGrid()
    m_curSelectTag = m_gridLogic.revertIndexToTag(x,y)
    local rootNode = m_rootLayer:getChildByTag(m_grid_start_tag + m_curSelectTag)
    m_gameObj.chooseIcon(rootNode,true)
end
--显示格子
local function createNodeByGrid(x,y)
    local iconNode = m_gameObj.createIconById(m_gameGrid.getGridDataByIndex(x,y))
    iconNode:setTag(m_grid_start_tag + m_gridLogic.revertIndexToTag(x,y))
	iconNode:setPosition(m_gridLogic.getGridPoint(x,y))
	return iconNode
end
--填充棋盘显示
local function initGameGridShow()
	for x = 1, HZBoardSizeX do
		for y = 1, HZBoardSizeY do
			local iconNode = createNodeByGrid(x,y)
			m_rootLayer:addChild(iconNode)
		end
	end
end
--交换两个点
local function exchangeGrid(grid1,grid2,callback)
    m_isTouching = false
    resetSelectGrid()
    local tag1 = m_gridLogic.revertIndexToTag(grid1.x,grid1.y)
    local tag2 = m_gridLogic.revertIndexToTag(grid2.x,grid2.y)
    local node1 = m_rootLayer:getChildByTag(m_grid_start_tag + tag1)
    local node2 = m_rootLayer:getChildByTag(m_grid_start_tag + tag2)
    --标签交换
    if node1 == nil or node2 == nil then
        return
    end
    local point1x,point1y = m_gridLogic.getGridPoint(grid1.x,grid1.y)
    local point2x,point2y = m_gridLogic.getGridPoint(grid2.x,grid2.y)
    local function moveEnd()
        node2:setTag(m_grid_start_tag + tag1)
        node1:setTag(m_grid_start_tag + tag2)
        m_gameGrid.exchangeData(grid1,grid2)
        if callback then
            callback()
        end
    end
    local sequence = cc.Sequence:create(cc.MoveTo:create(0.1,cc.p(m_gridLogic.getGridPoint(grid2.x,grid2.y))),
                                        cc.CallFunc:create(moveEnd))
    node1:runAction(sequence)    
    node2:runAction(cc.MoveTo:create(0.1, cc.p(m_gridLogic.getGridPoint(grid1.x,grid1.y))))
end
--填充ui
local fillUi = function(rootLayer)
    --创建背景
    local bgSp = cc.Sprite:create(HZ_GETRESOURCE("game_bg.png"))
	bgSp:setPosition(320, 400)
    rootLayer:addChild(bgSp)
    --初始化棋盘数据 关卡数据
    m_gameGrid.initGrid()
    --载入图片
    cc.SpriteFrameCache:getInstance():addSpriteFrames(HZ_GETRESOURCE("GameIcon.plist"))
    --生成关卡
    m_gameGrid.initGameGridData()
    --显示
    initGameGridShow()
end
--更新后检测
local gridFallAndCheck = function()
    local clearTable = {}
    for i = 1,#m_grid_down_table do
        if m_gameGrid.checkGrid(m_grid_down_table[i]) then
            clearTable[#clearTable + 1] = m_grid_down_table[i]
        end
    end
    m_grid_down_table = {}
    if #clearTable ~= 0 then
        clearGrid(clearTable)
    end
end
--更新棋盘
local refreshGrid = function()
    local clearTable,newTable,moveTable = m_gameGrid.updateGrid()
    local moveNodeTable = {}
    for i = 1, HZBoardSizeX do
        if clearTable[i] ~= nil then
            local aimpos = {x = clearTable[i].x,y = clearTable[i].y}
            --原有的向下移动
            for j = 1, #(moveTable[i]) do
                local grid = {x = moveTable[i][j].x, y = moveTable[i][j].y}
                local tag = m_gridLogic.revertIndexToTag(grid.x,grid.y)
                local node = m_rootLayer:getChildByTag(m_grid_start_tag + tag)

                local aimTag = 100 * m_gameGrid.getGridDataByIndex(grid.x,grid.y) + 10 * aimpos.x + aimpos.y
                node:setTag(m_grid_down_tag + aimTag)

                moveNodeTable[#moveNodeTable + 1] = {}
                moveNodeTable[#moveNodeTable][1] = node
                moveNodeTable[#moveNodeTable][2] = aimpos
                aimpos = {x = aimpos.x,y = aimpos.y + 1}
            end
            --新增加的
            for j = 1, #(newTable[i]) do
                local node = m_gameObj.createIconById(newTable[i][j])
                
                node:setPosition(m_gridLogic.getGridPoint(i,10))

                local desTag = 100 * newTable[i][j] + 10 * aimpos.x + aimpos.y
                node:setTag(m_grid_down_tag + desTag)
                m_rootLayer:addChild(node)

                moveNodeTable[#moveNodeTable + 1] = {}
                moveNodeTable[#moveNodeTable][1] = node
                moveNodeTable[#moveNodeTable][2] = aimpos
                aimpos = {x = aimpos.x,y = aimpos.y + 1}
            end
        end
    end
    --真正的移动
    for i = 1, #moveNodeTable do
        local node = moveNodeTable[i][1]
        local aimIndex = moveNodeTable[i][2]
        local moveEnd = function()
            local tag = node:getTag() - m_grid_down_tag
            local value = math.modf(tag / 100)
            tag = tag - value * 100
            m_gameGrid.setGridDataByIndex(math.modf(tag / 10),tag % 10,value)
            node:setTag(m_grid_start_tag + tag)
        end
        local sequence = cc.Sequence:create(cc.MoveTo:create(0.1, cc.p(m_gridLogic.getGridPoint(aimIndex.x,aimIndex.y)))
                                           ,cc.CallFunc:create(moveEnd))
        node:runAction(sequence)

        m_grid_down_table[#m_grid_down_table + 1] = aimIndex
    end
    m_rootLayer:runAction(cc.Sequence:create(cc.DelayTime:create(0.2)
                                            ,cc.CallFunc:create(gridFallAndCheck)))
end
--消除动画
local clearGridShow = function(clearTable)
    for i = 1, #clearTable do
        local tag = m_gridLogic.revertIndexToTag(clearTable[i].x,clearTable[i].y)
        local node = m_rootLayer:getChildByTag(m_grid_start_tag + tag)

        node:setTag(m_grid_romove_tag + tag)
        m_gameGrid.clearGridDataByIndex(clearTable[i].x,clearTable[i].y)
        m_gameObj.clearIcon(node)
    end
end
--消除
clearGrid = function(clearTable)
    local needClearTable = {}
    local flagTable = {}
    for i = 1, #clearTable do
        local tempTable = m_gameGrid.getClearTable(clearTable[i])
        for i = 1, #tempTable do
            local grid = tempTable[i]
            local tag = m_gridLogic.revertIndexToTag(grid.x,grid.y)
            if flagTable[tag] == nil then
                flagTable[tag] = true
                needClearTable[#needClearTable + 1] = grid
            end
        end
    end
    clearGridShow(needClearTable)

    m_rootLayer:runAction(cc.Sequence:create(cc.DelayTime:create(0.2)
                                            ,cc.CallFunc:create(refreshGrid)))
end
--检测是否消除
local checkIsClear = function()
    local clearTable = {}
    for i = 1,#m_switchPair do
        if m_gameGrid.checkGrid(m_switchPair[i]) then
            clearTable[#clearTable + 1] = m_switchPair[i]
        end
    end
    if #clearTable == 0 then
        exchangeGrid(m_switchPair[1],m_switchPair[2],nil)
        m_switchPair = {}
    else
        clearGrid(clearTable)
    end
end
--开始按下
local onTouchBegan = function(x,y)
    m_isTouching = true
    m_touchStartPoint = {x = x,y = y}
    m_touchStartIndex = m_gridLogic.getIndexByPoint(x,y)
    if m_curSelectTag ~= nil then
        local curSelectIndex = m_gridLogic.revertTagToIndex(m_curSelectTag)
        if m_gridLogic.isNearby(curSelectIndex,m_touchStartIndex) then
            m_switchPair[1] = curSelectIndex
            m_switchPair[2] = m_touchStartIndex
            exchangeGrid(curSelectIndex,m_touchStartIndex,checkIsClear)
            return true
        end
    end
    chooseGrid(m_touchStartIndex.x,m_touchStartIndex.y)
    return true
end
--移动按下
local onTouchMoved = function(x,y)
    local touchCurIndex = m_gridLogic.getIndexByPoint(x, y)
    if  m_isTouching then
        if m_gridLogic.isNearby(touchCurIndex,m_touchStartIndex) then
            m_switchPair[1] = touchCurIndex
            m_switchPair[2] = m_touchStartIndex
            exchangeGrid(touchCurIndex,m_touchStartIndex,checkIsClear)
            return true
        end
    end
end
--停止按下
local onTouchEnded = function(x,y)
    m_isTouching = false
end
--显示
show = function()
    m_rootLayer = cc.Layer:create()
    fillUi(m_rootLayer)

    local function onTouch(eventType, x, y)
        if eventType == "began" then   
            return onTouchBegan(x, y)
        elseif eventType == "moved" then
            return onTouchMoved(x, y)
        elseif eventType == "ended" then
            return onTouchEnded(x, y)
        end
    end

    m_rootLayer:registerScriptTouchHandler(onTouch)
    m_rootLayer:setTouchEnabled(true)
	return m_rootLayer
end	