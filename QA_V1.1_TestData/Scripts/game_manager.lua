game_manager = {
    counter = 0
}

function game_manager:ObjectSpawner()
    while true do    
        YieldWaitForSeconds(2)
        instantiate("block", 400, 50)         
    end
end
function game_manager:OnStart()
    CreateCoroutine(game_manager.ObjectSpawner, self)
end

function game_manager:OnUpdate( deltaTime )

end

function game_manager:IncrementCounter()
    self.counter = self.counter + 1
    log("counter is now "..tostring(self.counter))
end

