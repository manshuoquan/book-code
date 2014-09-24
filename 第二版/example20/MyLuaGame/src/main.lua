--错误捕捉函数
function __G__TRACKBACK__(msg)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(msg) .. "\n")
    print(debug.traceback())
    print("----------------------------------------")
end
--入口函数
local function main()
    --内存回收
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)
    require("src/const/const.lua")
    --随机数种子
    math.randomseed(math.random(os.time()))
    --文字
    HZ_LANG = require("src/const/lang.lua")
    --显示层和场景
    HZ_GAME_LAYER = cc.Layer:create()
    local scene = cc.Scene:create()
    HZ_SHOW_UI_LAYER(HZ_START)
    scene:addChild(HZ_GAME_LAYER)
    cc.Director:getInstance():runWithScene(scene)
end

HZ_START = "startLayer"
HZ_GAME = "gameLayer"
local uiTable = {}
uiTable["startLayer"] = require("src/game/startLayer.lua")
uiTable["gameLayer"] = require("src/game/gameLayer.lua")
--清空当前界面
function HZ_CLEAN_LAYER()
    HZ_GAME_LAYER:removeAllChildren(true)
end
--显示当前层
function HZ_SHOW_UI_LAYER(name)
    HZ_CLEAN_LAYER()
    HZ_GAME_LAYER:addChild(uiTable[name].show())
end
--获得图片完整路径
function HZ_GETRESOURCE(name)
    return "res/imgs/"..name
end

xpcall(main, __G__TRACKBACK__)
