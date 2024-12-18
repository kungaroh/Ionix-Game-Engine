raycastTest = 
{
    x = 0,
    y = 0,
    speed = 100,
    direction = 0 -- 0, 1, 2, 3 -> left, right, up, down
}





function raycastTest:OnStart()
  
end

function raycastTest:OnUpdate( deltaTime )
    raycast(self.__uid, self.x, self.y, 0. -1, 50)
    if raycast_hit(self.__uid, self.x, self.y, 0. -1, 50) then
        log("hit")
    end
end

