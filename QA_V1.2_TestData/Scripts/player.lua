player = 
{
    x = 0,
    y = 0,
    speed = 500
}

function player:OnStart()
    self.x, self.y = get_object_position( self.__uid )
end

function player:Shoot()
    new_bullet = instantiate("BulletPrefab", self.x, self.y)
    bullet_uid = uid_from_name(new_bullet)
    call_function("bullet", "Activate", bullet_uid)
end

function player:OnUpdate( deltaTime )
    -- check inputs and update position
    moved = false
    if ( is_key_held("Ionix_Left") ) then
        self.x = self.x - deltaTime * self.speed
        moved = true
    end
    if ( is_key_held("Ionix_Right") ) then
        self.x = self.x + deltaTime * self.speed
        moved = true
    end
    if (moved) then
        set_object_position( self.__uid, self.x, self.y)
    end

    if ( is_key_down("Ionix_Space")) then
        self:Shoot()
    end
end

function player:OnTriggerEnter(other)
end

function player:OnTriggerExit(other)
end

