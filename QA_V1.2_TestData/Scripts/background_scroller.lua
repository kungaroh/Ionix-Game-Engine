background_scroller = {
    x = 0,
    y = 0,
    speed = 100
}

function background_scroller:OnUpdate(deltaTime)
    self.y = self.y + self.speed *deltaTime
    if self.y > 1080 then
        self.y = -360
    end
    set_object_position(self.__uid,self.x,self.y)
end

function background_scroller:OnStart()
    self.x, self.y = get_object_position(self.__uid)
end

