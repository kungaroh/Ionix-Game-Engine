hero = 
{
    x = 0,
    y = 0,
    speed = 100,
    direction = 0 -- 0, 1, 2, 3 -> left, right, up, down
}





function hero:OnStart()
    self.x, self.y = get_object_position( self.__uid )
  
end

function hero:OnUpdate( deltaTime )
    -- check inputs and update position
    moved = false
    self.x, self.y = get_object_position( self.__uid ) -- get position from physics

    oldx = self.x
    oldy = self.y
    if ( is_key_held("Ionix_Left") or is_key_held("Ionix_A") ) then
        self.x = self.x - deltaTime * self.speed
        self.direction = 0
        moved = true
    end
    if ( is_key_held("Ionix_Right") or is_key_held("Ionix_D") ) then
        self.x = self.x + deltaTime * self.speed
        moved = true
        self.direction = 1

    end
    if ( is_key_held("Ionix_Up") or is_key_held("Ionix_W") ) then
        self.y = self.y - deltaTime * self.speed * 10
        moved = true
        self.direction = 2
    end
    if ( is_key_held("Ionix_Down") or is_key_held("Ionix_S") ) then
        self.y = self.y + deltaTime * self.speed
        moved = true
        self.direction = 3
    end



    set_velocity(self.__uid, (self.x - oldx)/deltaTime, (self.y - oldy)/deltaTime )

end

