CharacterTest = 
{
    x = 100, y = 100
}

function CharacterTest:OnStart()
end

function CharacterTest:OnUpdate(deltaT)
    
    if is_key_held(IONIX_LEFT_ARROW) then
        self.x = self.x - 3
    end
    if is_key_held(IONIX_RIGHT_ARROW) then
        self.x = self.x + 3
    end
    if is_key_held(IONIX_UP_ARROW) then
        self.y = self.y - 3
    end
    if is_key_held(IONIX_DOWN_ARROW) then
        self.y = self.y + 3
    end
	set_object_position(self._gameObjUID, self.x, self.y)
end

function CharacterTest:OnCollisionEnter(other)
    print("colliding with "..other)
end

function CharacterTest:OnCollisionExit(other)
    print("stopped colliding with "..other)
end
