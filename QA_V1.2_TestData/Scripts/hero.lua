hero = 
{
    x = 0,
    y = 0,
    speed = 100,
    direction = 0 -- 0, 1, 2, 3 -> left, right, up, down
}


function hero:UpdateAnimation( moving )
    if moving then
        num_frames = 4
    else
        num_frames = 1
    end
    -- switch to a new animation based on direction
    if self.direction == 0 then
        set_animation_params(self.__uid, 4, num_frames, 0, 10)
    elseif self.direction == 1 then
        set_animation_params(self.__uid, 4, num_frames, 3, 10)
    elseif self.direction == 2 then
        set_animation_params(self.__uid, 4, num_frames, 1, 10)
    else
        set_animation_params(self.__uid, 4, num_frames, 2, 10)
    end
end


function hero:OnStart()
    self.x, self.y = get_object_position( self.__uid )
    self:UpdateAnimation()
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
        self.y = self.y - deltaTime * self.speed
        moved = true
        self.direction = 2
    end
    if ( is_key_held("Ionix_Down") or is_key_held("Ionix_S") ) then
        self.y = self.y + deltaTime * self.speed
        moved = true
        self.direction = 3
    end

    self:UpdateAnimation( moved )

    set_velocity(self.__uid, (self.x - oldx)/deltaTime, (self.y - oldy)/deltaTime )

    -- update the camera
    w, h = get_window_dimensions()
    screen_x = math.floor( self.x / w )
    screen_y = math.floor( self.y / h )
    set_camera_pos( screen_x*w, screen_y*h )
end

