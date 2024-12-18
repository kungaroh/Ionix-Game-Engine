explosion = {
}

function explosion:OnStart()
end

function explosion:OnUpdate(deltaTime)
end

function explosion:do_explosion()
    for i = 1,49 do
        set_texture(self.__uid, "explosion/1_"..tostring(i)..".png")
        YieldNextUpdate()
    end
    remove_object(self.__uid)
end
    
function explosion:explode()
    CreateCoroutine( explosion.do_explosion, self )
end

