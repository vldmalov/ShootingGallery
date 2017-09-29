function BackgroundLayerFunc(message)
    WriteMessage("BackgroundLayerFunc has been called")
    WriteMessage(message:getPublisher().." - "..message:getData())

    local BGLayer = assert(GUI:getLayer("BackgroundLayer"))
    local BGWidget = assert(BGLayer:getWidget("BackgroundWidget"))
    BGWidget:setVisible(true)
    -- BGWidget:SetTextureName("background")
end

function MainSceneLayerFunc(message)
    WriteMessage("TestLayerFunc has been called")
	WriteMessage(message:getPublisher().." - "..message:getData())
end

function MenuLayerFunc(message)
    WriteMessage("MenuLayerFunc has been called")
    WriteMessage(message:getPublisher().." - "..message:getData())
end
