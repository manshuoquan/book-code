module(..., package.seeall)

m_gameGridData = {}
--初始化棋盘
initGrid = function()
    for i = 1, HZBoardSizeX do
	    m_gameGridData[i] = {}
	    for j = 1, HZBoardSizeY do
		    m_gameGridData[i][j] = 0
	    end
    end
end
--更新棋盘
updateGrid = function()
    local clearTable = {}
    local newTable = {}
    local moveTable = {}
    for i = 1, HZBoardSizeX do
    	moveTable[i] = {}
    	for j = 1, HZBoardSizeY do
    		if m_gameGridData[i][j] == 0 then
    			if clearTable[i] == nil then
    				clearTable[i] = {x = i,y = j}
    			end
    			if newTable[i] == nil then
    				newTable[i] = {}
    			end
				newTable[i][#(newTable[i]) + 1] = math.random(1,HZ_CUBE_COUNT)
    		else
				if newTable[i] ~= nil then					
					moveTable[i][#(moveTable[i]) + 1] = {x = i, y = j}
				end
    		end
    	end
    end
    return clearTable,newTable,moveTable
end
--交换数据
exchangeData = function(index1,index2)
    local temp = getGridDataByIndex(index1.x,index1.y)
    m_gameGridData[index1.x][index1.y] = getGridDataByIndex(index2.x,index2.y)
    m_gameGridData[index2.x][index2.y] = temp
end
--清除数据
clearGridDataByIndex = function(x,y)
    if x > 0 and x <= HZBoardSizeX then
		if y > 0 and y <= HZBoardSizeY then
		    m_gameGridData[x][y] = 0
	    end
	end
end
--获得数据
setGridDataByIndex = function(x,y,value)
	if x > 0 and x <= HZBoardSizeX then
		if y > 0 and y <= HZBoardSizeY then
		    m_gameGridData[x][y] = value
	    end
	end
end
--获得数据
getGridDataByIndex = function(x,y)
	if x > 0 and x <= HZBoardSizeX then
		if y > 0 and y <= HZBoardSizeY then
		    return m_gameGridData[x][y]
	    end
	end
	return -1
end
--是否生成的数据是合适的 判断上下左右是否有相同的
local isThreeGrid = function(x,y,value)
    if x > 2 and m_gameGridData[x - 1][y] == value and m_gameGridData[x - 2][y] == value then
    	return true
    end

    if x > 1 and x < HZBoardSizeX and m_gameGridData[x - 1][y] == value and m_gameGridData[x + 1][y] == value then
    	return true
    end

    if x < HZBoardSizeX - 1 and m_gameGridData[x + 1][y] == value and m_gameGridData[x + 2][y] == value then
    	return true
    end

    if y > 2 and m_gameGridData[x][y - 1] == value and m_gameGridData[x][y - 2] == value then
    	return true
    end

    if y > 1 and y < HZBoardSizeY and m_gameGridData[x][y - 1] == value and m_gameGridData[x][y + 1] == value then
    	return true
    end

    if y < HZBoardSizeY - 1 and m_gameGridData[x][y + 1] == value and m_gameGridData[x][y + 2] == value then
    	return true
    end
    return false
end
--获得清除的数据表
getClearTable = function(grid)
    local value = getGridDataByIndex(grid.x,grid.y)
    local x = grid.x
    local y = grid.y
    local retTable = {}
    retTable[1] = grid
    if x > 2 and m_gameGridData[x - 1][y] == value and m_gameGridData[x - 2][y] == value then
    	retTable[#retTable + 1] = {x = x - 1,y = y}
    	retTable[#retTable + 1] = {x = x - 2,y = y}
    end

    if x > 1 and x < HZBoardSizeX and m_gameGridData[x - 1][y] == value and m_gameGridData[x + 1][y] == value then
    	retTable[#retTable + 1] = {x = x - 1,y = y}
    	retTable[#retTable + 1] = {x = x + 1,y = y}
    end

    if x < HZBoardSizeX - 1 and m_gameGridData[x + 1][y] == value and m_gameGridData[x + 2][y] == value then
    	retTable[#retTable + 1] = {x = x + 2,y = y}
    	retTable[#retTable + 1] = {x = x + 1,y = y}
    end

    if y > 2 and m_gameGridData[x][y - 1] == value and m_gameGridData[x][y - 2] == value then
    	retTable[#retTable + 1] = {x = x,y = y - 1}
    	retTable[#retTable + 1] = {x = x,y = y - 2}
    end

    if y > 1 and y < HZBoardSizeY and m_gameGridData[x][y - 1] == value and m_gameGridData[x][y + 1] == value then
    	retTable[#retTable + 1] = {x = x,y = y - 1}
    	retTable[#retTable + 1] = {x = x,y = y + 1}
    end

    if y < HZBoardSizeY - 1 and m_gameGridData[x][y + 1] == value and m_gameGridData[x][y + 2] == value then
    	retTable[#retTable + 1] = {x = x,y = y + 1}
    	retTable[#retTable + 1] = {x = x,y = y + 2}
    end

    return retTable
end
--检测消除
checkGrid = function(grid)
    return isThreeGrid(grid.x,grid.y,getGridDataByIndex(grid.x,grid.y))
end
--生成数据
initGameGridData = function()
	for	x = 1, HZBoardSizeX do
		for y = 1, HZBoardSizeY do
			local value 
			repeat				
				value = math.random(1,HZ_CUBE_COUNT)
			until isThreeGrid(x,y,value) == false--判断没有可以消除的
			m_gameGridData[x][y] = value
		end
	end
end

--[[--´¥Ãþµã×ª»¯ÎªÆåÅÌ¸ñ×Óµã
function touchPointToCell(x, y)
	local cellX = math.modf((x - GLeftBottomOffsetX) / GCellWidth)
	local cellY = math.modf((y - GLeftBottomOffsetY) / GCellWidth)
	local cell = {}
	cell.x = cellX + 1
	cell.y = cellY + 1

	if cell.x > GBoardSizeX or x < GLeftBottomOffsetX or cell.y > GBoardSizeY or y < GLeftBottomOffsetY then
		cell.x = 0
		cell.y = 0
	end

	return cell
end

--¼ì²éÁ½¸ö¸ñ×ÓÊÇ·ñÏàÁÚ
function isTwoCellNearby(cellA, cellB)
	local ret = false
	if (math.abs(cellA.x - cellB.x) == 1 and cellA.y == cellB.y) or
	   (math.abs(cellA.y - cellB.y) == 1 and cellA.x == cellB.x) then
		ret = true
	end	
	return ret
end


--»ñµÃÓëÄ³¸ö¸ñ×ÓÍ¬É«ÏàÁ¬µÄ¸ñ×Ó¼¯ºÏ
function getNearbyCellSet(cell)
	local x = cell.x
	local y = cell.y
	local index = GameBoard[x][y]

	local cellSet = {}
	cellSet[#cellSet + 1] = {x = x, y = y}

	local assArray = {}
	local function addCellToSet(cell)
		if assArray[10 * cell.x + cell.y] == nil then
			cellSet[#cellSet + 1] = cell
			assArray[10 * cell.x + cell.y] = true
		end
	end

	local cond = {}
	cond[1] = x > 1 and GameBoard[x-1][y] == index
	cond[2] = x > 2 and GameBoard[x-2][y] == index
	cond[3] = x < GBoardSizeX and GameBoard[x+1][y] == index
	cond[4] = x < GBoardSizeX-1 and GameBoard[x+2][y] == index
	cond[5] = y > 1 and GameBoard[x][y-1] == index
	cond[6] = y > 2 and GameBoard[x][y-2] == index
	cond[7] = y < GBoardSizeY and GameBoard[x][y+1] == index
	cond[8] = y < GBoardSizeY-1 and GameBoard[x][y+2] == index

	if cond[1] and cond[2] then
		addCellToSet({x = x-1, y = y})
		addCellToSet({x = x-2, y = y})
	end

	if cond[1] and cond[3] then
		addCellToSet({x = x-1, y = y})
		addCellToSet({x = x+1, y = y})
	end

	if cond[3] and cond[4] then
		addCellToSet({x = x+1, y = y})
		addCellToSet({x = x+2, y = y})
	end

	if cond[5] and cond[6] then
		addCellToSet({x = x, y = y-1})
		addCellToSet({x = x, y = y-2})
	end

	if cond[5] and cond[7] then
		addCellToSet({x = x, y = y-1})
		addCellToSet({x = x, y = y+1})
	end

	if cond[7] and cond[8] then
		addCellToSet({x = x, y = y+1})
		addCellToSet({x = x, y = y+2})
	end
		
	return cellSet
end

function getRefreshBoardData()
	local firstEmptyCell = {}
	local addCellList = {}
	local moveCellList = {}

	for i = 1, GBoardSizeX do
		for j = 1, GBoardSizeY do
			if GameBoard[i][j] == 0 then
				if firstEmptyCell[i] == nil then
					firstEmptyCell[i] = {x = i, y = j}
				end

				--Ëæ»úÉú³Éindex²¢¼ÓÈë¶ÔÓ¦ÁÐµÄaddList
				math.randomseed(math.random(os.time()))
				local addIconIndex = math.random(GGameIconCount)

				if addCellList[i] == nil then
					addCellList[i] = {}
				end
				addCellList[i][#(addCellList[i]) + 1] = addIconIndex
			else
				if moveCellList[i] == nil then
					moveCellList[i] = {}
				end
				--ÅÐ¶ÏÊÇ·ñÒÑ¾­¼ìË÷µ½¿Õ½Úµã
				if firstEmptyCell[i] ~= nil then					
					moveCellList[i][#(moveCellList[i]) + 1] = {x = i, y = j}
				end
			end
		end
	end

	return firstEmptyCell, addCellList, moveCellList
end

--¼ì²âÆåÅÌÓÐÎÞ¿ÉÒÆ¶¯Ïû³ýÆå×Ó
function checkBoardMovable()
	local ret = false
	
	--¼ì²â½»»»Á½¸ö½ÚµãÊý¾Ýºó£¬ÆåÅÌÊÇ·ñ¿ÉÏû³ý
	local function checkTwinCell(cellA, cellB)
		local ret = false

		GameBoard[cellA.x][cellA.y], GameBoard[cellB.x][cellB.y] = GameBoard[cellB.x][cellB.y], GameBoard[cellA.x][cellA.y]
		ret = checkCell(cellA) or checkCell(cellB)
		GameBoard[cellA.x][cellA.y], GameBoard[cellB.x][cellB.y] = GameBoard[cellB.x][cellB.y], GameBoard[cellA.x][cellA.y]

		return ret
	end

	local succList = {}
	
	--ÉÏÏÂ¼ì²â
	for i = 1, GBoardSizeX do
		for j = 1, GBoardSizeY - 1 do
			local cellA = {x = i, y = j}
			local cellB = {x = i, y = j + 1}
			if checkTwinCell(cellA, cellB) then
				succList[#succList + 1] = cellA
			end
		end
	end

	--×óÓÒ¼ì²â
	for i = 1, GBoardSizeX - 1 do
		for j = 1, GBoardSizeY do
			local cellA = {x = i, y = j}
			local cellB = {x = i + 1, y = j}
			if checkTwinCell(cellA, cellB) then
				succList[#succList + 1] = cellA
			end
		end
	end

	if #succList > 0 then
		cclog("check success!!!")
		ret = true
	end

	return ret, succList
end]]--