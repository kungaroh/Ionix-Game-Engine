bullet = 
{
    x = 0,
    y = 0,
    speed = 1000,
    active = false,
    game_manager_uid = nil
}

function bullet:Activate()
    self.active = true
    play_audio("laserShoot.wav",0)
end

function bullet:OnStart()
    self.x, self.y = get_object_position( self.__uid )
    self.game_manager_uid = uid_from_name("GameManager") 
end

function bullet:OnUpdate( deltaTime )
    if (self.active) then
        self.y = self.y - deltaTime * self.speed
        set_object_position( self.__uid, self.x, self.y)
        -- destroy when off screen
        if self.y < -200.0 then
            remove_object( self.__uid)
        end
    end
end

function bullet:OnTriggerEnter( other )
    -- is the other thing an enemy?
    other_tag = get_object_tag( other )
    if ( other_tag == "enemy") then
        x, y = get_object_position(other)
        call_function("game_manager","RegisterKill",self.game_manager_uid)
        remove_object(other)
        remove_object(self.__uid)        
        play_audio("explosion.wav",0)
        expl, x, y = instantiate("ExplosionPrefab", x, y-50)
        expl_uid = uid_from_name(expl)
        call_function("explosion", "explode", expl_uid)
    end
end

function bullet:OnTriggerExit( other )
end
