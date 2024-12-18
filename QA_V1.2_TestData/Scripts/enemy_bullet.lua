enemy_bullet = 
{
    x = 0,
    y = 0,
    speed = 1000,
    active = false,
    game_manager_uid = nil
}

function enemy_bullet:Activate()
    self.active = true
    play_audio("laserShoot2.wav",0)
end

function enemy_bullet:OnStart()
    self.x, self.y = get_object_position( self.__uid )
    self.game_manager_uid = uid_from_name("GameManager")
end

function enemy_bullet:OnUpdate( deltaTime )
    if (self.active) then
        self.y = self.y + deltaTime * self.speed
        set_object_position( self.__uid, self.x, self.y)
        -- destroy when off screen
        if self.y > 850.0 then
            remove_object( self.__uid)
        end
    end
end

function enemy_bullet:OnTriggerEnter( other )
    -- is the other thing the player?
    other_tag = get_object_tag( other )
    if ( other_tag == "player") then
        remove_object(self.__uid) -- destroy self
        play_audio("explosion2.wav",0) 
        call_function("game_manager", "RegisterHit", self.game_manager_uid)
    end
end

function enemy_bullet:OnTriggerExit( other )
end
