
ITEM_BASE          = 400

function CONVERT_RGBA(r, g, b, a)
	return (bit.lshift(a, 24) + bit.lshift(b, 16) + bit.lshift(g, 8) + r)
end

function GET_ITEM(x, y)
	return (x * 32) + y
end

function GET_ITEM_MODEL(x, y)
	return ((x * 32) + y) + ITEM_BASE
end


function GET_ITEM_NAME2(x,y)

	return RenderItemName((x * 32) + y)
end

function GET_ITEM_NAME(x)

	return RenderItemName(x)
end

--Fun for check windows system
--	if not CheckWindowSystem(0) then
	--GiftCode.AntilagTest = false
--	end

--WindowSystem(0, 1) Fun Open Windows System

--		CreateCustomText(PosX + 10, PosY + 50, 1, 0, 0, GET_ITEM_NAME(399), 0)
--		CreateCustomText(PosX + 10, PosY + 80, 1, 0, 0, GET_ITEM_NAME2(12,5), 0)


