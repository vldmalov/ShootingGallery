function BackgroundLayerFunc(message)
    WriteMessage("BackgroundLayerFunc has been called")
    WriteMessage(message:getPublisher().." - "..message:getData())

    local BGLayer = assert(GUI:getLayer("BackgroundLayer"))
    -- local BGWidget = assert(BGLayer:getWidget("BackgroundWidget"))
end

function MainSceneLayerFunc(message)
    WriteMessage("TestLayerFunc has been called")
	WriteMessage(message:getPublisher().." - "..message:getData())
end
