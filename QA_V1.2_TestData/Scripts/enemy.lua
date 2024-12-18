enemy = {
   x = 0,
   y = 0,
   speed = 50
}

function enemy:OnStart()
    self.x, self.y = get_object_position( self.__uid )
    CreateCoroutine( enemy.Shoot, self )
end

function enemy:OnUpdate(deltaTime)
    self.y = self.y + deltaTime + self.speed * deltaTime
    set_object_position( self.__uid, self.x, self.y)
end

function enemy:Shoot()
    for i = 1, 5 do
        cwait = 3.0 + 5.5*math.random()
        YieldWaitForSeconds(cwait)
        new_bullet = instantiate("EnemyBulletPrefab", self.x, self.y)
        bullet_uid = uid_from_name(new_bullet)
        call_function("enemy_bullet", "Activate", bullet_uid)
    end
end

function enemy:OnTriggerEnter(other)
end

function enemy:OnTriggerExit(other)
end

--function for deathAnim
--on enemydeath create coroutine with that function
--coroutine will play animation, yieldforseconds, remove object