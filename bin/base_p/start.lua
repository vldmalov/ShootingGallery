--
-- Так загружаются описания ресурсов: какие текстуры, анимации и т.п.
-- будут видны в медеджере ресурсов по имени.
--
-- Фактическая загрузка ресурсов с диска в память выполняется
-- функцией UploadResourceGroup, которая вызывается ниже.
--
print("Load Resources")
LoadResource("Resources.xml")

--
-- Загрузка эффектов, созданных в редакторе частиц.
--
LoadEffects("Example2_Flames.xml")
LoadEffects("Example3_FindObject.xml")

--
-- Загрузка слоёв.
--
-- Слои создаются все сразу (вызываются конструкторы всех виджетов и т.п.),
-- но методы Draw() и Update() начинают вызываться только тогда, когда слой
-- добавлен на экран. В момент добавления на экран у виджетов слоя вызывается метод
-- AcceptMessage с параметром "Init".
--
print("Load Layers")
GUI:LoadLayers("Layers.xml")

--
-- Фактическая загрузка группы ресурсов: создаются объекты текстур, загружаются
-- изображения с диска и т.п. Это длительная операция.
--
UploadResourceGroup("Common")
UploadResourceGroup("TestGroup")
UploadResourceGroup("GameScene")

--
-- Слой кладётся на экран.
--
-- В этот момент у виджетов слоя один раз вызывается метод AcceptMessage("Init")
-- и начинают вызываться методы Draw() и Update() в каждом кадре.
--
Screen:pushLayer("BackgroundLayer")
Screen:pushLayer("MainSceneLayer")