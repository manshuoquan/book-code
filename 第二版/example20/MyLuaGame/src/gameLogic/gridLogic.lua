module(..., package.seeall)
--索引转换为标签
function revertIndexToTag(x,y)
    return 10 * x + y
end
--标签转换为索引
function revertTagToIndex(tag)
    return {x = math.modf(tag / 10), y = tag % 10}
end
--根据坐标获得格子索引
function getIndexByPoint(x,y)
    local indexX = math.modf((x - HZ_GRID_OFFSET_X) / HZ_GRID_WIDTH) + 1
    local indexY = math.modf((y - HZ_GRID_OFFSET_Y) / HZ_GRID_WIDTH) + 1
    if indexX > HZBoardSizeX or x < HZ_GRID_OFFSET_X or indexY > HZBoardSizeY or y < HZ_GRID_OFFSET_Y then
        indexX = 0
        indexY = 0
    end
    return {x = indexX,y = indexY}
end
--获得坐标
function getGridPoint(x,y)
	local pointx = (x - 1) * HZ_GRID_WIDTH + HZ_GRID_OFFSET_X + HZ_GRID_WIDTH / 2
	local pointy = (y - 1) * HZ_GRID_WIDTH + HZ_GRID_OFFSET_Y + HZ_GRID_WIDTH / 2
	return pointx,pointy
end
--是否挨着
function isNearby(grid1,grid2)
	if (math.abs(grid1.x - grid2.x) == 1 and grid1.y == grid2.y) or
	   (math.abs(grid1.y - grid2.y) == 1 and grid1.x == grid2.x) then
		return true
	end	
	return false
end