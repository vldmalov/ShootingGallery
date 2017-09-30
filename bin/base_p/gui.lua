function BackgroundLayerFunc(message)
    WriteMessage("BackgroundLayerFunc has been called")
    WriteMessage(message:getPublisher().." - "..message:getData())
end

function MainSceneLayerFunc(message)
    WriteMessage("TestLayerFunc has been called")
    WriteMessage(message:getPublisher().." - "..message:getData())
end