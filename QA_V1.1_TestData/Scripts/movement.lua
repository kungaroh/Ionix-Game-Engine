movement = {

    x = 350,
    y = 500,
    speed = 100
}

function movement:OnStart()
    -- set the position of the parent
    set_object_position( self.__uid, self.x, self.y)
end

function movement:OnUpdate( deltaTime )
    -- check inputs and update position
    moved = false
    if ( is_key_held("Ionix_A") ) then
        self.x = self.x - deltaTime * self.speed
        moved = true
    end
    if ( is_key_held("Ionix_D") ) then
        self.x = self.x + deltaTime * self.speed
        moved = true
    end
    if ( is_key_held("Ionix_W") ) then
        self.y = self.y - deltaTime * self.speed
        moved = true
    end
    if ( is_key_held("Ionix_S") ) then
        self.y = self.y + deltaTime * self.speed
        moved = true
    end
    -- set the position of the parent if changed
    if (moved) then
        set_object_position( self.__uid, self.x, self.y )
    end
end
