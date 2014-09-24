module(..., package.seeall)
LangDic = {}

LangDic["pressScreen"] = "点击屏幕开始"
LangDic["title"] = "天天消豆豆"

function stringFormDic(key)
	if LangDic[key] == nil then
		return "";
	else
		return LangDic[key];
	end
end